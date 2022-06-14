#ifndef NPY_SIMD
#error "Not a standalone header"
#endif

#ifndef _NPY_SIMD_SVE_ARITHMETIC_H
#define _NPY_SIMD_SVE_ARITHMETIC_H

#include "operators.h"

/***************************
 * Addition
 ***************************/
// non-saturated
NPY_FINLINE npyv_u8
npyv_add_u8(npyv_u8 a, npyv_u8 b)
{
    return svadd_u8_x(svptrue_b8(), a, b);
}
NPY_FINLINE npyv_u16
npyv_add_u16(npyv_u16 a, npyv_u16 b)
{
    return svadd_u16_x(svptrue_b16(), a, b);
}
NPY_FINLINE npyv_u32
npyv_add_u32(npyv_u32 a, npyv_u32 b)
{
    return svadd_u32_x(svptrue_b32(), a, b);
}
NPY_FINLINE npyv_u64
npyv_add_u64(npyv_u64 a, npyv_u64 b)
{
    return svadd_u64_x(svptrue_b64(), a, b);
}
NPY_FINLINE npyv_s8
npyv_add_s8(npyv_s8 a, npyv_s8 b)
{
    return svadd_s8_x(svptrue_b8(), a, b);
}
NPY_FINLINE npyv_s16
npyv_add_s16(npyv_s16 a, npyv_s16 b)
{
    return svadd_s16_x(svptrue_b16(), a, b);
}
NPY_FINLINE npyv_s32
npyv_add_s32(npyv_s32 a, npyv_s32 b)
{
    return svadd_s32_x(svptrue_b32(), a, b);
}
NPY_FINLINE npyv_s64
npyv_add_s64(npyv_s64 a, npyv_s64 b)
{
    return svadd_s64_x(svptrue_b64(), a, b);
}
NPY_FINLINE npyv_f32
npyv_add_f32(npyv_f32 a, npyv_f32 b)
{
    return svadd_f32_x(svptrue_b32(), a, b);
}
NPY_FINLINE npyv_f64
npyv_add_f64(npyv_f64 a, npyv_f64 b)
{
    return svadd_f64_x(svptrue_b64(), a, b);
}

// saturated
#define npyv_adds_u8 svqadd_u8
#define npyv_adds_s8 svqadd_s8
#define npyv_adds_u16 svqadd_u16
#define npyv_adds_s16 svqadd_s16

/***************************
 * Subtraction
 ***************************/
// non-saturated
NPY_FINLINE npyv_u8
npyv_sub_u8(npyv_u8 a, npyv_u8 b)
{
    return svsub_u8_x(svptrue_b8(), a, b);
}
NPY_FINLINE npyv_u16
npyv_sub_u16(npyv_u16 a, npyv_u16 b)
{
    return svsub_u16_x(svptrue_b16(), a, b);
}
NPY_FINLINE npyv_u32
npyv_sub_u32(npyv_u32 a, npyv_u32 b)
{
    return svsub_u32_x(svptrue_b32(), a, b);
}
NPY_FINLINE npyv_u64
npyv_sub_u64(npyv_u64 a, npyv_u64 b)
{
    return svsub_u64_x(svptrue_b64(), a, b);
}
NPY_FINLINE npyv_s8
npyv_sub_s8(npyv_s8 a, npyv_s8 b)
{
    return svsub_s8_x(svptrue_b8(), a, b);
}
NPY_FINLINE npyv_s16
npyv_sub_s16(npyv_s16 a, npyv_s16 b)
{
    return svsub_s16_x(svptrue_b16(), a, b);
}
NPY_FINLINE npyv_s32
npyv_sub_s32(npyv_s32 a, npyv_s32 b)
{
    return svsub_s32_x(svptrue_b32(), a, b);
}
NPY_FINLINE npyv_s64
npyv_sub_s64(npyv_s64 a, npyv_s64 b)
{
    return svsub_s64_x(svptrue_b64(), a, b);
}
NPY_FINLINE npyv_f32
npyv_sub_f32(npyv_f32 a, npyv_f32 b)
{
    return svsub_f32_x(svptrue_b32(), a, b);
}
NPY_FINLINE npyv_f64
npyv_sub_f64(npyv_f64 a, npyv_f64 b)
{
    return svsub_f64_x(svptrue_b64(), a, b);
}

