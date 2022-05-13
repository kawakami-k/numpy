#ifndef NPY_SIMD
#error "Not a standalone header"
#endif

#ifndef _NPY_SIMD_SVE_MISC_H
#define _NPY_SIMD_SVE_MISC_H

// vector with zero lanes
NPY_FINLINE npyv_u8
npyv_zero_u8()
{
    return svdup_n_u8(0);
}
NPY_FINLINE npyv_u16
npyv_zero_u16()
{
    return svdup_n_u16(0);
}
NPY_FINLINE npyv_u32
npyv_zero_u32()
{
    return svdup_n_u32(0);
}
NPY_FINLINE npyv_u64
npyv_zero_u64()
{
    return svdup_n_u64(0);
}
NPY_FINLINE npyv_s8
npyv_zero_s8()
{
    return svdup_n_s8(0);
}
NPY_FINLINE npyv_s16
npyv_zero_s16()
{
    return svdup_n_s16(0);
}
NPY_FINLINE npyv_s32
npyv_zero_s32()
{
    return svdup_n_s32(0);
}
NPY_FINLINE npyv_s64
npyv_zero_s64()
{
    return svdup_n_s64(0);
}
NPY_FINLINE npyv_f32
npyv_zero_f32()
{
    return svdup_n_f32(0.0f);
}
NPY_FINLINE npyv_f64
npyv_zero_f64()
{
    return svdup_n_f64(0.0);
}

// vector with a specific value set to all lanes
#define npyv_setall_u8 svdup_n_u8
#define npyv_setall_s8 svdup_n_s8
#define npyv_setall_u16 svdup_n_u16
#define npyv_setall_s16 svdup_n_s16
#define npyv_setall_u32 svdup_n_u32
#define npyv_setall_s32 svdup_n_s32
#define npyv_setall_u64 svdup_n_u64
#define npyv_setall_s64 svdup_n_s64
#define npyv_setall_f32 svdup_n_f32
#define npyv_setall_f64 svdup_n_f64

/**
 * vector with specific values set to each lane and
 * set a specific value to all remained lanes
 *
 */
NPY_FINLINE npyv_u8
npyv__set_u8(uint8_t i0, uint8_t i1, uint8_t i2, uint8_t i3, uint8_t i4,
             uint8_t i5, uint8_t i6, uint8_t i7, uint8_t i8, uint8_t i9,
             uint8_t i10, uint8_t i11, uint8_t i12, uint8_t i13, uint8_t i14,
             uint8_t i15, uint8_t i16, uint8_t i17, uint8_t i18, uint8_t i19,
             uint8_t i20, uint8_t i21, uint8_t i22, uint8_t i23, uint8_t i24,
             uint8_t i25, uint8_t i26, uint8_t i27, uint8_t i28, uint8_t i29,
             uint8_t i30, uint8_t i31, uint8_t i32, uint8_t i33, uint8_t i34,
             uint8_t i35, uint8_t i36, uint8_t i37, uint8_t i38, uint8_t i39,
             uint8_t i40, uint8_t i41, uint8_t i42, uint8_t i43, uint8_t i44,
             uint8_t i45, uint8_t i46, uint8_t i47, uint8_t i48, uint8_t i49,
             uint8_t i50, uint8_t i51, uint8_t i52, uint8_t i53, uint8_t i54,
             uint8_t i55, uint8_t i56, uint8_t i57, uint8_t i58, uint8_t i59,
             uint8_t i60, uint8_t i61, uint8_t i62, uint8_t i63)
{
    const uint8_t NPY_DECL_ALIGNED(64) data[64] = {
            i0,  i1,  i2,  i3,  i4,  i5,  i6,  i7,  i8,  i9,  i10, i11, i12,
            i13, i14, i15, i16, i17, i18, i19, i20, i21, i22, i23, i24, i25,
            i26, i27, i28, i29, i30, i31, i32, i33, i34, i35, i36, i37, i38,
            i39, i40, i41, i42, i43, i44, i45, i46, i47, i48, i49, i50, i51,
            i52, i53, i54, i55, i56, i57, i58, i59, i60, i61, i62, i63};
    return svld1_u8(svptrue_b8(), (const void *)data);
}

