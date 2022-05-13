#ifndef NPY_SIMD
#error "Not a standalone header"
#endif

#ifndef _NPY_SIMD_SVE_MATH_H
#define _NPY_SIMD_SVE_MATH_H

/***************************
 * Elementary
 ***************************/
// Square root
NPY_FINLINE npyv_f32
npyv_sqrt_f32(npyv_f32 a)
{
    return svsqrt_f32_x(svptrue_b32(), a);
}
NPY_FINLINE npyv_f64
npyv_sqrt_f64(npyv_f64 a)
{
    return svsqrt_f64_x(svptrue_b64(), a);
}

// Reciprocal
NPY_FINLINE npyv_f32
npyv_recip_f32(npyv_f32 a)
{
    return svdiv_f32_x(svptrue_b32(), svdup_f32(1.0f), a);
}
NPY_FINLINE npyv_f64
npyv_recip_f64(npyv_f64 a)
{
    return svdiv_f64_x(svptrue_b64(), svdup_f64(1.0f), a);
}

// Absolute
NPY_FINLINE npyv_f32
npyv_abs_f32(npyv_f32 a)
{
    return svabs_f32_x(svptrue_b32(), a);
}
NPY_FINLINE npyv_f64
npyv_abs_f64(npyv_f64 a)
{
    return svabs_f64_x(svptrue_b64(), a);
}

// Square
NPY_FINLINE npyv_f32
npyv_square_f32(npyv_f32 a)
{
    return svmul_f32_x(svptrue_b32(), a, a);
}
NPY_FINLINE npyv_f64
npyv_square_f64(npyv_f64 a)
{
    return svmul_f64_x(svptrue_b64(), a, a);
}

#if 0
// Maximum, natively mapping with no guarantees to handle NaN.
#define npyv_max_f32 _mm512_max_ps
#define npyv_max_f64 _mm512_max_pd
// Maximum, supports IEEE floating-point arithmetic (IEC 60559),
// - If one of the two vectors contains NaN, the equivalent element of the other vector is set
// - Only if both corresponded elements are NaN, NaN is set. 
NPY_FINLINE npyv_f32 npyv_maxp_f32(npyv_f32 a, npyv_f32 b)
{
    __mmask16 nn = _mm512_cmp_ps_mask(b, b, _CMP_ORD_Q);
    return _mm512_mask_max_ps(a, nn, a, b);
}
NPY_FINLINE npyv_f64 npyv_maxp_f64(npyv_f64 a, npyv_f64 b)
{
    __mmask8 nn = _mm512_cmp_pd_mask(b, b, _CMP_ORD_Q);
    return _mm512_mask_max_pd(a, nn, a, b);
}
// Maximum, integer operations
#ifdef NPY_HAVE_AVX512BW
#define npyv_max_u8 _mm512_max_epu8
#define npyv_max_s8 _mm512_max_epi8
#define npyv_max_u16 _mm512_max_epu16
#define npyv_max_s16 _mm512_max_epi16
#else
    NPYV_IMPL_AVX512_FROM_AVX2_2ARG(npyv_max_u8, _mm256_max_epu8)
    NPYV_IMPL_AVX512_FROM_AVX2_2ARG(npyv_max_s8, _mm256_max_epi8)
    NPYV_IMPL_AVX512_FROM_AVX2_2ARG(npyv_max_u16, _mm256_max_epu16)
    NPYV_IMPL_AVX512_FROM_AVX2_2ARG(npyv_max_s16, _mm256_max_epi16)
#endif
#define npyv_max_u32 _mm512_max_epu32
#define npyv_max_s32 _mm512_max_epi32
#define npyv_max_u64 _mm512_max_epu64
#define npyv_max_s64 _mm512_max_epi64

// Minimum, natively mapping with no guarantees to handle NaN.
#define npyv_min_f32 _mm512_min_ps
#define npyv_min_f64 _mm512_min_pd
// Minimum, supports IEEE floating-point arithmetic (IEC 60559),
// - If one of the two vectors contains NaN, the equivalent element of the other vector is set
// - Only if both corresponded elements are NaN, NaN is set. 
NPY_FINLINE npyv_f32 npyv_minp_f32(npyv_f32 a, npyv_f32 b)
{
    __mmask16 nn = _mm512_cmp_ps_mask(b, b, _CMP_ORD_Q);
    return _mm512_mask_min_ps(a, nn, a, b);
}
NPY_FINLINE npyv_f64 npyv_minp_f64(npyv_f64 a, npyv_f64 b)
{
    __mmask8 nn = _mm512_cmp_pd_mask(b, b, _CMP_ORD_Q);
    return _mm512_mask_min_pd(a, nn, a, b);
}
// Minimum, integer operations
#define npyv_min_u8(A, B) svmin_u8_x(svptrue_b8(), A, B)
#define npyv_min_u16(A, B) svmin_u16_x(svptrue_b16(), A, B)
#define npyv_min_u32(A, B) svmin_u32_x(svptrue_b32(), A, B)
#define npyv_min_u64(A, B) svmin_u64_x(svptrue_b64(), A, B)
#define npyv_min_s8(A, B) svmin_s8_x(svptrue_b8(), A, B)
#define npyv_min_s16(A, B) svmin_s16_x(svptrue_b16(), A, B)
#define npyv_min_s32(A, B) svmin_s32_x(svptrue_b32(), A, B)
#define npyv_min_s64(A, B) svmin_s64_x(svptrue_b64(), A, B)

// round to nearest integer even
#define npyv_rint_f32(A) svrintn_f32_x(svptrue_b32(), A)
#define npyv_rint_f64(A) svrintn_f64_x(svptrue_b64(), A)

// ceil
#define npyv_ceil_f32(A) svrintp_f32_x(svptrue_b32(), A)
#define npyv_ceil_f64(A) svrintp_f64_x(svptrue_b64(), A)

// trunc
#define npyv_trunc_f32(A) svrintz_f32_x(svptrue_b32(), A)
#define npyv_trunc_f64(A) svrintz_f64_x(svptrue_b64(), A)

// floor
#define npyv_floor_f32(A) svrintm_f32_x(svptrue_b32(), A)
#define npyv_floor_f64(A) svrintm_f64_x(svptrue_b64(), A)

#endif  // _NPY_SIMD_SVE_MATH_H
