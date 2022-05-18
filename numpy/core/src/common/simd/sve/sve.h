#ifndef _NPY_SIMD_H_
#error "Not a standalone header"
#endif
#define NPY_SIMD 512
#define NPY_SIMD_WIDTH 64
#define NPY_SIMD_F64 1
// これは何
#define NPY_SIMD_FMA3 1  // native support
// Enough limit to allow us to use _mm512_i32gather_* and _mm512_i32scatter_*
#define NPY_SIMD_MAXLOAD_STRIDE32 (0x7fffffff / 16)
#define NPY_SIMD_MAXSTORE_STRIDE32 (0x7fffffff / 16)

typedef svuint8_t npyv_u8;
typedef svint8_t npyv_s8;
typedef svuint16_t npyv_u16;
typedef svint16_t npyv_s16;
typedef svuint32_t npyv_u32;
typedef svint32_t npyv_s32;
typedef svuint64_t npyv_u64;
typedef svint64_t npyv_s64;
typedef svfloat32_t npyv_f32;
typedef svfloat64_t npyv_f64;

typedef svbool_t npyv_b8;
typedef svbool_t npyv_b16;
typedef svbool_t npyv_b32;
typedef svbool_t npyv_b64;

typedef svuint8x2_t npyv_u8x2;
typedef svuint16x2_t npyv_u16x2;
typedef svuint32x2_t npyv_u32x2;
typedef svuint64x2_t npyv_u64x2;
typedef svint8x2_t npyv_s8x2;
typedef svint16x2_t npyv_s16x2;
typedef svint32x2_t npyv_s32x2;
typedef svint64x2_t npyv_s64x2;
typedef svfloat32x2_t npyv_f32x2;
typedef svfloat64x2_t npyv_f64x2;

typedef svuint8x3_t npyv_u8x3;
typedef svuint16x3_t npyv_u16x3;
typedef svuint32x3_t npyv_u32x3;
typedef svuint64x3_t npyv_u64x3;
typedef svint8x3_t npyv_s8x3;
typedef svint16x3_t npyv_s16x3;
typedef svint32x3_t npyv_s32x3;
typedef svint64x3_t npyv_s64x3;
typedef svfloat32x3_t npyv_f32x3;
typedef svfloat64x3_t npyv_f64x3;

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
#include "memory.h"
#include "misc.h"
#include "reorder.h"
#include "conversion.h"
#include "arithmetic.h"
#include "operators.h"
#include "math.h"
#include "maskop.h"
