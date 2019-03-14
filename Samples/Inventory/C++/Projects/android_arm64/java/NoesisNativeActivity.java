package com.noesis.Samples.Inventory;

public class NoesisNativeActivity extends android.app.NativeActivity
{
    static
    {
        System.loadLibrary("Noesis");
        System.loadLibrary("NoesisApp");
    }
}
