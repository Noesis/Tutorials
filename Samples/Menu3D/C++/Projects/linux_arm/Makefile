# GNU Make project for 'Samples.Menu3D'

# Parallel builds can be enabled using the environment variable MAKEFLAGS (eg: MAKEFLAGS="-j 4")
# For parallel execution in Windows, Make 4.0 or better is required

CC = arm-linux-gnueabihf-gcc
CXX = arm-linux-gnueabihf-g++
AR = arm-linux-gnueabihf-ar

CFLAGS_COMMON = -g -pipe -Wall -Werror -Wfatal-errors -Wtype-limits -Wno-maybe-uninitialized -fvisibility=hidden -fmerge-all-constants
CXXFLAGS_COMMON = $(CFLAGS_COMMON) -std=c++11 -fno-exceptions -frtti -fvisibility-inlines-hidden -fno-threadsafe-statics
LDFLAGS_COMMON = -Wextra

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
  TARGET_DIR = ../../../../../../Bin/linux_arm
  TARGET = ../../../../../../Bin/linux_arm/Samples.Menu3D
  INTERMEDIATE = build/Debug
  LIB_DIRS = 
  LIBS = -lNoesis -lNoesisApp
  LIBS_DEPS = ../../../../../../Bin/linux_arm/libNoesis.so ../../../../../../Bin/linux_arm/libNoesisApp.so
  INCLUDES = -I../../../../../../Include -I../../../../App/ApplicationLauncher/Include -I../../../../App/Display/Include -I../../../../App/DisplayLauncher/Include -I../../../../App/Interactivity/Include -I../../../../App/Launcher/Include -I../../../../App/MediaElement/Include -I../../../../App/Providers/Include -Ibuild/Debug
  DEFINES = -DNS_BUILD -DNS_CONFIG=Debug -DNS_VERSION=3.1.0 -DNS_APP_FRAMEWORK -DNS_LICENSE -DNS_DEBUG -DNS_PROFILE -DNS_MINIMUM_LOG_LEVEL=1
  CFLAGS = $(CFLAGS_COMMON) -D_DEBUG
  CXXFLAGS = $(CXXFLAGS_COMMON) -D_DEBUG
  LDFLAGS = $(LDFLAGS_COMMON) $(CXXFLAGS)
else ifeq ($(CONFIG), Profile)
  TARGET_DIR = ../../../../../../Bin/linux_arm
  TARGET = ../../../../../../Bin/linux_arm/Samples.Menu3D
  INTERMEDIATE = build/Profile
  LIB_DIRS = 
  LIBS = -lNoesis -lNoesisApp
  LIBS_DEPS = ../../../../../../Bin/linux_arm/libNoesis.so ../../../../../../Bin/linux_arm/libNoesisApp.so
  INCLUDES = -I../../../../../../Include -I../../../../App/ApplicationLauncher/Include -I../../../../App/Display/Include -I../../../../App/DisplayLauncher/Include -I../../../../App/Interactivity/Include -I../../../../App/Launcher/Include -I../../../../App/MediaElement/Include -I../../../../App/Providers/Include -Ibuild/Profile
  DEFINES = -DNS_BUILD -DNS_CONFIG=Profile -DNS_VERSION=3.1.0 -DNS_APP_FRAMEWORK -DNS_LICENSE -DNS_PROFILE -DNS_MINIMUM_LOG_LEVEL=2
  CFLAGS = $(CFLAGS_COMMON) -Ofast -DNDEBUG -ffunction-sections -fdata-sections -fno-asynchronous-unwind-tables -U_FORTIFY_SOURCE
  CXXFLAGS = $(CXXFLAGS_COMMON) -Ofast -DNDEBUG -ffunction-sections -fdata-sections -fno-asynchronous-unwind-tables -U_FORTIFY_SOURCE
  LDFLAGS = $(LDFLAGS_COMMON) $(CXXFLAGS) -fuse-ld=gold -Wl,-O3,--gc-sections,--icf=all
else ifeq ($(CONFIG), Release)
  TARGET_DIR = ../../../../../../Bin/linux_arm
  TARGET = ../../../../../../Bin/linux_arm/Samples.Menu3D
  INTERMEDIATE = build/Release
  LIB_DIRS = 
  LIBS = -lNoesis -lNoesisApp
  LIBS_DEPS = ../../../../../../Bin/linux_arm/libNoesis.so ../../../../../../Bin/linux_arm/libNoesisApp.so
  INCLUDES = -I../../../../../../Include -I../../../../App/ApplicationLauncher/Include -I../../../../App/Display/Include -I../../../../App/DisplayLauncher/Include -I../../../../App/Interactivity/Include -I../../../../App/Launcher/Include -I../../../../App/MediaElement/Include -I../../../../App/Providers/Include -Ibuild/Release
  DEFINES = -DNS_BUILD -DNS_CONFIG=Release -DNS_VERSION=3.1.0 -DNS_APP_FRAMEWORK -DNS_LICENSE
  CFLAGS = $(CFLAGS_COMMON) -Ofast -flto=jobserver -DNDEBUG -ffunction-sections -fdata-sections -fno-asynchronous-unwind-tables -U_FORTIFY_SOURCE -fomit-frame-pointer
  CXXFLAGS = $(CXXFLAGS_COMMON) -Ofast -flto=jobserver -DNDEBUG -ffunction-sections -fdata-sections -fno-asynchronous-unwind-tables -U_FORTIFY_SOURCE -fomit-frame-pointer
  LDFLAGS = $(LDFLAGS_COMMON) $(CXXFLAGS) -fuse-ld=gold -Wl,-O3,--gc-sections,--icf=all
