# GNU Make project for 'Samples.Rive'

# Parallel builds can be enabled using the environment variable MAKEFLAGS (eg: MAKEFLAGS="-j 4")
# For parallel execution in Windows, Make 4.0 or better is required

# Environment variable 'ANDROID_NDK' must point to NDK (eg: C:\Android\SDK\ndk-bundle)
# Environment variable 'ANDROID_PLATFORM' must point to active platform (eg: C:\Android\SDK\platforms\android-30)
# Toolchain (clang++), Java (javac) and Android Build Tools (dx, aapt, zipalign, apksigner) binaries must be added to 'PATH' environment variable

CC = armv7a-linux-androideabi17-clang
CXX = armv7a-linux-androideabi17-clang++
AR = arm-linux-androideabi-ar

CFLAGS_COMMON = -g -pipe -Wall -Werror -Wfatal-errors -Wtype-limits -fvisibility=hidden -fmerge-all-constants
CXXFLAGS_COMMON = $(CFLAGS_COMMON) -std=c++11 -fno-exceptions -frtti -fvisibility-inlines-hidden -fno-threadsafe-statics
LDFLAGS_COMMON = -Wextra -static-libstdc++

SHELLTYPE = msdos
ifeq (, $(ComSpec)$(COMSPEC))
  SHELLTYPE = posix
endif
ifeq (/bin, $(findstring /bin, $(SHELL)))
  SHELLTYPE = posix
endif
ifeq (/bin, $(findstring /bin, $(MAKESHELL)))
  SHELLTYPE = posix
endif

ifeq (posix, $(SHELLTYPE))
  DEVNUL = /dev/null
  WHICH = which
  MKDIR = mkdir -p "$(1)"
  BIN2H = ../../../Tools/Bin2h/bin2h.py
  CP = cp "$(1)" "$(2)"
  MV = mv "$(1)" "$(2)"
  RM = rm -f "$(1)"
  RMTREE = rm -rf "$(1)"
  FIXSLASHES = 
else
  DEVNUL = NUL
  WHICH = where
  MKDIR = mkdir "$(subst /,\,$(1))" 2> nul || exit 0
  BIN2H = ..\..\..\Tools\Bin2h\bin2h.exe
  CP = copy /Y "$(subst /,\,$(1))" "$(subst /,\,$(2))" > nul
  MV = move /Y "$(subst /,\,$(1))" "$(subst /,\,$(2))" > nul
  RM = del /Q "$(subst /,\,$(1))" 2> nul || exit 0
  RMTREE = rmdir /S /Q "$(subst /,\,$(1))" 2> nul || exit 0
  SED = ..\..\..\Tools\sed\sed.exe
  FIXSLASHES = $(SED) -i "s/\(\S\)\\\(\S\)/\1\/\2/g" "$(1)"
endif

ifeq (, $(shell ${WHICH} $(CC) 2> $(DEVNUL) ))
$(error $(CC) not found in PATH)
endif

ifeq (, $(shell ${WHICH} $(CXX) 2> $(DEVNUL) ))
$(error $(CXX) not found in PATH)
endif

ifeq ($(V), 1)
  Q =
else
  Q = @
endif

ifndef CONFIG
  CONFIG = Release
endif

ifeq ($(CONFIG), Debug)
  TARGET_DIR = ../../../../Bin/android_arm
  TARGET = ../../../../Bin/android_arm/libSamples_Rive.so
  TARGET_APK = ../../../../Bin/android_arm/Samples.Rive.apk
  INTERMEDIATE = build/Debug
  LIB_DIRS = 
  LIBS = -llog -lNoesis -lNoesisApp -landroid
  LIBS_DEPS = ../../../../Bin/android_arm/libNoesisApp.so ../../../../Bin/android_arm/libNoesis.so
  INCLUDES = -I../../../../Include -I../../../Packages/App/ApplicationLauncher/Include -I../../../Packages/App/DisplayLauncher/Include -I../../../Packages/App/Display/Include -I../../../Packages/App/Launcher/Include -I../../../Packages/App/Providers/Include -I../../../Packages/App/Rive/Include -Ibuild/Debug -I$(ANDROID_NDK)/sources/android/native_app_glue
  DEFINES = -DNS_BUILD -DNS_CONFIG=Debug -DNS_VERSION=3.2.0rc1 -DNS_APP_FRAMEWORK -DNS_LICENSE -DNS_DEBUG -DNS_PROFILE -DNS_MINIMUM_LOG_LEVEL=1
  CFLAGS = $(CFLAGS_COMMON) -D_DEBUG
  CXXFLAGS = $(CXXFLAGS_COMMON) -D_DEBUG
  LDFLAGS = $(LDFLAGS_COMMON) $(CXXFLAGS)
  AAPT_FLAGS = --debug-mode
