#ifndef NPY_SIMD
#error "Not a standalone header"
#endif

#ifndef _NPY_SIMD_SVE_MEMORY_H
#define _NPY_SIMD_SVE_MEMORY_H

#include "misc.h"

/***************************
 * load/store
 ***************************/
// GCC requires literal type definitions for pointers types otherwise it causes
// ambiguous errors
#define NPYV_IMPL_SVE_MEM(SFX, SFX1, SFX2, CTYPE, VL_PAT, HALF_LANE)		\
    NPY_FINLINE npyv_##SFX npyv_load_##SFX(const npyv_lanetype_##SFX *ptr)  \
    {                                                                       \
        return svld1_##SFX(svptrue_##SFX1(), (const CTYPE *)ptr);           \
    }                                                                       \
    NPY_FINLINE npyv_##SFX npyv_loada_##SFX(const npyv_lanetype_##SFX *ptr) \
    {                                                                       \
        return svld1_##SFX(svptrue_##SFX1(), (const CTYPE *)ptr);           \
    }                                                                       \
    NPY_FINLINE npyv_##SFX npyv_loads_##SFX(const npyv_lanetype_##SFX *ptr) \
    {                                                                       \
        return svld1_##SFX(svptrue_##SFX1(), (const CTYPE *)ptr);           \
    }                                                                       \
    NPY_FINLINE npyv_##SFX npyv_loadl_##SFX(const npyv_lanetype_##SFX *ptr) \
    {                                                                       \
        return svld1_##SFX(svptrue_pat_##SFX1(VL_PAT), (const CTYPE *)ptr); \
    }                                                                       \
    NPY_FINLINE void npyv_store_##SFX(npyv_lanetype_##SFX *ptr,             \
                                      npyv_##SFX vec)                       \
    {                                                                       \
      svst1_##SFX(svptrue_##SFX1(), (CTYPE *)ptr, vec);			\
    }                                                                       \
    NPY_FINLINE void npyv_storea_##SFX(npyv_lanetype_##SFX *ptr,            \
                                       npyv_##SFX vec)                      \
    {                                                                       \
        svst1_##SFX(svptrue_##SFX1(), (CTYPE *)ptr, vec);                   \
    }                                                                       \
    NPY_FINLINE void npyv_stores_##SFX(npyv_lanetype_##SFX *ptr,            \
                                       npyv_##SFX vec)                      \
    {                                                                       \
        svst1_##SFX(svptrue_##SFX1(), (CTYPE *)ptr, vec);                   \
    }                                                                       \
    NPY_FINLINE void npyv_storel_##SFX(npyv_lanetype_##SFX *ptr,            \
                                       npyv_##SFX vec)                      \
    {                                                                       \
        svst1_##SFX(svptrue_pat_##SFX1(VL_PAT), (CTYPE *)ptr, vec);         \
    }                                                                       \
    NPY_FINLINE void npyv_storeh_##SFX(npyv_lanetype_##SFX *ptr,            \
                                       npyv_##SFX vec)                      \
    {                                                                       \
        svbool_t mask = svptrue_pat_##SFX1(VL_PAT);                         \
	sv ## CTYPE tmp = svext_ ## SFX (vec, vec, HALF_LANE); \
        svst1_##SFX(mask, (CTYPE *)ptr, tmp);	\
    }

NPYV_IMPL_SVE_MEM(u8, b8, u8, uint8_t, SV_VL32, 32)
  NPYV_IMPL_SVE_MEM(u16, b16, u16, uint16_t, SV_VL16, 16)
  NPYV_IMPL_SVE_MEM(u32, b32, u32, uint32_t, SV_VL8, 8)
  NPYV_IMPL_SVE_MEM(u64, b64, u64, uint64_t, SV_VL4, 4)
  NPYV_IMPL_SVE_MEM(s8, b8, s8, int8_t, SV_VL32, 32)
  NPYV_IMPL_SVE_MEM(s16, b16, s16, int16_t, SV_VL16, 16)
  NPYV_IMPL_SVE_MEM(s32, b32, s32, int32_t, SV_VL8, 8)
  NPYV_IMPL_SVE_MEM(s64, b64, s64, int64_t, SV_VL4, 4)
  NPYV_IMPL_SVE_MEM(f32, b32, u32, float32_t, SV_VL8, 8)
  NPYV_IMPL_SVE_MEM(f64, b64, u64, float64_t, SV_VL4, 4)

