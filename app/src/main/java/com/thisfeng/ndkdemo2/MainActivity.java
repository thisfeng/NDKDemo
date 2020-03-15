package com.thisfeng.ndkdemo2;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.TextView;
import android.widget.Toast;

/**
 * 1、Java 调用 C 执行加法运算
 * 2、Java 调用 C 执行字符串拼接运算
 * 3、Java 调用 C 执行数组运算
 * 4、Java 调用 C 执行密码校验
 */
public class MainActivity extends AppCompatActivity {

    private JNI mJIN;
    private TextView tvContent;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        tvContent = findViewById(R.id.tvContent);

        mJIN = new JNI();

        String result = mJIN.sayHello();

        tvContent.setText(result);

        System.out.println("result==" + result);
    }

    public void add(View view) {

        int result = mJIN.add(99, 1);

        Toast.makeText(this, String.valueOf(result), Toast.LENGTH_SHORT).show();
    }

    public void string(View view) {
        String result = mJIN.sayHello("Iam from java");
        Toast.makeText(this, result, Toast.LENGTH_SHORT).show();
    }

    public void array(View view) {

        int[] array = {1, 2, 3, 4, 5};
        int[] result = mJIN.increaseArrayEles(array);

        StringBuilder stringBuffer = new StringBuilder();
        for (int i = 0; i < result.length; i++) {
            Log.e(MainActivity.class.getSimpleName(), "array[" + i + "]===" + result[i]);
            stringBuffer.append("array[" + i + "]===" + result[i]);
            stringBuffer.append("\n");
        }

        tvContent.setText(stringBuffer.toString());

    }


    public void checkpwd(View view) {
        int result = mJIN.checkPwd("123456");
        Toast.makeText(this, String.valueOf(result), Toast.LENGTH_SHORT).show();
    }
}