else ifeq ($(CONFIG), Profile)
  TARGET_DIR = ../../../../Bin/android_arm
  TARGET = ../../../../Bin/android_arm/libSamples_Rive.so
  TARGET_APK = ../../../../Bin/android_arm/Samples.Rive.apk
  INTERMEDIATE = build/Profile
  LIB_DIRS = 
  LIBS = -llog -lNoesis -lNoesisApp -landroid
  LIBS_DEPS = ../../../../Bin/android_arm/libNoesisApp.so ../../../../Bin/android_arm/libNoesis.so
  INCLUDES = -I../../../../Include -I../../../Packages/App/ApplicationLauncher/Include -I../../../Packages/App/DisplayLauncher/Include -I../../../Packages/App/Display/Include -I../../../Packages/App/Launcher/Include -I../../../Packages/App/Providers/Include -I../../../Packages/App/Rive/Include -Ibuild/Profile -I$(ANDROID_NDK)/sources/android/native_app_glue
  DEFINES = -DNS_BUILD -DNS_CONFIG=Profile -DNS_VERSION=3.2.0rc1 -DNS_APP_FRAMEWORK -DNS_LICENSE -DNS_PROFILE -DNS_MINIMUM_LOG_LEVEL=2
  CFLAGS = $(CFLAGS_COMMON) -Ofast -DNDEBUG -ffunction-sections -fdata-sections -fno-asynchronous-unwind-tables -U_FORTIFY_SOURCE
  CXXFLAGS = $(CXXFLAGS_COMMON) -Ofast -DNDEBUG -ffunction-sections -fdata-sections -fno-asynchronous-unwind-tables -U_FORTIFY_SOURCE
  LDFLAGS = $(LDFLAGS_COMMON) $(CXXFLAGS) -fuse-ld=gold -Wl,-O3,--gc-sections,--icf=all
  AAPT_FLAGS = --debug-mode
else ifeq ($(CONFIG), Release)
  TARGET_DIR = ../../../../Bin/android_arm
  TARGET = ../../../../Bin/android_arm/libSamples_Rive.so
  TARGET_APK = ../../../../Bin/android_arm/Samples.Rive.apk
  INTERMEDIATE = build/Release
  LIB_DIRS = 
  LIBS = -llog -lNoesis -lNoesisApp -landroid
  LIBS_DEPS = ../../../../Bin/android_arm/libNoesisApp.so ../../../../Bin/android_arm/libNoesis.so
  INCLUDES = -I../../../../Include -I../../../Packages/App/ApplicationLauncher/Include -I../../../Packages/App/DisplayLauncher/Include -I../../../Packages/App/Display/Include -I../../../Packages/App/Launcher/Include -I../../../Packages/App/Providers/Include -I../../../Packages/App/Rive/Include -Ibuild/Release -I$(ANDROID_NDK)/sources/android/native_app_glue
  DEFINES = -DNS_BUILD -DNS_CONFIG=Release -DNS_VERSION=3.2.0rc1 -DNS_APP_FRAMEWORK -DNS_LICENSE
  CFLAGS = $(CFLAGS_COMMON) -Ofast -flto -DNDEBUG -ffunction-sections -fdata-sections -fno-asynchronous-unwind-tables -U_FORTIFY_SOURCE -fomit-frame-pointer
  CXXFLAGS = $(CXXFLAGS_COMMON) -Ofast -flto -DNDEBUG -ffunction-sections -fdata-sections -fno-asynchronous-unwind-tables -U_FORTIFY_SOURCE -fomit-frame-pointer
  LDFLAGS = $(LDFLAGS_COMMON) $(CXXFLAGS) -fuse-ld=gold -Wl,-O3,--gc-sections,--icf=all
  AAPT_FLAGS = 
else
  $(error Invalid configuration '$(CONFIG)')
endif