NPY_FINLINE npyv_s8
npyv__set_s8(int8_t i0, int8_t i1, int8_t i2, int8_t i3, int8_t i4, int8_t i5,
             int8_t i6, int8_t i7, int8_t i8, int8_t i9, int8_t i10,
             int8_t i11, int8_t i12, int8_t i13, int8_t i14, int8_t i15,
             int8_t i16, int8_t i17, int8_t i18, int8_t i19, int8_t i20,
             int8_t i21, int8_t i22, int8_t i23, int8_t i24, int8_t i25,
             int8_t i26, int8_t i27, int8_t i28, int8_t i29, int8_t i30,
             int8_t i31, int8_t i32, int8_t i33, int8_t i34, int8_t i35,
             int8_t i36, int8_t i37, int8_t i38, int8_t i39, int8_t i40,
             int8_t i41, int8_t i42, int8_t i43, int8_t i44, int8_t i45,
             int8_t i46, int8_t i47, int8_t i48, int8_t i49, int8_t i50,
             int8_t i51, int8_t i52, int8_t i53, int8_t i54, int8_t i55,
             int8_t i56, int8_t i57, int8_t i58, int8_t i59, int8_t i60,
             int8_t i61, int8_t i62, int8_t i63)
{
    const int8_t NPY_DECL_ALIGNED(64) data[64] = {
            i0,  i1,  i2,  i3,  i4,  i5,  i6,  i7,  i8,  i9,  i10, i11, i12,
            i13, i14, i15, i16, i17, i18, i19, i20, i21, i22, i23, i24, i25,
            i26, i27, i28, i29, i30, i31, i32, i33, i34, i35, i36, i37, i38,
            i39, i40, i41, i42, i43, i44, i45, i46, i47, i48, i49, i50, i51,
            i52, i53, i54, i55, i56, i57, i58, i59, i60, i61, i62, i63};
    return svld1_s8(svptrue_b8(), (const void *)data);
}

NPY_FINLINE npyv_s16
npyv__set_s16(int8_t i0, int8_t i1, int8_t i2, int8_t i3, int8_t i4, int8_t i5,
              int8_t i6, int8_t i7, int8_t i8, int8_t i9, int8_t i10,
              int8_t i11, int8_t i12, int8_t i13, int8_t i14, int8_t i15,
              int8_t i16, int8_t i17, int8_t i18, int8_t i19, int8_t i20,
              int8_t i21, int8_t i22, int8_t i23, int8_t i24, int8_t i25,
              int8_t i26, int8_t i27, int8_t i28, int8_t i29, int8_t i30,
              int8_t i31)
{
    const int8_t NPY_DECL_ALIGNED(64) data[64] = {
            i0, i1, i2,  i3,  i4,  i5,  i6,  i7,
            i8, i9, i10, i11, i12, i13, i14, i15,
    };

    return svld1_s16(svptrue_b16(), (const void *)data);
}

#define npyv_setf_u8(FILL, ...) \
    npyv__set_u8(NPYV__SET_FILL_16(npy_uint8, FILL, __VA_ARGS__))
#define npyv_setf_s8(FILL, ...) \
    npyv__set_s8(NPYV__SET_FILL_16(npy_int8, FILL, __VA_ARGS__))
#define npyv_setf_u16(FILL, ...) \
    npyv__set_u16(NPYV__SET_FILL_8(npy_uint16, FILL, __VA_ARGS__))

// Set mask for lane #0 - #(a-1)
#define NPYV_IMPL_SVE_SET_B(BITS) \
  NPY_FINLINE npyv_b ## BITS npyv_set_b ## BITS(int a) { \
    return svwhilelt_b ## BITS ## _s32(0, a);		 \
}
NPYV_IMPL_SVE_SET_B(8)
NPYV_IMPL_SVE_SET_B(16)
NPYV_IMPL_SVE_SET_B(32)
NPYV_IMPL_SVE_SET_B(64)

// Per lane select
#define npyv_select_u8 svsel_u8
#define npyv_select_s8 svsel_s8
#define npyv_select_u16 svsel_u16
#define npyv_select_s16 svsel_s16
#define npyv_select_u32 svsel_u32
#define npyv_select_s32 svsel_s32
#define npyv_select_u64 svsel_u64
#define npyv_select_s64 svsel_s64
#define npyv_select_f32 svsel_f32
#define npyv_select_f64 svsel_f64

// Reinterpret
#define npyv_reinterpret_u8_u8(X) X
#define npyv_reinterpret_u8_s8 svreinterpret_u8_s8
#define npyv_reinterpret_u8_u16 svreinterpret_u8_u16
#define npyv_reinterpret_u8_s16 svreinterpret_u8_s16
#define npyv_reinterpret_u8_u32 svreinterpret_u8_u32
#define npyv_reinterpret_u8_s32 svreinterpret_u8_s32
#define npyv_reinterpret_u8_u64 svreinterpret_u8_u64
#define npyv_reinterpret_u8_s64 svreinterpret_u8_s64
#define npyv_reinterpret_u8_f32 svreinterpret_u8_f32
#define npyv_reinterpret_u8_f64 svreinterpret_u8_f64

