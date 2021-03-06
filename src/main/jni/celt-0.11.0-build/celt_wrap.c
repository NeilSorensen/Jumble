/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 2.0.11
 *
 * This file is not intended to be easily readable and contains a number of
 * coding conventions designed to improve portability and efficiency. Do not make
 * changes to this file unless you know what you are doing--modify the SWIG
 * interface file instead.
 * ----------------------------------------------------------------------------- */

#define SWIGJAVA

/* -----------------------------------------------------------------------------
 *  This section contains generic SWIG labels for method/variable
 *  declarations/attributes, and other compiler dependent labels.
 * ----------------------------------------------------------------------------- */

/* template workaround for compilers that cannot correctly implement the C++ standard */
#ifndef SWIGTEMPLATEDISAMBIGUATOR
# if defined(__SUNPRO_CC) && (__SUNPRO_CC <= 0x560)
#  define SWIGTEMPLATEDISAMBIGUATOR template
# elif defined(__HP_aCC)
/* Needed even with `aCC -AA' when `aCC -V' reports HP ANSI C++ B3910B A.03.55 */
/* If we find a maximum version that requires this, the test would be __HP_aCC <= 35500 for A.03.55 */
#  define SWIGTEMPLATEDISAMBIGUATOR template
# else
#  define SWIGTEMPLATEDISAMBIGUATOR
# endif
#endif

/* inline attribute */
#ifndef SWIGINLINE
# if defined(__cplusplus) || (defined(__GNUC__) && !defined(__STRICT_ANSI__))
#   define SWIGINLINE inline
# else
#   define SWIGINLINE
# endif
#endif

/* attribute recognised by some compilers to avoid 'unused' warnings */
#ifndef SWIGUNUSED
# if defined(__GNUC__)
#   if !(defined(__cplusplus)) || (__GNUC__ > 3 || (__GNUC__ == 3 && __GNUC_MINOR__ >= 4))
#     define SWIGUNUSED __attribute__ ((__unused__))
#   else
#     define SWIGUNUSED
#   endif
# elif defined(__ICC)
#   define SWIGUNUSED __attribute__ ((__unused__))
# else
#   define SWIGUNUSED
# endif
#endif

#ifndef SWIG_MSC_UNSUPPRESS_4505
# if defined(_MSC_VER)
#   pragma warning(disable : 4505) /* unreferenced local function has been removed */
# endif
#endif

#ifndef SWIGUNUSEDPARM
# ifdef __cplusplus
#   define SWIGUNUSEDPARM(p)
# else
#   define SWIGUNUSEDPARM(p) p SWIGUNUSED
# endif
#endif

/* internal SWIG method */
#ifndef SWIGINTERN
# define SWIGINTERN static SWIGUNUSED
#endif

/* internal inline SWIG method */
#ifndef SWIGINTERNINLINE
# define SWIGINTERNINLINE SWIGINTERN SWIGINLINE
#endif

/* exporting methods */
#if (__GNUC__ >= 4) || (__GNUC__ == 3 && __GNUC_MINOR__ >= 4)
#  ifndef GCC_HASCLASSVISIBILITY
#    define GCC_HASCLASSVISIBILITY
#  endif
#endif

#ifndef SWIGEXPORT
# if defined(_WIN32) || defined(__WIN32__) || defined(__CYGWIN__)
#   if defined(STATIC_LINKED)
#     define SWIGEXPORT
#   else
#     define SWIGEXPORT __declspec(dllexport)
#   endif
# else
#   if defined(__GNUC__) && defined(GCC_HASCLASSVISIBILITY)
#     define SWIGEXPORT __attribute__ ((visibility("default")))
#   else
#     define SWIGEXPORT
#   endif
# endif
#endif

/* calling conventions for Windows */
#ifndef SWIGSTDCALL
# if defined(_WIN32) || defined(__WIN32__) || defined(__CYGWIN__)
#   define SWIGSTDCALL __stdcall
# else
#   define SWIGSTDCALL
# endif
#endif

/* Deal with Microsoft's attempt at deprecating C standard runtime functions */
#if !defined(SWIG_NO_CRT_SECURE_NO_DEPRECATE) && defined(_MSC_VER) && !defined(_CRT_SECURE_NO_DEPRECATE)
# define _CRT_SECURE_NO_DEPRECATE
#endif

/* Deal with Microsoft's attempt at deprecating methods in the standard C++ library */
#if !defined(SWIG_NO_SCL_SECURE_NO_DEPRECATE) && defined(_MSC_VER) && !defined(_SCL_SECURE_NO_DEPRECATE)
# define _SCL_SECURE_NO_DEPRECATE
#endif



/* Fix for jlong on some versions of gcc on Windows */
#if defined(__GNUC__) && !defined(__INTEL_COMPILER)
  typedef long long __int64;
#endif

/* Fix for jlong on 64-bit x86 Solaris */
#if defined(__x86_64)
# ifdef _LP64
#   undef _LP64
# endif
#endif

#include <jni.h>
#include <stdlib.h>
#include <string.h>


/* Support for throwing Java exceptions */
typedef enum {
  SWIG_JavaOutOfMemoryError = 1, 
  SWIG_JavaIOException, 
  SWIG_JavaRuntimeException, 
  SWIG_JavaIndexOutOfBoundsException,
  SWIG_JavaArithmeticException,
  SWIG_JavaIllegalArgumentException,
  SWIG_JavaNullPointerException,
  SWIG_JavaDirectorPureVirtual,
  SWIG_JavaUnknownError
} SWIG_JavaExceptionCodes;

typedef struct {
  SWIG_JavaExceptionCodes code;
  const char *java_exception;
} SWIG_JavaExceptions_t;


