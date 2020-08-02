# GNU Make project for 'Samples.Menu3D'

# Parallel builds can be enabled using the environment variable MAKEFLAGS (eg: MAKEFLAGS="-j 4")
# For parallel execution in Windows, Make 4.0 or better is required

# Environment variable 'ANDROID_NDK' must point to NDK (eg: C:\Android\SDK\ndk-bundle)
# Environment variable 'ANDROID_PLATFORM' must point to active platform (eg: C:\Android\SDK\platforms\android-17)
# Toolchain (clang++), Java (javac) and Android Build Tools (dx, aapt, zipalign, apksigner) binaries must be added to 'PATH' environment variable

include ../../../../../Config/Common.android.makeprops
include ../../../../../Config/Debug/Debug.android.makeprops
include ../../../../../Config/Profile/Profile.android.makeprops
include ../../../../../Config/Release/Release.android.makeprops

CC = i686-linux-android17-clang
CXX = i686-linux-android17-clang++
AR = i686-linux-android-ar

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
  TARGET_DIR = ../../../../../../Bin/android_x86
  TARGET = ../../../../../../Bin/android_x86/libSamples_Menu3D.so
  TARGET_APK = ../../../../../../Bin/android_x86/Samples.Menu3D.apk
  INTERMEDIATE = build/Debug
  LIB_DIRS = 
  LIBS = -lNoesisApp -landroid -llog -lNoesis
  LIBS_DEPS = ../../../../../../Bin/android_x86/libNoesisApp.so ../../../../../../Bin/android_x86/libNoesis.so
  INCLUDES = -I../../../../../../Include -I../../../../App/ApplicationLauncher/Include -I../../../../App/DisplayLauncher/Include -I../../../../App/Display/Include -I../../../../App/Interactivity/Include -I../../../../App/Launcher/Include -I../../../../App/Providers/Include -Ibuild/Debug -I$(ANDROID_NDK)/sources/android/native_app_glue
  DEFINES = -DNS_BUILD -DNS_CONFIG=Debug -DNS_VERSION=3.0.4 -DNS_APP_FRAMEWORK -DNS_LICENSE -DNS_DEBUG -DNS_PROFILE -DNS_MINIMUM_LOG_LEVEL=1
  CFLAGS = $(CFLAGS_DEBUG)
  CXXFLAGS = $(CXXFLAGS_DEBUG)
  LDFLAGS = $(LDFLAGS_DEBUG)
else ifeq ($(CONFIG), Profile)
  TARGET_DIR = ../../../../../../Bin/android_x86
  TARGET = ../../../../../../Bin/android_x86/libSamples_Menu3D.so
  TARGET_APK = ../../../../../../Bin/android_x86/Samples.Menu3D.apk
  INTERMEDIATE = build/Profile
  LIB_DIRS = 
  LIBS = -lNoesisApp -landroid -llog -lNoesis
  LIBS_DEPS = ../../../../../../Bin/android_x86/libNoesisApp.so ../../../../../../Bin/android_x86/libNoesis.so
  INCLUDES = -I../../../../../../Include -I../../../../App/ApplicationLauncher/Include -I../../../../App/DisplayLauncher/Include -I../../../../App/Display/Include -I../../../../App/Interactivity/Include -I../../../../App/Launcher/Include -I../../../../App/Providers/Include -Ibuild/Profile -I$(ANDROID_NDK)/sources/android/native_app_glue
  DEFINES = -DNS_BUILD -DNS_CONFIG=Profile -DNS_VERSION=3.0.4 -DNS_APP_FRAMEWORK -DNS_LICENSE -DNS_PROFILE -DNS_MINIMUM_LOG_LEVEL=2
  CFLAGS = $(CFLAGS_PROFILE)
  CXXFLAGS = $(CXXFLAGS_PROFILE)
  LDFLAGS = $(LDFLAGS_PROFILE)