/***************************
 * Non-contiguous Load
 ***************************/
//// 32
NPY_FINLINE npyv_u32
npyv_loadn_u32(const npy_uint32 *ptr, npy_intp stride)
{
#if 0
  assert(llabs(stride) <= NPY_SIMD_MAXLOAD_STRIDE32);
    const svbool_t mask_all = svptrue_b32();
    const svint32_t steps = svindex_s32(0, 1);
    const svint32_t idx =
            svmul_s32_x(mask_all, steps, svdup_s32((int)stride));

    return svld1_gather_s32index_u32(mask_all, ptr, idx);
#else
    svuint32_t vec;
    vec = svinsr_n_u32(vec, *(ptr + stride*15));
    vec = svinsr_n_u32(vec, *(ptr + stride*14));
    vec = svinsr_n_u32(vec, *(ptr + stride*13));
    vec = svinsr_n_u32(vec, *(ptr + stride*12));
    vec = svinsr_n_u32(vec, *(ptr + stride*11));
    vec = svinsr_n_u32(vec, *(ptr + stride*10));
    vec = svinsr_n_u32(vec, *(ptr + stride*9));
    vec = svinsr_n_u32(vec, *(ptr + stride*8));
    vec = svinsr_n_u32(vec, *(ptr + stride*7));
    vec = svinsr_n_u32(vec, *(ptr + stride*6));
    vec = svinsr_n_u32(vec, *(ptr + stride*5));
    vec = svinsr_n_u32(vec, *(ptr + stride*4));
    vec = svinsr_n_u32(vec, *(ptr + stride*3));
    vec = svinsr_n_u32(vec, *(ptr + stride*2));
    vec = svinsr_n_u32(vec, *(ptr + stride*1));
    vec = svinsr_n_u32(vec, *(ptr + stride*0));
    return vec;
#endif
}
NPY_FINLINE npyv_s32
npyv_loadn_s32(const npy_int32 *ptr, npy_intp stride)
{
    return svreinterpret_s32_u32(
            npyv_loadn_u32((const npy_uint32 *)ptr, stride));
}

NPY_FINLINE npyv_f32
npyv_loadn_f32(const float *ptr, npy_intp stride)
{
    return svreinterpret_f32_u32(
            npyv_loadn_u32((const npy_uint32 *)ptr, stride));
}

//// 64
NPY_FINLINE npyv_u64
npyv_loadn_u64(const npy_uint64 *ptr, npy_intp stride)
{
#if 0
    assert(llabs(stride) <= NPY_SIMD_MAXLOAD_STRIDE32);
    const svbool_t mask_all = svptrue_b64();
    const svint64_t steps = svindex_s64(0, 1);
    const svint64_t idx =
            svmul_s64_x(mask_all, steps, svdup_s64((int)stride));

    return svld1_gather_s64index_u64(mask_all, ptr, idx);
#else
    svuint64_t vec;
    vec = svinsr_n_u64(vec, *(ptr + stride*7));
    vec = svinsr_n_u64(vec, *(ptr + stride*6));
    vec = svinsr_n_u64(vec, *(ptr + stride*5));
    vec = svinsr_n_u64(vec, *(ptr + stride*4));
    vec = svinsr_n_u64(vec, *(ptr + stride*3));
    vec = svinsr_n_u64(vec, *(ptr + stride*2));
    vec = svinsr_n_u64(vec, *(ptr + stride*1));
    vec = svinsr_n_u64(vec, *(ptr + stride*0));
    return vec;
#endif    
}
NPY_FINLINE npyv_s64
npyv_loadn_s64(const npy_int64 *ptr, npy_intp stride)
{
    return svreinterpret_s64_u64(
    npyv_loadn_u64((const npy_uint64 *)ptr, stride));
}
NPY_FINLINE npyv_f64
npyv_loadn_f64(const double *ptr, npy_intp stride)
{
  return svreinterpret_f64_u64(
	npyv_loadn_u64((const npy_uint64 *)ptr, stride));
}
/***************************
 * Non-contiguous Store
 ***************************/
