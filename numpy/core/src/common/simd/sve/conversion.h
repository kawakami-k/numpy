#ifndef NPY_SIMD
#error "Not a standalone header"
#endif

#ifndef _NPY_SIMD_SVE_CVT_H
#define _NPY_SIMD_SVE_CVT_H

// convert mask to integer vectors
#define SVE_CVT_MASK(a, b)                                 \
    NPY_FINLINE npyv_##a npyv_cvt_##a##_##b(npyv_##b mask) \
    {                                                      \
        return svdup_##a##_z(mask, -1);                    \
    }
SVE_CVT_MASK(u8, b8)
SVE_CVT_MASK(u16, b16)
SVE_CVT_MASK(u32, b32)
SVE_CVT_MASK(u64, b64)
SVE_CVT_MASK(s8, b8)
SVE_CVT_MASK(s16, b16)
SVE_CVT_MASK(s32, b32)
SVE_CVT_MASK(s64, b64)
#undef SVE_CVT_MASK

#if 0
#define npyv_cvt_f32_b32(BL) _mm512_castsi512_ps(npyv_cvt_u32_b32(BL))
#define npyv_cvt_f64_b64(BL) _mm512_castsi512_pd(npyv_cvt_u64_b64(BL))
#endif  // #if 0

// convert integer vectors to mask
//#define npyv_cvt_b8_u8 _mm512_movepi8_mask
NPY_FINLINE npyv_b8
npyv_cvt_b8_s8(npyv_s8 a)
{
    return svcmplt_n_s8(svptrue_b8(), a, 0);
}
NPY_FINLINE npyv_b16
npyv_cvt_b16_s16(npyv_s16 a)
{
    return svcmplt_n_s16(svptrue_b16(), a, 0);
}
NPY_FINLINE npyv_b32
npyv_cvt_b32_s32(npyv_s32 a)
{
    return svcmplt_n_s32(svptrue_b32(), a, 0);
}
NPY_FINLINE npyv_b64
npyv_cvt_b64_s64(npyv_s64 a)
{
    return svcmplt_n_s64(svptrue_b64(), a, 0);
}
NPY_FINLINE npyv_b8
npyv_cvt_b8_u8(npyv_u8 a)
{
    return npyv_cvt_b8_s8(svreinterpret_s8_u8(a));
}
NPY_FINLINE npyv_b16
npyv_cvt_b16_u16(npyv_u16 a)
{
    return npyv_cvt_b16_s16(svreinterpret_s16_u16(a));
}
NPY_FINLINE npyv_b32
npyv_cvt_b32_u32(npyv_u32 a)
{
    return npyv_cvt_b32_s32(svreinterpret_s32_u32(a));
}
NPY_FINLINE npyv_b64
npyv_cvt_b64_u64(npyv_u64 a)
{
    return npyv_cvt_b64_s64(svreinterpret_s64_u64(a));
}
NPY_FINLINE npyv_b64
npyv_cvt_b32_f32(npyv_f32 a)
{
    return npyv_cvt_b32_s32(svreinterpret_s32_f32(a));
}
NPY_FINLINE npyv_b64
npyv_cvt_b64_f64(npyv_f64 a)
{
    return npyv_cvt_b64_s64(svreinterpret_s64_f64(a));
}

#if 0
// expand
NPY_FINLINE npyv_u16x2 npyv_expand_u16_u8(npyv_u8 data)
{
    npyv_u16x2 r;
    __m256i lo = npyv512_lower_si256(data);
    __m256i hi = npyv512_higher_si256(data);
#ifdef NPY_HAVE_AVX512BW
    r.val[0] = _mm512_cvtepu8_epi16(lo);
    r.val[1] = _mm512_cvtepu8_epi16(hi);
#else
    __m256i loelo = _mm256_cvtepu8_epi16(_mm256_castsi256_si128(lo));
    __m256i loehi = _mm256_cvtepu8_epi16(_mm256_extracti128_si256(lo, 1));
    __m256i hielo = _mm256_cvtepu8_epi16(_mm256_castsi256_si128(hi));
    __m256i hiehi = _mm256_cvtepu8_epi16(_mm256_extracti128_si256(hi, 1));
    r.val[0] = npyv512_combine_si256(loelo, loehi);
    r.val[1] = npyv512_combine_si256(hielo, hiehi);
#endif
    return r;
}

NPY_FINLINE npyv_u32x2 npyv_expand_u32_u16(npyv_u16 data)
{
    npyv_u32x2 r;
    __m256i lo = npyv512_lower_si256(data);
    __m256i hi = npyv512_higher_si256(data);
#ifdef NPY_HAVE_AVX512BW
    r.val[0] = _mm512_cvtepu16_epi32(lo);
    r.val[1] = _mm512_cvtepu16_epi32(hi);
#else
    __m256i loelo = _mm256_cvtepu16_epi32(_mm256_castsi256_si128(lo));
    __m256i loehi = _mm256_cvtepu16_epi32(_mm256_extracti128_si256(lo, 1));
    __m256i hielo = _mm256_cvtepu16_epi32(_mm256_castsi256_si128(hi));
    __m256i hiehi = _mm256_cvtepu16_epi32(_mm256_extracti128_si256(hi, 1));
    r.val[0] = npyv512_combine_si256(loelo, loehi);
    r.val[1] = npyv512_combine_si256(hielo, hiehi);
#endif
    return r;
}
#endif  // #if 0

#define NPYV_IMPL_SVE_TOBIT(BITS) \
  NPY_FINLINE npy_uint64 npyv_tobits_b ## BITS (npyv_b ## BITS a) {	\
  const svbool_t mask_all = svptrue_b ## BITS (); \
  npy_uint64 retVal = 0; \
  uint ## BITS ## _t buf[NPY_SIMD_WIDTH/sizeof(uint ## BITS ## _t)]; \
  svuint ## BITS ## _t mask_vec = svdup_n_u ## BITS ## _z(a, 0x1); \
  svst1_u ## BITS (mask_all, buf, mask_vec); \
\
  assert(sizeof(npy_uint64) * 8 >= NPY_SIMD_WIDTH/sizeof(uint ## BITS ## _t)); \
  for(int i=0; i<npyv_nlanes_u ## BITS ; i++) { \
    retVal |= buf[i] != 0 ? (1<<i) : 0; \
  } \
  return retVal;\
}

NPYV_IMPL_SVE_TOBIT(8)
NPYV_IMPL_SVE_TOBIT(16)
NPYV_IMPL_SVE_TOBIT(32)
NPYV_IMPL_SVE_TOBIT(64)

// round to nearest integer (assuming even)
NPY_FINLINE npyv_s32
npyv_round_s32_f32(npyv_f32 a)
{
    return svcvt_s32_f32_x(svptrue_b32(), svrinti_f32_x(svptrue_b32(), a));
}
NPY_FINLINE npyv_s32
npyv_round_s32_f64(npyv_f64 a, npyv_f64 b)
{
    svfloat64_t a_rinti = svrinti_f64_x(svptrue_b64(), a);
    svfloat64_t b_rinti = svrinti_f64_x(svptrue_b64(), b);
    svint32_t a_cvt = svcvt_s32_f64_x(svptrue_b64(), a_rinti);
    svint32_t b_cvt = svcvt_s32_f64_x(svptrue_b64(), b_rinti);
    return svzip1_s32(a_cvt, b_cvt);
}

#endif  // _NPY_SIMD_SVE_CVT_H
