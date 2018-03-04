package com.example.hellotriangle;

import android.app.NativeActivity;
import android.os.Bundle;

public class HelloTriangle extends NativeActivity {

	static {
		System.loadLibrary("Noesis");
	}
	
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		
		setContentView(android.R.layout.activity_list_item);
	}
}
