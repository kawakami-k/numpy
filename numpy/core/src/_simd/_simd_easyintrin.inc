/**
 * This file is included by `_simd.dispatch.c.src`. Its contents are affected by the simd configuration, and
 * therefore must be built multiple times. Making it a standalone `.c` file with `NPY_VISIBILITY_HIDDEN`
 * symbols would require judicious use of `NPY_CPU_DISPATCH_DECLARE` and `NPY_CPU_DISPATCH_CURFX`, which was
 * deemed too harmful to readability.
 */
#define SIMD_INTRIN_DEF(NAME) \
    { NPY_TOSTRING(NAME), simd__intrin_##NAME, METH_VARARGS, NULL } , // comma

#ifndef NPY_HAVE_SVE
#define SIMD_IMPL_INTRIN_0(NAME, RET, VAL)                \
    static PyObject *simd__intrin_##NAME                  \
    (PyObject* NPY_UNUSED(self), PyObject *args)          \
    {                                                     \
        if (!PyArg_ParseTuple(                            \
            args, ":" NPY_TOSTRING(NAME))                 \
        ) return NULL;                                    \
        simd_arg a = {                                    \
            .dtype = simd_data_##RET,                     \
            .data  = {.RET = npyv_##NAME()},              \
        };                                                \
        return simd_arg_to_obj(&a);                       \
    }
#else
#define SIMD_IMPL_INTRIN_0(NAME, RET, VAL)                \
    static PyObject *simd__intrin_##NAME                  \
    (PyObject* NPY_UNUSED(self), PyObject *args)          \
    {                                                     \
        if (!PyArg_ParseTuple(                            \
            args, ":" NPY_TOSTRING(NAME))                 \
        ) return NULL;                                    \
        simd_arg a = {                                    \
            .dtype = simd_data_##RET,                     \
        };                                                \
        memset(&(a.data), VAL, NPY_SIMD_WIDTH);           \
        return simd_arg_to_obj(&a);                       \
    }
#endif

#define SIMD_IMPL_INTRIN_0N(NAME)                         \
    static PyObject *simd__intrin_##NAME                  \
    (PyObject* NPY_UNUSED(self), PyObject *args)          \
    {                                                     \
        if (!PyArg_ParseTuple(                            \
            args, ":" NPY_TOSTRING(NAME))                 \
        ) return NULL;                                    \
        npyv_##NAME();                                    \
        Py_RETURN_NONE;                                   \
    }

#ifndef NPY_HAVE_SVE
#define SIMD_IMPL_INTRIN_1(NAME, RET, IN0)                \
    static PyObject *simd__intrin_##NAME                  \
    (PyObject* NPY_UNUSED(self), PyObject *args)          \
    {                                                     \
        simd_arg arg = {.dtype = simd_data_##IN0};        \
        if (!PyArg_ParseTuple(                            \
            args, "O&:"NPY_TOSTRING(NAME),                \
            simd_arg_converter, &arg                      \
        )) return NULL;                                   \
        simd_data data = {.RET = npyv_##NAME(             \
            arg.data.IN0                                  \
        )};                                               \
        simd_arg_free(&arg);                              \
        simd_arg ret = {                                  \
            .data = data, .dtype = simd_data_##RET        \
        };                                                \
        return simd_arg_to_obj(&ret);                     \
    }
#else
#define SIMD_IMPL_INTRIN_1(NAME, RET, IN0, TYPE, SIGN, BITS)                \
    static PyObject *simd__intrin_##NAME                  \
    (PyObject* NPY_UNUSED(self), PyObject *args)          \
    {                                                     \
        simd_arg arg = {.dtype = simd_data_##IN0};        \
        if (!PyArg_ParseTuple(                            \
            args, "O&:"NPY_TOSTRING(NAME),                \
            simd_arg_converter, &arg                      \
        )) return NULL;                                   \
        simd_data data;                                   \
        sv##TYPE##_t t = svld1_##SIGN##BITS(svptrue_b##BITS(), (npyv_lanetype_##SIGN##BITS *) &arg.data.IN0);  \
	sv##TYPE##_t r = npyv_##NAME(t);                  \
        svst1_##SIGN##BITS(svptrue_b##BITS(), (npyv_lanetype_##SIGN##BITS *) &data, r); \
        simd_arg_free(&arg);                              \
        simd_arg ret = {                                  \
            .data = data, .dtype = simd_data_##RET        \
        };                                                \
        return simd_arg_to_obj(&ret);                     \
    }
#define SIMD_IMPL_INTRIN_1_TOBITS(NAME, RET, IN0, TYPE, SIGN, BITS)                \
    static PyObject *simd__intrin_##NAME                  \
    (PyObject* NPY_UNUSED(self), PyObject *args)          \
    {                                                     \
        simd_arg arg = {.dtype = simd_data_##IN0};        \
        if (!PyArg_ParseTuple(                            \
            args, "O&:"NPY_TOSTRING(NAME),                \
            simd_arg_converter, &arg                      \
        )) return NULL;                                   \
        simd_data data;                                   \
        sv##TYPE##_t t = svld1_##SIGN##BITS(svptrue_b##BITS(), (npyv_lanetype_##SIGN##BITS *) &arg.data.IN0);  \
	sv##TYPE##_t r = npyv_##NAME(t);                  \
        svst1_##SIGN##BITS(svptrue_b##BITS(), (npyv_lanetype_##SIGN##BITS *) &data, r); \
        simd_arg_free(&arg);                              \
        simd_arg ret = {                                  \
            .data = data, .dtype = simd_data_##RET        \
        };                                                \
        return simd_arg_to_obj(&ret);                     \
    }
#define SIMD_IMPL_INTRIN_1_NOT(NAME, RET, IN0, TYPE, SIGN, BITS)                \
    static PyObject *simd__intrin_##NAME                  \
    (PyObject* NPY_UNUSED(self), PyObject *args)          \
    {                                                     \
        simd_arg arg = {.dtype = simd_data_##IN0};        \
        if (!PyArg_ParseTuple(                            \
            args, "O&:"NPY_TOSTRING(NAME),                \
            simd_arg_converter, &arg                      \
        )) return NULL;                                   \
        simd_data data;                                   \
        sv##TYPE##_t t = svld1_##SIGN##BITS(svptrue_b##BITS(), (npyv_lanetype_##SIGN##BITS *) &arg.data.IN0);  \
	sv##TYPE##_t r = npyv_##NAME(t);                  \
        svst1_##SIGN##BITS(svptrue_b##BITS(), (npyv_lanetype_##SIGN##BITS *) &data, r); \
        simd_arg_free(&arg);                              \
        simd_arg ret = {                                  \
            .data = data, .dtype = simd_data_##RET        \
        };                                                \
        return simd_arg_to_obj(&ret);                     \
    }
#define SIMD_IMPL_INTRIN_1_SUM(NAME, RET, IN0, TYPE, SIGN, BITS)                \
    static PyObject *simd__intrin_##NAME                  \
    (PyObject* NPY_UNUSED(self), PyObject *args)          \
    {                                                     \
        simd_arg arg = {.dtype = simd_data_##IN0};        \
        if (!PyArg_ParseTuple(                            \
            args, "O&:"NPY_TOSTRING(NAME),                \
            simd_arg_converter, &arg                      \
        )) return NULL;                                   \
        sv##TYPE##_t t = svld1_##SIGN##BITS(svptrue_b##BITS(), (npyv_lanetype_##SIGN##BITS *) &arg.data.IN0);  \
        simd_data data = {.RET = npyv_##NAME(t)};         \
        simd_arg_free(&arg);                              \
        simd_arg ret = {                                  \
            .data = data, .dtype = simd_data_##RET        \
        };                                                \
        return simd_arg_to_obj(&ret);                     \
    }
#define SIMD_IMPL_INTRIN_1_LD(NAME, RET, IN0, TYPE, SIGN, BITS, DIV)             \
    static PyObject *simd__intrin_##NAME                  \
    (PyObject* NPY_UNUSED(self), PyObject *args)          \
    {                                                     \
        simd_arg arg = {.dtype = simd_data_##IN0};        \
        if (!PyArg_ParseTuple(                            \
            args, "O&:"NPY_TOSTRING(NAME),                \
            simd_arg_converter, &arg                      \
        )) return NULL;                                   \
        simd_data data;                                   \
	for(int i=0; i<npyv_nlanes_##SIGN##BITS/DIV; i++)     \
            ((npyv_lanetype_##SIGN##BITS *) &data)[i] = ((npyv_lanetype_##SIGN##BITS *) arg.data.IN0)[i]; \
        simd_arg_free(&arg);                              \
        simd_arg ret = {                                  \
            .data = data, .dtype = simd_data_##RET        \
        };                                                \
        return simd_arg_to_obj(&ret);                     \
    }
#define SIMD_IMPL_INTRIN_1_LD_L(NAME, RET, IN0, TYPE, SIGN, BITS, DIV)             \
    static PyObject *simd__intrin_##NAME                  \
    (PyObject* NPY_UNUSED(self), PyObject *args)          \
    {                                                     \
        simd_arg arg = {.dtype = simd_data_##IN0};        \
        if (!PyArg_ParseTuple(                            \
            args, "O&:"NPY_TOSTRING(NAME),                \
            simd_arg_converter, &arg                      \
        )) return NULL;                                   \
        simd_data data;                                   \
	for(int i=0; i<npyv_nlanes_##SIGN##BITS/DIV; i++)     \
            ((npyv_lanetype_##SIGN##BITS *) &data)[i] = ((npyv_lanetype_##SIGN##BITS *) &arg.data.IN0)[i]; \
        simd_arg_free(&arg);                              \
        simd_arg ret = {                                  \
            .data = data, .dtype = simd_data_##RET        \
        };                                                \
        return simd_arg_to_obj(&ret);                     \
    }
#define SIMD_IMPL_INTRIN_1_SETALL(NAME, RET, IN0, TYPE, SIGN, BITS)                \
    static PyObject *simd__intrin_##NAME                  \
    (PyObject* NPY_UNUSED(self), PyObject *args)          \
    {                                                     \
        simd_arg arg = {.dtype = simd_data_##IN0};        \
        if (!PyArg_ParseTuple(                            \
            args, "O&:"NPY_TOSTRING(NAME),                \
            simd_arg_converter, &arg                      \
        )) return NULL;                                   \
        simd_data data;                                   \
        sv##TYPE##_t t = npyv_##NAME(arg.data.IN0);       \
        svst1_##SIGN##BITS(svptrue_b##BITS(), (npyv_lanetype_##SIGN##BITS *) &data, t); \
        simd_arg_free(&arg);                              \
        simd_arg ret = {                                  \
            .data = data, .dtype = simd_data_##RET        \
        };                                                \
        return simd_arg_to_obj(&ret);                     \
    }
#endif

#ifndef NPY_HAVE_SVE
#define SIMD_IMPL_INTRIN_2(NAME, RET, IN0, IN1)           \
    static PyObject *simd__intrin_##NAME                  \
    (PyObject* NPY_UNUSED(self), PyObject *args)          \
    {                                                     \
        simd_arg arg1 = {.dtype = simd_data_##IN0};       \
        simd_arg arg2 = {.dtype = simd_data_##IN1};       \
        if (!PyArg_ParseTuple(                            \
            args, "O&O&:"NPY_TOSTRING(NAME),              \
            simd_arg_converter, &arg1,                    \
            simd_arg_converter, &arg2                     \
        )) return NULL;                                   \
        simd_data data = {.RET = npyv_##NAME(             \
            arg1.data.IN0, arg2.data.IN1                  \
        )};                                               \
        simd_arg_free(&arg1);                             \
        simd_arg_free(&arg2);                             \
        simd_arg ret = {                                  \
            .data = data, .dtype = simd_data_##RET        \
        };                                                \
        return simd_arg_to_obj(&ret);                     \
    }
#else
#define SIMD_IMPL_INTRIN_2(NAME, RET, IN0, IN1, TYPE, SIGN, BITS)  \
    static PyObject *simd__intrin_##NAME                  \
    (PyObject* NPY_UNUSED(self), PyObject *args)          \
    {                                                     \
        simd_arg arg1 = {.dtype = simd_data_##IN0};       \
        simd_arg arg2 = {.dtype = simd_data_##IN1};       \
        if (!PyArg_ParseTuple(                            \
            args, "O&O&:"NPY_TOSTRING(NAME),              \
            simd_arg_converter, &arg1,                    \
            simd_arg_converter, &arg2                     \
        )) return NULL;                                   \
        sv##TYPE##_t buf1 = svld1_##SIGN##BITS(svptrue_b##BITS(), (npyv_lanetype_##SIGN##BITS *) &arg1.data.IN0); \
        sv##TYPE##_t buf2 = svld1_##SIGN##BITS(svptrue_b##BITS(), (npyv_lanetype_##SIGN##BITS *) &arg2.data.IN1); \
	sv##TYPE##_t r = npyv_##NAME(buf1, buf2); \
        simd_data data; \
	svst1_##SIGN##BITS (svptrue_b##BITS(), (npyv_lanetype_##SIGN##BITS *) &data, r); \
        simd_arg_free(&arg1);                             \
        simd_arg_free(&arg2);                             \
        simd_arg ret = {                                  \
            .data = data, .dtype = simd_data_##RET        \
        };                                                \
        return simd_arg_to_obj(&ret);                     \
    }

#define SIMD_IMPL_INTRIN_2_LD(NAME, RET, IN0, IN1, TYPE, SIGN, BITS)  \
    static PyObject *simd__intrin_##NAME                  \
    (PyObject* NPY_UNUSED(self), PyObject *args)          \
    {                                                     \
        simd_arg arg1 = {.dtype = simd_data_##IN0};       \
        simd_arg arg2 = {.dtype = simd_data_##IN1};       \
        if (!PyArg_ParseTuple(                            \
            args, "O&O&:"NPY_TOSTRING(NAME),              \
            simd_arg_converter, &arg1,                    \
            simd_arg_converter, &arg2                     \
        )) return NULL;                                   \
        simd_data data; \
	sv##TYPE##_t r = npyv_##NAME((npyv_lanetype_##SIGN##BITS *) arg1.data.IN0, arg2.data.IN1); \
	svst1_##SIGN##BITS(svptrue_b##BITS(), (npyv_lanetype_##SIGN##BITS *) &data, r); \
        simd_arg_free(&arg1);                             \
        simd_arg_free(&arg2);                             \
        simd_arg ret = {                                  \
            .data = data, .dtype = simd_data_##RET        \
        };                                                \
        return simd_arg_to_obj(&ret);                     \
    }

#define SIMD_IMPL_INTRIN_2_LUT(NAME, RET, IN0, IN1, TYPE, SIGN, BITS)  \
    static PyObject *simd__intrin_##NAME                  \
    (PyObject* NPY_UNUSED(self), PyObject *args)          \
    {                                                     \
        simd_arg arg1 = {.dtype = simd_data_##IN0};       \
        simd_arg arg2 = {.dtype = simd_data_##IN1};       \
        if (!PyArg_ParseTuple(                            \
            args, "O&O&:"NPY_TOSTRING(NAME),              \
            simd_arg_converter, &arg1,                    \
            simd_arg_converter, &arg2                     \
        )) return NULL;                                   \
        simd_data data; \
	sv##TYPE##_t t = svld1_##SIGN##BITS(svptrue_b##BITS(), (npyv_lanetype_##SIGN##BITS *) &arg2.data.IN1); \
	sv##TYPE##_t r = npyv_##NAME((npyv_lanetype_##SIGN##BITS *) arg1.data.IN0, svreinterpret_u##BITS##_##SIGN##BITS(t)); \
	svst1_##SIGN##BITS(svptrue_b##BITS(), (npyv_lanetype_##SIGN##BITS *) &data, r); \
        simd_arg_free(&arg1);                             \
        simd_arg_free(&arg2);                             \
        simd_arg ret = {                                  \
            .data = data, .dtype = simd_data_##RET        \
        };                                                \
        return simd_arg_to_obj(&ret);                     \
    }

#define SIMD_IMPL_INTRIN_2_MASK(NAME, RET, IN0, IN1, TYPE, SIGN, BITS)  \
    static PyObject *simd__intrin_##NAME                  \
    (PyObject* NPY_UNUSED(self), PyObject *args)          \
    {                                                     \
        simd_arg arg1 = {.dtype = simd_data_##IN0};       \
        simd_arg arg2 = {.dtype = simd_data_##IN1};       \
        if (!PyArg_ParseTuple(                            \
            args, "O&O&:"NPY_TOSTRING(NAME),              \
            simd_arg_converter, &arg1,                    \
            simd_arg_converter, &arg2                     \
        )) return NULL;                                   \
        sv##TYPE##_t buf1 = svld1_##SIGN##BITS(svptrue_b ## BITS(), (npyv_lanetype_##SIGN##BITS *) &arg1.data.IN0); \
        sv##TYPE##_t buf2 = svld1_##SIGN##BITS(svptrue_b ## BITS(), (npyv_lanetype_##SIGN##BITS *) &arg2.data.IN1); \
	svuint##BITS##_t r = npyv_cvt_u##BITS##_b##BITS(npyv_##NAME(buf1, buf2)); \
        simd_data data; \
	svst1_u##BITS (svptrue_b##BITS(), (npyv_lanetype_u##BITS *) &data, r); \
        simd_arg_free(&arg1);                             \
        simd_arg_free(&arg2);                             \
        simd_arg ret = {                                  \
            .data = data, .dtype = simd_data_##RET        \
        };                                                \
        return simd_arg_to_obj(&ret);                     \
    }

#define SIMD_IMPL_INTRIN_2_DIVC(NAME, RET, IN0, IN1, TYPE, SIGN, BITS)  \
    static PyObject *simd__intrin_##NAME                  \
    (PyObject* NPY_UNUSED(self), PyObject *args)          \
    {                                                     \
        simd_arg arg1 = {.dtype = simd_data_##IN0};       \
        simd_arg arg2 = {.dtype = simd_data_##IN1};       \
        if (!PyArg_ParseTuple(                            \
            args, "O&O&:"NPY_TOSTRING(NAME),              \
            simd_arg_converter, &arg1,                    \
            simd_arg_converter, &arg2                     \
        )) return NULL;                                   \
        sv##TYPE##_t buf1 = svld1_##SIGN##BITS(svptrue_b ## BITS(), (npyv_lanetype_##SIGN##BITS *) &arg1.data.IN0); \
        sv##TYPE##_t buf2_0 = svld1_##SIGN##BITS(svptrue_b ## BITS(), (npyv_lanetype_##SIGN##BITS *) &arg2.data.IN1.val[0]); \
        sv##TYPE##_t buf2_1 = svld1_##SIGN##BITS(svptrue_b ## BITS(), (npyv_lanetype_##SIGN##BITS *) &arg2.data.IN1.val[1]); \
        sv##TYPE##_t buf2_2 = svld1_##SIGN##BITS(svptrue_b ## BITS(), (npyv_lanetype_##SIGN##BITS *) &arg2.data.IN1.val[2]); \
	sv##TYPE##x3_t buf2 = svcreate3_##SIGN##BITS(buf2_0, buf2_1, buf2_2); \
	sv##TYPE##_t r = npyv_##NAME(buf1, buf2); \
        simd_data data; \
	svst1_##SIGN##BITS (svptrue_b##BITS(), (npyv_lanetype_##SIGN##BITS *) &data, r); \
        simd_arg_free(&arg1);                             \
        simd_arg_free(&arg2);                             \
        simd_arg ret = {                                  \
            .data = data, .dtype = simd_data_##RET        \
        };                                                \
        return simd_arg_to_obj(&ret);                     \
    }

#define SIMD_IMPL_INTRIN_X2_2(NAME, RET, IN0, IN1, TYPE, SIGN, BITS)  \
    static PyObject *simd__intrin_##NAME                  \
    (PyObject* NPY_UNUSED(self), PyObject *args)          \
    {                                                     \
        simd_arg arg1 = {.dtype = simd_data_##IN0};       \
        simd_arg arg2 = {.dtype = simd_data_##IN1};       \
        if (!PyArg_ParseTuple(                            \
            args, "O&O&:"NPY_TOSTRING(NAME),              \
            simd_arg_converter, &arg1,                    \
            simd_arg_converter, &arg2                     \
        )) return NULL;                                   \
        sv##TYPE##_t buf1 = svld1_##SIGN##BITS(svptrue_b ## BITS(), (npyv_lanetype_##SIGN##BITS *) &arg1.data.IN0); \
        sv##TYPE##_t buf2 = svld1_##SIGN##BITS(svptrue_b ## BITS(), (npyv_lanetype_##SIGN##BITS *) &arg2.data.IN1); \
	sv##TYPE##x2_t r = npyv_##NAME(buf1, buf2); \
        simd_data data; \
	svst1_##SIGN##BITS(svptrue_b##BITS(), (npyv_lanetype_##SIGN##BITS *) &(data.v##SIGN##BITS##x2.val[0]), svget2_##SIGN##BITS(r, 0)); \
	svst1_##SIGN##BITS(svptrue_b##BITS(), (npyv_lanetype_##SIGN##BITS *) &(data.v##SIGN##BITS##x2.val[1]), svget2_##SIGN##BITS(r, 1)); \
        simd_arg_free(&arg1);                             \
        simd_arg_free(&arg2);                             \
        simd_arg ret = {                                  \
            .data = data, .dtype = simd_data_##RET        \
        };                                                \
        return simd_arg_to_obj(&ret);                     \
    }

#define SIMD_IMPL_INTRIN_B_2(NAME, RET, IN0, IN1, TYPE, SIGN, BITS)  \
    static PyObject *simd__intrin_##NAME##_b##BITS        \
    (PyObject* NPY_UNUSED(self), PyObject *args)          \
    {                                                     \
        simd_arg arg1 = {.dtype = simd_data_##IN0};       \
        simd_arg arg2 = {.dtype = simd_data_##IN1};       \
        if (!PyArg_ParseTuple(                            \
            args, "O&O&:"NPY_TOSTRING(NAME),              \
            simd_arg_converter, &arg1,                    \
            simd_arg_converter, &arg2                     \
        )) return NULL;                                   \
        sv##TYPE##_t buf1 = svld1_##SIGN##BITS(svptrue_b##BITS(), (npyv_lanetype_##SIGN##BITS *) &arg1.data.IN0); \
        sv##TYPE##_t buf2 = svld1_##SIGN##BITS(svptrue_b##BITS(), (npyv_lanetype_##SIGN##BITS *) &arg2.data.IN1); \
	sv##TYPE##_t r = npyv_##NAME##_##SIGN##BITS(buf1, buf2); \
        simd_data data; \
	svst1_##SIGN##BITS (svptrue_b##BITS(), (npyv_lanetype_##SIGN##BITS *) &data, r); \
        simd_arg_free(&arg1);                             \
        simd_arg_free(&arg2);                             \
        simd_arg ret = {                                  \
            .data = data, .dtype = simd_data_##RET        \
        };                                                \
        return simd_arg_to_obj(&ret);                     \
    }

#define SIMD_IMPL_INTRIN_B_1(NAME, RET, IN0, TYPE, SIGN, BITS)  \
    static PyObject *simd__intrin_##NAME##_b##BITS        \
    (PyObject* NPY_UNUSED(self), PyObject *args)          \
    {                                                     \
        simd_arg arg = {.dtype = simd_data_##IN0};        \
        if (!PyArg_ParseTuple(                            \
            args, "O&:"NPY_TOSTRING(NAME),                \
            simd_arg_converter, &arg                      \
        )) return NULL;                                   \
        sv##TYPE##_t buf1 = svld1_##SIGN##BITS(svptrue_b##BITS(), (npyv_lanetype_##SIGN##BITS *) &arg.data.IN0); \
	sv##TYPE##_t r = npyv_##NAME##_##SIGN##BITS(buf1); \
        simd_data data; \
	svst1_##SIGN##BITS (svptrue_b##BITS(), (npyv_lanetype_##SIGN##BITS *) &data, r); \
        simd_arg_free(&arg);                             \
        simd_arg ret = {                                  \
            .data = data, .dtype = simd_data_##RET        \
        };                                                \
        return simd_arg_to_obj(&ret);                     \
    }

#define SIMD_IMPL_INTRIN_2_SH(NAME, RET, IN0, IN1, TYPE, SIGN, BITS)  \
    static PyObject *simd__intrin_##NAME                  \
    (PyObject* NPY_UNUSED(self), PyObject *args)          \
    {                                                     \
        simd_arg arg1 = {.dtype = simd_data_##IN0};       \
        simd_arg arg2 = {.dtype = simd_data_##IN1};       \
        if (!PyArg_ParseTuple(                            \
            args, "O&O&:"NPY_TOSTRING(NAME),              \
            simd_arg_converter, &arg1,                    \
            simd_arg_converter, &arg2                     \
        )) return NULL;                                   \
        sv##TYPE##_t buf1 = svld1_##SIGN##BITS(svptrue_b ## BITS(), (npyv_lanetype_##SIGN##BITS *) &arg1.data.IN0); \
	sv##TYPE##_t r = npyv_##NAME(buf1, arg2.data.IN1); \
        simd_data data; \
	svst1_##SIGN##BITS (svptrue_b##BITS(), (npyv_lanetype_##SIGN##BITS *) &data, r); \
        simd_arg_free(&arg1);                             \
        simd_arg_free(&arg2);                             \
        simd_arg ret = {                                  \
            .data = data, .dtype = simd_data_##RET        \
        };                                                \
        return simd_arg_to_obj(&ret);                     \
    }

#define SIMD_IMPL_INTRIN_2_ROUND(NAME, RET, IN0, IN1, TYPE, SIGN, BITS, TYPE2, SIGN2, BITS2)  \
    static PyObject *simd__intrin_##NAME                  \
    (PyObject* NPY_UNUSED(self), PyObject *args)          \
    {                                                     \
        simd_arg arg1 = {.dtype = simd_data_##IN0};       \
        simd_arg arg2 = {.dtype = simd_data_##IN1};       \
        if (!PyArg_ParseTuple(                            \
            args, "O&O&:"NPY_TOSTRING(NAME),              \
            simd_arg_converter, &arg1,                    \
            simd_arg_converter, &arg2                     \
        )) return NULL;                                   \
        sv##TYPE##_t buf1 = svld1_##SIGN##BITS(svptrue_b##BITS(), (npyv_lanetype_##SIGN##BITS *) &arg1.data.IN0); \
        sv##TYPE##_t buf2 = svld1_##SIGN##BITS(svptrue_b##BITS(), (npyv_lanetype_##SIGN##BITS *) &arg2.data.IN1); \
	sv##TYPE2##_t r = npyv_##NAME(buf1, buf2); \
        simd_data data; \
	svst1_##SIGN2##BITS2 (svptrue_b##BITS(), (npyv_lanetype_##SIGN2##BITS2 *) &data, r); \
        simd_arg_free(&arg1);                             \
        simd_arg_free(&arg2);                             \
        simd_arg ret = {                                  \
            .data = data, .dtype = simd_data_##RET        \
        };                                                \
        return simd_arg_to_obj(&ret);                     \
    }
#endif

#ifndef NPY_HAVE_SVE
#define SIMD__REPEAT_2IMM(C, NAME, IN0) \
    C == arg2.data.u8 ? NPY_CAT(npyv_, NAME)(arg1.data.IN0, C) :

#define SIMD_IMPL_INTRIN_2IMM(NAME, RET, IN0, CONST_RNG)  \
    static PyObject *simd__intrin_##NAME                  \
    (PyObject* NPY_UNUSED(self), PyObject *args)          \
    {                                                     \
        simd_arg arg1 = {.dtype = simd_data_##IN0};       \
        simd_arg arg2 = {.dtype = simd_data_u8};          \
        if (!PyArg_ParseTuple(                            \
            args, "O&O&:"NPY_TOSTRING(NAME),              \
            simd_arg_converter, &arg1,                    \
            simd_arg_converter, &arg2                     \
        )) return NULL;                                   \
        simd_data data = {.u64 = 0};                      \
        data.RET = NPY_CAT(SIMD__IMPL_COUNT_, CONST_RNG)( \
            SIMD__REPEAT_2IMM, NAME, IN0                  \
        ) data.RET;                                       \
        simd_arg_free(&arg1);                             \
        simd_arg ret = {                                  \
            .data = data, .dtype = simd_data_##RET        \
        };                                                \
        return simd_arg_to_obj(&ret);                     \
    }
#else
#define SIMD__REPEAT_2IMM(C, NAME, IN0) \
    C == arg2.data.u8 ? NPY_CAT(npyv_, NAME)(buf1, C) :

#define SIMD_IMPL_INTRIN_2IMM(NAME, RET, IN0, CONST_RNG, TYPE, SIGN, BITS)  \
    static PyObject *simd__intrin_##NAME                  \
    (PyObject* NPY_UNUSED(self), PyObject *args)          \
    {                                                     \
        simd_arg arg1 = {.dtype = simd_data_##IN0};       \
        simd_arg arg2 = {.dtype = simd_data_u8};          \
        if (!PyArg_ParseTuple(                            \
            args, "O&O&:"NPY_TOSTRING(NAME),              \
            simd_arg_converter, &arg1,                    \
            simd_arg_converter, &arg2                     \
        )) return NULL;                                   \
	sv##TYPE##_t buf1 = svld1_##SIGN##BITS(svptrue_b##BITS(), (npyv_lanetype_##SIGN##BITS *)&arg1.data.IN0); \
	sv##TYPE##_t r = svdup_n_##SIGN##BITS(0);         \
        r = NPY_CAT(SIMD__IMPL_COUNT_, CONST_RNG)(        \
            SIMD__REPEAT_2IMM, NAME, IN0                  \
        ) r;                                              \
	simd_data data;                                   \
	svst1_##SIGN##BITS(svptrue_b##BITS(), (npyv_lanetype_##SIGN##BITS *) &data, r);  \
        simd_arg_free(&arg1);                             \
        simd_arg ret = {                                  \
            .data = data, .dtype = simd_data_##RET        \
        };                                                \
        return simd_arg_to_obj(&ret);                     \
    }
#endif

#ifndef NPY_HAVE_SVE
#define 3SIMD_IMPL_INTRIN_3(NAME, RET, IN0, IN1, IN2)      \
    static PyObject *simd__intrin_##NAME                  \
    (PyObject* NPY_UNUSED(self), PyObject *args)          \
    {                                                     \
        simd_arg arg1 = {.dtype = simd_data_##IN0};       \
        simd_arg arg2 = {.dtype = simd_data_##IN1};       \
        simd_arg arg3 = {.dtype = simd_data_##IN2};       \
        if (!PyArg_ParseTuple(                            \
            args, "O&O&O&:"NPY_TOSTRING(NAME),            \
            simd_arg_converter, &arg1,                    \
            simd_arg_converter, &arg2,                    \
            simd_arg_converter, &arg3                     \
        )) return NULL;                                   \
        simd_data data = {.RET = npyv_##NAME(             \
            arg1.data.IN0, arg2.data.IN1,                 \
            arg3.data.IN2                                 \
        )};                                               \
        simd_arg_free(&arg1);                             \
        simd_arg_free(&arg2);                             \
        simd_arg_free(&arg3);                             \
        simd_arg ret = {                                  \
            .data = data, .dtype = simd_data_##RET        \
        };                                                \
        return simd_arg_to_obj(&ret);                     \
    }
#else
#define SIMD_IMPL_INTRIN_3(NAME, RET, IN0, IN1, IN2, TYPE, SIGN, BITS)      \
    static PyObject *simd__intrin_##NAME                  \
    (PyObject* NPY_UNUSED(self), PyObject *args)          \
    {                                                     \
        simd_arg arg1 = {.dtype = simd_data_##IN0};       \
        simd_arg arg2 = {.dtype = simd_data_##IN1};       \
        simd_arg arg3 = {.dtype = simd_data_##IN2};       \
        if (!PyArg_ParseTuple(                            \
            args, "O&O&O&:"NPY_TOSTRING(NAME),            \
            simd_arg_converter, &arg1,                    \
            simd_arg_converter, &arg2,                    \
            simd_arg_converter, &arg3                     \
        )) return NULL;                                   \
        simd_data data;                                   \
	sv##TYPE##_t tmp1 = svld1_##SIGN##BITS(svptrue_b##BITS(), (npyv_lanetype_##SIGN##BITS *) &arg2.data.IN1); \
	sv##TYPE##_t tmp2 = svld1_##SIGN##BITS(svptrue_b##BITS(), (npyv_lanetype_##SIGN##BITS *) &arg3.data.IN2); \
	svbool_t tmp0 = npyv_cvt_b##BITS##_##SIGN##BITS(svld1_##SIGN##BITS(svptrue_b##BITS(), (npyv_lanetype_##SIGN##BITS *) &arg1.data.IN0)); \
	svst1_##SIGN##BITS(svptrue_b##BITS(),(npyv_lanetype_##SIGN##BITS *) &data.RET, svsel_##SIGN##BITS(tmp0, tmp1, tmp2)); \
        simd_arg_free(&arg1);                             \
        simd_arg_free(&arg2);                             \
        simd_arg_free(&arg3);                             \
        simd_arg ret = {                                  \
            .data = data, .dtype = simd_data_##RET        \
        };                                                \
        return simd_arg_to_obj(&ret);                     \
    }

#define SIMD_IMPL_INTRIN_3_LD(NAME, RET, IN0, IN1, IN2, TYPE, SIGN, BITS)      \
    static PyObject *simd__intrin_##NAME                  \
    (PyObject* NPY_UNUSED(self), PyObject *args)          \
    {                                                     \
        simd_arg arg1 = {.dtype = simd_data_##IN0};       \
        simd_arg arg2 = {.dtype = simd_data_##IN1};       \
        simd_arg arg3 = {.dtype = simd_data_##IN2};       \
        if (!PyArg_ParseTuple(                            \
            args, "O&O&O&:"NPY_TOSTRING(NAME),            \
            simd_arg_converter, &arg1,                    \
            simd_arg_converter, &arg2,                    \
            simd_arg_converter, &arg3                     \
        )) return NULL;                                   \
        simd_data data;                                   \
	sv##TYPE##_t t = npyv_##NAME((npyv_lanetype_##SIGN##BITS*) arg1.data.IN0, arg2.data.IN1, arg3.data.IN2); \
        svst1_##SIGN##BITS(svptrue_b##BITS(), (npyv_lanetype_##SIGN##BITS *) &data, t); \
        simd_arg_free(&arg1);                             \
        simd_arg_free(&arg2);                             \
        simd_arg_free(&arg3);                             \
        simd_arg ret = {                                  \
            .data = data, .dtype = simd_data_##RET        \
        };                                                \
        return simd_arg_to_obj(&ret);                     \
    }
#endif

#ifndef NPY_HAVE_SVE
#define SIMD_IMPL_INTRIN_4(NAME, RET, IN0, IN1, IN2, IN3) \
    static PyObject *simd__intrin_##NAME                  \
    (PyObject* NPY_UNUSED(self), PyObject *args)          \
    {                                                     \
        simd_arg arg1 = {.dtype = simd_data_##IN0};       \
        simd_arg arg2 = {.dtype = simd_data_##IN1};       \
        simd_arg arg3 = {.dtype = simd_data_##IN2};       \
        simd_arg arg4 = {.dtype = simd_data_##IN3};       \
        if (!PyArg_ParseTuple(                            \
            args, "O&O&O&O&:"NPY_TOSTRING(NAME),          \
            simd_arg_converter, &arg1,                    \
            simd_arg_converter, &arg2,                    \
            simd_arg_converter, &arg3,                    \
            simd_arg_converter, &arg4                     \
        )) return NULL;                                   \
        simd_data data = {.RET = npyv_##NAME(             \
            arg1.data.IN0, arg2.data.IN1,                 \
            arg3.data.IN2, arg4.data.IN3                  \
        )};                                               \
        simd_arg_free(&arg1);                             \
        simd_arg_free(&arg2);                             \
        simd_arg_free(&arg3);                             \
        simd_arg_free(&arg4);                             \
        simd_arg ret = {                                  \
            .data = data, .dtype = simd_data_##RET        \
        };                                                \
        return simd_arg_to_obj(&ret);                     \
    }
#else
#define SIMD_IMPL_INTRIN_4(NAME, RET, IN0, IN1, IN2, IN3, TYPE, SIGN, BITS) \
    static PyObject *simd__intrin_##NAME                  \
    (PyObject* NPY_UNUSED(self), PyObject *args)          \
    {                                                     \
        simd_arg arg1 = {.dtype = simd_data_##IN0};       \
        simd_arg arg2 = {.dtype = simd_data_##IN1};       \
        simd_arg arg3 = {.dtype = simd_data_##IN2};       \
        simd_arg arg4 = {.dtype = simd_data_##IN3};       \
        if (!PyArg_ParseTuple(                            \
            args, "O&O&O&O&:"NPY_TOSTRING(NAME),          \
            simd_arg_converter, &arg1,                    \
            simd_arg_converter, &arg2,                    \
            simd_arg_converter, &arg3,                    \
            simd_arg_converter, &arg4                     \
        )) return NULL;                                   \
	simd_data data;                                   \
	sv##TYPE##_t t = svld1_##SIGN##BITS(svptrue_b##BITS(), (npyv_lanetype_##SIGN##BITS *) &arg1.data.IN0); \
	svbool_t mask = npyv_cvt_b##BITS##_##SIGN##BITS(t); \
	sv##TYPE##_t buf2 = svld1_##SIGN##BITS(svptrue_b##BITS(), (npyv_lanetype_##SIGN##BITS *) &arg2.data.IN1); \
	sv##TYPE##_t buf3 = svld1_##SIGN##BITS(svptrue_b##BITS(), (npyv_lanetype_##SIGN##BITS *) &arg3.data.IN2); \
	sv##TYPE##_t buf4 = svld1_##SIGN##BITS(svptrue_b##BITS(), (npyv_lanetype_##SIGN##BITS *) &arg4.data.IN3); \
	sv##TYPE##_t r = npyv_##NAME(mask, buf2, buf3, buf4); \
	svst1_##SIGN##BITS(svptrue_b##BITS(), (npyv_lanetype_##SIGN##BITS *) &data, r); \
        simd_arg_free(&arg1);                             \
        simd_arg_free(&arg2);                             \
        simd_arg_free(&arg3);                             \
        simd_arg_free(&arg4);                             \
        simd_arg ret = {                                  \
            .data = data, .dtype = simd_data_##RET        \
        };                                                \
        return simd_arg_to_obj(&ret);                     \
    }
#endif

/**
 * Helper macros for repeating and expand a certain macro.
 * Mainly used for converting a scalar to an immediate constant.
 */
#define SIMD__IMPL_COUNT_7(FN, ...)      \
    NPY_EXPAND(FN(0,  __VA_ARGS__))      \
    SIMD__IMPL_COUNT_7_(FN, __VA_ARGS__)

#define SIMD__IMPL_COUNT_8(FN, ...)      \
    SIMD__IMPL_COUNT_7_(FN, __VA_ARGS__) \
    NPY_EXPAND(FN(8,  __VA_ARGS__))

#define SIMD__IMPL_COUNT_15(FN, ...)     \
    NPY_EXPAND(FN(0,  __VA_ARGS__))      \
    SIMD__IMPL_COUNT_15_(FN, __VA_ARGS__)

#define SIMD__IMPL_COUNT_16(FN, ...)      \
    SIMD__IMPL_COUNT_15_(FN, __VA_ARGS__) \
    NPY_EXPAND(FN(16,  __VA_ARGS__))

#define SIMD__IMPL_COUNT_31(FN, ...)     \
    NPY_EXPAND(FN(0,  __VA_ARGS__))      \
    SIMD__IMPL_COUNT_31_(FN, __VA_ARGS__)

#define SIMD__IMPL_COUNT_32(FN, ...)      \
    SIMD__IMPL_COUNT_31_(FN, __VA_ARGS__) \
    NPY_EXPAND(FN(32,  __VA_ARGS__))

#define SIMD__IMPL_COUNT_47(FN, ...)     \
    NPY_EXPAND(FN(0,  __VA_ARGS__))      \
    SIMD__IMPL_COUNT_47_(FN, __VA_ARGS__)

#define SIMD__IMPL_COUNT_48(FN, ...)      \
    SIMD__IMPL_COUNT_47_(FN, __VA_ARGS__) \
    NPY_EXPAND(FN(48,  __VA_ARGS__))

#define SIMD__IMPL_COUNT_63(FN, ...)     \
    NPY_EXPAND(FN(0,  __VA_ARGS__))      \
    SIMD__IMPL_COUNT_63_(FN, __VA_ARGS__)

#define SIMD__IMPL_COUNT_64(FN, ...)      \
    SIMD__IMPL_COUNT_63_(FN, __VA_ARGS__) \
    NPY_EXPAND(FN(64,  __VA_ARGS__))

#define SIMD__IMPL_COUNT_7_(FN, ...)                                \
                                    NPY_EXPAND(FN(1,  __VA_ARGS__)) \
    NPY_EXPAND(FN(2,  __VA_ARGS__)) NPY_EXPAND(FN(3,  __VA_ARGS__)) \
    NPY_EXPAND(FN(4,  __VA_ARGS__)) NPY_EXPAND(FN(5,  __VA_ARGS__)) \
    NPY_EXPAND(FN(6,  __VA_ARGS__)) NPY_EXPAND(FN(7,  __VA_ARGS__))

#define SIMD__IMPL_COUNT_15_(FN, ...)                               \
    SIMD__IMPL_COUNT_7_(FN, __VA_ARGS__)                            \
    NPY_EXPAND(FN(8,  __VA_ARGS__)) NPY_EXPAND(FN(9,  __VA_ARGS__)) \
    NPY_EXPAND(FN(10, __VA_ARGS__)) NPY_EXPAND(FN(11, __VA_ARGS__)) \
    NPY_EXPAND(FN(12, __VA_ARGS__)) NPY_EXPAND(FN(13, __VA_ARGS__)) \
    NPY_EXPAND(FN(14, __VA_ARGS__)) NPY_EXPAND(FN(15, __VA_ARGS__))

#define SIMD__IMPL_COUNT_31_(FN, ...)                               \
    SIMD__IMPL_COUNT_15_(FN, __VA_ARGS__)                           \
    NPY_EXPAND(FN(16, __VA_ARGS__)) NPY_EXPAND(FN(17, __VA_ARGS__)) \
    NPY_EXPAND(FN(18, __VA_ARGS__)) NPY_EXPAND(FN(19, __VA_ARGS__)) \
    NPY_EXPAND(FN(20, __VA_ARGS__)) NPY_EXPAND(FN(21, __VA_ARGS__)) \
    NPY_EXPAND(FN(22, __VA_ARGS__)) NPY_EXPAND(FN(23, __VA_ARGS__)) \
    NPY_EXPAND(FN(24, __VA_ARGS__)) NPY_EXPAND(FN(25, __VA_ARGS__)) \
    NPY_EXPAND(FN(26, __VA_ARGS__)) NPY_EXPAND(FN(27, __VA_ARGS__)) \
    NPY_EXPAND(FN(28, __VA_ARGS__)) NPY_EXPAND(FN(29, __VA_ARGS__)) \
    NPY_EXPAND(FN(30, __VA_ARGS__)) NPY_EXPAND(FN(31, __VA_ARGS__))

#define SIMD__IMPL_COUNT_47_(FN, ...)                               \
    SIMD__IMPL_COUNT_31_(FN, __VA_ARGS__)                           \
    NPY_EXPAND(FN(32, __VA_ARGS__)) NPY_EXPAND(FN(33, __VA_ARGS__)) \
    NPY_EXPAND(FN(34, __VA_ARGS__)) NPY_EXPAND(FN(35, __VA_ARGS__)) \
    NPY_EXPAND(FN(36, __VA_ARGS__)) NPY_EXPAND(FN(37, __VA_ARGS__)) \
    NPY_EXPAND(FN(38, __VA_ARGS__)) NPY_EXPAND(FN(39, __VA_ARGS__)) \
    NPY_EXPAND(FN(40, __VA_ARGS__)) NPY_EXPAND(FN(41, __VA_ARGS__)) \
    NPY_EXPAND(FN(42, __VA_ARGS__)) NPY_EXPAND(FN(43, __VA_ARGS__)) \
    NPY_EXPAND(FN(44, __VA_ARGS__)) NPY_EXPAND(FN(45, __VA_ARGS__)) \
    NPY_EXPAND(FN(46, __VA_ARGS__)) NPY_EXPAND(FN(47, __VA_ARGS__))

#define SIMD__IMPL_COUNT_63_(FN, ...)                               \
    SIMD__IMPL_COUNT_47_(FN, __VA_ARGS__)                           \
    NPY_EXPAND(FN(48, __VA_ARGS__)) NPY_EXPAND(FN(49, __VA_ARGS__)) \
    NPY_EXPAND(FN(50, __VA_ARGS__)) NPY_EXPAND(FN(51, __VA_ARGS__)) \
    NPY_EXPAND(FN(52, __VA_ARGS__)) NPY_EXPAND(FN(53, __VA_ARGS__)) \
    NPY_EXPAND(FN(54, __VA_ARGS__)) NPY_EXPAND(FN(55, __VA_ARGS__)) \
    NPY_EXPAND(FN(56, __VA_ARGS__)) NPY_EXPAND(FN(57, __VA_ARGS__)) \
    NPY_EXPAND(FN(58, __VA_ARGS__)) NPY_EXPAND(FN(59, __VA_ARGS__)) \
    NPY_EXPAND(FN(60, __VA_ARGS__)) NPY_EXPAND(FN(61, __VA_ARGS__)) \
    NPY_EXPAND(FN(62, __VA_ARGS__)) NPY_EXPAND(FN(63, __VA_ARGS__))
