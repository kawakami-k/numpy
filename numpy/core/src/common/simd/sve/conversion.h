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
SVE_CVT_MASK(f32, b32)
SVE_CVT_MASK(f64, b64)
#undef SVE_CVT_MASK

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
NPY_FINLINE npyv_u16x2
npyv_expand_u16_u8(npyv_u8 data)
{
    npyv_u16x2 r;
    r.val[0] = svunpklo_u16(data);
    r.val[1] = svunpkhi_u16(data);
    return r;
}

NPY_FINLINE npyv_u32x2
npyv_expand_u32_u16(npyv_u16 data)
{
    npyv_u32x2 r;
    r.val[0] = svunpklo_u32(data);
    r.val[1] = svunpkhi_u32(data);
    return r;
}

// pack two 16-bit boolean into one 8-bit boolean vector
NPY_FINLINE npyv_b8 npyv_pack_b8_b16(npyv_b16 a, npyv_b16 b) {
    a = svuzp1_b8(a, a);
    b = svuzp1_b8(b, b);
    svuint8_t z0 = svdup_n_u8_z(a, 1);
    svuint8_t z1 = svdup_n_u8_z(b, 1);
    z0 = svext_u8(z0, z0, npyv_nlanes_u8/2);
    z0 = svext_u8(z0, z1, npyv_nlanes_u8/2);
    return svcmpeq_n_u8(svptrue_b8(), z0, 1);
}

// pack four 32-bit boolean vectors into one 8-bit boolean vector
NPY_FINLINE npyv_b8
npyv_pack_b8_b32(npyv_b32 a, npyv_b32 b, npyv_b32 c, npyv_b32 d) {
  npyv_u8 buf;
  uint8_t *ptr = (uint8_t *)(&buf);

  svst1b_vnum_u32(svptrue_b32(), ptr, 0, svdup_n_u32_z(a, 1));
  svst1b_vnum_u32(svptrue_b32(), ptr, 1, svdup_n_u32_z(b, 1));
  svst1b_vnum_u32(svptrue_b32(), ptr, 2, svdup_n_u32_z(c, 1));
  svst1b_vnum_u32(svptrue_b32(), ptr, 3, svdup_n_u32_z(d, 1));

  svuint8_t z0 = svld1_u8(svptrue_b8(), ptr);
  return svcmpeq_n_u8(svptrue_b8(), z0, 1);
}

// pack eight 64-bit boolean vectors into one 8-bit boolean vector
NPY_FINLINE npyv_b8
npyv_pack_b8_b64(npyv_b64 a, npyv_b64 b, npyv_b64 c, npyv_b64 d,
                 npyv_b64 e, npyv_b64 f, npyv_b64 g, npyv_b64 h) {
  npyv_u8 buf;
  uint8_t *ptr = (uint8_t *)(&buf);

  svst1b_vnum_u64(svptrue_b64(), ptr, 0, svdup_n_u64_z(a, 1));
  svst1b_vnum_u64(svptrue_b64(), ptr, 1, svdup_n_u64_z(b, 1));
  svst1b_vnum_u64(svptrue_b64(), ptr, 2, svdup_n_u64_z(c, 1));
  svst1b_vnum_u64(svptrue_b64(), ptr, 3, svdup_n_u64_z(d, 1));
  svst1b_vnum_u64(svptrue_b64(), ptr, 4, svdup_n_u64_z(e, 1));
  svst1b_vnum_u64(svptrue_b64(), ptr, 5, svdup_n_u64_z(f, 1));
  svst1b_vnum_u64(svptrue_b64(), ptr, 6, svdup_n_u64_z(g, 1));
  svst1b_vnum_u64(svptrue_b64(), ptr, 7, svdup_n_u64_z(h, 1));

  svuint8_t z0 = svld1_u8(svptrue_b8(), ptr);
  return svcmpeq_n_u8(svptrue_b8(), z0, 1);
}

#define NPYV_IMPL_SVE_TOBIT(BITS)                                      \
    NPY_FINLINE npy_uint64 npyv_tobits_b##BITS(npyv_b##BITS a)         \
    {                                                                  \
        const svbool_t mask_all = svptrue_b##BITS();                   \
        /*uint ## BITS ## _t buf[NPY_SIMD_WIDTH/sizeof(uint ## BITS ## \
         * _t)];*/                                                     \
        /*  svuint ## BITS ## _t sh = svindex_u ## BITS (0, 1);	*/     \
        svuint##BITS##_t mask = svdup_n_u##BITS##_z(a, 0x1);           \
        return svorv_u##BITS(mask_all, mask);                          \
    }

