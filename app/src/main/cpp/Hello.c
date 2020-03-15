//
// Created by ThisFeng on 2020/3/8.
//

// 引入一些头文件库方法
#include <stdio.h>
#include <stdlib.h>

#include <jni.h>
#include <string.h>


//打印log
#include <android/log.h>

#define LOG_TAG "C_LOG"//自定义 tag
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__)

#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__) // （ 参数 等级 , tag , args ）
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)


//tips:在native-lib.cpp文件中添加多少方法，必须添加在 extern "c" { } 中，或者在每个方法前加 extern "c" , 否则会报找不到方法!
//当前为 .c 文件可省略 extern "c" { }
/**
 * 把一个jstring转换成一个c语言的char* 类型.
 */
char *_JString2CStr(JNIEnv *env, jstring jstr) {
    char *rtn = NULL;
    jclass clsstring = (*env)->FindClass(env, "java/lang/String");
    jstring strencode = (*env)->NewStringUTF(env, "GB2312");
    jmethodID mid = (*env)->GetMethodID(env, clsstring, "getBytes", "(Ljava/lang/String;)[B");
    jbyteArray barr = (jbyteArray) (*env)->CallObjectMethod(env, jstr, mid,
                                                            strencode); // String .getByte("GB2312");
    jsize alen = (*env)->GetArrayLength(env, barr);
    jbyte *ba = (*env)->GetByteArrayElements(env, barr, JNI_FALSE);
    if (alen > 0) {
        rtn = (char *) malloc(alen + 1); //"\0"
        memcpy(rtn, ba, alen);
        rtn[alen] = 0;
    }
    (*env)->ReleaseByteArrayElements(env, barr, ba, 0);
    return rtn;
}


/**
jsString ：返回值
Java_全类名_方法名
JNIENV* env：里面有很多 C 的方法
jObject obj：谁调用了这个方法就是谁的实例
当前 就是 JNI.this
*/

//返回值也可以自定义 对称的，也可以如下方法 自动创建  ： JNIEXPORT 类型 JNICALL
jstring Java_com_thisfeng_ndkdemo2_JNI_sayHello__(JNIEnv *env, jobject jobj) {

    char *text = "I an From C ～";

    //jstring     (*NewStringUTF)(JNIEnv*, const char*);
    return (*env)->NewStringUTF(env, text);

}

/**
 *  java 重载方法 ，携带参数 s
 *
 *
 * 从java传入字符串，C代码进程拼接
     *
     * @param java : I am from java
     *        c    : add I am from C
     * @return  I am form java add I am from C
 */
JNIEXPORT jstring JNICALL
Java_com_thisfeng_ndkdemo2_JNI_sayHello__Ljava_lang_String_2(JNIEnv *env, jobject thiz,
                                                             jstring jstr) {

    char *fromJava = _JString2CStr(env, jstr);//I am form java
    //C:
    char *fromC = " add I am from C! 很高兴拼接成功";
    //拼接函数 strcat
    strcat(fromJava, fromC);//拼接的结果放在第一参数里面
    LOGE("fromJava===%s\n", fromJava);

    //jstring     (*NewStringUTF)(JNIEnv*, const char*);
    return (*env)->NewStringUTF(env, fromJava);
}

/**
 * 3.5 IDE 自动生成创建JNI对应的 C 方法
 */
JNIEXPORT jint JNICALL
Java_com_thisfeng_ndkdemo2_JNI_add(JNIEnv *env, jobject thiz, jint jx, jint jy) {

    int result = jx + jy;

    LOGE("value===%d\n", result);

    return result;
}

/**
 * 给每个元素加上10
 *
 *
 */
JNIEXPORT jintArray JNICALL
Java_com_thisfeng_ndkdemo2_JNI_increaseArrayEles(JNIEnv *env, jobject thiz, jintArray jarray) {

    //1.得到数组的长度
    // jsize       (*GetArrayLength)(JNIEnv*, jarray);
    jsize size = (*env)->GetArrayLength(env, jarray);
    //2.得到数组元素
    //jint*       (*GetIntArrayElements)(JNIEnv*, jintArray, jboolean*);
    jint *intArray = (*env)->GetIntArrayElements(env, jarray,
                                                 JNI_FALSE);//  true 重新开辟内存空间操作数组；false 相当于同一份就在当前传入的 jarray 的 Native 内存空间去操作数组

    //3.遍历数组，给每个元素加上10
    int i;
    for (i = 0; i < size; ++i) {
//                *(intArray+i) = *(intArray+i) + 10;
        *(intArray + i) += 10;//每循环一次指针往后移动下一位
    }

    // 4.使用完了别忘了释放内存 释放数组。注意：释放模式为0，java数组会修改；如果是JNI_ABORT，java的数组并不会被修改
    (*env)->ReleaseIntArrayElements(env, jarray, intArray, 0);
    //5.返回结果
    return jarray;
}

/**
 * 校验密码
 */
JNIEXPORT jint JNICALL
Java_com_thisfeng_ndkdemo2_JNI_checkPwd(JNIEnv *env, jobject thiz, jstring password) {

    //服务器的密码是123456
    char *origin = "123456";
    char *fromUser = _JString2CStr(env, password);
    //函数比较字符串是否相同
    int code = strcmp(origin, fromUser);

    if (code == 0) {
        return 200;
    } else {
        return 400;
    }
}

/**
 * -------------------------
 */