//// 32
NPY_FINLINE void
npyv_storen_u32(npy_uint32 *ptr, npy_intp stride, npyv_u32 a)
{
    assert(llabs(stride) <= NPY_SIMD_MAXLOAD_STRIDE32);
    const svbool_t mask_all = svptrue_b32();
    const svint32_t steps = svindex_s32(0, 1);
    const svint32_t idx =
            svmul_s32_x(mask_all, steps, svdup_s32((int)stride));

    svst1_scatter_s32index_u32(mask_all, ptr, idx, a);
}
NPY_FINLINE void
npyv_storen_s32(npy_int32 *ptr, npy_intp stride, npyv_s32 a)
{
    npyv_storen_u32((npy_uint32 *)ptr, stride, svreinterpret_u32_s32(a));
}
NPY_FINLINE void
npyv_storen_f32(float *ptr, npy_intp stride, npyv_f32 a)
{
    npyv_storen_u32((npy_uint32 *)ptr, stride, svreinterpret_u32_f32(a));
}
//// 64
NPY_FINLINE void
npyv_storen_u64(npy_uint64 *ptr, npy_intp stride, npyv_u64 a)
{
    assert(llabs(stride) <= NPY_SIMD_MAXLOAD_STRIDE32);
    const svbool_t mask_all = svptrue_b64();
    const svint64_t steps = svindex_s64(0, 1);
    const svint64_t idx =
            svmul_s64_x(mask_all, steps, svdup_s64((int)stride));

    svst1_scatter_s64index_u64(mask_all, ptr, idx, a);
}
NPY_FINLINE void
npyv_storen_s64(npy_int64 *ptr, npy_intp stride, npyv_s64 a)
{
    npyv_storen_u64((npy_uint64 *)ptr, stride, svreinterpret_u64_s64(a));
}
NPY_FINLINE void
npyv_storen_f64(double *ptr, npy_intp stride, npyv_f64 a)
{
    npyv_storen_u64((npy_uint64 *)ptr, stride, svreinterpret_u64_f64(a));
}

/*********************************
 * Partial Load
 *********************************/
