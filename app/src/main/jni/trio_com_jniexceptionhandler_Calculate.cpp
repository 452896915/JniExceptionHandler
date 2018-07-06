//
// Created by JackMeGo on 2018/7/2.
//

#include "trio_com_jniexceptionhandler_Calculate.h"
/*
jni捕获异常的方法之一：在每句jni调用之后判断是否发生了异常，如果有异常，打印log，进行处理，可以往java层抛出异常。
这种方法适用于jni代码量很小的情况。
*/

int checkExc(JNIEnv *env) {
    if(env->ExceptionCheck()) {
        env->ExceptionDescribe(); // writes to logcat
        env->ExceptionClear();
        return 1;
    }
    return -1;
}

void JNU_ThrowByName(JNIEnv *env, const char *name, const char *msg)
{
     // 查找异常类
     jclass cls = env->FindClass(name);
     /* 如果这个异常类没有找到，VM会抛出一个NowClassDefFoundError异常 */
     if (cls != NULL) {
         env->ThrowNew(cls, msg);  // 抛出指定名字的异常
     }
     /* 释放局部引用 */
     env->DeleteLocalRef(cls);
 }

JNIEXPORT jint JNICALL Java_trio_com_jniexceptionhandler_Calculate_jniDivide
  (JNIEnv * env, jobject jobj, jint m, jint n) {
    char* a = NULL;
    int val1 = a[1] - '0';

    // 每句jni执行之后都加入异常检查
    if (checkExc(env)) {
        LOGE("jni exception happened at p0");
        JNU_ThrowByName(env, "java/lang/Exception", "exception from jni: jni exception happened at p0");
        return -1;
    }

    char* b = NULL;
    int val2 = b[1] - '0';

    // 每句jni执行之后都加入异常检查
    if (checkExc(env)) {
        LOGE("jni exception happened at p1");
        JNU_ThrowByName(env, "java/lang/Exception", "exception from jni: jni exception happened at p1");
        return -1;
    }
    return val1/val2;
}