#define npyv_reinterpret_s8_s8(X) X
#define npyv_reinterpret_s8_u8 svreinterpret_s8_u8
#define npyv_reinterpret_s8_u16 svreinterpret_s8_u16
#define npyv_reinterpret_s8_s16 svreinterpret_s8_s16
#define npyv_reinterpret_s8_u32 svreinterpret_s8_u32
#define npyv_reinterpret_s8_s32 svreinterpret_s8_s32
#define npyv_reinterpret_s8_u64 svreinterpret_s8_u64
#define npyv_reinterpret_s8_s64 svreinterpret_s8_s64
#define npyv_reinterpret_s8_f32 svreinterpret_s8_f32
#define npyv_reinterpret_s8_f64 svreinterpret_s8_f64

#define npyv_reinterpret_u16_u16(X) X
#define npyv_reinterpret_u16_u8 svreinterpret_u16_u8
#define npyv_reinterpret_u16_s8 svreinterpret_u16_s8
#define npyv_reinterpret_u16_s16 svreinterpret_u16_s16
#define npyv_reinterpret_u16_u32 svreinterpret_u16_u32
#define npyv_reinterpret_u16_s32 svreinterpret_u16_s32
#define npyv_reinterpret_u16_u64 svreinterpret_u16_u64
#define npyv_reinterpret_u16_s64 svreinterpret_u16_s64
#define npyv_reinterpret_u16_f32 svreinterpret_u16_f32
#define npyv_reinterpret_u16_f64 svreinterpret_u16_f64

#define npyv_reinterpret_s16_s16(X) X
#define npyv_reinterpret_s16_u8 svreinterpret_s16_u8
#define npyv_reinterpret_s16_s8 svreinterpret_s16_s8
#define npyv_reinterpret_s16_u16 svreinterpret_s16_u16
#define npyv_reinterpret_s16_u32 svreinterpret_s16_u32
#define npyv_reinterpret_s16_s32 svreinterpret_s16_s32
#define npyv_reinterpret_s16_u64 svreinterpret_s16_u64
#define npyv_reinterpret_s16_s64 svreinterpret_s16_s64
#define npyv_reinterpret_s16_f32 svreinterpret_s16_f32
#define npyv_reinterpret_s16_f64 svreinterpret_s16_f64

#define npyv_reinterpret_u32_u32(X) X
#define npyv_reinterpret_u32_u8 svreinterpret_u32_u8
#define npyv_reinterpret_u32_s8 svreinterpret_u32_s8
#define npyv_reinterpret_u32_u16 svreinterpret_u32_u16
#define npyv_reinterpret_u32_s16 svreinterpret_u32_s16
#define npyv_reinterpret_u32_s32 svreinterpret_u32_s32
#define npyv_reinterpret_u32_u64 svreinterpret_u32_u64
#define npyv_reinterpret_u32_s64 svreinterpret_u32_s64
#define npyv_reinterpret_u32_f32 svreinterpret_u32_f32
#define npyv_reinterpret_u32_f64 svreinterpret_u32_f64

#define npyv_reinterpret_s32_s32(X) X
#define npyv_reinterpret_s32_u8 svreinterpret_s32_u8
#define npyv_reinterpret_s32_s8 svreinterpret_s32_s8
#define npyv_reinterpret_s32_u16 svreinterpret_s32_u16
#define npyv_reinterpret_s32_s16 svreinterpret_s32_s16
#define npyv_reinterpret_s32_u32 svreinterpret_s32_u32
#define npyv_reinterpret_s32_u64 svreinterpret_s32_u64
#define npyv_reinterpret_s32_s64 svreinterpret_s32_s64
#define npyv_reinterpret_s32_f32 svreinterpret_s32_f32
#define npyv_reinterpret_s32_f64 svreinterpret_s32_f64

#define npyv_reinterpret_u64_u64(X) X
#define npyv_reinterpret_u64_u8 svreinterpret_u64_u8
#define npyv_reinterpret_u64_s8 svreinterpret_u64_s8
#define npyv_reinterpret_u64_u16 svreinterpret_u64_u16
#define npyv_reinterpret_u64_s16 svreinterpret_u64_s16
#define npyv_reinterpret_u64_u32 svreinterpret_u64_u32
#define npyv_reinterpret_u64_s32 svreinterpret_u64_s32
#define npyv_reinterpret_u64_s64 svreinterpret_u64_s64
#define npyv_reinterpret_u64_f32 svreinterpret_u64_f32
#define npyv_reinterpret_u64_f64 svreinterpret_u64_f64