//// 32
NPY_FINLINE npyv_s32
npyv_load_till_s32(const npy_int32 *ptr, npy_uintp nlane, npy_int32 fill)
{
    assert(nlane > 0);
    const svbool_t mask_all = svptrue_b32();
    if (nlane == NPY_SIMD_WIDTH / sizeof(int32_t)) {
        return svld1_s32(mask_all, ptr);
    }
    else {
        const svint32_t vfill = svdup_s32(fill);
        const svint32_t idx = svindex_s32(0, 1);
        const svbool_t mask = svcmplt_n_s32(mask_all, idx, nlane);
        return svsel_s32(mask, svld1_s32(mask, ptr), vfill);
    }
}
// fill zero to rest lanes
NPY_FINLINE npyv_s32
npyv_load_tillz_s32(const npy_int32 *ptr, npy_uintp nlane)
{
    assert(nlane > 0);
    const svbool_t mask_all = svptrue_b32();
    if (nlane == NPY_SIMD_WIDTH / sizeof(int32_t)) {
        return svld1_s32(mask_all, ptr);
    }
    else {
        const svint32_t idx = svindex_s32(0, 1);
        const svbool_t mask = svcmplt_n_s32(mask_all, idx, nlane);
        return svld1_s32(mask, ptr);
    }
}
//// 64
NPY_FINLINE npyv_s64
npyv_load_till_s64(const npy_int64 *ptr, npy_uintp nlane, npy_int64 fill)
{
    assert(nlane > 0);
    const svbool_t mask_all = svptrue_b64();
    if (nlane == NPY_SIMD_WIDTH / sizeof(int64_t)) {
        return svld1_s64(mask_all, ptr);
    }
    else {
        const svint64_t vfill = svdup_s64(fill);
        const svint64_t idx = svindex_s64(0, 1);
        const svbool_t mask = svcmplt_n_s64(mask_all, idx, nlane);
        return svsel_s64(mask, svld1_s64(mask, ptr), vfill);
    }
}
// fill zero to rest lanes
NPY_FINLINE npyv_s64
npyv_load_tillz_s64(const npy_int64 *ptr, npy_uintp nlane)
{
    assert(nlane > 0);
    const svbool_t mask_all = svptrue_b64();
    if (nlane == NPY_SIMD_WIDTH / sizeof(int64_t)) {
        return svld1_s64(mask_all, ptr);
    }
    else {
        const svint64_t idx = svindex_s64(0, 1);
        const svbool_t mask = svcmplt_n_s64(mask_all, idx, nlane);
        return svld1_s64(mask, ptr);
    }
}
#if 0
//// f32
NPY_FINLINE npyv_f32
npyv_load_till_f32(const npy_float32 *ptr, npy_uintp nlane, npy_int32 fill)
{
    assert(nlane > 0);
    const svbool_t mask_all = svptrue_b32();
    if (nlane == NPY_SIMD_WIDTH / sizeof(int32_t)) {
        return svld1(mask_all, ptr);
    }
    else {
        const svfloat32_t vfill = svdup_f32(fill);
        const svint32_t idx = svindex_s32(0, 1);
        const svbool_t mask = svcmplt_n_s32(mask_all, idx, nlane);
        return svsel_f32(mask, svld1_f32(mask, ptr), vfill);
    }
}
//// f64
NPY_FINLINE npyv_f64
npyv_load_till_f64(const npy_float64 *ptr, npy_uintp nlane, npy_int64 fill)
{
    assert(nlane > 0);
    const svbool_t mask_all = svptrue_b64();
    if (nlane == NPY_SIMD_WIDTH / sizeof(int64_t)) {
        return svld1_f64(mask_all, ptr);
    }
    else {
        const svfloat64_t vfill = svdup_f64(fill);
        const svint64_t idx = svindex_s64(0, 1);
        const svbool_t mask = svcmplt_n_s64(mask_all, idx, nlane);
        return svsel_f64(mask, svld1_f64(mask, ptr), vfill);
    }
}
#endif // #if 0
/*********************************
 * Non-contiguous partial load
 *********************************/
//// 32
NPY_FINLINE npyv_s32
npyv_loadn_till_s32(const npy_int32 *ptr, npy_intp stride, npy_uintp nlane,
                    npy_int32 fill)
{
    assert(nlane > 0);
    assert(llabs(stride) <= NPY_SIMD_MAXLOAD_STRIDE32);
    const svbool_t mask_all = svptrue_b32();
    const svint32_t steps = svindex_s32(0, 1);
    const svint32_t idx =
            svmul_s32_x(mask_all, steps, svdup_s32((int)stride));

    if (nlane == NPY_SIMD_WIDTH / sizeof(int32_t)) {
        return svld1_gather_s32index_s32(mask_all, ptr, idx);
    }
    else {
        const svint32_t tmp = svindex_s32(0, 1);
        const svbool_t mask = svcmplt_n_s32(mask_all, tmp, nlane);
        const svint32_t vfill = svdup_s32(fill);
        return svsel_s32(mask, svld1_gather_s32index_s32(mask, ptr, idx),
                         vfill);
    }
}
// fill zero to rest lanes
NPY_FINLINE npyv_s32
npyv_loadn_tillz_s32(const npy_int32 *ptr, npy_intp stride, npy_uintp nlane)
{
    return npyv_loadn_till_s32(ptr, stride, nlane, 0);
}
//// 64
NPY_FINLINE npyv_s64
npyv_loadn_till_s64(const npy_int64 *ptr, npy_intp stride, npy_uintp nlane,
                    npy_int64 fill)
{
    assert(nlane > 0);
    assert(llabs(stride) <= NPY_SIMD_MAXLOAD_STRIDE32);
    const svbool_t mask_all = svptrue_b64();
    const svint64_t steps = svindex_s64(0, 1);
    const svint64_t idx =
            svmul_s64_x(mask_all, steps, svdup_s64((int)stride));

    if (nlane == NPY_SIMD_WIDTH / sizeof(int64_t)) {
        return svld1_gather_s64index_s64(mask_all, ptr, idx);
    }
    else {
        const svint64_t tmp = svindex_s64(0, 1);
        const svbool_t mask = svcmplt_n_s64(mask_all, tmp, nlane);
        const svint64_t vfill = svdup_s64(fill);
        return svsel_s64(mask, svld1_gather_s64index_s64(mask, ptr, idx),
                         vfill);
    }
}
// fill zero to rest lanes
NPY_FINLINE npyv_s64
npyv_loadn_tillz_s64(const npy_int64 *ptr, npy_intp stride, npy_uintp nlane)
{
    return npyv_loadn_till_s64(ptr, stride, nlane, 0);
}
/*********************************
 * Partial store
 *********************************/
