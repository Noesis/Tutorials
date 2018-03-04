LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)
LOCAL_MODULE := Noesis
LOCAL_SRC_FILES := ../../NoesisGUI-android/Bin/libNoesis.so
LOCAL_EXPORT_C_INCLUDES := ../NoesisGUI-android/Include
include $(PREBUILT_SHARED_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE := HelloTriangle
LOCAL_SRC_FILES := HelloTriangle.cpp
LOCAL_STATIC_LIBRARIES := android_native_app_glue
LOCAL_SHARED_LIBRARIES := Noesis
LOCAL_LDLIBS := -ldl -lGLESv2 -lEGL -landroid -llog
include $(BUILD_SHARED_LIBRARY)

$(call import-module,android/native_app_glue)
