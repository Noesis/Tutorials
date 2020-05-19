# GNU Make project for 'Samples.DataBinding'

# Parallel builds can be enabled using the environment variable MAKEFLAGS (eg: MAKEFLAGS="-j 4")
# For parallel execution in Windows, Make 4.0 or better is required

# Environment variable 'ANDROID_NDK' must point to NDK (eg: C:\Android\SDK\ndk-bundle)
# Environment variable 'ANDROID_PLATFORM' must point to active platform (eg: C:\Android\SDK\platforms\android-17)
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
  TARGET = ../../../../../../Bin/android_x86_64/libSamples_DataBinding.so
  TARGET_APK = ../../../../../../Bin/android_x86_64/Samples.DataBinding.apk
  INTERMEDIATE = build/Debug
  LIB_DIRS = 
  LIBS = -lNoesisApp -landroid -llog -lNoesis
  LIBS_DEPS = ../../../../../../Bin/android_x86_64/libNoesisApp.so ../../../../../../Bin/android_x86_64/libNoesis.so
  INCLUDES = -I../../../../../../Include -I../../../../App/ApplicationLauncher/Include -I../../../../App/DisplayLauncher/Include -I../../../../App/Display/Include -I../../../../App/Launcher/Include -I../../../../App/Providers/Include -Ibuild/Debug -I$(ANDROID_NDK)/sources/android/native_app_glue
  DEFINES = -DNS_BUILD -DNS_CONFIG=Debug -DNS_VERSION=3.0.0 -DNS_APP_FRAMEWORK -DNS_LICENSE -DNS_DEBUG -DNS_PROFILE -DNS_MINIMUM_LOG_LEVEL=1
  CFLAGS = $(CFLAGS_DEBUG)
  CXXFLAGS = $(CXXFLAGS_DEBUG)
  LDFLAGS = $(LDFLAGS_DEBUG)
else ifeq ($(CONFIG), Profile)
  TARGET_DIR = ../../../../../../Bin/android_x86_64
  TARGET = ../../../../../../Bin/android_x86_64/libSamples_DataBinding.so
  TARGET_APK = ../../../../../../Bin/android_x86_64/Samples.DataBinding.apk
  INTERMEDIATE = build/Profile
  LIB_DIRS = 
  LIBS = -lNoesisApp -landroid -llog -lNoesis
  LIBS_DEPS = ../../../../../../Bin/android_x86_64/libNoesisApp.so ../../../../../../Bin/android_x86_64/libNoesis.so
  INCLUDES = -I../../../../../../Include -I../../../../App/ApplicationLauncher/Include -I../../../../App/DisplayLauncher/Include -I../../../../App/Display/Include -I../../../../App/Launcher/Include -I../../../../App/Providers/Include -Ibuild/Profile -I$(ANDROID_NDK)/sources/android/native_app_glue
  DEFINES = -DNS_BUILD -DNS_CONFIG=Profile -DNS_VERSION=3.0.0 -DNS_APP_FRAMEWORK -DNS_LICENSE -DNS_PROFILE -DNS_MINIMUM_LOG_LEVEL=2
  CFLAGS = $(CFLAGS_PROFILE)
  CXXFLAGS = $(CXXFLAGS_PROFILE)
  LDFLAGS = $(LDFLAGS_PROFILE)
else ifeq ($(CONFIG), Release)
  TARGET_DIR = ../../../../../../Bin/android_x86_64
  TARGET = ../../../../../../Bin/android_x86_64/libSamples_DataBinding.so
  TARGET_APK = ../../../../../../Bin/android_x86_64/Samples.DataBinding.apk
  INTERMEDIATE = build/Release
  LIB_DIRS = 
  LIBS = -lNoesisApp -landroid -llog -lNoesis
  LIBS_DEPS = ../../../../../../Bin/android_x86_64/libNoesisApp.so ../../../../../../Bin/android_x86_64/libNoesis.so
  INCLUDES = -I../../../../../../Include -I../../../../App/ApplicationLauncher/Include -I../../../../App/DisplayLauncher/Include -I../../../../App/Display/Include -I../../../../App/Launcher/Include -I../../../../App/Providers/Include -Ibuild/Release -I$(ANDROID_NDK)/sources/android/native_app_glue
  DEFINES = -DNS_BUILD -DNS_CONFIG=Release -DNS_VERSION=3.0.0 -DNS_APP_FRAMEWORK -DNS_LICENSE
  CFLAGS = $(CFLAGS_RELEASE)
  CXXFLAGS = $(CXXFLAGS_RELEASE)
  LDFLAGS = $(LDFLAGS_RELEASE)
