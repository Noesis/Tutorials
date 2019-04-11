# GNU Make project for 'Samples.DataBinding'

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
  TARGET = ../../../../../../Bin/linux_x86_64/Samples.DataBinding
  INTERMEDIATE = build/Profile
  LIB_DIRS = 
  LIBS = -lNoesisApp -lNoesis
  LIBS_DEPS = ../../../../../../Bin/linux_x86_64/libNoesisApp.so ../../../../../../Bin/linux_x86_64/libNoesis.so
  INCLUDES = -I../../../../Core/NSTL/Include -I../../../../Math/VectorMath/Include -I../../../../../../3rdParty/EASTL/local/include -I../../../../App/Providers/Include -I../../../../Drawing/Types/Include -I../../../../Math/Utils/Include -I../../../../App/Display/Include -I../../../../App/Launcher/Include -I../../../../Gui/CachedFontProvider/Include -I../../../../Gui/Core/Include -I../../../../../../Include -I../../../../App/ApplicationLauncher/Include -I../../../../Gui/Providers/Include -I../../../../Samples/DataBinding/Include -I../../../../App/DisplayLauncher/Include -I../../../../Core/Kernel/Include -I../../../../Core/Nullable/Include -I../../../../Gui/DependencySystem/Include -Ibuild/Profile
  DEFINES = -DNS_BUILD -DNS_CONFIG=Profile -DNS_VERSION=2.2.1 -DNS_APP_FRAMEWORK -DNS_PROFILE -DNS_MINIMUM_LOG_LEVEL=2
  CFLAGS = $(CFLAGS_PROFILE)
  CXXFLAGS = $(CXXFLAGS_PROFILE)
  LDFLAGS = $(LDFLAGS_PROFILE)
else ifeq ($(CONFIG), Release)
  TARGET_DIR = ../../../../../../Bin/linux_x86_64
  TARGET = ../../../../../../Bin/linux_x86_64/Samples.DataBinding
  INTERMEDIATE = build/Release
  LIB_DIRS = 
  LIBS = -lNoesisApp -lNoesis
  LIBS_DEPS = ../../../../../../Bin/linux_x86_64/libNoesisApp.so ../../../../../../Bin/linux_x86_64/libNoesis.so
  INCLUDES = -I../../../../Core/NSTL/Include -I../../../../Math/VectorMath/Include -I../../../../../../3rdParty/EASTL/local/include -I../../../../App/Providers/Include -I../../../../Drawing/Types/Include -I../../../../Math/Utils/Include -I../../../../App/Display/Include -I../../../../App/Launcher/Include -I../../../../Gui/CachedFontProvider/Include -I../../../../Gui/Core/Include -I../../../../../../Include -I../../../../App/ApplicationLauncher/Include -I../../../../Gui/Providers/Include -I../../../../Samples/DataBinding/Include -I../../../../App/DisplayLauncher/Include -I../../../../Core/Kernel/Include -I../../../../Core/Nullable/Include -I../../../../Gui/DependencySystem/Include -Ibuild/Release
  DEFINES = -DNS_BUILD -DNS_CONFIG=Release -DNS_VERSION=2.2.1 -DNS_APP_FRAMEWORK
  CFLAGS = $(CFLAGS_RELEASE)
  CXXFLAGS = $(CXXFLAGS_RELEASE)
  LDFLAGS = $(LDFLAGS_RELEASE)
else ifeq ($(CONFIG), Debug)
  TARGET_DIR = ../../../../../../Bin/linux_x86_64
  TARGET = ../../../../../../Bin/linux_x86_64/Samples.DataBinding
  INTERMEDIATE = build/Debug
  LIB_DIRS = 
  LIBS = -lNoesisApp -lNoesis
  LIBS_DEPS = ../../../../../../Bin/linux_x86_64/libNoesisApp.so ../../../../../../Bin/linux_x86_64/libNoesis.so
  INCLUDES = -I../../../../Core/NSTL/Include -I../../../../Math/VectorMath/Include -I../../../../../../3rdParty/EASTL/local/include -I../../../../App/Providers/Include -I../../../../Drawing/Types/Include -I../../../../Math/Utils/Include -I../../../../App/Display/Include -I../../../../App/Launcher/Include -I../../../../Gui/CachedFontProvider/Include -I../../../../Gui/Core/Include -I../../../../../../Include -I../../../../App/ApplicationLauncher/Include -I../../../../Gui/Providers/Include -I../../../../Samples/DataBinding/Include -I../../../../App/DisplayLauncher/Include -I../../../../Core/Kernel/Include -I../../../../Core/Nullable/Include -I../../../../Gui/DependencySystem/Include -Ibuild/Debug
  DEFINES = -DNS_BUILD -DNS_CONFIG=Debug -DNS_VERSION=2.2.1 -DNS_APP_FRAMEWORK -DNS_DEBUG -DNS_PROFILE -DNS_MINIMUM_LOG_LEVEL=1
  CFLAGS = $(CFLAGS_DEBUG)
  CXXFLAGS = $(CXXFLAGS_DEBUG)
  LDFLAGS = $(LDFLAGS_DEBUG)
