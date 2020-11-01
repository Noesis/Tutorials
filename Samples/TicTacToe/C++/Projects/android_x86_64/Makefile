# GNU Make project for 'Samples.TicTacToe'

# Parallel builds can be enabled using the environment variable MAKEFLAGS (eg: MAKEFLAGS="-j 4")
# For parallel execution in Windows, Make 4.0 or better is required

# Environment variable 'ANDROID_NDK' must point to NDK (eg: C:\Android\SDK\ndk-bundle)
# Environment variable 'ANDROID_PLATFORM' must point to active platform (eg: C:\Android\SDK\platforms\android-30)
# Toolchain (clang++), Java (javac) and Android Build Tools (dx, aapt, zipalign, apksigner) binaries must be added to 'PATH' environment variable

include ../../../../../Config/Common.android.makeprops
include ../../../../../Config/Debug/Debug.android.makeprops
include ../../../../../Config/Profile/Profile.android.makeprops
include ../../../../../Config/Release/Release.android.makeprops

CC = x86_64-linux-android21-clang
CXX = x86_64-linux-android21-clang++
AR = x86_64-linux-android-ar

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
  TARGET_DIR = ../../../../../../Bin/android_x86_64
  TARGET = ../../../../../../Bin/android_x86_64/libSamples_TicTacToe.so
  TARGET_APK = ../../../../../../Bin/android_x86_64/Samples.TicTacToe.apk
  INTERMEDIATE = build/Debug
  LIB_DIRS = 
  LIBS = -lNoesisApp -landroid -llog -lNoesis
  LIBS_DEPS = ../../../../../../Bin/android_x86_64/libNoesisApp.so ../../../../../../Bin/android_x86_64/libNoesis.so
  INCLUDES = -I../../../../../../Include -I../../../../App/ApplicationLauncher/Include -I../../../../App/DisplayLauncher/Include -I../../../../App/Display/Include -I../../../../App/Interactivity/Include -I../../../../App/Launcher/Include -I../../../../App/Providers/Include -Ibuild/Debug -I$(ANDROID_NDK)/sources/android/native_app_glue
  DEFINES = -DNS_BUILD -DNS_CONFIG=Debug -DNS_VERSION=3.0.7 -DNS_APP_FRAMEWORK -DNS_LICENSE -DNS_DEBUG -DNS_PROFILE -DNS_MINIMUM_LOG_LEVEL=1
  CFLAGS = $(CFLAGS_DEBUG)
  CXXFLAGS = $(CXXFLAGS_DEBUG)
  LDFLAGS = $(LDFLAGS_DEBUG)
  AAPT_FLAGS = --debug-mode
else ifeq ($(CONFIG), Profile)
  TARGET_DIR = ../../../../../../Bin/android_x86_64
  TARGET = ../../../../../../Bin/android_x86_64/libSamples_TicTacToe.so
  TARGET_APK = ../../../../../../Bin/android_x86_64/Samples.TicTacToe.apk
  INTERMEDIATE = build/Profile
  LIB_DIRS = 
  LIBS = -lNoesisApp -landroid -llog -lNoesis
  LIBS_DEPS = ../../../../../../Bin/android_x86_64/libNoesisApp.so ../../../../../../Bin/android_x86_64/libNoesis.so
  INCLUDES = -I../../../../../../Include -I../../../../App/ApplicationLauncher/Include -I../../../../App/DisplayLauncher/Include -I../../../../App/Display/Include -I../../../../App/Interactivity/Include -I../../../../App/Launcher/Include -I../../../../App/Providers/Include -Ibuild/Profile -I$(ANDROID_NDK)/sources/android/native_app_glue
  DEFINES = -DNS_BUILD -DNS_CONFIG=Profile -DNS_VERSION=3.0.7 -DNS_APP_FRAMEWORK -DNS_LICENSE -DNS_PROFILE -DNS_MINIMUM_LOG_LEVEL=2
  CFLAGS = $(CFLAGS_PROFILE)
  CXXFLAGS = $(CXXFLAGS_PROFILE)
  LDFLAGS = $(LDFLAGS_PROFILE)
  AAPT_FLAGS = --debug-mode