else
  $(error Invalid configuration '$(CONFIG)')
endif

PCH =
PCHFLAGS =
DATA = $(INTERMEDIATE)/App.xaml.bin.h $(INTERMEDIATE)/MainWindow.xaml.bin.h $(INTERMEDIATE)/Roboto-Regular.ttf.bin.h $(INTERMEDIATE)/Roboto-Bold.ttf.bin.h $(INTERMEDIATE)/moons_2.jpg.bin.h $(INTERMEDIATE)/earglobe.jpg.bin.h $(INTERMEDIATE)/jupglobe.jpg.bin.h $(INTERMEDIATE)/marglobe.jpg.bin.h $(INTERMEDIATE)/merglobe.jpg.bin.h $(INTERMEDIATE)/nepglobe.jpg.bin.h $(INTERMEDIATE)/plutoch_2.jpg.bin.h $(INTERMEDIATE)/sun.jpg.bin.h $(INTERMEDIATE)/uraglobe.jpg.bin.h $(INTERMEDIATE)/venglobe.jpg.bin.h

.SUFFIXES:
.DELETE_ON_ERROR:
.PHONY: all prebuild data clean

all: prebuild $(TARGET_APK)

prebuild:
	@echo ==== [Samples.DataBinding] Building '$(CONFIG)' configuration ====
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

$(INTERMEDIATE)/%.o: ../../../../Samples/DataBinding/Src/%.cpp $(PCH) | $(INTERMEDIATE) data
	@echo [CXX] [Samples/DataBinding] $(notdir $<)
	$(Q)$(CXX) $(CXXFLAGS) $(PCHFLAGS) $(INCLUDES) $(DEFINES) -fno-rtti -march=x86-64 -mtune=intel -msse4.2 -mpopcnt -m64 -fPIC -c -MMD -MF $(basename $@).d.tmp -MP -o $@ $< && $(call MV,$(basename $@).d.tmp,$(basename $@).d)

	$(Q)$(call FIXSLASHES,$(@:.o=.d))

$(INTERMEDIATE)/%.o: ../../../../Samples/DataBinding/Src/%.c | $(INTERMEDIATE) data
	@echo [CC] [Samples/DataBinding] $(notdir $<)
	$(Q)$(CC) $(CFLAGS) $(INCLUDES) $(DEFINES) -march=x86-64 -mtune=intel -msse4.2 -mpopcnt -m64 -fPIC -c -MMD -MF $(basename $@).d.tmp -MP -o $@ $< && $(call MV,$(basename $@).d.tmp,$(basename $@).d)

	$(Q)$(call FIXSLASHES,$(@:.o=.d))

$(INTERMEDIATE)/App.xaml.bin.h: ../../../../Samples/DataBinding/Data/App.xaml | $(INTERMEDIATE)
	@echo [BIN] [Samples/DataBinding] $(notdir $<)
	$(Q)$(BIN2H) "../../../../Samples/DataBinding/Data/App.xaml" > "$(INTERMEDIATE)/App.xaml.bin.h" 

$(INTERMEDIATE)/MainWindow.xaml.bin.h: ../../../../Samples/DataBinding/Data/MainWindow.xaml | $(INTERMEDIATE)
	@echo [BIN] [Samples/DataBinding] $(notdir $<)
	$(Q)$(BIN2H) "../../../../Samples/DataBinding/Data/MainWindow.xaml" > "$(INTERMEDIATE)/MainWindow.xaml.bin.h" 

$(INTERMEDIATE)/Roboto-Regular.ttf.bin.h: ../../../../Samples/DataBinding/Data/Roboto-Regular.ttf | $(INTERMEDIATE)
	@echo [BIN] [Samples/DataBinding] $(notdir $<)
	$(Q)$(BIN2H) "../../../../Samples/DataBinding/Data/Roboto-Regular.ttf" > "$(INTERMEDIATE)/Roboto-Regular.ttf.bin.h" 

$(INTERMEDIATE)/Roboto-Bold.ttf.bin.h: ../../../../Samples/DataBinding/Data/Roboto-Bold.ttf | $(INTERMEDIATE)
	@echo [BIN] [Samples/DataBinding] $(notdir $<)
	$(Q)$(BIN2H) "../../../../Samples/DataBinding/Data/Roboto-Bold.ttf" > "$(INTERMEDIATE)/Roboto-Bold.ttf.bin.h" 

