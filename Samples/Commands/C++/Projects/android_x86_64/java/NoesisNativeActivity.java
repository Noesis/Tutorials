package com.noesis.Samples.Commands;

public class NoesisNativeActivity extends android.app.NativeActivity
{
    static
    {
        System.loadLibrary("Noesis");
        System.loadLibrary("NoesisApp");
    }
}
