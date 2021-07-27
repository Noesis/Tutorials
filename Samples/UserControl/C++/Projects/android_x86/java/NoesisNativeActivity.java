package com.noesis.Samples.UserControl;

import android.annotation.TargetApi;
import android.view.View;
import android.os.Bundle;

public class NoesisNativeActivity extends android.app.NativeActivity
{
    static
    {
        System.loadLibrary("Noesis");
        System.loadLibrary("NoesisApp");
    }

    @Override
    public void onWindowFocusChanged(boolean hasFocus)
    {
        super.onWindowFocusChanged(hasFocus);
        if (hasFocus)
        {
            if (android.os.Build.VERSION.SDK_INT >= 19)
            {
                setImmersiveSticky();
            }
        }
    }

    @Override
    protected void onCreate(Bundle savedInstanceState)
    {
        super.onCreate(savedInstanceState);
        if (android.os.Build.VERSION.SDK_INT >= 19)
        {
            setImmersiveSticky();
        }
    }

    @TargetApi(19)
    @SuppressWarnings("deprecation")
    void setImmersiveSticky()
    {
        View decorView = getWindow().getDecorView();
        decorView.setSystemUiVisibility
        (
            // https://developer.android.com/training/system-ui/immersive
            View.SYSTEM_UI_FLAG_IMMERSIVE_STICKY |
            View.SYSTEM_UI_FLAG_LAYOUT_STABLE |
            View.SYSTEM_UI_FLAG_LAYOUT_HIDE_NAVIGATION |
            View.SYSTEM_UI_FLAG_LAYOUT_FULLSCREEN |
            View.SYSTEM_UI_FLAG_HIDE_NAVIGATION |
            View.SYSTEM_UI_FLAG_FULLSCREEN
        );
    }
}