else ifeq ($(CONFIG), Release)
  TARGET_DIR = ../../../../../../Bin/android_x86
  TARGET = ../../../../../../Bin/android_x86/libSamples_Menu3D.so
  TARGET_APK = ../../../../../../Bin/android_x86/Samples.Menu3D.apk
  INTERMEDIATE = build/Release
  LIB_DIRS = 
  LIBS = -lNoesisApp -landroid -llog -lNoesis
  LIBS_DEPS = ../../../../../../Bin/android_x86/libNoesisApp.so ../../../../../../Bin/android_x86/libNoesis.so
  INCLUDES = -I../../../../../../Include -I../../../../App/ApplicationLauncher/Include -I../../../../App/DisplayLauncher/Include -I../../../../App/Display/Include -I../../../../App/Interactivity/Include -I../../../../App/Launcher/Include -I../../../../App/Providers/Include -Ibuild/Release -I$(ANDROID_NDK)/sources/android/native_app_glue
  DEFINES = -DNS_BUILD -DNS_CONFIG=Release -DNS_VERSION=3.0.4 -DNS_APP_FRAMEWORK -DNS_LICENSE
  CFLAGS = $(CFLAGS_RELEASE)
  CXXFLAGS = $(CXXFLAGS_RELEASE)
  LDFLAGS = $(LDFLAGS_RELEASE)
else
  $(error Invalid configuration '$(CONFIG)')
endif

PCH =
PCHFLAGS =
DATA = $(INTERMEDIATE)/App.xaml.bin.h $(INTERMEDIATE)/MainWindow.xaml.bin.h $(INTERMEDIATE)/MenuResources.xaml.bin.h $(INTERMEDIATE)/MenuDescription.xaml.bin.h $(INTERMEDIATE)/MainMenu.xaml.bin.h $(INTERMEDIATE)/StartMenu.xaml.bin.h $(INTERMEDIATE)/SettingsMenu.xaml.bin.h $(INTERMEDIATE)/OptionSelector.xaml.bin.h $(INTERMEDIATE)/BackClouds.png.bin.h $(INTERMEDIATE)/FrontClouds.png.bin.h $(INTERMEDIATE)/FrontTrees.png.bin.h $(INTERMEDIATE)/LakeAndMountains.png.bin.h $(INTERMEDIATE)/SkyAndSun.jpg.bin.h $(INTERMEDIATE)/weblysleekuisb.ttf.bin.h $(INTERMEDIATE)/weblysleekuisl.ttf.bin.h $(INTERMEDIATE)/SoundTrack.mp3.bin.h $(INTERMEDIATE)/WaterDropBig.mp3.bin.h $(INTERMEDIATE)/WaterDropSmall.mp3.bin.h

.SUFFIXES:
.DELETE_ON_ERROR:
.PHONY: all prebuild data clean

all: prebuild $(TARGET_APK)

prebuild:
	@echo ==== [Samples.Menu3D] Building '$(CONFIG)' configuration ====
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
	$(Q)$(CC) $(CFLAGS) $(INCLUDES) $(DEFINES) -march=i686 -mtune=intel -mssse3 -mfpmath=sse -m32 -fPIC -c -MMD -MF $(basename $@).d.tmp -MP -o $@ $< && $(call MV,$(basename $@).d.tmp,$(basename $@).d)

	$(Q)$(call FIXSLASHES,$(@:.o=.d))

$(INTERMEDIATE)/%.o: ../../../../Samples/Menu3D/Src/%.cpp $(PCH) | $(INTERMEDIATE) data
	@echo [CXX] [Samples/Menu3D] $(notdir $<)
	$(Q)$(CXX) $(CXXFLAGS) $(PCHFLAGS) $(INCLUDES) $(DEFINES) -fno-rtti -march=i686 -mtune=intel -mssse3 -mfpmath=sse -m32 -fPIC -c -MMD -MF $(basename $@).d.tmp -MP -o $@ $< && $(call MV,$(basename $@).d.tmp,$(basename $@).d)

	$(Q)$(call FIXSLASHES,$(@:.o=.d))

$(INTERMEDIATE)/%.o: ../../../../Samples/Menu3D/Src/%.c | $(INTERMEDIATE) data
	@echo [CC] [Samples/Menu3D] $(notdir $<)
	$(Q)$(CC) $(CFLAGS) $(INCLUDES) $(DEFINES) -march=i686 -mtune=intel -mssse3 -mfpmath=sse -m32 -fPIC -c -MMD -MF $(basename $@).d.tmp -MP -o $@ $< && $(call MV,$(basename $@).d.tmp,$(basename $@).d)

	$(Q)$(call FIXSLASHES,$(@:.o=.d))

$(INTERMEDIATE)/App.xaml.bin.h: ../../../../Samples/Menu3D/Data/App.xaml | $(INTERMEDIATE)
	@echo [BIN] [Samples/Menu3D] $(notdir $<)
	$(Q)$(BIN2H) "../../../../Samples/Menu3D/Data/App.xaml" > "$(INTERMEDIATE)/App.xaml.bin.h" 