static void SWIGUNUSED SWIG_JavaThrowException(JNIEnv *jenv, SWIG_JavaExceptionCodes code, const char *msg) {
  jclass excep;
  static const SWIG_JavaExceptions_t java_exceptions[] = {
    { SWIG_JavaOutOfMemoryError, "java/lang/OutOfMemoryError" },
    { SWIG_JavaIOException, "java/io/IOException" },
    { SWIG_JavaRuntimeException, "java/lang/RuntimeException" },
    { SWIG_JavaIndexOutOfBoundsException, "java/lang/IndexOutOfBoundsException" },
    { SWIG_JavaArithmeticException, "java/lang/ArithmeticException" },
    { SWIG_JavaIllegalArgumentException, "java/lang/IllegalArgumentException" },
    { SWIG_JavaNullPointerException, "java/lang/NullPointerException" },
    { SWIG_JavaDirectorPureVirtual, "java/lang/RuntimeException" },
    { SWIG_JavaUnknownError,  "java/lang/UnknownError" },
    { (SWIG_JavaExceptionCodes)0,  "java/lang/UnknownError" }
  };
  const SWIG_JavaExceptions_t *except_ptr = java_exceptions;

  while (except_ptr->code != code && except_ptr->code)
    except_ptr++;

  (*jenv)->ExceptionClear(jenv);
  excep = (*jenv)->FindClass(jenv, except_ptr->java_exception);
  if (excep)
    (*jenv)->ThrowNew(jenv, excep, msg);
}


/* Contract support */

#define SWIG_contract_assert(nullreturn, expr, msg) if (!(expr)) {SWIG_JavaThrowException(jenv, SWIG_JavaIllegalArgumentException, msg); return nullreturn; } else


#include <celt_types.h>
#include <celt.h>