// saturated
#define npyv_subs_u8 svqsub_u8
#define npyv_subs_s8 svqsub_s8
#define npyv_subs_u16 svqsub_u16
#define npyv_subs_s16 svqsub_s16

/***************************
 * Multiplication
 ***************************/
// non-saturated
NPY_FINLINE npyv_u8
npyv_mul_u8(npyv_u8 a, npyv_u8 b)
{
    return svmul_u8_x(svptrue_b8(), a, b);
}
NPY_FINLINE npyv_u16
npyv_mul_u16(npyv_u16 a, npyv_u16 b)
{
    return svmul_u16_x(svptrue_b16(), a, b);
}
NPY_FINLINE npyv_u32
npyv_mul_u32(npyv_u32 a, npyv_u32 b)
{
    return svmul_u32_x(svptrue_b32(), a, b);
}
NPY_FINLINE npyv_u64
npyv_mul_u64(npyv_u64 a, npyv_u64 b)
{
    return svmul_u64_x(svptrue_b64(), a, b);
}
NPY_FINLINE npyv_s8
npyv_mul_s8(npyv_s8 a, npyv_s8 b)
{
    return svmul_s8_x(svptrue_b8(), a, b);
}
NPY_FINLINE npyv_s16
npyv_mul_s16(npyv_s16 a, npyv_s16 b)
{
    return svmul_s16_x(svptrue_b16(), a, b);
}
NPY_FINLINE npyv_s32
npyv_mul_s32(npyv_s32 a, npyv_s32 b)
{
    return svmul_s32_x(svptrue_b32(), a, b);
}
NPY_FINLINE npyv_s64
npyv_mul_s64(npyv_s64 a, npyv_s64 b)
{
    return svmul_s64_x(svptrue_b64(), a, b);
}
NPY_FINLINE npyv_f32
npyv_mul_f32(npyv_f32 a, npyv_f32 b)
{
    return svmul_f32_x(svptrue_b32(), a, b);
}
NPY_FINLINE npyv_f64
npyv_mul_f64(npyv_f64 a, npyv_f64 b)
{
    return svmul_f64_x(svptrue_b64(), a, b);
}

/***************************
 * Integer Division
 ***************************/
// See simd/intdiv.h for more clarification
// divide each unsigned 8-bit element by divisor

// mulhi: high part of unsigned multiplication
// floor(a/d)      = (mulhi + ((a-mulhi) >> sh1)) >> sh2
#define NPYV_IMPL_SVE_DIVC_U(WIDTH)                                   \
    NPY_FINLINE npyv_u##WIDTH npyv_divc_u##WIDTH(                     \
            npyv_u##WIDTH a, const npyv_u##WIDTH##x3 divisor)         \
    {                                                                 \
        const svbool_t mask_all = svptrue_b##WIDTH();                 \
        svuint##WIDTH##_t mulhi =                                     \
                svmulh_u##WIDTH##_x(mask_all, a, divisor.val[0]);     \
        svuint##WIDTH##_t q = svsub_u##WIDTH##_x(mask_all, a, mulhi); \
        q = svlsr_u##WIDTH##_x(mask_all, q, divisor.val[1]);          \
        q = svadd_u##WIDTH##_x(mask_all, mulhi, q);                   \
        q = svlsr_u##WIDTH##_x(mask_all, q, divisor.val[2]);          \
        return q;                                                     \
    }