else ifeq ($(CONFIG), Release)
  TARGET_DIR = ../../../../../../Bin/android_x86_64
  TARGET = ../../../../../../Bin/android_x86_64/libSamples_TicTacToe.so
  TARGET_APK = ../../../../../../Bin/android_x86_64/Samples.TicTacToe.apk
  INTERMEDIATE = build/Release
  LIB_DIRS = 
  LIBS = -lNoesisApp -landroid -llog -lNoesis
  LIBS_DEPS = ../../../../../../Bin/android_x86_64/libNoesisApp.so ../../../../../../Bin/android_x86_64/libNoesis.so
  INCLUDES = -I../../../../../../Include -I../../../../App/ApplicationLauncher/Include -I../../../../App/DisplayLauncher/Include -I../../../../App/Display/Include -I../../../../App/Interactivity/Include -I../../../../App/Launcher/Include -I../../../../App/Providers/Include -Ibuild/Release -I$(ANDROID_NDK)/sources/android/native_app_glue
  DEFINES = -DNS_BUILD -DNS_CONFIG=Release -DNS_VERSION=3.0.7 -DNS_APP_FRAMEWORK -DNS_LICENSE
  CFLAGS = $(CFLAGS_RELEASE)
  CXXFLAGS = $(CXXFLAGS_RELEASE)
  LDFLAGS = $(LDFLAGS_RELEASE)
  AAPT_FLAGS = 
else
  $(error Invalid configuration '$(CONFIG)')
endif

PCH =
PCHFLAGS =
DATA = $(INTERMEDIATE)/App.xaml.bin.h $(INTERMEDIATE)/MainWindow.xaml.bin.h $(INTERMEDIATE)/Multicolore.otf.bin.h $(INTERMEDIATE)/NoughtEffect.mp3.bin.h $(INTERMEDIATE)/CrossEffect.mp3.bin.h $(INTERMEDIATE)/WinEffect.mp3.bin.h $(INTERMEDIATE)/TieEffect.mp3.bin.h

.SUFFIXES:
.DELETE_ON_ERROR:
.PHONY: all prebuild data clean

all: prebuild $(TARGET_APK)

prebuild:
	@echo ==== [Samples.TicTacToe] Building '$(CONFIG)' configuration ====
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
	$(Q)$(CC) $(CFLAGS) $(INCLUDES) $(DEFINES) -march=x86-64 -mtune=intel -msse4.2 -mpopcnt -m64 -fPIC -c -MMD -MF $(basename $@).d.tmp -MP -o $@ $< && $(call MV,$(basename $@).d.tmp,$(basename $@).d)

	$(Q)$(call FIXSLASHES,$(@:.o=.d))

$(INTERMEDIATE)/%.o: ../../../../Samples/TicTacToe/Src/%.cpp $(PCH) | $(INTERMEDIATE) data
	@echo [CXX] [Samples/TicTacToe] $(notdir $<)
	$(Q)$(CXX) $(CXXFLAGS) $(PCHFLAGS) $(INCLUDES) $(DEFINES) -fno-rtti -march=x86-64 -mtune=intel -msse4.2 -mpopcnt -m64 -fPIC -c -MMD -MF $(basename $@).d.tmp -MP -o $@ $< && $(call MV,$(basename $@).d.tmp,$(basename $@).d)

	$(Q)$(call FIXSLASHES,$(@:.o=.d))

$(INTERMEDIATE)/%.o: ../../../../Samples/TicTacToe/Src/%.c | $(INTERMEDIATE) data
	@echo [CC] [Samples/TicTacToe] $(notdir $<)
	$(Q)$(CC) $(CFLAGS) $(INCLUDES) $(DEFINES) -march=x86-64 -mtune=intel -msse4.2 -mpopcnt -m64 -fPIC -c -MMD -MF $(basename $@).d.tmp -MP -o $@ $< && $(call MV,$(basename $@).d.tmp,$(basename $@).d)

	$(Q)$(call FIXSLASHES,$(@:.o=.d))