#define npyv_reinterpret_s64_s64(X) X
#define npyv_reinterpret_s64_u8 svreinterpret_s64_u8
#define npyv_reinterpret_s64_s8 svreinterpret_s64_s8
#define npyv_reinterpret_s64_u16 svreinterpret_s64_u16
#define npyv_reinterpret_s64_s16 svreinterpret_s64_s16
#define npyv_reinterpret_s64_u32 svreinterpret_s64_u32
#define npyv_reinterpret_s64_s32 svreinterpret_s64_s32
#define npyv_reinterpret_s64_u64 svreinterpret_s64_u64
#define npyv_reinterpret_s64_f32 svreinterpret_s64_f32
#define npyv_reinterpret_s64_f64 svreinterpret_s64_f64

#define npyv_reinterpret_f32_f32(X) X
#define npyv_reinterpret_f32_u8 svreinterpret_f32_u8
#define npyv_reinterpret_f32_s8 svreinterpret_f32_s8
#define npyv_reinterpret_f32_u16 svreinterpret_f32_u16
#define npyv_reinterpret_f32_s16 svreinterpret_f32_s16
#define npyv_reinterpret_f32_u32 svreinterpret_f32_u32
#define npyv_reinterpret_f32_s32 svreinterpret_f32_s32
#define npyv_reinterpret_f32_u64 svreinterpret_f32_u64
#define npyv_reinterpret_f32_s64 svreinterpret_f32_s64
#define npyv_reinterpret_f32_f64 svreinterpret_f32_f64

#define npyv_reinterpret_f64_f64(X) X
#define npyv_reinterpret_f64_u8 svreinterpret_f64_u8
#define npyv_reinterpret_f64_s8 svreinterpret_f64_s8
#define npyv_reinterpret_f64_u16 svreinterpret_f64_u16
#define npyv_reinterpret_f64_s16 svreinterpret_f64_s16
#define npyv_reinterpret_f64_u32 svreinterpret_f64_u32
#define npyv_reinterpret_f64_s32 svreinterpret_f64_s32
#define npyv_reinterpret_f64_u64 svreinterpret_f64_u64
#define npyv_reinterpret_f64_s64 svreinterpret_f64_s64
#define npyv_reinterpret_f64_f32 svreinterpret_f64_f32

// broadcast simd lane#0 to others
#define NPYV_IMPL_SVE_BROADCAST_LANE0(WIDTH, SIGN) \
NPY_FINLINE npyv_ ## SIGN ## WIDTH npyv_broadcast_lane0_ ## SIGN ## WIDTH (npyv_ ## SIGN ## WIDTH A) { \
    return svdup_lane_ ## SIGN ## WIDTH (A, 0); \
}

NPYV_IMPL_SVE_BROADCAST_LANE0(8, u)
NPYV_IMPL_SVE_BROADCAST_LANE0(16, u)
NPYV_IMPL_SVE_BROADCAST_LANE0(32, u)
NPYV_IMPL_SVE_BROADCAST_LANE0(64, u)
NPYV_IMPL_SVE_BROADCAST_LANE0(8, s)
NPYV_IMPL_SVE_BROADCAST_LANE0(16, s)
NPYV_IMPL_SVE_BROADCAST_LANE0(32, s)
NPYV_IMPL_SVE_BROADCAST_LANE0(64, s)
NPYV_IMPL_SVE_BROADCAST_LANE0(32, f)
NPYV_IMPL_SVE_BROADCAST_LANE0(64, f)

// get simd lane#0
#define NPYV_IMPL_SVE_GET_LANE0(WIDTH, SIGN, TYPE)				\
NPY_FINLINE npy_ ## TYPE ## WIDTH npyv__get_simd_lane0_ ## SIGN ## WIDTH (npyv_ ## SIGN ## WIDTH A) { \
 return svorv_ ## SIGN ## WIDTH (svptrue_pat_b ## WIDTH (SV_VL1), A); \
}

NPYV_IMPL_SVE_GET_LANE0(8, u, uint)
NPYV_IMPL_SVE_GET_LANE0(16, u, uint)
NPYV_IMPL_SVE_GET_LANE0(32, u, uint)
NPYV_IMPL_SVE_GET_LANE0(64, u, uint)
NPYV_IMPL_SVE_GET_LANE0(8, s, int)
NPYV_IMPL_SVE_GET_LANE0(16, s, int)
NPYV_IMPL_SVE_GET_LANE0(32, s, int)
NPYV_IMPL_SVE_GET_LANE0(64, s, int)

// Only required by AVX2/AVX512
#define npyv_cleanup() ((void)0)

#endif  // _NPY_SIMD_NEON_MISC_H
