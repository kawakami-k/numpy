#ifndef NPY_SIMD
    #error "Not a standalone header"
#endif

#ifndef _NPY_SIMD_SVE_REORDER_H
#define _NPY_SIMD_SVE_REORDER_H

// combine lower part of two vectors
#define NPYV_IMPL_SVE_COMBINEL(TYPE, SIGN, BITS, VL)			\
NPY_FINLINE npyv_ ## SIGN ## BITS npyv_combinel_ ## SIGN ## BITS (npyv_ ## SIGN ## BITS a, npyv_ ## SIGN ## BITS b) \
{ \
  sv ## TYPE t = svext_ ## SIGN ## BITS (b, b, NPY_SIMD_WIDTH/sizeof(TYPE)/2); \
  return svsel_ ## SIGN ## BITS (svptrue_pat_b ## BITS (VL), a, t); \
}

NPYV_IMPL_SVE_COMBINEL(uint8_t, u, 8, SV_VL32)
NPYV_IMPL_SVE_COMBINEL(uint16_t, u, 16, SV_VL16)
NPYV_IMPL_SVE_COMBINEL(uint32_t, u, 32, SV_VL8)
NPYV_IMPL_SVE_COMBINEL(uint64_t, u, 64, SV_VL4)
NPYV_IMPL_SVE_COMBINEL(int8_t, s, 8, SV_VL32)
NPYV_IMPL_SVE_COMBINEL(int16_t, s, 16, SV_VL16)
NPYV_IMPL_SVE_COMBINEL(int32_t, s, 32, SV_VL8)
NPYV_IMPL_SVE_COMBINEL(int64_t, s, 64, SV_VL4)
NPYV_IMPL_SVE_COMBINEL(float32_t, f, 32, SV_VL8)
NPYV_IMPL_SVE_COMBINEL(float64_t, f, 64, SV_VL4)

// combine higher part of two vectors
#define NPYV_IMPL_SVE_COMBINEH(TYPE, SIGN, BITS, VL)			\
NPY_FINLINE npyv_ ## SIGN ## BITS npyv_combineh_ ## SIGN ## BITS (npyv_ ## SIGN ## BITS a, npyv_ ## SIGN ## BITS b) \
{ \
  sv ## TYPE t = svext_ ## SIGN ## BITS (a, a, NPY_SIMD_WIDTH/sizeof(TYPE)/2); \
  return svsel_ ## SIGN ## BITS (svptrue_pat_b ## BITS (VL), t, b); \
}

NPYV_IMPL_SVE_COMBINEH(uint8_t, u, 8, SV_VL32)
NPYV_IMPL_SVE_COMBINEH(uint16_t, u, 16, SV_VL16)
NPYV_IMPL_SVE_COMBINEH(uint32_t, u, 32, SV_VL8)
NPYV_IMPL_SVE_COMBINEH(uint64_t, u, 64, SV_VL4)
NPYV_IMPL_SVE_COMBINEH(int8_t, s, 8, SV_VL32)
NPYV_IMPL_SVE_COMBINEH(int16_t, s, 16, SV_VL16)
NPYV_IMPL_SVE_COMBINEH(int32_t, s, 32, SV_VL8)
NPYV_IMPL_SVE_COMBINEH(int64_t, s, 64, SV_VL4)
NPYV_IMPL_SVE_COMBINEH(float32_t, f, 32, SV_VL8)
NPYV_IMPL_SVE_COMBINEH(float64_t, f, 64, SV_VL4)

// combine two vectors from lower and higher parts of two other vectors
#define NPYV_IMPL_SVE_COMBINE(SIGN, BITS) \
  NPY_FINLINE npyv_ ## SIGN ## BITS ## x2 npyv_combine_ ## SIGN ## BITS (npyv_ ## SIGN ## BITS a, npyv_ ## SIGN ## BITS b) \
{						\
  npyv_ ## SIGN ## BITS ## x2 r = svundef2_ ## SIGN ## BITS (); \
  r = svset2_ ## SIGN ## BITS (r, 0, npyv_combinel_ ## SIGN ## BITS (a, b)); \
  r = svset2_ ## SIGN ## BITS (r, 1, npyv_combineh_ ## SIGN ## BITS (a, b)); \
  return r; \
}

NPYV_IMPL_SVE_COMBINE(u, 8)
NPYV_IMPL_SVE_COMBINE(u, 16)
NPYV_IMPL_SVE_COMBINE(u, 32)
NPYV_IMPL_SVE_COMBINE(u, 64)
NPYV_IMPL_SVE_COMBINE(s, 8)
NPYV_IMPL_SVE_COMBINE(s, 16)
NPYV_IMPL_SVE_COMBINE(s, 32)
NPYV_IMPL_SVE_COMBINE(s, 64)
NPYV_IMPL_SVE_COMBINE(f, 32)
NPYV_IMPL_SVE_COMBINE(f, 64)

// interleave two vectors
#define NPYV_IMPL_SVE_ZIP(TYPE, SIGN, BITS) \
NPY_FINLINE npyv_ ## SIGN ## BITS ## x2 npyv_zip_ ## SIGN ## BITS (npyv_ ## SIGN ## BITS a, npyv_ ## SIGN ## BITS b) \
{ \
    npyv_ ## SIGN ## BITS ## x2 r = svundef2_ ## SIGN ## BITS (); \
    r = svset2_ ## SIGN ## BITS (r, 0, svzip1_ ## SIGN ## BITS (a, b)); \
    sv ## TYPE t0 = svext_ ## SIGN ## BITS (a, a, NPY_SIMD_WIDTH/sizeof(TYPE)/2); \
    sv ## TYPE t1 = svext_ ## SIGN ## BITS (b, b, NPY_SIMD_WIDTH/sizeof(TYPE)/2); \
    r = svset2_  ## SIGN ## BITS (r, 1, svzip1_  ## SIGN ## BITS (t0, t1)); \
    return r; \
}

NPYV_IMPL_SVE_ZIP(uint8_t, u, 8)
NPYV_IMPL_SVE_ZIP(uint16_t, u, 16)
NPYV_IMPL_SVE_ZIP(uint32_t, u, 32)
NPYV_IMPL_SVE_ZIP(uint64_t, u, 64)
NPYV_IMPL_SVE_ZIP(int8_t, s, 8)
NPYV_IMPL_SVE_ZIP(int16_t, s, 16)
NPYV_IMPL_SVE_ZIP(int32_t, s, 32)
NPYV_IMPL_SVE_ZIP(int64_t, s, 64)
NPYV_IMPL_SVE_ZIP(float32_t, f, 32)
NPYV_IMPL_SVE_ZIP(float64_t, f, 64)

// Reverse elements of each 64-bit lane
#define npyv_rev64_u8 svrev_u8
#define npyv_rev64_u16 svrev_u16
#define npyv_rev64_u32 svrev_u32
#define npyv_rev64_u64 svrev_u64
#define npyv_rev64_s8 svrev_s8
#define npyv_rev64_s16 svrev_s16
#define npyv_rev64_s32 svrev_s32
#define npyv_rev64_s64 svrev_sa64

#endif // _NPY_SIMD_SVE_REORDER_H
