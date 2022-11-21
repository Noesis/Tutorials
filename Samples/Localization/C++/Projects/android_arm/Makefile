# GNU Make project for 'Samples.Localization'

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
  BIN2H = ../../../../../Tools/Bin2h/bin2h.py
  CP = cp "$(1)" "$(2)"
  MV = mv "$(1)" "$(2)"
  RM = rm -f "$(1)"
  RMTREE = rm -rf "$(1)"
  FIXSLASHES = 
else
  DEVNUL = NUL
  WHICH = where
  MKDIR = mkdir "$(subst /,\,$(1))" 2> nul || exit 0
  BIN2H = ..\..\..\..\..\Tools\Bin2h\bin2h.exe
  CP = copy /Y "$(subst /,\,$(1))" "$(subst /,\,$(2))" > nul
  MV = move /Y "$(subst /,\,$(1))" "$(subst /,\,$(2))" > nul
  RM = del /Q "$(subst /,\,$(1))" 2> nul || exit 0
  RMTREE = rmdir /S /Q "$(subst /,\,$(1))" 2> nul || exit 0
  SED = ..\..\..\..\..\Tools\sed\sed.exe
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
  TARGET_DIR = ../../../../../../Bin/android_arm
  TARGET = ../../../../../../Bin/android_arm/libSamples_Localization.so
  TARGET_APK = ../../../../../../Bin/android_arm/Samples.Localization.apk
  INTERMEDIATE = build/Debug
  LIB_DIRS = 
  LIBS = -lNoesis -llog -lNoesisApp -landroid
  LIBS_DEPS = ../../../../../../Bin/android_arm/libNoesisApp.so ../../../../../../Bin/android_arm/libNoesis.so
  INCLUDES = -I../../../../../../Include -I../../../../App/ApplicationLauncher/Include -I../../../../App/DisplayLauncher/Include -I../../../../App/Display/Include -I../../../../App/Launcher/Include -I../../../../App/Providers/Include -Ibuild/Debug -I$(ANDROID_NDK)/sources/android/native_app_glue
  DEFINES = -DNS_BUILD -DNS_CONFIG=Debug -DNS_VERSION=3.1.6 -DNS_APP_FRAMEWORK -DNS_LICENSE -DNS_DEBUG -DNS_PROFILE -DNS_MINIMUM_LOG_LEVEL=1
  CFLAGS = $(CFLAGS_COMMON) -D_DEBUG
  CXXFLAGS = $(CXXFLAGS_COMMON) -D_DEBUG
  LDFLAGS = $(LDFLAGS_COMMON) $(CXXFLAGS)
  AAPT_FLAGS = --debug-mode
else ifeq ($(CONFIG), Profile)
  TARGET_DIR = ../../../../../../Bin/android_arm
  TARGET = ../../../../../../Bin/android_arm/libSamples_Localization.so
  TARGET_APK = ../../../../../../Bin/android_arm/Samples.Localization.apk
  INTERMEDIATE = build/Profile
  LIB_DIRS = 
  LIBS = -lNoesis -llog -lNoesisApp -landroid
  LIBS_DEPS = ../../../../../../Bin/android_arm/libNoesisApp.so ../../../../../../Bin/android_arm/libNoesis.so
  INCLUDES = -I../../../../../../Include -I../../../../App/ApplicationLauncher/Include -I../../../../App/DisplayLauncher/Include -I../../../../App/Display/Include -I../../../../App/Launcher/Include -I../../../../App/Providers/Include -Ibuild/Profile -I$(ANDROID_NDK)/sources/android/native_app_glue
  DEFINES = -DNS_BUILD -DNS_CONFIG=Profile -DNS_VERSION=3.1.6 -DNS_APP_FRAMEWORK -DNS_LICENSE -DNS_PROFILE -DNS_MINIMUM_LOG_LEVEL=2
  CFLAGS = $(CFLAGS_COMMON) -Ofast -DNDEBUG -ffunction-sections -fdata-sections -fno-asynchronous-unwind-tables -U_FORTIFY_SOURCE
  CXXFLAGS = $(CXXFLAGS_COMMON) -Ofast -DNDEBUG -ffunction-sections -fdata-sections -fno-asynchronous-unwind-tables -U_FORTIFY_SOURCE
  LDFLAGS = $(LDFLAGS_COMMON) $(CXXFLAGS) -fuse-ld=gold -Wl,-O3,--gc-sections,--icf=all
  AAPT_FLAGS = --debug-mode