//// 32
NPY_FINLINE void
npyv_store_till_s32(npy_int32 *ptr, npy_uintp nlane, npyv_s32 a)
{
    assert(nlane > 0);
    const svbool_t mask_all = svptrue_b32();
    if (nlane == NPY_SIMD_WIDTH / sizeof(int32_t)) {
        svst1_s32(mask_all, ptr, a);
    }
    else {
        const svint32_t idx = svindex_s32(0, 1);
        const svbool_t mask = svcmplt_n_s32(mask_all, idx, nlane);
        svst1_s32(mask, ptr, a);
    }
}
//// 64
NPY_FINLINE void
npyv_store_till_s64(npy_int64 *ptr, npy_uintp nlane, npyv_s64 a)
{
    assert(nlane > 0);
    const svbool_t mask_all = svptrue_b64();
    if (nlane == NPY_SIMD_WIDTH / sizeof(int64_t)) {
        svst1_s64(mask_all, ptr, a);
    }
    else {
        const svint64_t idx = svindex_s64(0, 1);
        const svbool_t mask = svcmplt_n_s64(mask_all, idx, nlane);
	svst1_s64(mask, ptr, a);
    }
}
/*********************************
 * Non-contiguous partial store
 *********************************/
//// 32
NPY_FINLINE void
npyv_storen_till_s32(npy_int32 *ptr, npy_intp stride, npy_uintp nlane,
                     npyv_s32 a)
{
    assert(nlane > 0);
    assert(llabs(stride) <= NPY_SIMD_MAXLOAD_STRIDE32);
    const svbool_t mask_all = svptrue_b32();
    const svint32_t steps = svindex_s32(0, 1);
    const svint32_t idx =
            svmul_s32_x(mask_all, steps, svdup_s32((int)stride));

    if (nlane == NPY_SIMD_WIDTH / sizeof(int32_t)) {
        svst1_scatter_s32index_s32(mask_all, ptr, idx, a);
    }
    else {
        const svint32_t tmp = svindex_s32(0, 1);
        const svbool_t mask = svcmplt_n_s32(mask_all, tmp, nlane);
        svst1_scatter_s32index_s32(mask, ptr, idx, a);
    }
}
//// 64
NPY_FINLINE void
npyv_storen_till_s64(npy_int64 *ptr, npy_intp stride, npy_uintp nlane,
                     npyv_s64 a)
{
    assert(nlane > 0);
    assert(llabs(stride) <= NPY_SIMD_MAXLOAD_STRIDE32);
    const svbool_t mask_all = svptrue_b64();
    const svint64_t steps = svindex_s64(0, 1);
    const svint64_t idx =
            svmul_s64_x(mask_all, steps, svdup_s64((int)stride));

    if (nlane == NPY_SIMD_WIDTH / sizeof(int64_t)) {
        svst1_scatter_s64index_s64(mask_all, ptr, idx, a);
    }
    else {
        const svint64_t tmp = svindex_s64(0, 1);
        const svbool_t mask = svcmplt_n_s64(mask_all, tmp, nlane);
        svst1_scatter_s64index_s64(mask, ptr, idx, a);
    }
}

