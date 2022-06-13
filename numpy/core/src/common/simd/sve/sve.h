#ifndef _NPY_SIMD_H_
#error "Not a standalone header"
#endif

#define NPY_SIMD 512
#define NPY_SIMD_WIDTH 64
#define NPY_SIMD_F64 1
#define NPY_SIMD_FMA3 1
// Enough limit to allow us to use _mm512_i32gather_* and _mm512_i32scatter_*
#define NPY_SIMD_MAXLOAD_STRIDE32 (0x7fffffff / 16)
#define NPY_SIMD_MAXSTORE_STRIDE32 (0x7fffffff / 16)

#define __SVE_ATTRIBUTE_SIZE_ __attribute__((arm_sve_vector_bits(NPY_SIMD)))

typedef svbool_t __pred __SVE_ATTRIBUTE_SIZE_;

#define NPYV_IMPL_SVE_TYPE(TYPE, S)                           \
    typedef sv##TYPE##8 __sve_##S##8 __SVE_ATTRIBUTE_SIZE_;   \
    typedef sv##TYPE##16 __sve_##S##16 __SVE_ATTRIBUTE_SIZE_; \
    typedef sv##TYPE##32 __sve_##S##32 __SVE_ATTRIBUTE_SIZE_; \
    typedef sv##TYPE##64 __sve_##S##64 __SVE_ATTRIBUTE_SIZE_; \
    typedef __sve_##S##8 npyv_##S##8;                         \
    typedef __sve_##S##16 npyv_##S##16;                       \
    typedef __sve_##S##32 npyv_##S##32;                       \
    typedef __sve_##S##64 npyv_##S##64;

#define NPYV_IMPL_SVE_TYPE_X(TYPE, S, X)                            \
    typedef sv##TYPE##8##X __sve_##S##8##X __SVE_ATTRIBUTE_SIZE_;   \
    typedef sv##TYPE##16##X __sve_##S##16##X __SVE_ATTRIBUTE_SIZE_; \
    typedef sv##TYPE##32##X __sve_##S##32##X __SVE_ATTRIBUTE_SIZE_; \
    typedef sv##TYPE##64##X __sve_##S##64##X __SVE_ATTRIBUTE_SIZE_; \
    typedef __sve_##S##8##X npyv_##S##8##X;                         \
    typedef __sve_##S##16##X npyv_##S##16##X;                       \
    typedef __sve_##S##32##X npyv_##S##32##X;                       \
    typedef __sve_##S##64##X npyv_##S##64##X;

NPYV_IMPL_SVE_TYPE(uint, u)
NPYV_IMPL_SVE_TYPE_X(uint, u, x2)
NPYV_IMPL_SVE_TYPE_X(uint, u, x3)
NPYV_IMPL_SVE_TYPE(int, s)
NPYV_IMPL_SVE_TYPE_X(int, s, x2)
NPYV_IMPL_SVE_TYPE_X(int, s, x3)

typedef svfloat32_t __sve_f32 __SVE_ATTRIBUTE_SIZE_;
typedef svfloat32x2_t __sve_f32x2 __SVE_ATTRIBUTE_SIZE_;
typedef svfloat32x3_t __sve_f32x3 __SVE_ATTRIBUTE_SIZE_;
typedef svfloat64_t __sve_f64 __SVE_ATTRIBUTE_SIZE_;
typedef svfloat64x2_t __sve_f64x2 __SVE_ATTRIBUTE_SIZE_;
typedef svfloat64x3_t __sve_f64x3 __SVE_ATTRIBUTE_SIZE_;

typedef __pred npyv_b8;
typedef __pred npyv_b16;
typedef __pred npyv_b32;
typedef __pred npyv_b64;

#define npyv_nlanes_u8 (NPY_SIMD / 8)
#define npyv_nlanes_u16 (NPY_SIMD / 16)
#define npyv_nlanes_u32 (NPY_SIMD / 32)
#define npyv_nlanes_u64 (NPY_SIMD / 64)
#define npyv_nlanes_s8 (NPY_SIMD / 8)
#define npyv_nlanes_s16 (NPY_SIMD / 16)
#define npyv_nlanes_s32 (NPY_SIMD / 32)
#define npyv_nlanes_s64 (NPY_SIMD / 64)
#define npyv_nlanes_f32 (NPY_SIMD / 32)
#define npyv_nlanes_f64 (NPY_SIMD / 64)

//#include "utils.h"
#include "arithmetic.h"
#include "conversion.h"
#include "maskop.h"
#include "math.h"
#include "memory.h"
#include "misc.h"
#include "operators.h"
#include "reorder.h"