NPY_FINLINE npy_uint64
npyv_tobits_b8(npyv_b8 A)
{
    const __pred mask_zero = svpfalse();
    const uint64_t len = svcntb();

    npyv_b8 l, h, l_l, l_h, h_l, h_h;
    npyv_b8 l_l_l, l_l_h, l_h_l, l_h_h, h_l_l, h_l_h, h_h_l, h_h_h;

    if (len >= 16) {
        l = svzip1_b8(A, mask_zero);
        h = svzip2_b8(A, mask_zero);
    }
    if (len >= 32) {
        l_l = svzip1_b8(l, mask_zero);
        l_h = svzip2_b8(l, mask_zero);
        h_l = svzip1_b8(h, mask_zero);
        h_h = svzip2_b8(h, mask_zero);
    }
    if (len >= 64) {
        l_l_l = svzip1_b8(l_l, mask_zero);
        l_l_h = svzip2_b8(l_l, mask_zero);
        l_h_l = svzip1_b8(l_h, mask_zero);
        l_h_h = svzip2_b8(l_h, mask_zero);
        h_l_l = svzip1_b8(h_l, mask_zero);
        h_l_h = svzip2_b8(h_l, mask_zero);
        h_h_l = svzip1_b8(h_h, mask_zero);
        h_h_h = svzip2_b8(h_h, mask_zero);
    }

    switch (len) {
        case 16: {
            const npyv_u16 one = svdup_u16(1);
            npyv_u16 idx0 = svindex_u16(0, 1);
            npyv_u16 idx1 = svindex_u16(8, 1);
            idx0 = svlsl_u16_x(svptrue_b16(), one, idx0);
            idx1 = svlsl_u16_x(svptrue_b16(), one, idx1);
            uint64_t retVal = svorv_u16(l, idx0);
            retVal |= svorv_u16(h, idx1);
            return retVal;
        }
        case 32: {
            const npyv_u32 one = svdup_u32(1);
            npyv_u32 idx0 = svindex_u32(0, 1);
            npyv_u32 idx1 = svindex_u32(8, 1);
            npyv_u32 idx2 = svindex_u32(16, 1);
            npyv_u32 idx3 = svindex_u32(24, 1);
            idx0 = svlsl_u32_x(svptrue_b32(), one, idx0);
            idx1 = svlsl_u32_x(svptrue_b32(), one, idx1);
            idx2 = svlsl_u32_x(svptrue_b32(), one, idx2);
            idx3 = svlsl_u32_x(svptrue_b32(), one, idx3);
            uint64_t retVal = svorv_u32(l_l, idx0);
            retVal |= svorv_u32(l_h, idx1);
            retVal |= svorv_u32(h_l, idx2);
            retVal |= svorv_u32(h_h, idx3);
            return retVal;
        }
        case 64: {
            const npyv_u64 one = svdup_u64(1);
            npyv_u64 idx0 = svindex_u64(0, 1);
            npyv_u64 idx1 = svindex_u64(8, 1);
            npyv_u64 idx2 = svindex_u64(16, 1);
            npyv_u64 idx3 = svindex_u64(24, 1);
            npyv_u64 idx4 = svindex_u64(32, 1);
            npyv_u64 idx5 = svindex_u64(40, 1);
            npyv_u64 idx6 = svindex_u64(48, 1);
            npyv_u64 idx7 = svindex_u64(56, 1);
            idx0 = svlsl_u64_x(svptrue_b64(), one, idx0);
            idx1 = svlsl_u64_x(svptrue_b64(), one, idx1);
            idx2 = svlsl_u64_x(svptrue_b64(), one, idx2);
            idx3 = svlsl_u64_x(svptrue_b64(), one, idx3);
            idx4 = svlsl_u64_x(svptrue_b64(), one, idx4);
            idx5 = svlsl_u64_x(svptrue_b64(), one, idx5);
            idx6 = svlsl_u64_x(svptrue_b64(), one, idx6);
            idx7 = svlsl_u64_x(svptrue_b64(), one, idx7);
            uint64_t retVal = svorv_u64(l_l_l, idx0);
            retVal |= svorv_u64(l_l_h, idx1);
            retVal |= svorv_u64(l_h_l, idx2);
            retVal |= svorv_u64(l_h_h, idx3);
            retVal |= svorv_u64(h_l_l, idx4);
            retVal |= svorv_u64(h_l_h, idx5);
            retVal |= svorv_u64(h_h_l, idx6);
            retVal |= svorv_u64(h_h_h, idx7);
            return retVal;
        }
        default:
            assert(!"unsupported SVE size!");
    }

    return 0;
}

NPY_FINLINE npy_uint64
npyv_tobits_b16(npyv_b16 A)
{
    const uint64_t len = svcntb();

    switch (len) {
        case 16:
        case 32: {
            const npyv_u16 one = svdup_u16(1);
            npyv_u16 idx = svindex_u16(0, 1);
            idx = svlsl_u16_x(svptrue_b16(), one, idx);
            uint64_t retVal = svorv_u16(A, idx);
            return retVal;
        }
        case 64: {
            const npyv_b16 mask_zero = svpfalse();
            const npyv_u32 one = svdup_u32(1);
            npyv_b16 l = svzip1_b16(A, mask_zero);
            npyv_b16 h = svzip1_b16(A, mask_zero);
            npyv_u32 idx0 = svindex_u32(0, 1);
            npyv_u32 idx1 = svindex_u32(16, 1);
            idx0 = svlsl_u32_x(svptrue_b32(), one, idx0);
            idx1 = svlsl_u32_x(svptrue_b32(), one, idx1);
            uint64_t retVal = svorv_u32(l, idx0);
            retVal |= svorv_u32(h, idx1);
            return retVal;
        }
        default:
            assert(!"unsupported SVE size!");
    }

    return 0;
}

NPY_FINLINE npy_uint64
npyv_tobits_b32(npyv_b32 A)
{
    const npyv_u32 one = svdup_u32(1);
    npyv_u32 idx = svindex_u32(0, 1);
    idx = svlsl_u32_x(svptrue_b32(), one, idx);
    return svorv_u32(A, idx);
}

NPY_FINLINE npy_uint64
npyv_tobits_b64(npyv_b64 A)
{
    const npyv_u64 one = svdup_u64(1);
    npyv_u64 idx = svindex_u64(0, 1);
    idx = svlsl_u64_x(svptrue_b64(), one, idx);
    return svorv_u64(A, idx);
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
    return svuzp1_s32(a_cvt, b_cvt);
}

#endif  // _NPY_SIMD_SVE_CVT_H