else
  $(error Invalid configuration '$(CONFIG)')
endif

PCH =
PCHFLAGS =
DATA = $(INTERMEDIATE)/App.xaml.bin.h $(INTERMEDIATE)/MainWindow.xaml.bin.h $(INTERMEDIATE)/MenuResources.xaml.bin.h $(INTERMEDIATE)/MenuDescription.xaml.bin.h $(INTERMEDIATE)/MainMenu.xaml.bin.h $(INTERMEDIATE)/StartMenu.xaml.bin.h $(INTERMEDIATE)/SettingsMenu.xaml.bin.h $(INTERMEDIATE)/OptionSelector.xaml.bin.h $(INTERMEDIATE)/BackClouds.png.bin.h $(INTERMEDIATE)/FrontClouds.png.bin.h $(INTERMEDIATE)/FrontTrees.png.bin.h $(INTERMEDIATE)/LakeAndMountains.png.bin.h $(INTERMEDIATE)/SkyAndSun.jpg.bin.h $(INTERMEDIATE)/weblysleekuisb.ttf.bin.h $(INTERMEDIATE)/weblysleekuisl.ttf.bin.h $(INTERMEDIATE)/SoundTrack.mp3.bin.h $(INTERMEDIATE)/WaterDropBig.mp3.bin.h $(INTERMEDIATE)/WaterDropSmall.mp3.bin.h

.SUFFIXES:
.DELETE_ON_ERROR:
.PHONY: all prebuild data clean

all: prebuild $(TARGET)

prebuild:
	@echo ==== [Samples.Menu3D] Building '$(CONFIG)' configuration ====

data: $(DATA)

$(INTERMEDIATE):
	$(Q)$(call MKDIR,$(INTERMEDIATE))

$(TARGET_DIR):
	$(Q)$(call MKDIR,$(TARGET_DIR))

$(INTERMEDIATE)/%.o: ../../../../Samples/Menu3D/Src/%.cpp $(PCH) | $(INTERMEDIATE) data
	@echo [CXX] [Samples/Menu3D] $(notdir $<)
	$(Q)$(CXX) $(CXXFLAGS) $(PCHFLAGS) $(INCLUDES) $(DEFINES) -fPIC -c -MMD -MF $(basename $@).d.tmp -MP -o $@ $< && $(call MV,$(basename $@).d.tmp,$(basename $@).d)

	$(Q)$(call FIXSLASHES,$(@:.o=.d))

$(INTERMEDIATE)/%.o: ../../../../Samples/Menu3D/Src/%.c | $(INTERMEDIATE) data
	@echo [CC] [Samples/Menu3D] $(notdir $<)
	$(Q)$(CC) $(CFLAGS) $(INCLUDES) $(DEFINES) -fPIC -c -MMD -MF $(basename $@).d.tmp -MP -o $@ $< && $(call MV,$(basename $@).d.tmp,$(basename $@).d)

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

$(TARGET): $(LIBS_DEPS) $(INTERMEDIATE)/ViewModel.o $(INTERMEDIATE)/OptionSelector.xaml.o $(INTERMEDIATE)/StartMenu.xaml.o $(INTERMEDIATE)/SettingsMenu.xaml.o $(INTERMEDIATE)/MainWindow.xaml.o $(INTERMEDIATE)/MainMenu.xaml.o $(INTERMEDIATE)/MenuDescription.xaml.o $(INTERMEDIATE)/MultiplierConverter.o $(INTERMEDIATE)/Main.o $(INTERMEDIATE)/App.xaml.o | $(TARGET_DIR)
	@echo [LD] $(notdir $@)
	+$(Q)$(CXX) $(LDFLAGS) -pie -Wl,-rpath,\$$ORIGIN -Wl,-rpath,../../../../../../Bin/linux_arm -L../../../../../../Bin/linux_arm $(LIB_DIRS) -o $(TARGET) @$(CONFIG).rsp $(LIBS)
	@echo [STRIP] $(notdir $@)
	$(Q)arm-linux-gnueabihf-objcopy --only-keep-debug $(TARGET) $(TARGET).debug
	$(Q)arm-linux-gnueabihf-strip --strip-unneeded $(TARGET)
	$(Q)arm-linux-gnueabihf-objcopy --add-gnu-debuglink=$(TARGET).debug $(TARGET)

-include $(INTERMEDIATE)/ViewModel.d $(INTERMEDIATE)/OptionSelector.xaml.d $(INTERMEDIATE)/StartMenu.xaml.d $(INTERMEDIATE)/SettingsMenu.xaml.d $(INTERMEDIATE)/MainWindow.xaml.d $(INTERMEDIATE)/MainMenu.xaml.d $(INTERMEDIATE)/MenuDescription.xaml.d $(INTERMEDIATE)/MultiplierConverter.d $(INTERMEDIATE)/Main.d $(INTERMEDIATE)/App.xaml.d

clean:
	@echo ==== [Samples.Menu3D] Cleaning '$(CONFIG)' configuration ====
	$(Q)$(call RMTREE,$(INTERMEDIATE))
	$(Q)$(call RM,$(TARGET))
	$(Q)$(call RM,$(TARGET).debug)