#ifdef __cplusplus
extern "C" {
#endif

SWIGEXPORT jint JNICALL Java_com_morlunk_jumble_audio_celt11_CELT11JNI_CELT_1OK_1get(JNIEnv *jenv, jclass jcls) {
  jint jresult = 0 ;
  int result;
  
  (void)jenv;
  (void)jcls;
  result = (int)(0);
  jresult = (jint)result; 
  return jresult;
}


SWIGEXPORT jint JNICALL Java_com_morlunk_jumble_audio_celt11_CELT11JNI_CELT_1BAD_1ARG_1get(JNIEnv *jenv, jclass jcls) {
  jint jresult = 0 ;
  int result;
  
  (void)jenv;
  (void)jcls;
  result = (int)(-1);
  jresult = (jint)result; 
  return jresult;
}


SWIGEXPORT jint JNICALL Java_com_morlunk_jumble_audio_celt11_CELT11JNI_CELT_1INVALID_1MODE_1get(JNIEnv *jenv, jclass jcls) {
  jint jresult = 0 ;
  int result;
  
  (void)jenv;
  (void)jcls;
  result = (int)(-2);
  jresult = (jint)result; 
  return jresult;
}


SWIGEXPORT jint JNICALL Java_com_morlunk_jumble_audio_celt11_CELT11JNI_CELT_1INTERNAL_1ERROR_1get(JNIEnv *jenv, jclass jcls) {
  jint jresult = 0 ;
  int result;
  
  (void)jenv;
  (void)jcls;
  result = (int)(-3);
  jresult = (jint)result; 
  return jresult;
}


SWIGEXPORT jint JNICALL Java_com_morlunk_jumble_audio_celt11_CELT11JNI_CELT_1CORRUPTED_1DATA_1get(JNIEnv *jenv, jclass jcls) {
  jint jresult = 0 ;
  int result;
  
  (void)jenv;
  (void)jcls;
  result = (int)(-4);
  jresult = (jint)result; 
  return jresult;
}


SWIGEXPORT jint JNICALL Java_com_morlunk_jumble_audio_celt11_CELT11JNI_CELT_1UNIMPLEMENTED_1get(JNIEnv *jenv, jclass jcls) {
  jint jresult = 0 ;
  int result;
  
  (void)jenv;
  (void)jcls;
  result = (int)(-5);
  jresult = (jint)result; 
  return jresult;
}


SWIGEXPORT jint JNICALL Java_com_morlunk_jumble_audio_celt11_CELT11JNI_CELT_1INVALID_1STATE_1get(JNIEnv *jenv, jclass jcls) {
  jint jresult = 0 ;
  int result;
  
  (void)jenv;
  (void)jcls;
  result = (int)(-6);
  jresult = (jint)result; 
  return jresult;
}


SWIGEXPORT jint JNICALL Java_com_morlunk_jumble_audio_celt11_CELT11JNI_CELT_1ALLOC_1FAIL_1get(JNIEnv *jenv, jclass jcls) {
  jint jresult = 0 ;
  int result;
  
  (void)jenv;
  (void)jcls;
  result = (int)(-7);
  jresult = (jint)result; 
  return jresult;
}


SWIGEXPORT jint JNICALL Java_com_morlunk_jumble_audio_celt11_CELT11JNI_CELT_1GET_1MODE_1REQUEST_1get(JNIEnv *jenv, jclass jcls) {
  jint jresult = 0 ;
  int result;
  
  (void)jenv;
  (void)jcls;
  result = (int)(1);
  jresult = (jint)result; 
  return jresult;
}


SWIGEXPORT jint JNICALL Java_com_morlunk_jumble_audio_celt11_CELT11JNI_CELT_1SET_1COMPLEXITY_1REQUEST_1get(JNIEnv *jenv, jclass jcls) {
  jint jresult = 0 ;
  int result;
  
  (void)jenv;
  (void)jcls;
  result = (int)(2);
  jresult = (jint)result; 
  return jresult;
}


SWIGEXPORT jint JNICALL Java_com_morlunk_jumble_audio_celt11_CELT11JNI_CELT_1SET_1PREDICTION_1REQUEST_1get(JNIEnv *jenv, jclass jcls) {
  jint jresult = 0 ;
  int result;
  
  (void)jenv;
  (void)jcls;
  result = (int)(4);
  jresult = (jint)result; 
  return jresult;
}


SWIGEXPORT jint JNICALL Java_com_morlunk_jumble_audio_celt11_CELT11JNI_CELT_1SET_1BITRATE_1REQUEST_1get(JNIEnv *jenv, jclass jcls) {
  jint jresult = 0 ;
  int result;
  
  (void)jenv;
  (void)jcls;
  result = (int)(6);
  jresult = (jint)result; 
  return jresult;
}


SWIGEXPORT jint JNICALL Java_com_morlunk_jumble_audio_celt11_CELT11JNI_CELT_1RESET_1STATE_1REQUEST_1get(JNIEnv *jenv, jclass jcls) {
  jint jresult = 0 ;
  int result;
  
  (void)jenv;
  (void)jcls;
  result = (int)(8);
  jresult = (jint)result; 
  return jresult;
}


SWIGEXPORT jint JNICALL Java_com_morlunk_jumble_audio_celt11_CELT11JNI_CELT_1RESET_1STATE_1get(JNIEnv *jenv, jclass jcls) {
  jint jresult = 0 ;
  int result;
  
  (void)jenv;
  (void)jcls;
  result = (int)(8);
  jresult = (jint)result; 
  return jresult;
}


SWIGEXPORT jint JNICALL Java_com_morlunk_jumble_audio_celt11_CELT11JNI_CELT_1SET_1VBR_1CONSTRAINT_1REQUEST_1get(JNIEnv *jenv, jclass jcls) {
  jint jresult = 0 ;
  int result;
  
  (void)jenv;
  (void)jcls;
  result = (int)(10);
  jresult = (jint)result; 
  return jresult;
}


SWIGEXPORT jint JNICALL Java_com_morlunk_jumble_audio_celt11_CELT11JNI_CELT_1SET_1VBR_1REQUEST_1get(JNIEnv *jenv, jclass jcls) {
  jint jresult = 0 ;
  int result;
  
  (void)jenv;
  (void)jcls;
  result = (int)(12);
  jresult = (jint)result; 
  return jresult;
}


SWIGEXPORT jint JNICALL Java_com_morlunk_jumble_audio_celt11_CELT11JNI_CELT_1SET_1INPUT_1CLIPPING_1REQUEST_1get(JNIEnv *jenv, jclass jcls) {
  jint jresult = 0 ;
  int result;
  
  (void)jenv;
  (void)jcls;
  result = (int)(14);
  jresult = (jint)result; 
  return jresult;
}


SWIGEXPORT jint JNICALL Java_com_morlunk_jumble_audio_celt11_CELT11JNI_CELT_1SET_1START_1BAND_1REQUEST_1get(JNIEnv *jenv, jclass jcls) {
  jint jresult = 0 ;
  int result;
  
  (void)jenv;
  (void)jcls;
  result = (int)(10000);
  jresult = (jint)result; 
  return jresult;
}


SWIGEXPORT jint JNICALL Java_com_morlunk_jumble_audio_celt11_CELT11JNI_CELT_1SET_1END_1BAND_1REQUEST_1get(JNIEnv *jenv, jclass jcls) {
  jint jresult = 0 ;
  int result;
  
  (void)jenv;
  (void)jcls;
  result = (int)(10001);
  jresult = (jint)result; 
  return jresult;
}


SWIGEXPORT jint JNICALL Java_com_morlunk_jumble_audio_celt11_CELT11JNI_CELT_1SET_1CHANNELS_1REQUEST_1get(JNIEnv *jenv, jclass jcls) {
  jint jresult = 0 ;
  int result;
  
  (void)jenv;
  (void)jcls;
  result = (int)(10002);
  jresult = (jint)result; 
  return jresult;
}


SWIGEXPORT jint JNICALL Java_com_morlunk_jumble_audio_celt11_CELT11JNI_CELT_1GET_1LOOKAHEAD_1get(JNIEnv *jenv, jclass jcls) {
  jint jresult = 0 ;
  int result;
  
  (void)jenv;
  (void)jcls;
  result = (int)(1001);
  jresult = (jint)result; 
  return jresult;
}


SWIGEXPORT jint JNICALL Java_com_morlunk_jumble_audio_celt11_CELT11JNI_CELT_1GET_1SAMPLE_1RATE_1get(JNIEnv *jenv, jclass jcls) {
  jint jresult = 0 ;
  int result;
  
  (void)jenv;
  (void)jcls;
  result = (int)(1003);
  jresult = (jint)result; 
  return jresult;
}


SWIGEXPORT jint JNICALL Java_com_morlunk_jumble_audio_celt11_CELT11JNI_CELT_1GET_1BITSTREAM_1VERSION_1get(JNIEnv *jenv, jclass jcls) {
  jint jresult = 0 ;
  int result;
  
  (void)jenv;
  (void)jcls;
  result = (int)(2000);
  jresult = (jint)result; 
  return jresult;
}


SWIGEXPORT jlong JNICALL Java_com_morlunk_jumble_audio_celt11_CELT11JNI_celt_1mode_1create(JNIEnv *jenv, jclass jcls, jint jarg1, jint jarg2, jintArray jarg3) {
  jlong jresult = 0 ;
  celt_int32 arg1 ;
  int arg2 ;
  int *arg3 = (int *) 0 ;
  int temp3 ;
  CELTMode *result = 0 ;
  
  (void)jenv;
  (void)jcls;
  arg1 = (celt_int32)jarg1; 
  arg2 = (int)jarg2; 
  {
    if (!jarg3) {
      SWIG_JavaThrowException(jenv, SWIG_JavaNullPointerException, "array null");
      return 0;
    }
    if ((*jenv)->GetArrayLength(jenv, jarg3) == 0) {
      SWIG_JavaThrowException(jenv, SWIG_JavaIndexOutOfBoundsException, "Array must contain at least 1 element");
      return 0;
    }
    temp3 = (int)0;
    arg3 = &temp3; 
  }
  result = (CELTMode *)celt_mode_create(arg1,arg2,arg3);
  *(CELTMode **)&jresult = result; 
  {
    jint jvalue = (jint)temp3;
    (*jenv)->SetIntArrayRegion(jenv, jarg3, 0, 1, &jvalue);
  }
  
  return jresult;
}


SWIGEXPORT void JNICALL Java_com_morlunk_jumble_audio_celt11_CELT11JNI_celt_1mode_1destroy(JNIEnv *jenv, jclass jcls, jlong jarg1) {
  CELTMode *arg1 = (CELTMode *) 0 ;
  
  (void)jenv;
  (void)jcls;
  arg1 = *(CELTMode **)&jarg1; 
  celt_mode_destroy(arg1);
}


SWIGEXPORT jint JNICALL Java_com_morlunk_jumble_audio_celt11_CELT11JNI_celt_1mode_1info(JNIEnv *jenv, jclass jcls, jlong jarg1, jint jarg2, jintArray jarg3) {
  jint jresult = 0 ;
  CELTMode *arg1 = (CELTMode *) 0 ;
  int arg2 ;
  celt_int32 *arg3 = (celt_int32 *) 0 ;
  celt_int32 temp3 ;
  int result;
  
  (void)jenv;
  (void)jcls;
  arg1 = *(CELTMode **)&jarg1; 
  arg2 = (int)jarg2; 
  {
    if (!jarg3) {
      SWIG_JavaThrowException(jenv, SWIG_JavaNullPointerException, "array null");
      return 0;
    }
    if ((*jenv)->GetArrayLength(jenv, jarg3) == 0) {
      SWIG_JavaThrowException(jenv, SWIG_JavaIndexOutOfBoundsException, "Array must contain at least 1 element");
      return 0;
    }
    temp3 = (celt_int32)0;
    arg3 = &temp3; 
  }
  result = (int)celt_mode_info((struct CELTMode const *)arg1,arg2,arg3);
  jresult = (jint)result; 
  {
    jint jvalue = (jint)temp3;
    (*jenv)->SetIntArrayRegion(jenv, jarg3, 0, 1, &jvalue);
  }
  
  return jresult;
}


SWIGEXPORT jint JNICALL Java_com_morlunk_jumble_audio_celt11_CELT11JNI_celt_1encoder_1get_1size(JNIEnv *jenv, jclass jcls, jint jarg1) {
  jint jresult = 0 ;
  int arg1 ;
  int result;
  
  (void)jenv;
  (void)jcls;
  arg1 = (int)jarg1; 
  result = (int)celt_encoder_get_size(arg1);
  jresult = (jint)result; 
  return jresult;
}


SWIGEXPORT jint JNICALL Java_com_morlunk_jumble_audio_celt11_CELT11JNI_celt_1encoder_1get_1size_1custom(JNIEnv *jenv, jclass jcls, jlong jarg1, jint jarg2) {
  jint jresult = 0 ;
  CELTMode *arg1 = (CELTMode *) 0 ;
  int arg2 ;
  int result;
  
  (void)jenv;
  (void)jcls;
  arg1 = *(CELTMode **)&jarg1; 
  arg2 = (int)jarg2; 
  result = (int)celt_encoder_get_size_custom((struct CELTMode const *)arg1,arg2);
  jresult = (jint)result; 
  return jresult;
}


SWIGEXPORT jlong JNICALL Java_com_morlunk_jumble_audio_celt11_CELT11JNI_celt_1encoder_1create(JNIEnv *jenv, jclass jcls, jint jarg1, jint jarg2, jintArray jarg3) {
  jlong jresult = 0 ;
  int arg1 ;
  int arg2 ;
  int *arg3 = (int *) 0 ;
  int temp3 ;
  CELTEncoder *result = 0 ;
  
  (void)jenv;
  (void)jcls;
  arg1 = (int)jarg1; 
  arg2 = (int)jarg2; 
  {
    if (!jarg3) {
      SWIG_JavaThrowException(jenv, SWIG_JavaNullPointerException, "array null");
      return 0;
    }
    if ((*jenv)->GetArrayLength(jenv, jarg3) == 0) {
      SWIG_JavaThrowException(jenv, SWIG_JavaIndexOutOfBoundsException, "Array must contain at least 1 element");
      return 0;
    }
    temp3 = (int)0;
    arg3 = &temp3; 
  }
  result = (CELTEncoder *)celt_encoder_create(arg1,arg2,arg3);
  *(CELTEncoder **)&jresult = result; 
  {
    jint jvalue = (jint)temp3;
    (*jenv)->SetIntArrayRegion(jenv, jarg3, 0, 1, &jvalue);
  }
  
  return jresult;
}


SWIGEXPORT jlong JNICALL Java_com_morlunk_jumble_audio_celt11_CELT11JNI_celt_1encoder_1create_1custom(JNIEnv *jenv, jclass jcls, jlong jarg1, jint jarg2, jintArray jarg3) {
  jlong jresult = 0 ;
  CELTMode *arg1 = (CELTMode *) 0 ;
  int arg2 ;
  int *arg3 = (int *) 0 ;
  int temp3 ;
  CELTEncoder *result = 0 ;
  
  (void)jenv;
  (void)jcls;
  arg1 = *(CELTMode **)&jarg1; 
  arg2 = (int)jarg2; 
  {
    if (!jarg3) {
      SWIG_JavaThrowException(jenv, SWIG_JavaNullPointerException, "array null");
      return 0;
    }
    if ((*jenv)->GetArrayLength(jenv, jarg3) == 0) {
      SWIG_JavaThrowException(jenv, SWIG_JavaIndexOutOfBoundsException, "Array must contain at least 1 element");
      return 0;
    }
    temp3 = (int)0;
    arg3 = &temp3; 
  }
  result = (CELTEncoder *)celt_encoder_create_custom((struct CELTMode const *)arg1,arg2,arg3);
  *(CELTEncoder **)&jresult = result; 
  {
    jint jvalue = (jint)temp3;
    (*jenv)->SetIntArrayRegion(jenv, jarg3, 0, 1, &jvalue);
  }
  
  return jresult;
}


SWIGEXPORT jlong JNICALL Java_com_morlunk_jumble_audio_celt11_CELT11JNI_celt_1encoder_1init(JNIEnv *jenv, jclass jcls, jlong jarg1, jint jarg2, jint jarg3, jintArray jarg4) {
  jlong jresult = 0 ;
  CELTEncoder *arg1 = (CELTEncoder *) 0 ;
  int arg2 ;
  int arg3 ;
  int *arg4 = (int *) 0 ;
  int temp4 ;
  CELTEncoder *result = 0 ;
  
  (void)jenv;
  (void)jcls;
  arg1 = *(CELTEncoder **)&jarg1; 
  arg2 = (int)jarg2; 
  arg3 = (int)jarg3; 
  {
    if (!jarg4) {
      SWIG_JavaThrowException(jenv, SWIG_JavaNullPointerException, "array null");
      return 0;
    }
    if ((*jenv)->GetArrayLength(jenv, jarg4) == 0) {
      SWIG_JavaThrowException(jenv, SWIG_JavaIndexOutOfBoundsException, "Array must contain at least 1 element");
      return 0;
    }
    temp4 = (int)0;
    arg4 = &temp4; 
  }
  result = (CELTEncoder *)celt_encoder_init(arg1,arg2,arg3,arg4);
  *(CELTEncoder **)&jresult = result; 
  {
    jint jvalue = (jint)temp4;
    (*jenv)->SetIntArrayRegion(jenv, jarg4, 0, 1, &jvalue);
  }
  
  return jresult;
}


SWIGEXPORT jlong JNICALL Java_com_morlunk_jumble_audio_celt11_CELT11JNI_celt_1encoder_1init_1custom(JNIEnv *jenv, jclass jcls, jlong jarg1, jlong jarg2, jint jarg3, jintArray jarg4) {
  jlong jresult = 0 ;
  CELTEncoder *arg1 = (CELTEncoder *) 0 ;
  CELTMode *arg2 = (CELTMode *) 0 ;
  int arg3 ;
  int *arg4 = (int *) 0 ;
  int temp4 ;
  CELTEncoder *result = 0 ;
  
  (void)jenv;
  (void)jcls;
  arg1 = *(CELTEncoder **)&jarg1; 
  arg2 = *(CELTMode **)&jarg2; 
  arg3 = (int)jarg3; 
  {
    if (!jarg4) {
      SWIG_JavaThrowException(jenv, SWIG_JavaNullPointerException, "array null");
      return 0;
    }
    if ((*jenv)->GetArrayLength(jenv, jarg4) == 0) {
      SWIG_JavaThrowException(jenv, SWIG_JavaIndexOutOfBoundsException, "Array must contain at least 1 element");
      return 0;
    }
    temp4 = (int)0;
    arg4 = &temp4; 
  }
  result = (CELTEncoder *)celt_encoder_init_custom(arg1,(struct CELTMode const *)arg2,arg3,arg4);
  *(CELTEncoder **)&jresult = result; 
  {
    jint jvalue = (jint)temp4;
    (*jenv)->SetIntArrayRegion(jenv, jarg4, 0, 1, &jvalue);
  }
  
  return jresult;
}


SWIGEXPORT void JNICALL Java_com_morlunk_jumble_audio_celt11_CELT11JNI_celt_1encoder_1destroy(JNIEnv *jenv, jclass jcls, jlong jarg1) {
  CELTEncoder *arg1 = (CELTEncoder *) 0 ;
  
  (void)jenv;
  (void)jcls;
  arg1 = *(CELTEncoder **)&jarg1; 
  celt_encoder_destroy(arg1);
}


SWIGEXPORT jint JNICALL Java_com_morlunk_jumble_audio_celt11_CELT11JNI_celt_1encode_1float(JNIEnv *jenv, jclass jcls, jlong jarg1, jfloatArray jarg2, jint jarg3, jbyteArray jarg4, jint jarg5) {
  jint jresult = 0 ;
  CELTEncoder *arg1 = (CELTEncoder *) 0 ;
  float *arg2 = (float *) 0 ;
  int arg3 ;
  unsigned char *arg4 = (unsigned char *) 0 ;
  int arg5 ;
  int result;
  
  (void)jenv;
  (void)jcls;
  arg1 = *(CELTEncoder **)&jarg1; 
  {
    if (!jarg2) {
      SWIG_JavaThrowException(jenv, SWIG_JavaNullPointerException, "array null");
      return 0;
    }
    if ((*jenv)->GetArrayLength(jenv, jarg2) == 0) {
      SWIG_JavaThrowException(jenv, SWIG_JavaIndexOutOfBoundsException, "Array must contain at least 1 element");
      return 0;
    }
    arg2 = (float *) (*jenv)->GetFloatArrayElements(jenv, jarg2, 0); 
  }
  arg3 = (int)jarg3; 
  {
    arg4 = (char *) (*jenv)->GetByteArrayElements(jenv, jarg4, 0); 
  }
  arg5 = (int)jarg5; 
  result = (int)celt_encode_float(arg1,(float const *)arg2,arg3,arg4,arg5);
  jresult = (jint)result; 
  {
    (*jenv)->ReleaseFloatArrayElements(jenv, jarg2, (jfloat *)arg2, 0); 
  }
  {
    (*jenv)->ReleaseByteArrayElements(jenv, jarg4, (jbyte *) arg4, 0); 
  }
  
  
  return jresult;
}


SWIGEXPORT jint JNICALL Java_com_morlunk_jumble_audio_celt11_CELT11JNI_celt_1encode(JNIEnv *jenv, jclass jcls, jlong jarg1, jshortArray jarg2, jint jarg3, jbyteArray jarg4, jint jarg5) {
  jint jresult = 0 ;
  CELTEncoder *arg1 = (CELTEncoder *) 0 ;
  celt_int16 *arg2 = (celt_int16 *) 0 ;
  int arg3 ;
  unsigned char *arg4 = (unsigned char *) 0 ;
  int arg5 ;
  int result;
  
  (void)jenv;
  (void)jcls;
  arg1 = *(CELTEncoder **)&jarg1; 
  {
    if (!jarg2) {
      SWIG_JavaThrowException(jenv, SWIG_JavaNullPointerException, "array null");
      return 0;
    }
    if ((*jenv)->GetArrayLength(jenv, jarg2) == 0) {
      SWIG_JavaThrowException(jenv, SWIG_JavaIndexOutOfBoundsException, "Array must contain at least 1 element");
      return 0;
    }
    arg2 = (celt_int16 *) (*jenv)->GetShortArrayElements(jenv, jarg2, 0); 
  }
  arg3 = (int)jarg3; 
  {
    arg4 = (char *) (*jenv)->GetByteArrayElements(jenv, jarg4, 0); 
  }
  arg5 = (int)jarg5; 
  result = (int)celt_encode(arg1,(short const *)arg2,arg3,arg4,arg5);
  jresult = (jint)result; 
  {
    (*jenv)->ReleaseShortArrayElements(jenv, jarg2, (jshort *)arg2, 0); 
  }
  {
    (*jenv)->ReleaseByteArrayElements(jenv, jarg4, (jbyte *) arg4, 0); 
  }
  
  
  return jresult;
}


SWIGEXPORT jint JNICALL Java_com_morlunk_jumble_audio_celt11_CELT11JNI_celt_1encoder_1ctl(JNIEnv *jenv, jclass jcls, jlong jarg1, jint jarg2, jintArray jarg3) {
  jint jresult = 0 ;
  CELTEncoder *arg1 = (CELTEncoder *) 0 ;
  int arg2 ;
  int *arg3 = (int *) 0 ;
  int temp3 ;
  int result;
  
  (void)jenv;
  (void)jcls;
  arg1 = *(CELTEncoder **)&jarg1; 
  arg2 = (int)jarg2; 
  {
    if (!jarg3) {
      SWIG_JavaThrowException(jenv, SWIG_JavaNullPointerException, "array null");
      return 0;
    }
    if ((*jenv)->GetArrayLength(jenv, jarg3) == 0) {
      SWIG_JavaThrowException(jenv, SWIG_JavaIndexOutOfBoundsException, "Array must contain at least 1 element");
      return 0;
    }
    temp3 = (int)0;
    arg3 = &temp3; 
  }
  result = (int)celt_encoder_ctl(arg1,arg2,arg3);
  jresult = (jint)result; 
  {
    jint jvalue = (jint)temp3;
    (*jenv)->SetIntArrayRegion(jenv, jarg3, 0, 1, &jvalue);
  }
  
  return jresult;
}


SWIGEXPORT jint JNICALL Java_com_morlunk_jumble_audio_celt11_CELT11JNI_celt_1decoder_1get_1size(JNIEnv *jenv, jclass jcls, jint jarg1) {
  jint jresult = 0 ;
  int arg1 ;
  int result;
  
  (void)jenv;
  (void)jcls;
  arg1 = (int)jarg1; 
  result = (int)celt_decoder_get_size(arg1);
  jresult = (jint)result; 
  return jresult;
}


SWIGEXPORT jint JNICALL Java_com_morlunk_jumble_audio_celt11_CELT11JNI_celt_1decoder_1get_1size_1custom(JNIEnv *jenv, jclass jcls, jlong jarg1, jint jarg2) {
  jint jresult = 0 ;
  CELTMode *arg1 = (CELTMode *) 0 ;
  int arg2 ;
  int result;
  
  (void)jenv;
  (void)jcls;
  arg1 = *(CELTMode **)&jarg1; 
  arg2 = (int)jarg2; 
  result = (int)celt_decoder_get_size_custom((struct CELTMode const *)arg1,arg2);
  jresult = (jint)result; 
  return jresult;
}


SWIGEXPORT jlong JNICALL Java_com_morlunk_jumble_audio_celt11_CELT11JNI_celt_1decoder_1create(JNIEnv *jenv, jclass jcls, jint jarg1, jint jarg2, jintArray jarg3) {
  jlong jresult = 0 ;
  int arg1 ;
  int arg2 ;
  int *arg3 = (int *) 0 ;
  int temp3 ;
  CELTDecoder *result = 0 ;
  
  (void)jenv;
  (void)jcls;
  arg1 = (int)jarg1; 
  arg2 = (int)jarg2; 
  {
    if (!jarg3) {
      SWIG_JavaThrowException(jenv, SWIG_JavaNullPointerException, "array null");
      return 0;
    }
    if ((*jenv)->GetArrayLength(jenv, jarg3) == 0) {
      SWIG_JavaThrowException(jenv, SWIG_JavaIndexOutOfBoundsException, "Array must contain at least 1 element");
      return 0;
    }
    temp3 = (int)0;
    arg3 = &temp3; 
  }
  result = (CELTDecoder *)celt_decoder_create(arg1,arg2,arg3);
  *(CELTDecoder **)&jresult = result; 
  {
    jint jvalue = (jint)temp3;
    (*jenv)->SetIntArrayRegion(jenv, jarg3, 0, 1, &jvalue);
  }
  
  return jresult;
}


SWIGEXPORT jlong JNICALL Java_com_morlunk_jumble_audio_celt11_CELT11JNI_celt_1decoder_1create_1custom(JNIEnv *jenv, jclass jcls, jlong jarg1, jint jarg2, jintArray jarg3) {
  jlong jresult = 0 ;
  CELTMode *arg1 = (CELTMode *) 0 ;
  int arg2 ;
  int *arg3 = (int *) 0 ;
  int temp3 ;
  CELTDecoder *result = 0 ;
  
  (void)jenv;
  (void)jcls;
  arg1 = *(CELTMode **)&jarg1; 
  arg2 = (int)jarg2; 
  {
    if (!jarg3) {
      SWIG_JavaThrowException(jenv, SWIG_JavaNullPointerException, "array null");
      return 0;
    }
    if ((*jenv)->GetArrayLength(jenv, jarg3) == 0) {
      SWIG_JavaThrowException(jenv, SWIG_JavaIndexOutOfBoundsException, "Array must contain at least 1 element");
      return 0;
    }
    temp3 = (int)0;
    arg3 = &temp3; 
  }
  result = (CELTDecoder *)celt_decoder_create_custom((struct CELTMode const *)arg1,arg2,arg3);
  *(CELTDecoder **)&jresult = result; 
  {
    jint jvalue = (jint)temp3;
    (*jenv)->SetIntArrayRegion(jenv, jarg3, 0, 1, &jvalue);
  }
  
  return jresult;
}


SWIGEXPORT jlong JNICALL Java_com_morlunk_jumble_audio_celt11_CELT11JNI_celt_1decoder_1init(JNIEnv *jenv, jclass jcls, jlong jarg1, jint jarg2, jint jarg3, jintArray jarg4) {
  jlong jresult = 0 ;
  CELTDecoder *arg1 = (CELTDecoder *) 0 ;
  int arg2 ;
  int arg3 ;
  int *arg4 = (int *) 0 ;
  int temp4 ;
  CELTDecoder *result = 0 ;
  
  (void)jenv;
  (void)jcls;
  arg1 = *(CELTDecoder **)&jarg1; 
  arg2 = (int)jarg2; 
  arg3 = (int)jarg3; 
  {
    if (!jarg4) {
      SWIG_JavaThrowException(jenv, SWIG_JavaNullPointerException, "array null");
      return 0;
    }
    if ((*jenv)->GetArrayLength(jenv, jarg4) == 0) {
      SWIG_JavaThrowException(jenv, SWIG_JavaIndexOutOfBoundsException, "Array must contain at least 1 element");
      return 0;
    }
    temp4 = (int)0;
    arg4 = &temp4; 
  }
  result = (CELTDecoder *)celt_decoder_init(arg1,arg2,arg3,arg4);
  *(CELTDecoder **)&jresult = result; 
  {
    jint jvalue = (jint)temp4;
    (*jenv)->SetIntArrayRegion(jenv, jarg4, 0, 1, &jvalue);
  }
  
  return jresult;
}


SWIGEXPORT jlong JNICALL Java_com_morlunk_jumble_audio_celt11_CELT11JNI_celt_1decoder_1init_1custom(JNIEnv *jenv, jclass jcls, jlong jarg1, jlong jarg2, jint jarg3, jintArray jarg4) {
  jlong jresult = 0 ;
  CELTDecoder *arg1 = (CELTDecoder *) 0 ;
  CELTMode *arg2 = (CELTMode *) 0 ;
  int arg3 ;
  int *arg4 = (int *) 0 ;
  int temp4 ;
  CELTDecoder *result = 0 ;
  
  (void)jenv;
  (void)jcls;
  arg1 = *(CELTDecoder **)&jarg1; 
  arg2 = *(CELTMode **)&jarg2; 
  arg3 = (int)jarg3; 
  {
    if (!jarg4) {
      SWIG_JavaThrowException(jenv, SWIG_JavaNullPointerException, "array null");
      return 0;
    }
    if ((*jenv)->GetArrayLength(jenv, jarg4) == 0) {
      SWIG_JavaThrowException(jenv, SWIG_JavaIndexOutOfBoundsException, "Array must contain at least 1 element");
      return 0;
    }
    temp4 = (int)0;
    arg4 = &temp4; 
  }
  result = (CELTDecoder *)celt_decoder_init_custom(arg1,(struct CELTMode const *)arg2,arg3,arg4);
  *(CELTDecoder **)&jresult = result; 
  {
    jint jvalue = (jint)temp4;
    (*jenv)->SetIntArrayRegion(jenv, jarg4, 0, 1, &jvalue);
  }
  
  return jresult;
}


SWIGEXPORT void JNICALL Java_com_morlunk_jumble_audio_celt11_CELT11JNI_celt_1decoder_1destroy(JNIEnv *jenv, jclass jcls, jlong jarg1) {
  CELTDecoder *arg1 = (CELTDecoder *) 0 ;
  
  (void)jenv;
  (void)jcls;
  arg1 = *(CELTDecoder **)&jarg1; 
  celt_decoder_destroy(arg1);
}


SWIGEXPORT jint JNICALL Java_com_morlunk_jumble_audio_celt11_CELT11JNI_celt_1decode_1float(JNIEnv *jenv, jclass jcls, jlong jarg1, jbyteArray jarg2, jint jarg3, jfloatArray jarg4, jint jarg5) {
  jint jresult = 0 ;
  CELTDecoder *arg1 = (CELTDecoder *) 0 ;
  unsigned char *arg2 = (unsigned char *) 0 ;
  int arg3 ;
  float *arg4 = (float *) 0 ;
  int arg5 ;
  int result;
  
  (void)jenv;
  (void)jcls;
  arg1 = *(CELTDecoder **)&jarg1; 
  {
    arg2 = (char *) (*jenv)->GetByteArrayElements(jenv, jarg2, 0); 
  }
  arg3 = (int)jarg3; 
  {
    if (!jarg4) {
      SWIG_JavaThrowException(jenv, SWIG_JavaNullPointerException, "array null");
      return 0;
    }
    if ((*jenv)->GetArrayLength(jenv, jarg4) == 0) {
      SWIG_JavaThrowException(jenv, SWIG_JavaIndexOutOfBoundsException, "Array must contain at least 1 element");
      return 0;
    }
    arg4 = (float *) (*jenv)->GetFloatArrayElements(jenv, jarg4, 0); 
  }
  arg5 = (int)jarg5; 
  result = (int)celt_decode_float(arg1,(unsigned char const *)arg2,arg3,arg4,arg5);
  jresult = (jint)result; 
  {
    (*jenv)->ReleaseByteArrayElements(jenv, jarg2, (jbyte *) arg2, 0); 
  }
  {
    (*jenv)->ReleaseFloatArrayElements(jenv, jarg4, (jfloat *)arg4, 0); 
  }
  
  
  return jresult;
}


SWIGEXPORT jint JNICALL Java_com_morlunk_jumble_audio_celt11_CELT11JNI_celt_1decode(JNIEnv *jenv, jclass jcls, jlong jarg1, jbyteArray jarg2, jint jarg3, jshortArray jarg4, jint jarg5) {
  jint jresult = 0 ;
  CELTDecoder *arg1 = (CELTDecoder *) 0 ;
  unsigned char *arg2 = (unsigned char *) 0 ;
  int arg3 ;
  celt_int16 *arg4 = (celt_int16 *) 0 ;
  int arg5 ;
  int result;
  
  (void)jenv;
  (void)jcls;
  arg1 = *(CELTDecoder **)&jarg1; 
  {
    arg2 = (char *) (*jenv)->GetByteArrayElements(jenv, jarg2, 0); 
  }
  arg3 = (int)jarg3; 
  {
    if (!jarg4) {
      SWIG_JavaThrowException(jenv, SWIG_JavaNullPointerException, "array null");
      return 0;
    }
    if ((*jenv)->GetArrayLength(jenv, jarg4) == 0) {
      SWIG_JavaThrowException(jenv, SWIG_JavaIndexOutOfBoundsException, "Array must contain at least 1 element");
      return 0;
    }
    arg4 = (celt_int16 *) (*jenv)->GetShortArrayElements(jenv, jarg4, 0); 
  }
  arg5 = (int)jarg5; 
  result = (int)celt_decode(arg1,(unsigned char const *)arg2,arg3,arg4,arg5);
  jresult = (jint)result; 
  {
    (*jenv)->ReleaseByteArrayElements(jenv, jarg2, (jbyte *) arg2, 0); 
  }
  {
    (*jenv)->ReleaseShortArrayElements(jenv, jarg4, (jshort *)arg4, 0); 
  }
  
  
  return jresult;
}


SWIGEXPORT jint JNICALL Java_com_morlunk_jumble_audio_celt11_CELT11JNI_celt_1decoder_1ctl(JNIEnv *jenv, jclass jcls, jlong jarg1, jint jarg2) {
  jint jresult = 0 ;
  CELTDecoder *arg1 = (CELTDecoder *) 0 ;
  int arg2 ;
  void *arg3 = 0 ;
  int result;
  
  (void)jenv;
  (void)jcls;
  arg1 = *(CELTDecoder **)&jarg1; 
  arg2 = (int)jarg2; 
  result = (int)celt_decoder_ctl(arg1,arg2,arg3);
  jresult = (jint)result; 
  return jresult;
}


SWIGEXPORT jbyteArray JNICALL Java_com_morlunk_jumble_audio_celt11_CELT11JNI_celt_1strerror(JNIEnv *jenv, jclass jcls, jint jarg1) {
  jbyteArray jresult = 0 ;
  int arg1 ;
  char *result = 0 ;
  
  (void)jenv;
  (void)jcls;
  arg1 = (int)jarg1; 
  result = (char *)celt_strerror(arg1);
  if (result) jresult = (*jenv)->NewStringUTF(jenv, (const char *)result);
  return jresult;
}


#ifdef __cplusplus
}
#endif