PCH =
PCHFLAGS =
DATA = $(INTERMEDIATE)/App.xaml.bin.h $(INTERMEDIATE)/MainWindow.xaml.bin.h $(INTERMEDIATE)/Milky\ Boba.otf.bin.h $(INTERMEDIATE)/background.riv.bin.h $(INTERMEDIATE)/logo.riv.bin.h $(INTERMEDIATE)/start.riv.bin.h $(INTERMEDIATE)/rewards.riv.bin.h $(INTERMEDIATE)/settings.riv.bin.h $(INTERMEDIATE)/leaves-tl.riv.bin.h $(INTERMEDIATE)/leaves-tr.riv.bin.h $(INTERMEDIATE)/leaves-br.riv.bin.h $(INTERMEDIATE)/leaves-bl.riv.bin.h

.SUFFIXES:
.DELETE_ON_ERROR:
.PHONY: all prebuild data clean

all: prebuild $(TARGET_APK)

prebuild:
	@echo ==== [Samples.Rive] Building '$(CONFIG)' configuration ====
ifndef ANDROID_NDK
	$(error Environment variable ANDROID_NDK not set)
endif
ifndef ANDROID_PLATFORM
	$(error Environment variable ANDROID_PLATFORM not set)
endif

data: $(DATA)

$(INTERMEDIATE):
	$(Q)$(call MKDIR,$(INTERMEDIATE))

$(TARGET_DIR):
	$(Q)$(call MKDIR,$(TARGET_DIR))

$(INTERMEDIATE)/android_native_app_glue.o: $(ANDROID_NDK)/sources/android/native_app_glue/android_native_app_glue.c | $(INTERMEDIATE)
	@echo [CC] $(notdir $<)
	$(Q)$(CC) $(CFLAGS) $(INCLUDES) $(DEFINES) -march=armv7-a -mthumb -fPIC -c -MMD -MF $(basename $@).d.tmp -MP -o $@ $< && $(call MV,$(basename $@).d.tmp,$(basename $@).d)

	$(Q)$(call FIXSLASHES,$(@:.o=.d))

$(INTERMEDIATE)/%.o: ../../../Packages/Samples/Rive/Src/%.cpp $(PCH) | $(INTERMEDIATE) data
	@echo [CXX] [Samples/Rive] $(notdir $<)
	$(Q)$(CXX) $(CXXFLAGS) $(PCHFLAGS) $(INCLUDES) $(DEFINES) -march=armv7-a -mthumb -fPIC -c -MMD -MF $(basename $@).d.tmp -MP -o $@ $< && $(call MV,$(basename $@).d.tmp,$(basename $@).d)

	$(Q)$(call FIXSLASHES,$(@:.o=.d))

$(INTERMEDIATE)/%.o: ../../../Packages/Samples/Rive/Src/%.c | $(INTERMEDIATE) data
	@echo [CC] [Samples/Rive] $(notdir $<)
	$(Q)$(CC) $(CFLAGS) $(INCLUDES) $(DEFINES) -march=armv7-a -mthumb -fPIC -c -MMD -MF $(basename $@).d.tmp -MP -o $@ $< && $(call MV,$(basename $@).d.tmp,$(basename $@).d)

	$(Q)$(call FIXSLASHES,$(@:.o=.d))

$(INTERMEDIATE)/App.xaml.bin.h: ../../../Packages/Samples/Rive/Data/App.xaml | $(INTERMEDIATE)
	@echo [BIN] [Samples/Rive] $(notdir $<)
	$(Q)$(BIN2H) "../../../Packages/Samples/Rive/Data/App.xaml" > "$(INTERMEDIATE)/App.xaml.bin.h" 

$(INTERMEDIATE)/MainWindow.xaml.bin.h: ../../../Packages/Samples/Rive/Data/MainWindow.xaml | $(INTERMEDIATE)
	@echo [BIN] [Samples/Rive] $(notdir $<)
	$(Q)$(BIN2H) "../../../Packages/Samples/Rive/Data/MainWindow.xaml" > "$(INTERMEDIATE)/MainWindow.xaml.bin.h" 

$(INTERMEDIATE)/Milky\ Boba.otf.bin.h: ../../../Packages/Samples/Rive/Data/Milky\ Boba.otf | $(INTERMEDIATE)
	@echo [BIN] [Samples/Rive] $(notdir $<)
	$(Q)$(BIN2H) "../../../Packages/Samples/Rive/Data/Milky Boba.otf" > "$(INTERMEDIATE)/Milky Boba.otf.bin.h" 

$(INTERMEDIATE)/background.riv.bin.h: ../../../Packages/Samples/Rive/Data/background.riv | $(INTERMEDIATE)
	@echo [BIN] [Samples/Rive] $(notdir $<)
	$(Q)$(BIN2H) "../../../Packages/Samples/Rive/Data/background.riv" > "$(INTERMEDIATE)/background.riv.bin.h" 