else ifeq ($(CONFIG), Release)
  TARGET_DIR = ../../../../../../Bin/android_arm
  TARGET = ../../../../../../Bin/android_arm/libSamples_Localization.so
  TARGET_APK = ../../../../../../Bin/android_arm/Samples.Localization.apk
  INTERMEDIATE = build/Release
  LIB_DIRS = 
  LIBS = -lNoesis -llog -lNoesisApp -landroid
  LIBS_DEPS = ../../../../../../Bin/android_arm/libNoesisApp.so ../../../../../../Bin/android_arm/libNoesis.so
  INCLUDES = -I../../../../../../Include -I../../../../App/ApplicationLauncher/Include -I../../../../App/DisplayLauncher/Include -I../../../../App/Display/Include -I../../../../App/Launcher/Include -I../../../../App/Providers/Include -Ibuild/Release -I$(ANDROID_NDK)/sources/android/native_app_glue
  DEFINES = -DNS_BUILD -DNS_CONFIG=Release -DNS_VERSION=3.1.6 -DNS_APP_FRAMEWORK -DNS_LICENSE
  CFLAGS = $(CFLAGS_COMMON) -Ofast -flto -DNDEBUG -ffunction-sections -fdata-sections -fno-asynchronous-unwind-tables -U_FORTIFY_SOURCE -fomit-frame-pointer
  CXXFLAGS = $(CXXFLAGS_COMMON) -Ofast -flto -DNDEBUG -ffunction-sections -fdata-sections -fno-asynchronous-unwind-tables -U_FORTIFY_SOURCE -fomit-frame-pointer
  LDFLAGS = $(LDFLAGS_COMMON) $(CXXFLAGS) -fuse-ld=gold -Wl,-O3,--gc-sections,--icf=all
  AAPT_FLAGS = 
else
  $(error Invalid configuration '$(CONFIG)')
endif

PCH =
PCHFLAGS =
DATA = $(INTERMEDIATE)/App.xaml.bin.h $(INTERMEDIATE)/MainWindow.xaml.bin.h $(INTERMEDIATE)/Resources.xaml.bin.h $(INTERMEDIATE)/Language-en.xaml.bin.h $(INTERMEDIATE)/Language-fr.xaml.bin.h $(INTERMEDIATE)/Language-jp.xaml.bin.h $(INTERMEDIATE)/Flag-en.png.bin.h $(INTERMEDIATE)/Flag-fr.png.bin.h $(INTERMEDIATE)/Flag-jp.png.bin.h $(INTERMEDIATE)/PTSans-Bold.ttf.bin.h $(INTERMEDIATE)/PTSans-BoldItalic.ttf.bin.h $(INTERMEDIATE)/PTSans-Italic.ttf.bin.h $(INTERMEDIATE)/PTSans-Regular.ttf.bin.h $(INTERMEDIATE)/FontopoNIHONGO.otf.bin.h

.SUFFIXES:
.DELETE_ON_ERROR:
.PHONY: all prebuild data clean

all: prebuild $(TARGET_APK)

prebuild:
	@echo ==== [Samples.Localization] Building '$(CONFIG)' configuration ====
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

