#ifndef _NPY_SIMD_H_
#error "Not a standalone header"
#endif

#if __ARM_FEATURE_SVE_BITS == 512
#define NPY_SIMD 512
#define __SVE_ATTRIBUTE_SIZE_ __attribute__((arm_sve_vector_bits(NPY_SIMD)))
#elif __ARM_FEATURE_SVE_BITS == 256
#define NPY_SIMD 256
#define __SVE_ATTRIBUTE_SIZE_ __attribute__((arm_sve_vector_bits(NPY_SIMD)))
#else
#error "unsupported sve size"
#endif

#define NPY_SIMD_WIDTH (NPY_SIMD / 8)

#define NPY_SIMD_F64 1
#define NPY_SIMD_F32 1
#define NPY_SIMD_FMA3 1
#define NPY_SIMD_BIGENDIAN 0

#define NPY_SIMD_MAXLOAD_STRIDE32 (0x7fffffff / 16)
#define NPY_SIMD_MAXSTORE_STRIDE32 (0x7fffffff / 16)


typedef svbool_t __pred __SVE_ATTRIBUTE_SIZE_;

#define NPYV_IMPL_SVE_TYPE(TYPE, S)                            \
    typedef sv##TYPE##8_t npyv_##S##8 __SVE_ATTRIBUTE_SIZE_;   \
    typedef sv##TYPE##16_t npyv_##S##16 __SVE_ATTRIBUTE_SIZE_; \
    typedef sv##TYPE##32_t npyv_##S##32 __SVE_ATTRIBUTE_SIZE_; \
    typedef sv##TYPE##64_t npyv_##S##64 __SVE_ATTRIBUTE_SIZE_;

NPYV_IMPL_SVE_TYPE(uint, u)
NPYV_IMPL_SVE_TYPE(int, s)

#define NPYV_IMPL_SVE_TUPLE(TYPE, S) \
    typedef struct {                 \
        npyv_##S##8 val[2];          \
    } npyv_##S##8x2;                 \
    typedef struct {                 \
        npyv_##S##16 val[2];         \
    } npyv_##S##16x2;                \
    typedef struct {                 \
        npyv_##S##32 val[2];         \
    } npyv_##S##32x2;                \
    typedef struct {                 \
        npyv_##S##64 val[2];         \
    } npyv_##S##64x2;                \
    typedef struct {                 \
        npyv_##S##8 val[3];          \
    } npyv_##S##8x3;                 \
    typedef struct {                 \
        npyv_##S##16 val[3];         \
    } npyv_##S##16x3;                \
    typedef struct {                 \
        npyv_##S##32 val[3];         \
    } npyv_##S##32x3;                \
    typedef struct {                 \
        npyv_##S##64 val[3];         \
    } npyv_##S##64x3;

NPYV_IMPL_SVE_TUPLE(uint, u)
NPYV_IMPL_SVE_TUPLE(int, s)

typedef svfloat32_t npyv_f32 __SVE_ATTRIBUTE_SIZE_;
typedef svfloat64_t npyv_f64 __SVE_ATTRIBUTE_SIZE_;
typedef struct {
    npyv_f32 val[2];
} npyv_f32x2;
typedef struct {
    npyv_f32 val[3];
} npyv_f32x3;
typedef struct {
    npyv_f64 val[2];
} npyv_f64x2;
typedef struct {
    npyv_f64 val[3];
} npyv_f64x3;

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
