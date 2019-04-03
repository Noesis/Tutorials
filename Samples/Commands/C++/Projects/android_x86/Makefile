# GNU Make project for 'Samples.Commands'

# Parallel builds can be enabled using the environment variable MAKEFLAGS (eg: MAKEFLAGS="-j 4")
# For parallel execution in Windows, Make 4.0 or better is required

# Environment variable 'ANDROID_NDK' must point to NDK (eg: C:\Android\SDK\ndk-bundle)
# Environment variable 'ANDROID_PLATFORM' must point to active platform (eg: C:\Android\SDK\platforms\android-17)
# Environment variable 'JAVA_HOME' must point to JDK (eg: C:\Program Files\Java\jdk1.8.0_192)
# Toolchain (clang++) and Android Build Tools (aapt) binaries must be added to 'PATH' environment variable

include ../../../../../../Config/Common.android.makeprops
include ../../../../../../Config/Debug/Debug.android.makeprops
include ../../../../../../Config/Profile/Profile.android.makeprops
include ../../../../../../Config/Release/Release.android.makeprops

CC = i686-linux-android-clang
CXX = i686-linux-android-clang++

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
  MKDIR = $(Q)mkdir -p "$(1)"
  BIN2H = ../../../../../Tools/Bin2h/bin2h.py
  CP = $(Q)cp "$(1)" "$(2)"
  RM = $(Q)rm -f "$(1)"
  RMTREE = $(Q)rm -rf "$(1)"
  FIXSLASHES = 
else
  MKDIR = $(Q)mkdir "$(subst /,\,$(1))" 2> nul || exit 0
  BIN2H = ..\..\..\..\..\Tools\Bin2h\bin2h.exe
  CP = $(Q)copy /Y "$(subst /,\,$(1))" "$(subst /,\,$(2))" > nul
  RM = $(Q)del /Q "$(subst /,\,$(1))" 2> nul || exit 0
  RMTREE = $(Q)rmdir /S /Q "$(subst /,\,$(1))" 2> nul || exit 0
  SED = ..\..\..\..\..\Tools\sed\sed.exe
  FIXSLASHES = $(Q)$(SED) -i "s/\(\S\)\\/\1\//g" "$(1)"
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
  TARGET_DIR = ../../../../../../Bin/android_x86
  TARGET = ../../../../../../Bin/android_x86/libSamples_Commands.so
  TARGET_APK = ../../../../../../Bin/android_x86/Samples.Commands.apk
  INTERMEDIATE = build/Debug
  LIB_DIRS = 
  LIBS = -lNoesisApp -landroid -llog -lNoesis
  LIBS_DEPS = ../../../../../../Bin/android_x86/libNoesisApp.so ../../../../../../Bin/android_x86/libNoesis.so
  INCLUDES = -I../../../../App/Display/Include -I../../../../Core/Kernel/Include -I../../../../../../Include -I../../../../Core/Nullable/Include -I../../../../App/Providers/Include -I../../../../Math/Utils/Include -I../../../../App/ApplicationLauncher/Include -I../../../../Gui/Core/Include -I../../../../Samples/Commands/Include -I../../../../App/DisplayLauncher/Include -I../../../../../../3rdParty/EASTL/local/include -I../../../../Math/VectorMath/Include -I../../../../Gui/DependencySystem/Include -I../../../../App/Launcher/Include -I../../../../Drawing/Types/Include -I../../../../Core/NSTL/Include -I../../../../Gui/CachedFontProvider/Include -I../../../../Gui/Providers/Include -Ibuild/Debug -I$(ANDROID_NDK)/sources/android/native_app_glue
  DEFINES = -DNS_BUILD -DNS_CONFIG=Debug -DNS_VERSION=2.2.1 -DNS_APP_FRAMEWORK -DNS_DEBUG -DNS_PROFILE -DNS_MINIMUM_LOG_LEVEL=1
  CFLAGS = $(CFLAGS_DEBUG)
  CXXFLAGS = $(CXXFLAGS_DEBUG)
  LDFLAGS = $(LDFLAGS_DEBUG)