$(INTERMEDIATE)/moons_2.jpg.bin.h: ../../../../Samples/DataBinding/Data/Images/moons_2.jpg | $(INTERMEDIATE)
	@echo [BIN] [Samples/DataBinding] $(notdir $<)
	$(Q)$(BIN2H) "../../../../Samples/DataBinding/Data/Images/moons_2.jpg" > "$(INTERMEDIATE)/moons_2.jpg.bin.h" 

$(INTERMEDIATE)/earglobe.jpg.bin.h: ../../../../Samples/DataBinding/Data/Images/earglobe.jpg | $(INTERMEDIATE)
	@echo [BIN] [Samples/DataBinding] $(notdir $<)
	$(Q)$(BIN2H) "../../../../Samples/DataBinding/Data/Images/earglobe.jpg" > "$(INTERMEDIATE)/earglobe.jpg.bin.h" 

$(INTERMEDIATE)/jupglobe.jpg.bin.h: ../../../../Samples/DataBinding/Data/Images/jupglobe.jpg | $(INTERMEDIATE)
	@echo [BIN] [Samples/DataBinding] $(notdir $<)
	$(Q)$(BIN2H) "../../../../Samples/DataBinding/Data/Images/jupglobe.jpg" > "$(INTERMEDIATE)/jupglobe.jpg.bin.h" 

$(INTERMEDIATE)/marglobe.jpg.bin.h: ../../../../Samples/DataBinding/Data/Images/marglobe.jpg | $(INTERMEDIATE)
	@echo [BIN] [Samples/DataBinding] $(notdir $<)
	$(Q)$(BIN2H) "../../../../Samples/DataBinding/Data/Images/marglobe.jpg" > "$(INTERMEDIATE)/marglobe.jpg.bin.h" 

$(INTERMEDIATE)/merglobe.jpg.bin.h: ../../../../Samples/DataBinding/Data/Images/merglobe.jpg | $(INTERMEDIATE)
	@echo [BIN] [Samples/DataBinding] $(notdir $<)
	$(Q)$(BIN2H) "../../../../Samples/DataBinding/Data/Images/merglobe.jpg" > "$(INTERMEDIATE)/merglobe.jpg.bin.h" 

$(INTERMEDIATE)/nepglobe.jpg.bin.h: ../../../../Samples/DataBinding/Data/Images/nepglobe.jpg | $(INTERMEDIATE)
	@echo [BIN] [Samples/DataBinding] $(notdir $<)
	$(Q)$(BIN2H) "../../../../Samples/DataBinding/Data/Images/nepglobe.jpg" > "$(INTERMEDIATE)/nepglobe.jpg.bin.h" 

$(INTERMEDIATE)/plutoch_2.jpg.bin.h: ../../../../Samples/DataBinding/Data/Images/plutoch_2.jpg | $(INTERMEDIATE)
	@echo [BIN] [Samples/DataBinding] $(notdir $<)
	$(Q)$(BIN2H) "../../../../Samples/DataBinding/Data/Images/plutoch_2.jpg" > "$(INTERMEDIATE)/plutoch_2.jpg.bin.h" 

$(INTERMEDIATE)/sun.jpg.bin.h: ../../../../Samples/DataBinding/Data/Images/sun.jpg | $(INTERMEDIATE)
	@echo [BIN] [Samples/DataBinding] $(notdir $<)
	$(Q)$(BIN2H) "../../../../Samples/DataBinding/Data/Images/sun.jpg" > "$(INTERMEDIATE)/sun.jpg.bin.h" 

$(INTERMEDIATE)/uraglobe.jpg.bin.h: ../../../../Samples/DataBinding/Data/Images/uraglobe.jpg | $(INTERMEDIATE)
	@echo [BIN] [Samples/DataBinding] $(notdir $<)
	$(Q)$(BIN2H) "../../../../Samples/DataBinding/Data/Images/uraglobe.jpg" > "$(INTERMEDIATE)/uraglobe.jpg.bin.h" 

$(INTERMEDIATE)/venglobe.jpg.bin.h: ../../../../Samples/DataBinding/Data/Images/venglobe.jpg | $(INTERMEDIATE)
	@echo [BIN] [Samples/DataBinding] $(notdir $<)
	$(Q)$(BIN2H) "../../../../Samples/DataBinding/Data/Images/venglobe.jpg" > "$(INTERMEDIATE)/venglobe.jpg.bin.h" 

