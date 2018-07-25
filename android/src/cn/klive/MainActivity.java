package cn.klive;


import android.content.Context;
import android.os.Build;
import android.os.Bundle;
import android.view.WindowManager;

public class MainActivity extends org.qtproject.qt5.android.bindings.QtActivity {

    private static Context context;

    @Override
    public void onCreate(Bundle savedInstanceState) {
        context = getApplicationContext();
        getWindow().addFlags(WindowManager.LayoutParams.FLAG_KEEP_SCREEN_ON);   //应用运行时，保持屏幕高亮，不锁屏
        super.onCreate(savedInstanceState);        

    }


    //全局获取Context
    public static Context getContext() {
        return context;
    }

}