$(INTERMEDIATE)/App.xaml.bin.h: ../../../../Samples/TicTacToe/Data/App.xaml | $(INTERMEDIATE)
	@echo [BIN] [Samples/TicTacToe] $(notdir $<)
	$(Q)$(BIN2H) "../../../../Samples/TicTacToe/Data/App.xaml" > "$(INTERMEDIATE)/App.xaml.bin.h" 

$(INTERMEDIATE)/MainWindow.xaml.bin.h: ../../../../Samples/TicTacToe/Data/MainWindow.xaml | $(INTERMEDIATE)
	@echo [BIN] [Samples/TicTacToe] $(notdir $<)
	$(Q)$(BIN2H) "../../../../Samples/TicTacToe/Data/MainWindow.xaml" > "$(INTERMEDIATE)/MainWindow.xaml.bin.h" 

$(INTERMEDIATE)/Multicolore.otf.bin.h: ../../../../Samples/TicTacToe/Data/Fonts/Multicolore.otf | $(INTERMEDIATE)
	@echo [BIN] [Samples/TicTacToe] $(notdir $<)
	$(Q)$(BIN2H) "../../../../Samples/TicTacToe/Data/Fonts/Multicolore.otf" > "$(INTERMEDIATE)/Multicolore.otf.bin.h" 

$(INTERMEDIATE)/NoughtEffect.mp3.bin.h: ../../../../Samples/TicTacToe/Data/Sounds/NoughtEffect.mp3 | $(INTERMEDIATE)
	@echo [BIN] [Samples/TicTacToe] $(notdir $<)
	$(Q)$(BIN2H) "../../../../Samples/TicTacToe/Data/Sounds/NoughtEffect.mp3" > "$(INTERMEDIATE)/NoughtEffect.mp3.bin.h" 

$(INTERMEDIATE)/CrossEffect.mp3.bin.h: ../../../../Samples/TicTacToe/Data/Sounds/CrossEffect.mp3 | $(INTERMEDIATE)
	@echo [BIN] [Samples/TicTacToe] $(notdir $<)
	$(Q)$(BIN2H) "../../../../Samples/TicTacToe/Data/Sounds/CrossEffect.mp3" > "$(INTERMEDIATE)/CrossEffect.mp3.bin.h" 

$(INTERMEDIATE)/WinEffect.mp3.bin.h: ../../../../Samples/TicTacToe/Data/Sounds/WinEffect.mp3 | $(INTERMEDIATE)
	@echo [BIN] [Samples/TicTacToe] $(notdir $<)
	$(Q)$(BIN2H) "../../../../Samples/TicTacToe/Data/Sounds/WinEffect.mp3" > "$(INTERMEDIATE)/WinEffect.mp3.bin.h" 

$(INTERMEDIATE)/TieEffect.mp3.bin.h: ../../../../Samples/TicTacToe/Data/Sounds/TieEffect.mp3 | $(INTERMEDIATE)
	@echo [BIN] [Samples/TicTacToe] $(notdir $<)
	$(Q)$(BIN2H) "../../../../Samples/TicTacToe/Data/Sounds/TieEffect.mp3" > "$(INTERMEDIATE)/TieEffect.mp3.bin.h" 

$(TARGET): $(LIBS_DEPS) $(INTERMEDIATE)/android_native_app_glue.o $(INTERMEDIATE)/App.xaml.o $(INTERMEDIATE)/Main.o $(INTERMEDIATE)/MainWindow.xaml.o $(INTERMEDIATE)/ViewModel.o | $(TARGET_DIR)
	@echo [LD] $(notdir $@)
	+$(Q)$(CXX) $(LDFLAGS) -march=x86-64 -mtune=intel -msse4.2 -mpopcnt -m64 -shared -Wl,--no-undefined -Wl,-soname,libSamples_TicTacToe.so -L../../../../../../Bin/android_x86_64 $(LIB_DIRS) -o $(TARGET) @$(CONFIG).rsp $(LIBS)
	@echo [STRIP] $(notdir $@)
	$(Q)x86_64-linux-android-objcopy --only-keep-debug $(TARGET) $(TARGET).debug
	$(Q)x86_64-linux-android-strip --strip-unneeded $(TARGET)
	$(Q)x86_64-linux-android-objcopy --add-gnu-debuglink=$(TARGET).debug $(TARGET)

