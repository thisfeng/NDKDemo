package com.thisfeng.ccalljava;

import android.util.Log;

/**
 * @author：thisfeng
 * @time 2020/3/9 12:25
 */
public class JNI {


    static {
        System.loadLibrary("ccalljava");
    }


    /**
     * 当执行这个方法的时候，让C代码调用
     * public int add(int x, int y)
     */
    public native void callbackAdd();

    /**
     * 当执行这个方法的时候，让C代码调用
     * public void helloFromJava()
     */
    public native void callbackHelloFromJava();


    /**
     * 当执行这个方法的时候，让C代码调用void printString(String s)
     */
    public native void callbackPrintString();

    /**
     * 当执行这个方法的时候，让C代码静态方法 static void sayHello(String s)
     */
    public native void callbackSayHello();


    public int add(int x, int y) {
        //接收到 C 传递过来的参数 进行使用 ，在 java 层 进行 相加处理 然后返回
        Log.e("TAG", "add() x=" + x + " y=" + y);
        return x + y;
    }

    public void helloFromJava() {
        Log.e("TAG", "helloFromJava()");
    }

    public void printString(String s) {
        Log.e("TAG", "C中输入的：" + s);
    }

    public static void sayHello(String s) {
        Log.e("TAG", "我是java代码中的JNI.java中的sayHello(String s)静态方法，我被C调用了:" + s);
    }



}
