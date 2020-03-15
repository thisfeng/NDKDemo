package com.thisfeng.ccalljava;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.view.View;
import android.widget.TextView;
import android.widget.Toast;

/**
 * 打开 log 查看 效果
 * <p>
 * <p>
 * * 让C代码调用 java 中JNI类的 public int add(int x, int y)
 * * 让C代码调用 public void helloFromJava()
 * *  让C代码调用 void printString(String s)
 * *  让C代码静态方法 static void sayHello(String s)
 * *  让C代码调用 MainActivity 中的showToast 方法进行更新UI（谁调用就是谁的实例）
 *
 */
public class MainActivity extends AppCompatActivity {

    private TextView tvContent;

    private JNI jni;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        tvContent = findViewById(R.id.tvContent);

        jni = new JNI();
    }


    /**
     * 让C代码调用MainActiity里面的showToast
     */
    public native void callBackShowToast();


    public void onClick(View view) {
//        jni.callbackAdd();
//        jni.callbackHelloFromJava();
//        jni.callbackPrintString();
//        jni.callbackSayHello();

        //更新UI
//        jni.callBackShowToast(); //上下文对象错误

        this.callBackShowToast();//使用当前的上下文
    }

    public void showToast() {
        System.out.println("showToast----------------");
        Toast.makeText(MainActivity.this, "showToast----------------", Toast.LENGTH_SHORT).show();
    }

}