$(INTERMEDIATE)/MainWindow.xaml.bin.h: ../../../../Samples/Menu3D/Data/MainWindow.xaml | $(INTERMEDIATE)
	@echo [BIN] [Samples/Menu3D] $(notdir $<)
	$(Q)$(BIN2H) "../../../../Samples/Menu3D/Data/MainWindow.xaml" > "$(INTERMEDIATE)/MainWindow.xaml.bin.h" 

$(INTERMEDIATE)/MenuResources.xaml.bin.h: ../../../../Samples/Menu3D/Data/MenuResources.xaml | $(INTERMEDIATE)
	@echo [BIN] [Samples/Menu3D] $(notdir $<)
	$(Q)$(BIN2H) "../../../../Samples/Menu3D/Data/MenuResources.xaml" > "$(INTERMEDIATE)/MenuResources.xaml.bin.h" 

$(INTERMEDIATE)/MenuDescription.xaml.bin.h: ../../../../Samples/Menu3D/Data/MenuDescription.xaml | $(INTERMEDIATE)
	@echo [BIN] [Samples/Menu3D] $(notdir $<)
	$(Q)$(BIN2H) "../../../../Samples/Menu3D/Data/MenuDescription.xaml" > "$(INTERMEDIATE)/MenuDescription.xaml.bin.h" 

$(INTERMEDIATE)/MainMenu.xaml.bin.h: ../../../../Samples/Menu3D/Data/MainMenu.xaml | $(INTERMEDIATE)
	@echo [BIN] [Samples/Menu3D] $(notdir $<)
	$(Q)$(BIN2H) "../../../../Samples/Menu3D/Data/MainMenu.xaml" > "$(INTERMEDIATE)/MainMenu.xaml.bin.h" 

$(INTERMEDIATE)/StartMenu.xaml.bin.h: ../../../../Samples/Menu3D/Data/StartMenu.xaml | $(INTERMEDIATE)
	@echo [BIN] [Samples/Menu3D] $(notdir $<)
	$(Q)$(BIN2H) "../../../../Samples/Menu3D/Data/StartMenu.xaml" > "$(INTERMEDIATE)/StartMenu.xaml.bin.h" 

$(INTERMEDIATE)/SettingsMenu.xaml.bin.h: ../../../../Samples/Menu3D/Data/SettingsMenu.xaml | $(INTERMEDIATE)
	@echo [BIN] [Samples/Menu3D] $(notdir $<)
	$(Q)$(BIN2H) "../../../../Samples/Menu3D/Data/SettingsMenu.xaml" > "$(INTERMEDIATE)/SettingsMenu.xaml.bin.h" 

$(INTERMEDIATE)/OptionSelector.xaml.bin.h: ../../../../Samples/Menu3D/Data/OptionSelector.xaml | $(INTERMEDIATE)
	@echo [BIN] [Samples/Menu3D] $(notdir $<)
	$(Q)$(BIN2H) "../../../../Samples/Menu3D/Data/OptionSelector.xaml" > "$(INTERMEDIATE)/OptionSelector.xaml.bin.h" 

$(INTERMEDIATE)/BackClouds.png.bin.h: ../../../../Samples/Menu3D/Data/Images/BackClouds.png | $(INTERMEDIATE)
	@echo [BIN] [Samples/Menu3D] $(notdir $<)
	$(Q)$(BIN2H) "../../../../Samples/Menu3D/Data/Images/BackClouds.png" > "$(INTERMEDIATE)/BackClouds.png.bin.h" 

$(INTERMEDIATE)/FrontClouds.png.bin.h: ../../../../Samples/Menu3D/Data/Images/FrontClouds.png | $(INTERMEDIATE)
	@echo [BIN] [Samples/Menu3D] $(notdir $<)
	$(Q)$(BIN2H) "../../../../Samples/Menu3D/Data/Images/FrontClouds.png" > "$(INTERMEDIATE)/FrontClouds.png.bin.h" 

$(INTERMEDIATE)/FrontTrees.png.bin.h: ../../../../Samples/Menu3D/Data/Images/FrontTrees.png | $(INTERMEDIATE)
	@echo [BIN] [Samples/Menu3D] $(notdir $<)
	$(Q)$(BIN2H) "../../../../Samples/Menu3D/Data/Images/FrontTrees.png" > "$(INTERMEDIATE)/FrontTrees.png.bin.h" 