else ifeq ($(CONFIG), Profile)
  TARGET_DIR = ../../../../../../Bin/android_x86
  TARGET = ../../../../../../Bin/android_x86/libSamples_Commands.so
  TARGET_APK = ../../../../../../Bin/android_x86/Samples.Commands.apk
  INTERMEDIATE = build/Profile
  LIB_DIRS = 
  LIBS = -lNoesisApp -landroid -llog -lNoesis
  LIBS_DEPS = ../../../../../../Bin/android_x86/libNoesisApp.so ../../../../../../Bin/android_x86/libNoesis.so
  INCLUDES = -I../../../../App/Display/Include -I../../../../Core/Kernel/Include -I../../../../../../Include -I../../../../Core/Nullable/Include -I../../../../App/Providers/Include -I../../../../Math/Utils/Include -I../../../../App/ApplicationLauncher/Include -I../../../../Gui/Core/Include -I../../../../Samples/Commands/Include -I../../../../App/DisplayLauncher/Include -I../../../../../../3rdParty/EASTL/local/include -I../../../../Math/VectorMath/Include -I../../../../Gui/DependencySystem/Include -I../../../../App/Launcher/Include -I../../../../Drawing/Types/Include -I../../../../Core/NSTL/Include -I../../../../Gui/CachedFontProvider/Include -I../../../../Gui/Providers/Include -Ibuild/Profile -I$(ANDROID_NDK)/sources/android/native_app_glue
  DEFINES = -DNS_BUILD -DNS_CONFIG=Profile -DNS_VERSION=2.2.1 -DNS_APP_FRAMEWORK -DNS_PROFILE -DNS_MINIMUM_LOG_LEVEL=2
  CFLAGS = $(CFLAGS_PROFILE)
  CXXFLAGS = $(CXXFLAGS_PROFILE)
  LDFLAGS = $(LDFLAGS_PROFILE)
else ifeq ($(CONFIG), Release)
  TARGET_DIR = ../../../../../../Bin/android_x86
  TARGET = ../../../../../../Bin/android_x86/libSamples_Commands.so
  TARGET_APK = ../../../../../../Bin/android_x86/Samples.Commands.apk
  INTERMEDIATE = build/Release
  LIB_DIRS = 
  LIBS = -lNoesisApp -landroid -llog -lNoesis
  LIBS_DEPS = ../../../../../../Bin/android_x86/libNoesisApp.so ../../../../../../Bin/android_x86/libNoesis.so
  INCLUDES = -I../../../../App/Display/Include -I../../../../Core/Kernel/Include -I../../../../../../Include -I../../../../Core/Nullable/Include -I../../../../App/Providers/Include -I../../../../Math/Utils/Include -I../../../../App/ApplicationLauncher/Include -I../../../../Gui/Core/Include -I../../../../Samples/Commands/Include -I../../../../App/DisplayLauncher/Include -I../../../../../../3rdParty/EASTL/local/include -I../../../../Math/VectorMath/Include -I../../../../Gui/DependencySystem/Include -I../../../../App/Launcher/Include -I../../../../Drawing/Types/Include -I../../../../Core/NSTL/Include -I../../../../Gui/CachedFontProvider/Include -I../../../../Gui/Providers/Include -Ibuild/Release -I$(ANDROID_NDK)/sources/android/native_app_glue
  DEFINES = -DNS_BUILD -DNS_CONFIG=Release -DNS_VERSION=2.2.1 -DNS_APP_FRAMEWORK
  CFLAGS = $(CFLAGS_RELEASE)
  CXXFLAGS = $(CXXFLAGS_RELEASE)
  LDFLAGS = $(LDFLAGS_RELEASE)
else
  $(error Invalid configuration '$(CONFIG)')
endif

