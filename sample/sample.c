#include "sample.h"
#include <string.h>

JNIEXPORT jint JNICALL Java_NativeMethodTest_intMethod
  (JNIEnv * env, jobject obj, jint i)
{
    return i * i;
}

JNIEXPORT jboolean JNICALL Java_NativeMethodTest_booleanMethod
  (JNIEnv * env, jobject obj, jboolean b)
{
    return !b;
}

JNIEXPORT jstring JNICALL Java_NativeMethodTest_stringMethod
  (JNIEnv * env, jobject obj, jstring string)
{
    const char* str = (*env)->GetStringUTFChars(env, string, 0);
    char cap[128];
    strcpy(cap, str);
    (*env)->ReleaseStringUTFChars(env, string, 0);
    return (*env)->NewStringUTF(env, cap);
}

JNIEXPORT jint JNICALL Java_NativeMethodTest_intArrayMethod
  (JNIEnv * env, jobject obj, jintArray array)
{
    int i, sum = 0;
    jsize len = (*env)->GetArrayLength(env, array);
    jint * body = (*env)->GetIntArrayElements(env, array, 0);

    for (i=0; i<len; i++)
    {
        sum += body[i];
    }
    (*env)->ReleaseIntArrayElements(env, array, body, 0);
    return sum;
}
