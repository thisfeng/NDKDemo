//
// Created by ThisFeng on 2020/3/9.
//

#include <jni.h>
#include <stdio.h>


//打印log
#include <android/log.h>

#define LOG_TAG "C_LOG"//自定义 tag
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__)

#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__) // （ 参数 等级 , tag , args ）
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)


/**
 * 让C代码调用 java 中JNI类的 public int add(int x, int y)
 */
JNIEXPORT void JNICALL
Java_com_thisfeng_ccalljava_JNI_callbackAdd(JNIEnv *env, jobject thiz) {
    //1.得到字节码
    //jclass      (*FindClass)(JNIEnv*, const char*);
    jclass jclazz = (*env)->FindClass(env, "com/thisfeng/ccalljava/JNI");//注意需要将包.使用 / 杠 类名
    //2. 通过字节码得到方法
    //jmethodID   (*GetMethodID)(JNIEnv*, jclass, const char*, const char*);
    //最后一个参数是方法签名 ,IDE 可自动生成 对应的签名标记，输入任意 进行 提示 fix
    jmethodID jmethodIDs = (*env)->GetMethodID(env, jclazz, "add", "(II)I");
    //3.实例化该类 , 分配对象
    // jobject     (*AllocObject)(JNIEnv*, jclass);
    jobject jobject = (*env)->AllocObject(env, jclazz);
    //4.调用方法
    //jint        (*CallIntMethod)(JNIEnv*, jobject, jmethodID, ...);
    jint value = (*env)->CallIntMethod(env, jobject, jmethodIDs, 99, 1); //传入的参数 可在java中使用
    //成功调用了public int add(int x, int y)
//    printf("value===%d\n", value);
    LOGE("value===%d\n", value); //注意 要打印有返回值 的
}

/**
 * 让C代码调用 public void helloFromJava()
 */
JNIEXPORT void JNICALL
Java_com_thisfeng_ccalljava_JNI_callbackHelloFromJava(JNIEnv *env, jobject thiz) {
    //1.得到字节码
    //jclass      (*FindClass)(JNIEnv*, const char*);
    jclass jclazz = (*env)->FindClass(env, "com/thisfeng/ccalljava/JNI");//注意需要将包.使用 / 杠 类名
    //2. 通过字节码得到方法
    //jmethodID   (*GetMethodID)(JNIEnv*, jclass, const char*, const char*);
    //最后一个参数是方法签名  
    jmethodID jmethodIDs = (*env)->GetMethodID(env, jclazz, "helloFromJava", "()V");
    //3.实例化该类 , 分配对象
    // jobject     (*AllocObject)(JNIEnv*, jclass);
    jobject jobject = (*env)->AllocObject(env, jclazz);
    //4.调用方法
    //void        (*CallVoidMethod)(JNIEnv*, jobject, jmethodID, ...);
    (*env)->CallVoidMethod(env, jobject, jmethodIDs); //传入的参数 可在java中使用
    //成功调用了public void helloFromJava()

}
/**
 * 让C代码调用void printString(String s)
 */

JNIEXPORT void JNICALL
Java_com_thisfeng_ccalljava_JNI_callbackPrintString(JNIEnv *env, jobject thiz) {
    //1.得到字节码
    //jclass      (*FindClass)(JNIEnv*, const char*);
    jclass jclazz = (*env)->FindClass(env, "com/thisfeng/ccalljava/JNI");//注意需要将包.使用 / 杠 类名
    //2. 通过字节码得到方法
    //jmethodID   (*GetMethodID)(JNIEnv*, jclass, const char*, const char*);
    //最后一个参数是方法签名
    jmethodID jmethodIDs = (*env)->GetMethodID(env, jclazz, "printString", "(Ljava/lang/String;)V");
    //3.实例化该类 , 分配对象
    // jobject     (*AllocObject)(JNIEnv*, jclass);
    jobject jobject = (*env)->AllocObject(env, jclazz);
    //4.调用方法
    //void        (*CallVoidMethod)(JNIEnv*, jobject, jmethodID, ...);
    //jstring     (*NewStringUTF)(JNIEnv*, const char*);//java 的String 对应 JNI 里面的 jstring
    jstring jst = (*env)->NewStringUTF(env, "I am thisfeng!!!(*env)->");


    (*env)->CallVoidMethod(env, jobject, jmethodIDs, jst); //传入的参数 可在java中使用


}
/**
 * 让C代码调用 静态方法 static void sayHello(String s)
 */