NPYV_IMPL_SVE_DIVC_U(8)
NPYV_IMPL_SVE_DIVC_U(16)
NPYV_IMPL_SVE_DIVC_U(32)

// divide each signed 16-bit element by divisor (round towards zero)
// q               = ((a + mulhi) >> sh1) - XSIGN(a)
// trunc(a/d)      = (q ^ dsign) - dsign
#define NPYV_IMPL_SVE_DIVC_S(WIDTH)                                           \
    NPY_FINLINE npyv_s##WIDTH npyv_divc_s##WIDTH(                             \
            npyv_s##WIDTH a, const npyv_s##WIDTH##x3 divisor)                 \
    {                                                                         \
        const svbool_t mask_all = svptrue_b##WIDTH();                         \
        const svint##WIDTH##_t dsign = divisor.val[2];                        \
        svint##WIDTH##_t mulhi =                                              \
                svmulh_s##WIDTH##_x(mask_all, a, divisor.val[0]);             \
        svint##WIDTH##_t q = svasr_s##WIDTH##_x(                              \
                mask_all, svadd_s##WIDTH##_x(mask_all, a, mulhi),             \
                svreinterpret_u##WIDTH##_s##WIDTH(divisor.val[1]));           \
        q = svsub_s##WIDTH##_x(mask_all, q,                                   \
                               svasr_n_s##WIDTH##_x(mask_all, a, WIDTH - 1)); \
        q = svsub_s##WIDTH##_x(                                               \
                mask_all, sveor_s##WIDTH##_x(mask_all, q, dsign), dsign);     \
        return q;                                                             \
    }

NPYV_IMPL_SVE_DIVC_S(8)
NPYV_IMPL_SVE_DIVC_S(16)
NPYV_IMPL_SVE_DIVC_S(32)

// divide each unsigned 64-bit element by a divisor
NPY_FINLINE npyv_u64 npyv_divc_u64(npyv_u64 a, const npyv_u64x3 divisor)
{
    // high part of unsigned multiplication
  npyv_u64 mulhi      = svmulh_u64_x(svptrue_b64(), a, divisor.val[0]);
    // floor(a/d)      = (mulhi + ((a-mulhi) >> sh1)) >> sh2
  npyv_u64 q          = svsub_u64_x(svptrue_b64(), a, mulhi);
    q          = svlsr_u64_x(svptrue_b64(), q, divisor.val[1]);
    q          = svadd_u64_x(svptrue_b64(), mulhi, q);
    q          = svlsr_x(svptrue_b64(), q, divisor.val[2]);
    return  q;
}
// divide each unsigned 64-bit element by a divisor (round towards zero)
NPY_FINLINE npyv_s64 npyv_divc_s64(npyv_s64 a, const npyv_s64x3 divisor)
{
    // high part of unsigned multiplication
  npyv_s64 mulhi      = svreinterpret_s64_u64(svmulh_u64_x(svptrue_b64(), svreinterpret_u64_s64(a), svreinterpret_u64_s64(divisor.val[0])));
    // convert unsigned to signed high multiplication
    // mulhi - ((a < 0) ? m : 0) - ((m < 0) ? a : 0);
  npyv_s64 asign      = svasr_n_s64_x(svptrue_b64(), a, 63);
  npyv_s64 msign      = svasr_n_s64_x(svptrue_b64(), divisor.val[0], 63);
  npyv_s64 m_asign    = svand_s64_x(svptrue_b64(), divisor.val[0], asign);
  npyv_s64 a_msign    = svand_s64_x(svptrue_b64(), a, msign);
  mulhi      = svsub_s64_x(svptrue_b64(), mulhi, m_asign);
  mulhi      = svsub_s64_x(svptrue_b64(), mulhi, a_msign);
    // q               = ((a + mulhi) >> sh1) - XSIGN(a)
    // trunc(a/d)      = (q ^ dsign) - dsign
  npyv_s64 q = svasr_s64_x(svptrue_b64(), svadd_s64_x(svptrue_b64(), a, mulhi), svreinterpret_u64_s64(divisor.val[1]));
            q          = svsub_s64_x(svptrue_b64(), q, asign);
            q          = svsub_s64_x(svptrue_b64(), sveor_s64_x(svptrue_b64(), q, divisor.val[2]), divisor.val[2]);
    return  q;
}