else
  $(error Invalid configuration '$(CONFIG)')
endif

PCH =
PCHFLAGS =
DATA = $(INTERMEDIATE)/App.xaml.bin.h $(INTERMEDIATE)/MainWindow.xaml.bin.h $(INTERMEDIATE)/Roboto-Regular.ttf.bin.h $(INTERMEDIATE)/Roboto-Bold.ttf.bin.h $(INTERMEDIATE)/moons_2.jpg.bin.h $(INTERMEDIATE)/earglobe.jpg.bin.h $(INTERMEDIATE)/jupglobe.jpg.bin.h $(INTERMEDIATE)/marglobe.jpg.bin.h $(INTERMEDIATE)/merglobe.jpg.bin.h $(INTERMEDIATE)/nepglobe.jpg.bin.h $(INTERMEDIATE)/plutoch_2.jpg.bin.h $(INTERMEDIATE)/sun.jpg.bin.h $(INTERMEDIATE)/uraglobe.jpg.bin.h $(INTERMEDIATE)/venglobe.jpg.bin.h

.SUFFIXES:
.PHONY: all prebuild data clean

all: prebuild $(TARGET)

prebuild:
	@echo ==== [Samples.DataBinding] Building '$(CONFIG)' configuration ====

data: $(DATA)

$(INTERMEDIATE):
	$(call MKDIR,$(INTERMEDIATE))

$(TARGET_DIR):
	$(call MKDIR,$(TARGET_DIR))

$(INTERMEDIATE)/%.o: ../../../../Samples/DataBinding/Src/%.cpp $(PCH) | $(INTERMEDIATE) data
	@echo [CXX] [Samples/DataBinding] $(notdir $<)
	$(Q)$(CXX) $(CXXFLAGS) $(PCHFLAGS) $(INCLUDES) $(DEFINES) -march=x86-64 -m64 -fPIC -c -MMD -MP -o $@ $<
	$(call FIXSLASHES,$(@:.o=.d))

$(INTERMEDIATE)/%.o: ../../../../Samples/DataBinding/Src/%.c | $(INTERMEDIATE) data
	@echo [CC] [Samples/DataBinding] $(notdir $<)
	$(Q)$(CC) $(CFLAGS) $(INCLUDES) $(DEFINES) -march=x86-64 -m64 -fPIC -c -MMD -MP -o $@ $<
	$(call FIXSLASHES,$(@:.o=.d))

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

$(TARGET): $(LIBS_DEPS) $(INTERMEDIATE)/Main.o | $(TARGET_DIR)
	@echo [LD] $(notdir $@)
	+$(Q)$(CXX) $(LDFLAGS) -march=x86-64 -m64 -pie -Wl,-rpath,\$$ORIGIN -Wl,-rpath,../../../../../../Bin/linux_x86_64 -L../../../../../../Bin/linux_x86_64 $(LIB_DIRS) -o $(TARGET) @$(CONFIG).rsp $(LIBS)
	@echo [STRIP] $(notdir $@)
	$(Q)objcopy --only-keep-debug $(TARGET) $(TARGET).debug
	$(Q)strip --strip-unneeded $(TARGET)
	$(Q)objcopy --add-gnu-debuglink=$(TARGET).debug $(TARGET)

-include $(INTERMEDIATE)/Main.d

clean:
	@echo ==== [Samples.DataBinding] Cleaning '$(CONFIG)' configuration ====
	$(call RMTREE,$(INTERMEDIATE))
	$(call RM,$(TARGET))
	$(call RM,$(TARGET).debug)