PCH =
PCHFLAGS =
DATA = $(INTERMEDIATE)/MainWindow.xaml.bin.h $(INTERMEDIATE)/App.xaml.bin.h $(INTERMEDIATE)/Aero\ Matics\ Regular.ttf.bin.h

.SUFFIXES:
.PHONY: all prebuild data clean

all: prebuild $(TARGET_APK)

prebuild:
	@echo ==== [Samples.Commands] Building '$(CONFIG)' configuration ====
ifndef ANDROID_NDK
	$(error Environment variable ANDROID_NDK not set)
endif
ifndef ANDROID_PLATFORM
	$(error Environment variable ANDROID_PLATFORM not set)
endif
ifndef JAVA_HOME
	$(error Environment variable JAVA_HOME not set)
endif

data: $(DATA)

$(INTERMEDIATE):
	$(call MKDIR,$(INTERMEDIATE))

$(TARGET_DIR):
	$(call MKDIR,$(TARGET_DIR))

$(INTERMEDIATE)/android_native_app_glue.o: $(ANDROID_NDK)/sources/android/native_app_glue/android_native_app_glue.c | $(INTERMEDIATE)
	@echo [CC] $(notdir $<)
	$(Q)$(CC) $(CFLAGS) $(INCLUDES) $(DEFINES) -march=i686 -mtune=intel -mssse3 -mfpmath=sse -m32 -fPIC -c -MMD -MP -o $@ $<
	$(call FIXSLASHES,$(@:.o=.d))

$(INTERMEDIATE)/%.o: ../../../../Samples/Commands/Src/%.cpp $(PCH) | $(INTERMEDIATE) data
	@echo [CXX] [Samples/Commands] $(notdir $<)
	$(Q)$(CXX) $(CXXFLAGS) $(PCHFLAGS) $(INCLUDES) $(DEFINES) -march=i686 -mtune=intel -mssse3 -mfpmath=sse -m32 -fPIC -c -MMD -MP -o $@ $<
	$(call FIXSLASHES,$(@:.o=.d))

$(INTERMEDIATE)/%.o: ../../../../Samples/Commands/Src/%.c | $(INTERMEDIATE) data
	@echo [CC] [Samples/Commands] $(notdir $<)
	$(Q)$(CC) $(CFLAGS) $(INCLUDES) $(DEFINES) -march=i686 -mtune=intel -mssse3 -mfpmath=sse -m32 -fPIC -c -MMD -MP -o $@ $<
	$(call FIXSLASHES,$(@:.o=.d))

$(INTERMEDIATE)/MainWindow.xaml.bin.h: ../../../../Samples/Commands/Data/MainWindow.xaml | $(INTERMEDIATE)
	@echo [BIN] [Samples/Commands] $(notdir $<)
	$(Q)$(BIN2H) "../../../../Samples/Commands/Data/MainWindow.xaml" > "$(INTERMEDIATE)/MainWindow.xaml.bin.h" 

$(INTERMEDIATE)/App.xaml.bin.h: ../../../../Samples/Commands/Data/App.xaml | $(INTERMEDIATE)
	@echo [BIN] [Samples/Commands] $(notdir $<)
	$(Q)$(BIN2H) "../../../../Samples/Commands/Data/App.xaml" > "$(INTERMEDIATE)/App.xaml.bin.h" 

$(INTERMEDIATE)/Aero\ Matics\ Regular.ttf.bin.h: ../../../../Samples/Commands/Data/Aero\ Matics\ Regular.ttf | $(INTERMEDIATE)
	@echo [BIN] [Samples/Commands] $(notdir $<)
	$(Q)$(BIN2H) "../../../../Samples/Commands/Data/Aero Matics Regular.ttf" > "$(INTERMEDIATE)/Aero Matics Regular.ttf.bin.h" 