/***************************
 * Division
 ***************************/
NPY_FINLINE npyv_f32
npyv_div_f32(npyv_f32 a, npyv_f32 b)
{
    return svdiv_f32_x(svptrue_b32(), a, b);
}
NPY_FINLINE npyv_f64
npyv_div_f64(npyv_f64 a, npyv_f64 b)
{
    return svdiv_f64_x(svptrue_b64(), a, b);
}

/***************************
 * FUSED F32
 ***************************/
// a*b + c
NPY_FINLINE npyv_f32
npyv_muladd_f32(npyv_f32 a, npyv_f32 b, npyv_f32 c)
{
    return svmla_f32_x(svptrue_b32(), c, b, a);
}
// a*b - c
NPY_FINLINE npyv_f32
npyv_mulsub_f32(npyv_f32 a, npyv_f32 b, npyv_f32 c)
{
    return svnmls_f32_x(svptrue_b32(), c, b, a);
}
// -(a*b) + c
NPY_FINLINE npyv_f32
npyv_nmuladd_f32(npyv_f32 a, npyv_f32 b, npyv_f32 c)
{
    return svmls_f32_x(svptrue_b32(), c, a, b);
}
// -(a*b) - c
NPY_FINLINE npyv_f32
npyv_nmulsub_f32(npyv_f32 a, npyv_f32 b, npyv_f32 c)
{
    return svnmla_f32_x(svptrue_b32(), c, a, b);
}

/***************************
 * FUSED F64
 ***************************/
// a*b + c
NPY_FINLINE npyv_f64
npyv_muladd_f64(npyv_f64 a, npyv_f64 b, npyv_f64 c)
{
    return svmla_f64_x(svptrue_b64(), c, b, a);
}
// a*b - c
NPY_FINLINE npyv_f64
npyv_mulsub_f64(npyv_f64 a, npyv_f64 b, npyv_f64 c)
{
    return svnmls_f64_x(svptrue_b64(), c, b, a);
}
// -(a*b) + c
NPY_FINLINE npyv_f64
npyv_nmuladd_f64(npyv_f64 a, npyv_f64 b, npyv_f64 c)
{
    return svmls_f64_x(svptrue_b64(), c, a, b);
}
// -(a*b) - c
NPY_FINLINE npyv_f64
npyv_nmulsub_f64(npyv_f64 a, npyv_f64 b, npyv_f64 c)
{
    return svnmla_f64_x(svptrue_b64(), c, a, b);
}

/***************************
 * Summation
 ***************************/
// reduce sum across vector
NPY_FINLINE npy_uint32
npyv_sum_u32(npyv_u32 a)
{
    return svaddv_u32(svptrue_b32(), a);
}

NPY_FINLINE npy_uint64
npyv_sum_u64(npyv_u64 a)
{
    return svaddv_u64(svptrue_b64(), a);
}

NPY_FINLINE float
npyv_sum_f32(npyv_f32 a)
{
    return svaddv_f32(svptrue_b32(), a);
}

NPY_FINLINE double
npyv_sum_f64(npyv_f64 a)
{
    return svaddv_f64(svptrue_b64(), a);
}

NPY_FINLINE npy_uint16
npyv_sumup_u8(npyv_u8 a)
{
    return svaddv_u8(svptrue_b8(), a);
}

NPY_FINLINE npy_uint32
npyv_sumup_u16(npyv_u16 a)
{
    return svaddv_u16(svptrue_b16(), a);
}

#endif  // _NPY_SIMD_SVE_ARITHMETIC_H