$(INTERMEDIATE)/%.o: ../../../../Samples/Localization/Src/%.cpp $(PCH) | $(INTERMEDIATE) data
	@echo [CXX] [Samples/Localization] $(notdir $<)
	$(Q)$(CXX) $(CXXFLAGS) $(PCHFLAGS) $(INCLUDES) $(DEFINES) -march=armv7-a -mthumb -fPIC -c -MMD -MF $(basename $@).d.tmp -MP -o $@ $< && $(call MV,$(basename $@).d.tmp,$(basename $@).d)

	$(Q)$(call FIXSLASHES,$(@:.o=.d))

$(INTERMEDIATE)/%.o: ../../../../Samples/Localization/Src/%.c | $(INTERMEDIATE) data
	@echo [CC] [Samples/Localization] $(notdir $<)
	$(Q)$(CC) $(CFLAGS) $(INCLUDES) $(DEFINES) -march=armv7-a -mthumb -fPIC -c -MMD -MF $(basename $@).d.tmp -MP -o $@ $< && $(call MV,$(basename $@).d.tmp,$(basename $@).d)

	$(Q)$(call FIXSLASHES,$(@:.o=.d))

$(INTERMEDIATE)/App.xaml.bin.h: ../../../../Samples/Localization/Data/App.xaml | $(INTERMEDIATE)
	@echo [BIN] [Samples/Localization] $(notdir $<)
	$(Q)$(BIN2H) "../../../../Samples/Localization/Data/App.xaml" > "$(INTERMEDIATE)/App.xaml.bin.h" 

$(INTERMEDIATE)/MainWindow.xaml.bin.h: ../../../../Samples/Localization/Data/MainWindow.xaml | $(INTERMEDIATE)
	@echo [BIN] [Samples/Localization] $(notdir $<)
	$(Q)$(BIN2H) "../../../../Samples/Localization/Data/MainWindow.xaml" > "$(INTERMEDIATE)/MainWindow.xaml.bin.h" 

$(INTERMEDIATE)/Resources.xaml.bin.h: ../../../../Samples/Localization/Data/Resources.xaml | $(INTERMEDIATE)
	@echo [BIN] [Samples/Localization] $(notdir $<)
	$(Q)$(BIN2H) "../../../../Samples/Localization/Data/Resources.xaml" > "$(INTERMEDIATE)/Resources.xaml.bin.h" 

$(INTERMEDIATE)/Language-en.xaml.bin.h: ../../../../Samples/Localization/Data/Language-en.xaml | $(INTERMEDIATE)
	@echo [BIN] [Samples/Localization] $(notdir $<)
	$(Q)$(BIN2H) "../../../../Samples/Localization/Data/Language-en.xaml" > "$(INTERMEDIATE)/Language-en.xaml.bin.h" 

$(INTERMEDIATE)/Language-fr.xaml.bin.h: ../../../../Samples/Localization/Data/Language-fr.xaml | $(INTERMEDIATE)
	@echo [BIN] [Samples/Localization] $(notdir $<)
	$(Q)$(BIN2H) "../../../../Samples/Localization/Data/Language-fr.xaml" > "$(INTERMEDIATE)/Language-fr.xaml.bin.h" 

$(INTERMEDIATE)/Language-jp.xaml.bin.h: ../../../../Samples/Localization/Data/Language-jp.xaml | $(INTERMEDIATE)
	@echo [BIN] [Samples/Localization] $(notdir $<)
	$(Q)$(BIN2H) "../../../../Samples/Localization/Data/Language-jp.xaml" > "$(INTERMEDIATE)/Language-jp.xaml.bin.h" 

$(INTERMEDIATE)/Flag-en.png.bin.h: ../../../../Samples/Localization/Data/Flag-en.png | $(INTERMEDIATE)
	@echo [BIN] [Samples/Localization] $(notdir $<)
	$(Q)$(BIN2H) "../../../../Samples/Localization/Data/Flag-en.png" > "$(INTERMEDIATE)/Flag-en.png.bin.h" 