/*****************************************************************************
 * Implement partial load/store for u32/f32/u64/f64... via reinterpret cast
 *****************************************************************************/
#define NPYV_IMPL_SVE_REST_PARTIAL_TYPES(F_SFX, T_SFX)                        \
    NPY_FINLINE npyv_##F_SFX npyv_load_till_##F_SFX(                          \
            const npyv_lanetype_##F_SFX *ptr, npy_uintp nlane,                \
            npyv_lanetype_##F_SFX fill)                                       \
    {                                                                         \
        union {                                                               \
            npyv_lanetype_##F_SFX from_##F_SFX;                               \
            npyv_lanetype_##T_SFX to_##T_SFX;                                 \
        } pun = {.from_##F_SFX = fill};                                       \
        return npyv_reinterpret_##F_SFX##_##T_SFX(npyv_load_till_##T_SFX(     \
                (const npyv_lanetype_##T_SFX *)ptr, nlane, pun.to_##T_SFX));  \
    }                                                                         \
    NPY_FINLINE npyv_##F_SFX npyv_loadn_till_##F_SFX(                         \
            const npyv_lanetype_##F_SFX *ptr, npy_intp stride,                \
            npy_uintp nlane, npyv_lanetype_##F_SFX fill)                      \
    {                                                                         \
        union {                                                               \
            npyv_lanetype_##F_SFX from_##F_SFX;                               \
            npyv_lanetype_##T_SFX to_##T_SFX;                                 \
        } pun = {.from_##F_SFX = fill};                                       \
        return npyv_reinterpret_##F_SFX##_##T_SFX(                            \
                npyv_loadn_till_##T_SFX((const npyv_lanetype_##T_SFX *)ptr,   \
                                        stride, nlane, pun.to_##T_SFX));      \
    }                                                                         \
    NPY_FINLINE npyv_##F_SFX npyv_load_tillz_##F_SFX(                         \
            const npyv_lanetype_##F_SFX *ptr, npy_uintp nlane)                \
    {                                                                         \
        return npyv_reinterpret_##F_SFX##_##T_SFX(npyv_load_tillz_##T_SFX(    \
                (const npyv_lanetype_##T_SFX *)ptr, nlane));                  \
    }                                                                         \
    NPY_FINLINE npyv_##F_SFX npyv_loadn_tillz_##F_SFX(                        \
            const npyv_lanetype_##F_SFX *ptr, npy_intp stride,                \
            npy_uintp nlane)                                                  \
    {                                                                         \
        return npyv_reinterpret_##F_SFX##_##T_SFX(npyv_loadn_tillz_##T_SFX(   \
                (const npyv_lanetype_##T_SFX *)ptr, stride, nlane));          \
    }                                                                         \
    NPY_FINLINE void npyv_store_till_##F_SFX(npyv_lanetype_##F_SFX *ptr,      \
                                             npy_uintp nlane, npyv_##F_SFX a) \
    {                                                                         \
        npyv_store_till_##T_SFX((npyv_lanetype_##T_SFX *)ptr, nlane,          \
                                npyv_reinterpret_##T_SFX##_##F_SFX(a));       \
    }                                                                         \
    NPY_FINLINE void npyv_storen_till_##F_SFX(                                \
            npyv_lanetype_##F_SFX *ptr, npy_intp stride, npy_uintp nlane,     \
            npyv_##F_SFX a)                                                   \
    {                                                                         \
        npyv_storen_till_##T_SFX((npyv_lanetype_##T_SFX *)ptr, stride, nlane, \
                                 npyv_reinterpret_##T_SFX##_##F_SFX(a));      \
    }

NPYV_IMPL_SVE_REST_PARTIAL_TYPES(u32, s32)
NPYV_IMPL_SVE_REST_PARTIAL_TYPES(f32, s32)
NPYV_IMPL_SVE_REST_PARTIAL_TYPES(u64, s64)
NPYV_IMPL_SVE_REST_PARTIAL_TYPES(f64, s64)

#endif  // _NPY_SIMD_SVE_MEMORY_H
