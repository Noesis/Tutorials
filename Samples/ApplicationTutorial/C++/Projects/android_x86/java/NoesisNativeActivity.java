package com.noesis.Samples.ApplicationTutorial;

public class NoesisNativeActivity extends android.app.NativeActivity
{
    static
    {
        System.loadLibrary("Noesis");
        System.loadLibrary("NoesisApp");
    }
}
