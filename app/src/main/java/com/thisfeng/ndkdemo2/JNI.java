package com.thisfeng.ndkdemo2;

/**
 * @author：thisfeng
 * @time 2020/3/8 17:10
 * <p>
 * 编写本地 方法
 */
public class JNI {


    /**
     * 加载动态链接库 和C 代码进行交互
     *
     * 编译的动态链接库 是以当前 的 module 名称为库名称，  lib+moduleName+.so
     *
     * 并且在 build.gradle 中配置 NDK 对应的 CPU 架构 ，并配置动态链接库名称
     *   ndk{
     *             moduleName "Hello" //so文件: lib+moduleName+.so
     *             abiFilters   "armeabi-v7a", "x86", 'x86_64' //cpu的类型一定要适配多数，否则运行在少部分机型上会崩溃
     *    }
     *
     *     也需要在 CMakeLists.txt 配置 编译动态链接库名称 保持一致
     */
    static {
        System.loadLibrary("Hello");
    }

    /**
     * 重载方法 ，无参数的调用
     */
    public native String sayHello();


    /**
     * 让C代码做加法运算，把结果返回
     *
     * @param x
     * @param y
     * @return
     */
    public native int add(int x, int y);

    /**
     * 定义  native 方法
     * 调用 C 代码对应的方法
     * 从java传入字符串，C代码进程拼接
     * *
     * * @param s I am from java
     * * @return  I am form java add I am from C
     */

    public native String sayHello(String s);

    /**
     * 从 Native 返回基本数据类型数组
     * <p>
     * 让C代码给每个元素都加上10
     */

    public native int[] increaseArrayEles(int[] intArray);

    /**
     * 应用: 检查密码是否正确, 如果正确返回200, 否则返回400
     */
    public native int checkPwd(String password);


}