$(INTERMEDIATE)/LakeAndMountains.png.bin.h: ../../../../Samples/Menu3D/Data/Images/LakeAndMountains.png | $(INTERMEDIATE)
	@echo [BIN] [Samples/Menu3D] $(notdir $<)
	$(Q)$(BIN2H) "../../../../Samples/Menu3D/Data/Images/LakeAndMountains.png" > "$(INTERMEDIATE)/LakeAndMountains.png.bin.h" 

$(INTERMEDIATE)/SkyAndSun.jpg.bin.h: ../../../../Samples/Menu3D/Data/Images/SkyAndSun.jpg | $(INTERMEDIATE)
	@echo [BIN] [Samples/Menu3D] $(notdir $<)
	$(Q)$(BIN2H) "../../../../Samples/Menu3D/Data/Images/SkyAndSun.jpg" > "$(INTERMEDIATE)/SkyAndSun.jpg.bin.h" 

$(INTERMEDIATE)/weblysleekuisb.ttf.bin.h: ../../../../Samples/Menu3D/Data/Fonts/weblysleekuisb.ttf | $(INTERMEDIATE)
	@echo [BIN] [Samples/Menu3D] $(notdir $<)
	$(Q)$(BIN2H) "../../../../Samples/Menu3D/Data/Fonts/weblysleekuisb.ttf" > "$(INTERMEDIATE)/weblysleekuisb.ttf.bin.h" 

$(INTERMEDIATE)/weblysleekuisl.ttf.bin.h: ../../../../Samples/Menu3D/Data/Fonts/weblysleekuisl.ttf | $(INTERMEDIATE)
	@echo [BIN] [Samples/Menu3D] $(notdir $<)
	$(Q)$(BIN2H) "../../../../Samples/Menu3D/Data/Fonts/weblysleekuisl.ttf" > "$(INTERMEDIATE)/weblysleekuisl.ttf.bin.h" 

$(INTERMEDIATE)/SoundTrack.mp3.bin.h: ../../../../Samples/Menu3D/Data/Sounds/SoundTrack.mp3 | $(INTERMEDIATE)
	@echo [BIN] [Samples/Menu3D] $(notdir $<)
	$(Q)$(BIN2H) "../../../../Samples/Menu3D/Data/Sounds/SoundTrack.mp3" > "$(INTERMEDIATE)/SoundTrack.mp3.bin.h" 

$(INTERMEDIATE)/WaterDropBig.mp3.bin.h: ../../../../Samples/Menu3D/Data/Sounds/WaterDropBig.mp3 | $(INTERMEDIATE)
	@echo [BIN] [Samples/Menu3D] $(notdir $<)
	$(Q)$(BIN2H) "../../../../Samples/Menu3D/Data/Sounds/WaterDropBig.mp3" > "$(INTERMEDIATE)/WaterDropBig.mp3.bin.h" 

$(INTERMEDIATE)/WaterDropSmall.mp3.bin.h: ../../../../Samples/Menu3D/Data/Sounds/WaterDropSmall.mp3 | $(INTERMEDIATE)
	@echo [BIN] [Samples/Menu3D] $(notdir $<)
	$(Q)$(BIN2H) "../../../../Samples/Menu3D/Data/Sounds/WaterDropSmall.mp3" > "$(INTERMEDIATE)/WaterDropSmall.mp3.bin.h" 

$(TARGET): $(LIBS_DEPS) $(INTERMEDIATE)/android_native_app_glue.o $(INTERMEDIATE)/App.xaml.o $(INTERMEDIATE)/Main.o $(INTERMEDIATE)/MainMenu.xaml.o $(INTERMEDIATE)/MainWindow.xaml.o $(INTERMEDIATE)/MenuDescription.xaml.o $(INTERMEDIATE)/MultiplierConverter.o $(INTERMEDIATE)/OptionSelector.xaml.o $(INTERMEDIATE)/SettingsMenu.xaml.o $(INTERMEDIATE)/StartMenu.xaml.o $(INTERMEDIATE)/ViewModel.o | $(TARGET_DIR)
	@echo [LD] $(notdir $@)
	+$(Q)$(CXX) $(LDFLAGS) -march=i686 -mtune=intel -mssse3 -mfpmath=sse -m32 -shared -Wl,--no-undefined -Wl,-soname,libSamples_Menu3D.so -L../../../../../../Bin/android_x86 $(LIB_DIRS) -o $(TARGET) @$(CONFIG).rsp $(LIBS)
	@echo [STRIP] $(notdir $@)
	$(Q)i686-linux-android-objcopy --only-keep-debug $(TARGET) $(TARGET).debug
	$(Q)i686-linux-android-strip --strip-unneeded $(TARGET)
	$(Q)i686-linux-android-objcopy --add-gnu-debuglink=$(TARGET).debug $(TARGET)

