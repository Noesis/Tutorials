# GNU Make project for 'Samples.Menu3D'

# Parallel builds can be enabled using the environment variable MAKEFLAGS (eg: MAKEFLAGS="-j 4")
# For parallel execution in Windows, Make 4.0 or better is required

include ../../../../../../Config/Common.makeprops
include ../../../../../../Config/Profile/Profile.makeprops
include ../../../../../../Config/Release/Release.makeprops
include ../../../../../../Config/Debug/Debug.makeprops

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

ifeq ($(CONFIG), Profile)
  TARGET_DIR = ../../../../../../Bin/linux_x86_64
  TARGET = ../../../../../../Bin/linux_x86_64/Samples.Menu3D
  INTERMEDIATE = build/Profile
  LIB_DIRS = 
  LIBS = -lNoesisApp -lNoesis
  LIBS_DEPS = ../../../../../../Bin/linux_x86_64/libNoesisApp.so ../../../../../../Bin/linux_x86_64/libNoesis.so
  INCLUDES = -I../../../../Core/NSTL/Include -I../../../../Math/Utils/Include -I../../../../Math/VectorMath/Include -I../../../../App/Providers/Include -I../../../../../../3rdParty/EASTL/local/include -I../../../../Samples/Menu3D/Include -I../../../../Drawing/Types/Include -I../../../../App/Interactivity/Include -I../../../../Core/TypeConverter/Include -I../../../../App/Display/Include -I../../../../App/Launcher/Include -I../../../../Core/Nullable/Include -I../../../../Gui/Core/Include -I../../../../Gui/Animation/Include -I../../../../../../Include -I../../../../App/ApplicationLauncher/Include -I../../../../Gui/Providers/Include -I../../../../App/DisplayLauncher/Include -I../../../../Core/Kernel/Include -I../../../../Gui/CachedFontProvider/Include -I../../../../Gui/DependencySystem/Include -Ibuild/Profile
  DEFINES = -DNS_BUILD -DNS_CONFIG=Profile -DNS_VERSION=2.2.4 -DNS_APP_FRAMEWORK -DNS_PROFILE -DNS_MINIMUM_LOG_LEVEL=2
  CFLAGS = $(CFLAGS_PROFILE)
  CXXFLAGS = $(CXXFLAGS_PROFILE)
  LDFLAGS = $(LDFLAGS_PROFILE)
else ifeq ($(CONFIG), Release)
  TARGET_DIR = ../../../../../../Bin/linux_x86_64
  TARGET = ../../../../../../Bin/linux_x86_64/Samples.Menu3D
  INTERMEDIATE = build/Release
  LIB_DIRS = 
  LIBS = -lNoesisApp -lNoesis
  LIBS_DEPS = ../../../../../../Bin/linux_x86_64/libNoesisApp.so ../../../../../../Bin/linux_x86_64/libNoesis.so
  INCLUDES = -I../../../../Core/NSTL/Include -I../../../../Math/Utils/Include -I../../../../Math/VectorMath/Include -I../../../../App/Providers/Include -I../../../../../../3rdParty/EASTL/local/include -I../../../../Samples/Menu3D/Include -I../../../../Drawing/Types/Include -I../../../../App/Interactivity/Include -I../../../../Core/TypeConverter/Include -I../../../../App/Display/Include -I../../../../App/Launcher/Include -I../../../../Core/Nullable/Include -I../../../../Gui/Core/Include -I../../../../Gui/Animation/Include -I../../../../../../Include -I../../../../App/ApplicationLauncher/Include -I../../../../Gui/Providers/Include -I../../../../App/DisplayLauncher/Include -I../../../../Core/Kernel/Include -I../../../../Gui/CachedFontProvider/Include -I../../../../Gui/DependencySystem/Include -Ibuild/Release
  DEFINES = -DNS_BUILD -DNS_CONFIG=Release -DNS_VERSION=2.2.4 -DNS_APP_FRAMEWORK
  CFLAGS = $(CFLAGS_RELEASE)
  CXXFLAGS = $(CXXFLAGS_RELEASE)
  LDFLAGS = $(LDFLAGS_RELEASE)
else ifeq ($(CONFIG), Debug)
  TARGET_DIR = ../../../../../../Bin/linux_x86_64
  TARGET = ../../../../../../Bin/linux_x86_64/Samples.Menu3D
  INTERMEDIATE = build/Debug
  LIB_DIRS = 
  LIBS = -lNoesisApp -lNoesis
  LIBS_DEPS = ../../../../../../Bin/linux_x86_64/libNoesisApp.so ../../../../../../Bin/linux_x86_64/libNoesis.so
  INCLUDES = -I../../../../Core/NSTL/Include -I../../../../Math/Utils/Include -I../../../../Math/VectorMath/Include -I../../../../App/Providers/Include -I../../../../../../3rdParty/EASTL/local/include -I../../../../Samples/Menu3D/Include -I../../../../Drawing/Types/Include -I../../../../App/Interactivity/Include -I../../../../Core/TypeConverter/Include -I../../../../App/Display/Include -I../../../../App/Launcher/Include -I../../../../Core/Nullable/Include -I../../../../Gui/Core/Include -I../../../../Gui/Animation/Include -I../../../../../../Include -I../../../../App/ApplicationLauncher/Include -I../../../../Gui/Providers/Include -I../../../../App/DisplayLauncher/Include -I../../../../Core/Kernel/Include -I../../../../Gui/CachedFontProvider/Include -I../../../../Gui/DependencySystem/Include -Ibuild/Debug
  DEFINES = -DNS_BUILD -DNS_CONFIG=Debug -DNS_VERSION=2.2.4 -DNS_APP_FRAMEWORK -DNS_DEBUG -DNS_PROFILE -DNS_MINIMUM_LOG_LEVEL=1
  CFLAGS = $(CFLAGS_DEBUG)
  CXXFLAGS = $(CXXFLAGS_DEBUG)
  LDFLAGS = $(LDFLAGS_DEBUG)