$(INTERMEDIATE)/logo.riv.bin.h: ../../../Packages/Samples/Rive/Data/logo.riv | $(INTERMEDIATE)
	@echo [BIN] [Samples/Rive] $(notdir $<)
	$(Q)$(BIN2H) "../../../Packages/Samples/Rive/Data/logo.riv" > "$(INTERMEDIATE)/logo.riv.bin.h" 

$(INTERMEDIATE)/start.riv.bin.h: ../../../Packages/Samples/Rive/Data/start.riv | $(INTERMEDIATE)
	@echo [BIN] [Samples/Rive] $(notdir $<)
	$(Q)$(BIN2H) "../../../Packages/Samples/Rive/Data/start.riv" > "$(INTERMEDIATE)/start.riv.bin.h" 

$(INTERMEDIATE)/rewards.riv.bin.h: ../../../Packages/Samples/Rive/Data/rewards.riv | $(INTERMEDIATE)
	@echo [BIN] [Samples/Rive] $(notdir $<)
	$(Q)$(BIN2H) "../../../Packages/Samples/Rive/Data/rewards.riv" > "$(INTERMEDIATE)/rewards.riv.bin.h" 

$(INTERMEDIATE)/settings.riv.bin.h: ../../../Packages/Samples/Rive/Data/settings.riv | $(INTERMEDIATE)
	@echo [BIN] [Samples/Rive] $(notdir $<)
	$(Q)$(BIN2H) "../../../Packages/Samples/Rive/Data/settings.riv" > "$(INTERMEDIATE)/settings.riv.bin.h" 

$(INTERMEDIATE)/leaves-tl.riv.bin.h: ../../../Packages/Samples/Rive/Data/leaves-tl.riv | $(INTERMEDIATE)
	@echo [BIN] [Samples/Rive] $(notdir $<)
	$(Q)$(BIN2H) "../../../Packages/Samples/Rive/Data/leaves-tl.riv" > "$(INTERMEDIATE)/leaves-tl.riv.bin.h" 

$(INTERMEDIATE)/leaves-tr.riv.bin.h: ../../../Packages/Samples/Rive/Data/leaves-tr.riv | $(INTERMEDIATE)
	@echo [BIN] [Samples/Rive] $(notdir $<)
	$(Q)$(BIN2H) "../../../Packages/Samples/Rive/Data/leaves-tr.riv" > "$(INTERMEDIATE)/leaves-tr.riv.bin.h" 

$(INTERMEDIATE)/leaves-br.riv.bin.h: ../../../Packages/Samples/Rive/Data/leaves-br.riv | $(INTERMEDIATE)
	@echo [BIN] [Samples/Rive] $(notdir $<)
	$(Q)$(BIN2H) "../../../Packages/Samples/Rive/Data/leaves-br.riv" > "$(INTERMEDIATE)/leaves-br.riv.bin.h" 

$(INTERMEDIATE)/leaves-bl.riv.bin.h: ../../../Packages/Samples/Rive/Data/leaves-bl.riv | $(INTERMEDIATE)
	@echo [BIN] [Samples/Rive] $(notdir $<)
	$(Q)$(BIN2H) "../../../Packages/Samples/Rive/Data/leaves-bl.riv" > "$(INTERMEDIATE)/leaves-bl.riv.bin.h" 

$(TARGET): $(LIBS_DEPS) $(INTERMEDIATE)/android_native_app_glue.o $(INTERMEDIATE)/Main.o | $(TARGET_DIR)
	@echo [LD] $(notdir $@)
	+$(Q)$(CXX) $(LDFLAGS) -march=armv7-a -mthumb -Wl,--fix-cortex-a8 -shared -Wl,--no-undefined -Wl,-soname,libSamples_Rive.so -L../../../../Bin/android_arm $(LIB_DIRS) -o $(TARGET) @$(CONFIG).rsp $(LIBS)
	@echo [STRIP] $(notdir $@)
	$(Q)arm-linux-androideabi-objcopy --only-keep-debug $(TARGET) $(TARGET).debug
	$(Q)arm-linux-androideabi-strip --strip-unneeded $(TARGET)
	$(Q)arm-linux-androideabi-objcopy --add-gnu-debuglink=$(TARGET).debug $(TARGET)

