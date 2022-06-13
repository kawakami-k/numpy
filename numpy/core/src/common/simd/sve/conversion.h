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

// expand
NPY_FINLINE npyv_u16x2 npyv_expand_u16_u8(npyv_u8 data)
{
    npyv_u16x2 r = svundef2_u16();
    svuint8_t lo = svzip1_u8(data, data);
    svuint8_t hi = svzip2_u8(data, data);
    r = svset2_u16(r, 0, svextb_u16_x(svptrue_b16(), svreinterpret_u16_u8(lo)));
    r = svset2_u16(r, 1, svextb_u16_x(svptrue_b16(), svreinterpret_u16_u8(hi)));
    return r;
}

NPY_FINLINE npyv_u32x2 npyv_expand_u32_u16(npyv_u16 data)
{
    npyv_u32x2 r = svundef2_u32();
    svuint16_t lo = svzip1_u16(data, data);
    svuint16_t hi = svzip2_u16(data, data);
    r = svset2_u32(r, 0, svexth_u32_x(svptrue_b32(), svreinterpret_u32_u16(lo)));
    r = svset2_u32(r, 1, svexth_u32_x(svptrue_b32(), svreinterpret_u32_u16(hi)));
    return r;
}

#define NPYV_IMPL_SVE_TOBIT(BITS) \
  NPY_FINLINE npy_uint64 npyv_tobits_b ## BITS (npyv_b ## BITS a) {	\
  const svbool_t mask_all = svptrue_b ## BITS (); \
  /*uint ## BITS ## _t buf[NPY_SIMD_WIDTH/sizeof(uint ## BITS ## _t)];*/ \
  /*  svuint ## BITS ## _t sh = svindex_u ## BITS (0, 1);	*/   \
  svuint ## BITS ## _t mask = svdup_n_u ## BITS ## _z(a, 0x1); \
  return svorv_u ## BITS (mask_all, mask);	       \
}

NPY_FINLINE npy_uint64 npyv_tobits_b8(npyv_b8 A)
{
  const svbool_t mask_zero = svpfalse();

  svbool_t l, h, l_l, l_h, h_l, h_h;
  svbool_t l_l_l, l_l_h, l_h_l, l_h_h;
  svbool_t h_l_l, h_l_h, h_h_l, h_h_h;
  svuint64_t idx0, idx1, idx2, idx3, idx4, idx5, idx6, idx7;
  const uint64_t len = svcntb();
  uint64_t retVal = 0;

  l = svzip1_b64(A, mask_zero);
  h = svzip2_b64(A, mask_zero);
  idx0 = svindex_u64(0, 1);
  idx1 = svindex_u64(8, 1);

  if(len >= 32) {
    l_l = svzip1_b64(l, mask_zero);
    l_h = svzip2_b64(l, mask_zero);
    h_l = svzip1_b64(h, mask_zero);
    h_h = svzip2_b64(h, mask_zero);
    idx2 = svindex_u64(16, 1);
    idx3 = svindex_u64(24, 1);
  }
  if(len >= 64) {
    l_l_l = svzip1_b64(l_l, mask_zero);
    l_l_h = svzip2_b64(l_l, mask_zero);
    l_h_l = svzip1_b64(l_h, mask_zero);
    l_h_h = svzip2_b64(l_h, mask_zero);
    h_l_l = svzip1_b64(h_l, mask_zero);
    h_l_h = svzip2_b64(h_l, mask_zero);
    h_h_l = svzip1_b64(h_h, mask_zero);
    h_h_h = svzip2_b64(h_h, mask_zero);
    idx4 = svindex_u64(32, 1);
    idx5 = svindex_u64(40, 1);
    idx6 = svindex_u64(48, 1);
    idx7 = svindex_u64(56, 1);
  }

  switch(len) {
  case 16:
    retVal = svorv_u64(l, idx0);
    retVal |= svorv_u64(h, idx1);
    break;
  case 32:
    retVal = svorv_u64(l_l, idx0);
    retVal = svorv_u64(l_h, idx1);
    retVal = svorv_u64(h_l, idx2);
    retVal = svorv_u64(h_h, idx3);
    break;
  case 64:
    retVal |= svorv_u64(l_l_h, idx1);
    retVal |= svorv_u64(l_h_l, idx2);
    retVal |= svorv_u64(l_h_h, idx3);
    retVal |= svorv_u64(h_l_l, idx4);
    retVal |= svorv_u64(h_l_h, idx5);
    retVal |= svorv_u64(h_h_l, idx6);
    retVal |= svorv_u64(h_h_h, idx7);
    break;
  default:
    assert(!"unsupported SVE size!");
  }

  return retVal;
}

NPY_FINLINE npy_uint64 npyv_tobits_b16(npyv_b16 A)
{
  const svbool_t mask_all = svptrue_b32();
  svuint16_t a = svdup_n_u16_z(A, 1);
  const svuint16_t zero = svdup_n_u16(0);
  svuint32_t l = svreinterpret_u32_u16(svzip1_u16(a, zero));
  svuint32_t h = svreinterpret_u32_u16(svzip2_u16(a, zero));

  svuint32_t idx0 = svindex_u32(0, 1);
  svuint32_t idx1 = svindex_u32(16, 1);

  idx0 = svlsl_u32_x(mask_all, l, idx0);
  idx1 = svlsl_u32_x(mask_all, h, idx1);

  return (npy_uint32) (svorv_u32(mask_all, idx0) + (svorv_u32(mask_all, idx1) << 16));
}

NPY_FINLINE npy_uint64 npyv_tobits_b32(npyv_b32 A)
{
  const svbool_t mask_all = svptrue_b32();
  svuint32_t a = svdup_n_u32_z(A, 1);
  svuint32_t idx0 = svindex_u32(0, 1);

  idx0 = svlsl_u32_x(mask_all, a, idx0);
  return (npy_uint64) svorv_u32(mask_all, idx0);
}

NPY_FINLINE npy_uint64 npyv_tobits_b64(npyv_b64 A)
{
  const svbool_t mask_all = svptrue_b64();
  svuint64_t a = svdup_n_u64_z(A, 1);
  svuint64_t idx0 = svindex_u64(0, 1);

  idx0 = svlsl_u64_x(mask_all, a, idx0);
  return svorv_u64(mask_all, idx0);
}

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