$(INTERMEDIATE)/Flag-fr.png.bin.h: ../../../../Samples/Localization/Data/Flag-fr.png | $(INTERMEDIATE)
	@echo [BIN] [Samples/Localization] $(notdir $<)
	$(Q)$(BIN2H) "../../../../Samples/Localization/Data/Flag-fr.png" > "$(INTERMEDIATE)/Flag-fr.png.bin.h" 

$(INTERMEDIATE)/Flag-jp.png.bin.h: ../../../../Samples/Localization/Data/Flag-jp.png | $(INTERMEDIATE)
	@echo [BIN] [Samples/Localization] $(notdir $<)
	$(Q)$(BIN2H) "../../../../Samples/Localization/Data/Flag-jp.png" > "$(INTERMEDIATE)/Flag-jp.png.bin.h" 

$(INTERMEDIATE)/PTSans-Bold.ttf.bin.h: ../../../../Samples/Localization/Data/PTSans-Bold.ttf | $(INTERMEDIATE)
	@echo [BIN] [Samples/Localization] $(notdir $<)
	$(Q)$(BIN2H) "../../../../Samples/Localization/Data/PTSans-Bold.ttf" > "$(INTERMEDIATE)/PTSans-Bold.ttf.bin.h" 

$(INTERMEDIATE)/PTSans-BoldItalic.ttf.bin.h: ../../../../Samples/Localization/Data/PTSans-BoldItalic.ttf | $(INTERMEDIATE)
	@echo [BIN] [Samples/Localization] $(notdir $<)
	$(Q)$(BIN2H) "../../../../Samples/Localization/Data/PTSans-BoldItalic.ttf" > "$(INTERMEDIATE)/PTSans-BoldItalic.ttf.bin.h" 

$(INTERMEDIATE)/PTSans-Italic.ttf.bin.h: ../../../../Samples/Localization/Data/PTSans-Italic.ttf | $(INTERMEDIATE)
	@echo [BIN] [Samples/Localization] $(notdir $<)
	$(Q)$(BIN2H) "../../../../Samples/Localization/Data/PTSans-Italic.ttf" > "$(INTERMEDIATE)/PTSans-Italic.ttf.bin.h" 

$(INTERMEDIATE)/PTSans-Regular.ttf.bin.h: ../../../../Samples/Localization/Data/PTSans-Regular.ttf | $(INTERMEDIATE)
	@echo [BIN] [Samples/Localization] $(notdir $<)
	$(Q)$(BIN2H) "../../../../Samples/Localization/Data/PTSans-Regular.ttf" > "$(INTERMEDIATE)/PTSans-Regular.ttf.bin.h" 

$(INTERMEDIATE)/FontopoNIHONGO.otf.bin.h: ../../../../Samples/Localization/Data/FontopoNIHONGO.otf | $(INTERMEDIATE)
	@echo [BIN] [Samples/Localization] $(notdir $<)
	$(Q)$(BIN2H) "../../../../Samples/Localization/Data/FontopoNIHONGO.otf" > "$(INTERMEDIATE)/FontopoNIHONGO.otf.bin.h" 

$(TARGET): $(LIBS_DEPS) $(INTERMEDIATE)/android_native_app_glue.o $(INTERMEDIATE)/App.xaml.o $(INTERMEDIATE)/Main.o $(INTERMEDIATE)/MainWindow.xaml.o $(INTERMEDIATE)/ViewModel.o | $(TARGET_DIR)
	@echo [LD] $(notdir $@)
	+$(Q)$(CXX) $(LDFLAGS) -march=armv7-a -mthumb -Wl,--fix-cortex-a8 -shared -Wl,--no-undefined -Wl,-soname,libSamples_Localization.so -L../../../../../../Bin/android_arm $(LIB_DIRS) -o $(TARGET) @$(CONFIG).rsp $(LIBS)
	@echo [STRIP] $(notdir $@)
	$(Q)arm-linux-androideabi-objcopy --only-keep-debug $(TARGET) $(TARGET).debug
	$(Q)arm-linux-androideabi-strip --strip-unneeded $(TARGET)
	$(Q)arm-linux-androideabi-objcopy --add-gnu-debuglink=$(TARGET).debug $(TARGET)