$(INTERMEDIATE)/java/com/noesis/Samples/Rive/NoesisNativeActivity.class: java/NoesisNativeActivity.java
	@echo [JAVA] $(notdir $<)
	$(Q)$(call MKDIR,$(INTERMEDIATE)/java)
	$(Q)javac -source 1.7 -target 1.7 -Xlint:-options -d $(INTERMEDIATE)/java -classpath "${ANDROID_PLATFORM}/android.jar" -sourcepath $(dir $<) $<

$(INTERMEDIATE)/apk/classes.dex: $(INTERMEDIATE)/java/com/noesis/Samples/Rive/NoesisNativeActivity.class
	@echo [DEX] $(notdir $@)
	$(Q)$(call MKDIR,$(INTERMEDIATE)/apk)
	$(Q)dx --dex --output=$(INTERMEDIATE)/apk/classes.dex $(INTERMEDIATE)/java

$(INTERMEDIATE)/Samples.Rive-unsigned.apk: $(TARGET) $(LIBS_DEPS) $(INTERMEDIATE)/apk/classes.dex AndroidManifest.xml
	@echo [AAPT] $(notdir $@)
	$(Q)$(call MKDIR,$(INTERMEDIATE)/apk/lib/armeabi-v7a)
	$(Q)$(call CP,$(TARGET),$(INTERMEDIATE)/apk/lib/armeabi-v7a)
	$(Q)$(call CP,../../../../Bin/android_arm/libNoesisApp.so,$(INTERMEDIATE)/apk/lib/armeabi-v7a)
	$(Q)$(call CP,../../../../Bin/android_arm/libNoesis.so,$(INTERMEDIATE)/apk/lib/armeabi-v7a)
	$(Q)aapt package -f -S res -M AndroidManifest.xml $(AAPT_FLAGS) -I $(ANDROID_PLATFORM)/android.jar -F $(INTERMEDIATE)/Samples.Rive-unsigned.apk $(INTERMEDIATE)/apk

$(INTERMEDIATE)/Samples.Rive-unsigned-aligned.apk: $(INTERMEDIATE)/Samples.Rive-unsigned.apk
	@echo [ALIGN] $(notdir $@)
	$(Q)zipalign -f 4 $(INTERMEDIATE)/Samples.Rive-unsigned.apk $(INTERMEDIATE)/Samples.Rive-unsigned-aligned.apk

$(TARGET_APK): $(INTERMEDIATE)/Samples.Rive-unsigned-aligned.apk
	@echo [SIGN] $(notdir $@)
	$(Q)apksigner sign --ks android.jks --ks-pass pass:noesis --out $(TARGET_APK) $(INTERMEDIATE)/Samples.Rive-unsigned-aligned.apk

-include $(INTERMEDIATE)/android_native_app_glue.d $(INTERMEDIATE)/Main.d

run:
	$(Q)adb install -r $(TARGET_APK)
	$(Q)adb logcat -c
	$(Q)adb shell monkey -p com.noesis.Samples.Rive -c android.intent.category.LAUNCHER 1
	$(Q)adb logcat -s Noesis:V VALIDATION

enable_validation:
	$(Q)@echo =====================================================================
	$(Q)@echo https://github.com/KhronosGroup/Vulkan-ValidationLayers/releases
	$(Q)@echo Copy libVkLayer_khronos_validation.so next to Makefile
	$(Q)@echo Copy libc++_shared.so to build/$(CONFIGURATION)/apk/lib/armeabi-v7a
	$(Q)@echo =====================================================================
	$(Q)adb push libVkLayer_khronos_validation.so /data/local/tmp
	$(Q)adb shell run-as com.noesis.Samples.Rive cp /data/local/tmp/libVkLayer_khronos_validation.so .
	$(Q)adb shell settings put global enable_gpu_debug_layers 1
	$(Q)adb shell settings put global gpu_debug_app com.noesis.Samples.Rive
	$(Q)adb shell settings put global gpu_debug_layers VK_LAYER_KHRONOS_validation

disable_validation:
	$(Q)adb shell settings delete global enable_gpu_debug_layers
	$(Q)adb shell settings delete global gpu_debug_app
	$(Q)adb shell settings delete global gpu_debug_layers

clean:
	@echo ==== [Samples.Rive] Cleaning '$(CONFIG)' configuration ====
	$(Q)$(call RMTREE,$(INTERMEDIATE))
	$(Q)$(call RM,$(TARGET))
	$(Q)$(call RM,$(TARGET).debug)
	$(Q)$(call RM,$(TARGET_APK))