$(INTERMEDIATE)/java/com/noesis/Samples/TicTacToe/NoesisNativeActivity.class: java/NoesisNativeActivity.java
	@echo [JAVA] $(notdir $<)
	$(Q)$(call MKDIR,$(INTERMEDIATE)/java)
	$(Q)javac -source 1.7 -target 1.7 -Xlint:-options -d $(INTERMEDIATE)/java -classpath "${ANDROID_PLATFORM}/android.jar" -sourcepath $(dir $<) $<

$(INTERMEDIATE)/apk/classes.dex: $(INTERMEDIATE)/java/com/noesis/Samples/TicTacToe/NoesisNativeActivity.class
	@echo [DEX] $(notdir $@)
	$(Q)$(call MKDIR,$(INTERMEDIATE)/apk)
	$(Q)dx --dex --output=$(INTERMEDIATE)/apk/classes.dex $(INTERMEDIATE)/java

$(INTERMEDIATE)/Samples.TicTacToe-unsigned.apk: $(TARGET) $(LIBS_DEPS) $(INTERMEDIATE)/apk/classes.dex AndroidManifest.xml
	@echo [AAPT] $(notdir $@)
	$(Q)$(call MKDIR,$(INTERMEDIATE)/apk/lib/x86_64)
	$(Q)$(call CP,$(TARGET),$(INTERMEDIATE)/apk/lib/x86_64)
	$(Q)$(call CP,../../../../../../Bin/android_x86_64/libNoesisApp.so,$(INTERMEDIATE)/apk/lib/x86_64)
	$(Q)$(call CP,../../../../../../Bin/android_x86_64/libNoesis.so,$(INTERMEDIATE)/apk/lib/x86_64)
	$(Q)aapt package -f -S res -M AndroidManifest.xml $(AAPT_FLAGS) -I $(ANDROID_PLATFORM)/android.jar -F $(INTERMEDIATE)/Samples.TicTacToe-unsigned.apk $(INTERMEDIATE)/apk

$(INTERMEDIATE)/Samples.TicTacToe-unsigned-aligned.apk: $(INTERMEDIATE)/Samples.TicTacToe-unsigned.apk
	@echo [ALIGN] $(notdir $@)
	$(Q)zipalign -f 4 $(INTERMEDIATE)/Samples.TicTacToe-unsigned.apk $(INTERMEDIATE)/Samples.TicTacToe-unsigned-aligned.apk

$(TARGET_APK): $(INTERMEDIATE)/Samples.TicTacToe-unsigned-aligned.apk
	@echo [SIGN] $(notdir $@)
	$(Q)apksigner sign --ks android.jks --ks-pass pass:noesis --out $(TARGET_APK) $(INTERMEDIATE)/Samples.TicTacToe-unsigned-aligned.apk

-include $(INTERMEDIATE)/android_native_app_glue.d $(INTERMEDIATE)/App.xaml.d $(INTERMEDIATE)/Main.d $(INTERMEDIATE)/MainWindow.xaml.d $(INTERMEDIATE)/ViewModel.d

run:
	$(Q)adb install -r $(TARGET_APK)
	$(Q)adb logcat -c
	$(Q)adb shell monkey -p com.noesis.Samples.TicTacToe -c android.intent.category.LAUNCHER 1
	$(Q)adb logcat -s Noesis:V

clean:
	@echo ==== [Samples.TicTacToe] Cleaning '$(CONFIG)' configuration ====
	$(Q)$(call RMTREE,$(INTERMEDIATE))
	$(Q)$(call RM,$(TARGET))
	$(Q)$(call RM,$(TARGET).debug)
	$(Q)$(call RM,$(TARGET_APK))