$(INTERMEDIATE)/java/com/noesis/Samples/Localization/NoesisNativeActivity.class: java/NoesisNativeActivity.java
	@echo [JAVA] $(notdir $<)
	$(Q)$(call MKDIR,$(INTERMEDIATE)/java)
	$(Q)javac -source 1.7 -target 1.7 -Xlint:-options -d $(INTERMEDIATE)/java -classpath "${ANDROID_PLATFORM}/android.jar" -sourcepath $(dir $<) $<

$(INTERMEDIATE)/apk/classes.dex: $(INTERMEDIATE)/java/com/noesis/Samples/Localization/NoesisNativeActivity.class
	@echo [DEX] $(notdir $@)
	$(Q)$(call MKDIR,$(INTERMEDIATE)/apk)
	$(Q)dx --dex --output=$(INTERMEDIATE)/apk/classes.dex $(INTERMEDIATE)/java

$(INTERMEDIATE)/Samples.Localization-unsigned.apk: $(TARGET) $(LIBS_DEPS) $(INTERMEDIATE)/apk/classes.dex AndroidManifest.xml
	@echo [AAPT] $(notdir $@)
	$(Q)$(call MKDIR,$(INTERMEDIATE)/apk/lib/armeabi-v7a)
	$(Q)$(call CP,$(TARGET),$(INTERMEDIATE)/apk/lib/armeabi-v7a)
	$(Q)$(call CP,../../../../../../Bin/android_arm/libNoesisApp.so,$(INTERMEDIATE)/apk/lib/armeabi-v7a)
	$(Q)$(call CP,../../../../../../Bin/android_arm/libNoesis.so,$(INTERMEDIATE)/apk/lib/armeabi-v7a)
	$(Q)aapt package -f -S res -M AndroidManifest.xml $(AAPT_FLAGS) -I $(ANDROID_PLATFORM)/android.jar -F $(INTERMEDIATE)/Samples.Localization-unsigned.apk $(INTERMEDIATE)/apk

$(INTERMEDIATE)/Samples.Localization-unsigned-aligned.apk: $(INTERMEDIATE)/Samples.Localization-unsigned.apk
	@echo [ALIGN] $(notdir $@)
	$(Q)zipalign -f 4 $(INTERMEDIATE)/Samples.Localization-unsigned.apk $(INTERMEDIATE)/Samples.Localization-unsigned-aligned.apk

$(TARGET_APK): $(INTERMEDIATE)/Samples.Localization-unsigned-aligned.apk
	@echo [SIGN] $(notdir $@)
	$(Q)apksigner sign --ks android.jks --ks-pass pass:noesis --out $(TARGET_APK) $(INTERMEDIATE)/Samples.Localization-unsigned-aligned.apk

-include $(INTERMEDIATE)/android_native_app_glue.d $(INTERMEDIATE)/App.xaml.d $(INTERMEDIATE)/Main.d $(INTERMEDIATE)/MainWindow.xaml.d $(INTERMEDIATE)/ViewModel.d

run:
	$(Q)adb install -r $(TARGET_APK)
	$(Q)adb logcat -c
	$(Q)adb shell monkey -p com.noesis.Samples.Localization -c android.intent.category.LAUNCHER 1
	$(Q)adb logcat -s Noesis:V

clean:
	@echo ==== [Samples.Localization] Cleaning '$(CONFIG)' configuration ====
	$(Q)$(call RMTREE,$(INTERMEDIATE))
	$(Q)$(call RM,$(TARGET))
	$(Q)$(call RM,$(TARGET).debug)
	$(Q)$(call RM,$(TARGET_APK))