$(TARGET): $(LIBS_DEPS) $(INTERMEDIATE)/android_native_app_glue.o $(INTERMEDIATE)/Main.o | $(TARGET_DIR)
	@echo [LD] $(notdir $@)
	+$(Q)$(CXX) $(LDFLAGS) -march=x86-64 -mtune=intel -msse4.2 -mpopcnt -m64 -shared -Wl,--no-undefined -Wl,-soname,libSamples_DataBinding.so -L../../../../../../Bin/android_x86_64 $(LIB_DIRS) -o $(TARGET) @$(CONFIG).rsp $(LIBS)
	@echo [STRIP] $(notdir $@)
	$(Q)x86_64-linux-android-objcopy --only-keep-debug $(TARGET) $(TARGET).debug
	$(Q)x86_64-linux-android-strip --strip-unneeded $(TARGET)
	$(Q)x86_64-linux-android-objcopy --add-gnu-debuglink=$(TARGET).debug $(TARGET)

$(INTERMEDIATE)/java/com/noesis/Samples/DataBinding/NoesisNativeActivity.class: java/NoesisNativeActivity.java
	@echo [JAVA] $(notdir $<)
	$(Q)$(call MKDIR,$(INTERMEDIATE)/java)
	$(Q)javac -source 1.7 -target 1.7 -Xlint:-options -d $(INTERMEDIATE)/java -classpath "${ANDROID_PLATFORM}/android.jar" -sourcepath $(dir $<) $<

$(INTERMEDIATE)/apk/classes.dex: $(INTERMEDIATE)/java/com/noesis/Samples/DataBinding/NoesisNativeActivity.class
	@echo [DEX] $(notdir $@)
	$(Q)$(call MKDIR,$(INTERMEDIATE)/apk)
	$(Q)dx --dex --output=$(INTERMEDIATE)/apk/classes.dex $(INTERMEDIATE)/java

$(INTERMEDIATE)/Samples.DataBinding-unsigned.apk: $(TARGET) $(LIBS_DEPS) $(INTERMEDIATE)/apk/classes.dex AndroidManifest.xml
	@echo [AAPT] $(notdir $@)
	$(Q)$(call MKDIR,$(INTERMEDIATE)/apk/lib/x86_64)
	$(Q)$(call CP,$(TARGET),$(INTERMEDIATE)/apk/lib/x86_64)
	$(Q)$(call CP,../../../../../../Bin/android_x86_64/libNoesisApp.so,$(INTERMEDIATE)/apk/lib/x86_64)
	$(Q)$(call CP,../../../../../../Bin/android_x86_64/libNoesis.so,$(INTERMEDIATE)/apk/lib/x86_64)
	$(Q)aapt package -f -S res -M AndroidManifest.xml -I $(ANDROID_PLATFORM)/android.jar -F $(INTERMEDIATE)/Samples.DataBinding-unsigned.apk $(INTERMEDIATE)/apk

$(INTERMEDIATE)/Samples.DataBinding-unsigned-aligned.apk: $(INTERMEDIATE)/Samples.DataBinding-unsigned.apk
	@echo [ALIGN] $(notdir $@)
	$(Q)zipalign -f 4 $(INTERMEDIATE)/Samples.DataBinding-unsigned.apk $(INTERMEDIATE)/Samples.DataBinding-unsigned-aligned.apk

$(TARGET_APK): $(INTERMEDIATE)/Samples.DataBinding-unsigned-aligned.apk
	@echo [SIGN] $(notdir $@)
	$(Q)apksigner sign --ks android.jks --ks-pass pass:noesis --out $(TARGET_APK) $(INTERMEDIATE)/Samples.DataBinding-unsigned-aligned.apk

-include $(INTERMEDIATE)/android_native_app_glue.d $(INTERMEDIATE)/Main.d

run:
	$(Q)adb install -r $(TARGET_APK)
	$(Q)adb logcat -c
	$(Q)adb shell monkey -p com.noesis.Samples.DataBinding -c android.intent.category.LAUNCHER 1
	$(Q)adb logcat -s Noesis:V

clean:
	@echo ==== [Samples.DataBinding] Cleaning '$(CONFIG)' configuration ====
	$(Q)$(call RMTREE,$(INTERMEDIATE))
	$(Q)$(call RM,$(TARGET))
	$(Q)$(call RM,$(TARGET).debug)
	$(Q)$(call RM,$(TARGET_APK))