JNIEXPORT void JNICALL
Java_com_thisfeng_ccalljava_JNI_callbackSayHello(JNIEnv *env, jobject thiz) {
    //1.得到字节码
    //jclass      (*FindClass)(JNIEnv*, const char*);
    jclass jclazz = (*env)->FindClass(env, "com/thisfeng/ccalljava/JNI");//注意需要将包.使用 / 杠 类名
    //2. 通过字节码得到方法
    //jmethodID   (*GetMethodID)(JNIEnv*, jclass, const char*, const char*);
    //最后一个参数是方法签名
    jmethodID jmethodIDs = (*env)->GetStaticMethodID(env, jclazz, "sayHello","(Ljava/lang/String;)V");//调用静态方法 不需要实例化

    //3.创建jstring 对象 对应方法 传递给 java
    //void        (*CallStaticVoidMethod)(JNIEnv*, jclass, jmethodID, ...);
    jstring jst1 = (*env)->NewStringUTF(env, "I am Android 123");
    //log 直接打印 jst1 会报错
    //4.调用方法
    (*env)->CallStaticVoidMethod(env, jclazz, jmethodIDs, jst1); //传入的参数 可在java中使用
    //成功调用了public void sayHello()
}
/**
 * instance:谁调用了当前 Java_com_thisfeng_ccalljava_JNI_callBackShowToast 对应的Java的接口
 * 就是谁的实例：当前是JNI.this-->MainActivity.this
 */
JNIEXPORT void JNICALL
Java_com_thisfeng_ccalljava_JNI_callBackShowToast(JNIEnv *env, jobject instance) {
    //1.得到字节码
    //jclass      (*FindClass)(JNIEnv*, const char*);
    jclass jclazz = (*env)->FindClass(env, "com/thisfeng/ccalljava/MainActivity");
    //2. 通过字节码得到方法
    //jmethodID   (*GetMethodID)(JNIEnv*, jclass, const char*, const char*);
    //最后一个参数是方法签名
    jmethodID jmethodIDs = (*env)->GetMethodID(env, jclazz, "showToast", "()V");
    //3.实例化该类 , 分配对象
    // jobject     (*AllocObject)(JNIEnv*, jclass);
    jobject jobject = (*env)->AllocObject(env, jclazz);
    //4.调用方法
    //void        (*CallVoidMethod)(JNIEnv*, jobject, jmethodID, ...);

    //// 此方式错误
    (*env)->CallVoidMethod(env, jobject, jmethodIDs); //传入的参数 可在java中使用
    //成功调用了public void helloFromJava()

}

/**
 *  instance:谁调用了当前 Java_com_thisfeng_ccalljava_JNI_callBackShowToast 对应的Java的接口
 * 就是谁的实例：当前是JNI.this-->MainActivity.this
 *
 * 需要使用此
 * @param env
 * @param thiz
 */
JNIEXPORT void JNICALL
Java_com_thisfeng_ccalljava_MainActivity_callBackShowToast(JNIEnv *env, jobject instance) {
    //1.得到字节码
    //jclass      (*FindClass)(JNIEnv*, const char*);
    jclass jclazz = (*env)->FindClass(env, "com/thisfeng/ccalljava/MainActivity");
    //2. 通过字节码得到方法
    //jmethodID   (*GetMethodID)(JNIEnv*, jclass, const char*, const char*);
    //最后一个参数是方法签名
    jmethodID jmethodIDs = (*env)->GetMethodID(env, jclazz, "showToast", "()V");
    //3.实例化该类 , 分配对象
    // jobject     (*AllocObject)(JNIEnv*, jclass);
//    jobject jobject = (*env)->AllocObject(env, jclazz);
    //4.调用方法
    //void        (*CallVoidMethod)(JNIEnv*, jobject, jmethodID, ...);
    (*env)->CallVoidMethod(env, instance, jmethodIDs); //传入的参数 可在java中使用
    //成功调用了public void helloFromJava()

}