else
  $(error Invalid configuration '$(CONFIG)')
endif

PCH =
PCHFLAGS =
DATA = $(INTERMEDIATE)/App.xaml.bin.h $(INTERMEDIATE)/MainWindow.xaml.bin.h $(INTERMEDIATE)/MenuResources.xaml.bin.h $(INTERMEDIATE)/MenuDescription.xaml.bin.h $(INTERMEDIATE)/MainMenu.xaml.bin.h $(INTERMEDIATE)/StartMenu.xaml.bin.h $(INTERMEDIATE)/SettingsMenu.xaml.bin.h $(INTERMEDIATE)/OptionSelector.xaml.bin.h $(INTERMEDIATE)/BackClouds.png.bin.h $(INTERMEDIATE)/FrontClouds.png.bin.h $(INTERMEDIATE)/FrontTrees.png.bin.h $(INTERMEDIATE)/LakeAndMountains.png.bin.h $(INTERMEDIATE)/SkyAndSun.jpg.bin.h $(INTERMEDIATE)/weblysleekuisb.ttf.bin.h $(INTERMEDIATE)/weblysleekuisl.ttf.bin.h $(INTERMEDIATE)/SoundTrack.mp3.bin.h $(INTERMEDIATE)/WaterDropBig.mp3.bin.h $(INTERMEDIATE)/WaterDropSmall.mp3.bin.h

.SUFFIXES:
.PHONY: all prebuild data clean

all: prebuild $(TARGET)

prebuild:
	@echo ==== [Samples.Menu3D] Building '$(CONFIG)' configuration ====

data: $(DATA)

$(INTERMEDIATE):
	$(call MKDIR,$(INTERMEDIATE))

$(TARGET_DIR):
	$(call MKDIR,$(TARGET_DIR))

$(INTERMEDIATE)/%.o: ../../../../Samples/Menu3D/Src/%.cpp $(PCH) | $(INTERMEDIATE) data
	@echo [CXX] [Samples/Menu3D] $(notdir $<)
	$(Q)$(CXX) $(CXXFLAGS) $(PCHFLAGS) $(INCLUDES) $(DEFINES) -march=x86-64 -msse2 -mfpmath=sse -m64 -fPIC -c -MMD -MP -o $@ $<
	$(call FIXSLASHES,$(@:.o=.d))

$(INTERMEDIATE)/%.o: ../../../../Samples/Menu3D/Src/%.c | $(INTERMEDIATE) data
	@echo [CC] [Samples/Menu3D] $(notdir $<)
	$(Q)$(CC) $(CFLAGS) $(INCLUDES) $(DEFINES) -march=x86-64 -msse2 -mfpmath=sse -m64 -fPIC -c -MMD -MP -o $@ $<
	$(call FIXSLASHES,$(@:.o=.d))

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

$(TARGET): $(LIBS_DEPS) $(INTERMEDIATE)/SettingsMenu.xaml.o $(INTERMEDIATE)/Main.o $(INTERMEDIATE)/MainMenu.xaml.o $(INTERMEDIATE)/MultiplierConverter.o $(INTERMEDIATE)/ViewModel.o $(INTERMEDIATE)/App.xaml.o $(INTERMEDIATE)/StartMenu.xaml.o $(INTERMEDIATE)/OptionSelector.xaml.o $(INTERMEDIATE)/MainWindow.xaml.o $(INTERMEDIATE)/MenuDescription.xaml.o | $(TARGET_DIR)
	@echo [LD] $(notdir $@)
	+$(Q)$(CXX) $(LDFLAGS) -march=x86-64 -msse2 -mfpmath=sse -m64 -pie -Wl,-rpath,\$$ORIGIN -Wl,-rpath,../../../../../../Bin/linux_x86_64 -L../../../../../../Bin/linux_x86_64 $(LIB_DIRS) -o $(TARGET) @$(CONFIG).rsp $(LIBS)
	@echo [STRIP] $(notdir $@)
	$(Q)objcopy --only-keep-debug $(TARGET) $(TARGET).debug
	$(Q)strip --strip-unneeded $(TARGET)
	$(Q)objcopy --add-gnu-debuglink=$(TARGET).debug $(TARGET)

-include $(INTERMEDIATE)/SettingsMenu.xaml.d $(INTERMEDIATE)/Main.d $(INTERMEDIATE)/MainMenu.xaml.d $(INTERMEDIATE)/MultiplierConverter.d $(INTERMEDIATE)/ViewModel.d $(INTERMEDIATE)/App.xaml.d $(INTERMEDIATE)/StartMenu.xaml.d $(INTERMEDIATE)/OptionSelector.xaml.d $(INTERMEDIATE)/MainWindow.xaml.d $(INTERMEDIATE)/MenuDescription.xaml.d

clean:
	@echo ==== [Samples.Menu3D] Cleaning '$(CONFIG)' configuration ====
	$(call RMTREE,$(INTERMEDIATE))
	$(call RM,$(TARGET))
	$(call RM,$(TARGET).debug)
