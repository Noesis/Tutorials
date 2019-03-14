package com.noesis.Samples.UserControl;

public class NoesisNativeActivity extends android.app.NativeActivity
{
    static
    {
        System.loadLibrary("Noesis");
        System.loadLibrary("NoesisApp");
    }
}