$(TARGET): $(LIBS_DEPS) $(INTERMEDIATE)/android_native_app_glue.o $(INTERMEDIATE)/Main.o | $(TARGET_DIR)
	@echo [LD] $(notdir $@)
	+$(Q)$(CXX) $(LDFLAGS) -march=i686 -mtune=intel -mssse3 -mfpmath=sse -m32 -shared -Wl,--no-undefined -Wl,-soname,libSamples_Commands.so -L../../../../../../Bin/android_x86 $(LIB_DIRS) -o $(TARGET) @$(CONFIG).rsp $(LIBS)
	@echo [STRIP] $(notdir $@)
	$(Q)i686-linux-android-objcopy --only-keep-debug $(TARGET) $(TARGET).debug
	$(Q)i686-linux-android-strip --strip-unneeded $(TARGET)
	$(Q)i686-linux-android-objcopy --add-gnu-debuglink=$(TARGET).debug $(TARGET)

$(INTERMEDIATE)/java/com/noesis/Samples/Commands/NoesisNativeActivity.class: java/NoesisNativeActivity.java
	@echo [JAVA] $(notdir $<)
	$(call MKDIR,$(INTERMEDIATE)/java)
	$(Q)javac -source 1.7 -target 1.7 -d $(INTERMEDIATE)/java -bootclasspath "${JAVA_HOME}/jre/lib/rt.jar" -classpath "${ANDROID_PLATFORM}/android.jar" -sourcepath $(dir $<) $<

$(INTERMEDIATE)/apk/classes.dex: $(INTERMEDIATE)/java/com/noesis/Samples/Commands/NoesisNativeActivity.class
	@echo [DEX] $(notdir $@)
	$(call MKDIR,$(INTERMEDIATE)/apk)
	$(Q)dx --dex --output=$(INTERMEDIATE)/apk/classes.dex $(INTERMEDIATE)/java

$(INTERMEDIATE)/Samples.Commands-unsigned.apk: $(TARGET) $(LIBS_DEPS) $(INTERMEDIATE)/apk/classes.dex AndroidManifest.xml
	@echo [AAPT] $(notdir $@)
	$(call MKDIR,$(INTERMEDIATE)/apk/lib/x86)
	$(call CP,$(TARGET),$(INTERMEDIATE)/apk/lib/x86)
	$(call CP,../../../../../../Bin/android_x86/libNoesisApp.so,$(INTERMEDIATE)/apk/lib/x86)
	$(call CP,../../../../../../Bin/android_x86/libNoesis.so,$(INTERMEDIATE)/apk/lib/x86)
	$(Q)aapt package -f -S res -M AndroidManifest.xml -I $(ANDROID_PLATFORM)/android.jar -F $(INTERMEDIATE)/Samples.Commands-unsigned.apk $(INTERMEDIATE)/apk

$(INTERMEDIATE)/Samples.Commands-unsigned-aligned.apk: $(INTERMEDIATE)/Samples.Commands-unsigned.apk
	@echo [ALIGN] $(notdir $@)
	$(Q)zipalign -f 4 $(INTERMEDIATE)/Samples.Commands-unsigned.apk $(INTERMEDIATE)/Samples.Commands-unsigned-aligned.apk

$(TARGET_APK): $(INTERMEDIATE)/Samples.Commands-unsigned-aligned.apk
	@echo [SIGN] $(notdir $@)
	$(Q)apksigner sign --ks android.jks --ks-pass pass:noesis --out $(TARGET_APK) $(INTERMEDIATE)/Samples.Commands-unsigned-aligned.apk

-include $(INTERMEDIATE)/android_native_app_glue.d $(INTERMEDIATE)/Main.d

run:
	$(Q)adb install -r $(TARGET_APK)
	$(Q)adb logcat -c
	$(Q)adb shell monkey -p com.noesis.Samples.Commands -c android.intent.category.LAUNCHER 1
	$(Q)adb logcat -s Noesis:V

clean:
	@echo ==== [Samples.Commands] Cleaning '$(CONFIG)' configuration ====
	$(call RMTREE,$(INTERMEDIATE))
	$(call RM,$(TARGET))
	$(call RM,$(TARGET).debug)
	$(call RM,$(TARGET_APK))