$(INTERMEDIATE)/java/com/noesis/Samples/Menu3D/NoesisNativeActivity.class: java/NoesisNativeActivity.java
	@echo [JAVA] $(notdir $<)
	$(Q)$(call MKDIR,$(INTERMEDIATE)/java)
	$(Q)javac -source 1.7 -target 1.7 -Xlint:-options -d $(INTERMEDIATE)/java -classpath "${ANDROID_PLATFORM}/android.jar" -sourcepath $(dir $<) $<

$(INTERMEDIATE)/apk/classes.dex: $(INTERMEDIATE)/java/com/noesis/Samples/Menu3D/NoesisNativeActivity.class
	@echo [DEX] $(notdir $@)
	$(Q)$(call MKDIR,$(INTERMEDIATE)/apk)
	$(Q)dx --dex --output=$(INTERMEDIATE)/apk/classes.dex $(INTERMEDIATE)/java

$(INTERMEDIATE)/Samples.Menu3D-unsigned.apk: $(TARGET) $(LIBS_DEPS) $(INTERMEDIATE)/apk/classes.dex AndroidManifest.xml
	@echo [AAPT] $(notdir $@)
	$(Q)$(call MKDIR,$(INTERMEDIATE)/apk/lib/x86)
	$(Q)$(call CP,$(TARGET),$(INTERMEDIATE)/apk/lib/x86)
	$(Q)$(call CP,../../../../../../Bin/android_x86/libNoesisApp.so,$(INTERMEDIATE)/apk/lib/x86)
	$(Q)$(call CP,../../../../../../Bin/android_x86/libNoesis.so,$(INTERMEDIATE)/apk/lib/x86)
	$(Q)aapt package -f -S res -M AndroidManifest.xml -I $(ANDROID_PLATFORM)/android.jar -F $(INTERMEDIATE)/Samples.Menu3D-unsigned.apk $(INTERMEDIATE)/apk

$(INTERMEDIATE)/Samples.Menu3D-unsigned-aligned.apk: $(INTERMEDIATE)/Samples.Menu3D-unsigned.apk
	@echo [ALIGN] $(notdir $@)
	$(Q)zipalign -f 4 $(INTERMEDIATE)/Samples.Menu3D-unsigned.apk $(INTERMEDIATE)/Samples.Menu3D-unsigned-aligned.apk

$(TARGET_APK): $(INTERMEDIATE)/Samples.Menu3D-unsigned-aligned.apk
	@echo [SIGN] $(notdir $@)
	$(Q)apksigner sign --ks android.jks --ks-pass pass:noesis --out $(TARGET_APK) $(INTERMEDIATE)/Samples.Menu3D-unsigned-aligned.apk

-include $(INTERMEDIATE)/android_native_app_glue.d $(INTERMEDIATE)/App.xaml.d $(INTERMEDIATE)/Main.d $(INTERMEDIATE)/MainMenu.xaml.d $(INTERMEDIATE)/MainWindow.xaml.d $(INTERMEDIATE)/MenuDescription.xaml.d $(INTERMEDIATE)/MultiplierConverter.d $(INTERMEDIATE)/OptionSelector.xaml.d $(INTERMEDIATE)/SettingsMenu.xaml.d $(INTERMEDIATE)/StartMenu.xaml.d $(INTERMEDIATE)/ViewModel.d

run:
	$(Q)adb install -r $(TARGET_APK)
	$(Q)adb logcat -c
	$(Q)adb shell monkey -p com.noesis.Samples.Menu3D -c android.intent.category.LAUNCHER 1
	$(Q)adb logcat -s Noesis:V

clean:
	@echo ==== [Samples.Menu3D] Cleaning '$(CONFIG)' configuration ====
	$(Q)$(call RMTREE,$(INTERMEDIATE))
	$(Q)$(call RM,$(TARGET))
	$(Q)$(call RM,$(TARGET).debug)
	$(Q)$(call RM,$(TARGET_APK))
