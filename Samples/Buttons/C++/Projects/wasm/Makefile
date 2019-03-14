# GNU Make project for 'Samples.Buttons'

# Parallel builds can be enabled using the environment variable MAKEFLAGS (eg: MAKEFLAGS="-j 4")
# For parallel execution in Windows, Make 4.0 or better is required

include ../../../../../../Config/Common.wasm.makeprops
include ../../../../../../Config/Debug/Debug.wasm.makeprops
include ../../../../../../Config/Profile/Profile.wasm.makeprops
include ../../../../../../Config/Release/Release.wasm.makeprops

CC = emcc
CXX = em++

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
  TARGET_DIR = ../../../../../../Bin/wasm
  TARGET = ../../../../../../Bin/wasm/Samples.Buttons.bc
  TARGET_HTML = ../../../../../../Bin/wasm/Samples.Buttons.html
  INTERMEDIATE = build/Debug
  LIB_DIRS = 
  LIBS = 
  LIBS_DEPS = 
  INCLUDES = -I../../../../App/Display/Include -I../../../../Core/Kernel/Include -I../../../../../../Include -I../../../../Samples/Buttons/Include -I../../../../Core/Nullable/Include -I../../../../App/Providers/Include -I../../../../Math/Utils/Include -I../../../../App/ApplicationLauncher/Include -I../../../../Gui/Core/Include -I../../../../App/DisplayLauncher/Include -I../../../../../../3rdParty/EASTL/local/include -I../../../../Math/VectorMath/Include -I../../../../Gui/DependencySystem/Include -I../../../../App/Interactivity/Include -I../../../../App/Launcher/Include -I../../../../Drawing/Types/Include -I../../../../Core/NSTL/Include -I../../../../Gui/CachedFontProvider/Include -I../../../../Gui/Providers/Include -Ibuild/Debug
  DEFINES = -DNS_BUILD -DNS_CONFIG=Debug -DNS_VERSION=2.2.0 -DNS_APP_FRAMEWORK -DNS_STATIC_LIBRARY -DNS_DEBUG -DNS_PROFILE -DNS_MINIMUM_LOG_LEVEL=1
  CFLAGS = $(CFLAGS_DEBUG)
  CXXFLAGS = $(CXXFLAGS_DEBUG)
  LDFLAGS = $(LDFLAGS_DEBUG)
else ifeq ($(CONFIG), Profile)
  TARGET_DIR = ../../../../../../Bin/wasm
  TARGET = ../../../../../../Bin/wasm/Samples.Buttons.bc
  TARGET_HTML = ../../../../../../Bin/wasm/Samples.Buttons.html
  INTERMEDIATE = build/Profile
  LIB_DIRS = 
  LIBS = 
  LIBS_DEPS = 
  INCLUDES = -I../../../../App/Display/Include -I../../../../Core/Kernel/Include -I../../../../../../Include -I../../../../Samples/Buttons/Include -I../../../../Core/Nullable/Include -I../../../../App/Providers/Include -I../../../../Math/Utils/Include -I../../../../App/ApplicationLauncher/Include -I../../../../Gui/Core/Include -I../../../../App/DisplayLauncher/Include -I../../../../../../3rdParty/EASTL/local/include -I../../../../Math/VectorMath/Include -I../../../../Gui/DependencySystem/Include -I../../../../App/Interactivity/Include -I../../../../App/Launcher/Include -I../../../../Drawing/Types/Include -I../../../../Core/NSTL/Include -I../../../../Gui/CachedFontProvider/Include -I../../../../Gui/Providers/Include -Ibuild/Profile
  DEFINES = -DNS_BUILD -DNS_CONFIG=Profile -DNS_VERSION=2.2.0 -DNS_APP_FRAMEWORK -DNS_STATIC_LIBRARY -DNS_PROFILE -DNS_MINIMUM_LOG_LEVEL=2
  CFLAGS = $(CFLAGS_PROFILE)
  CXXFLAGS = $(CXXFLAGS_PROFILE)
  LDFLAGS = $(LDFLAGS_PROFILE)
else ifeq ($(CONFIG), Release)
  TARGET_DIR = ../../../../../../Bin/wasm
  TARGET = ../../../../../../Bin/wasm/Samples.Buttons.bc
  TARGET_HTML = ../../../../../../Bin/wasm/Samples.Buttons.html
  INTERMEDIATE = build/Release
  LIB_DIRS = 
  LIBS = 
  LIBS_DEPS = 
  INCLUDES = -I../../../../App/Display/Include -I../../../../Core/Kernel/Include -I../../../../../../Include -I../../../../Samples/Buttons/Include -I../../../../Core/Nullable/Include -I../../../../App/Providers/Include -I../../../../Math/Utils/Include -I../../../../App/ApplicationLauncher/Include -I../../../../Gui/Core/Include -I../../../../App/DisplayLauncher/Include -I../../../../../../3rdParty/EASTL/local/include -I../../../../Math/VectorMath/Include -I../../../../Gui/DependencySystem/Include -I../../../../App/Interactivity/Include -I../../../../App/Launcher/Include -I../../../../Drawing/Types/Include -I../../../../Core/NSTL/Include -I../../../../Gui/CachedFontProvider/Include -I../../../../Gui/Providers/Include -Ibuild/Release
  DEFINES = -DNS_BUILD -DNS_CONFIG=Release -DNS_VERSION=2.2.0 -DNS_APP_FRAMEWORK -DNS_STATIC_LIBRARY
  CFLAGS = $(CFLAGS_RELEASE)
  CXXFLAGS = $(CXXFLAGS_RELEASE)
  LDFLAGS = $(LDFLAGS_RELEASE)
else
  $(error Invalid configuration '$(CONFIG)')
endif

PCH =
PCHFLAGS =
DATA = $(INTERMEDIATE)/App.xaml.bin.h $(INTERMEDIATE)/Resources.xaml.bin.h $(INTERMEDIATE)/MainWindow.xaml.bin.h $(INTERMEDIATE)/AudioSlide.mp3.bin.h $(INTERMEDIATE)/AudioClick.mp3.bin.h $(INTERMEDIATE)/Aero\ Matics\ Regular.ttf.bin.h

.SUFFIXES:
.PHONY: all prebuild data clean

all: prebuild $(TARGET_HTML)

prebuild:
	@echo ==== [Samples.Buttons] Building '$(CONFIG)' configuration ====

data: $(DATA)

$(INTERMEDIATE):
	$(call MKDIR,$(INTERMEDIATE))

$(TARGET_DIR):
	$(call MKDIR,$(TARGET_DIR))

$(INTERMEDIATE)/%.o: ../../../../Samples/Buttons/Src/%.cpp $(PCH) | $(INTERMEDIATE) data
	@echo [CXX] [Samples/Buttons] $(notdir $<)
	$(Q)$(CXX) $(CXXFLAGS) $(PCHFLAGS) $(INCLUDES) $(DEFINES)  -c -MMD -MP -o $@ $<
	$(call FIXSLASHES,$(@:.o=.d))

$(INTERMEDIATE)/%.o: ../../../../Samples/Buttons/Src/%.c | $(INTERMEDIATE) data
	@echo [CC] [Samples/Buttons] $(notdir $<)
	$(Q)$(CC) $(CFLAGS) $(INCLUDES) $(DEFINES)  -c -MMD -MP -o $@ $<
	$(call FIXSLASHES,$(@:.o=.d))

$(INTERMEDIATE)/App.xaml.bin.h: ../../../../Samples/Buttons/Data/App.xaml | $(INTERMEDIATE)
	@echo [BIN] [Samples/Buttons] $(notdir $<)
	$(Q)$(BIN2H) "../../../../Samples/Buttons/Data/App.xaml" > "$(INTERMEDIATE)/App.xaml.bin.h" 

$(INTERMEDIATE)/Resources.xaml.bin.h: ../../../../Samples/Buttons/Data/Resources.xaml | $(INTERMEDIATE)
	@echo [BIN] [Samples/Buttons] $(notdir $<)
	$(Q)$(BIN2H) "../../../../Samples/Buttons/Data/Resources.xaml" > "$(INTERMEDIATE)/Resources.xaml.bin.h" 

$(INTERMEDIATE)/MainWindow.xaml.bin.h: ../../../../Samples/Buttons/Data/MainWindow.xaml | $(INTERMEDIATE)
	@echo [BIN] [Samples/Buttons] $(notdir $<)
	$(Q)$(BIN2H) "../../../../Samples/Buttons/Data/MainWindow.xaml" > "$(INTERMEDIATE)/MainWindow.xaml.bin.h" 

$(INTERMEDIATE)/AudioSlide.mp3.bin.h: ../../../../Samples/Buttons/Data/AudioSlide.mp3 | $(INTERMEDIATE)
	@echo [BIN] [Samples/Buttons] $(notdir $<)
	$(Q)$(BIN2H) "../../../../Samples/Buttons/Data/AudioSlide.mp3" > "$(INTERMEDIATE)/AudioSlide.mp3.bin.h" 

$(INTERMEDIATE)/AudioClick.mp3.bin.h: ../../../../Samples/Buttons/Data/AudioClick.mp3 | $(INTERMEDIATE)
	@echo [BIN] [Samples/Buttons] $(notdir $<)
	$(Q)$(BIN2H) "../../../../Samples/Buttons/Data/AudioClick.mp3" > "$(INTERMEDIATE)/AudioClick.mp3.bin.h" 

$(INTERMEDIATE)/Aero\ Matics\ Regular.ttf.bin.h: ../../../../Samples/Buttons/Data/Aero\ Matics\ Regular.ttf | $(INTERMEDIATE)
	@echo [BIN] [Samples/Buttons] $(notdir $<)
	$(Q)$(BIN2H) "../../../../Samples/Buttons/Data/Aero Matics Regular.ttf" > "$(INTERMEDIATE)/Aero Matics Regular.ttf.bin.h" 

$(TARGET): $(LIBS_DEPS) $(INTERMEDIATE)/App.xaml.o $(INTERMEDIATE)/Main.o $(INTERMEDIATE)/MainWindow.xaml.o $(INTERMEDIATE)/ViewModel.o | $(TARGET_DIR)
	@echo [LD] $(notdir $@)
	+$(Q)$(CXX) $(LDFLAGS)  -L../../../../../../Bin/wasm $(LIB_DIRS) -o $(TARGET) @$(CONFIG).rsp $(LIBS)

$(TARGET_HTML): $(TARGET) ../../../../../../Bin/wasm/Noesis.bc ../../../../../../Bin/wasm/NoesisApp.bc
	@echo [HTML] $(notdir $@)
	$(Q)emcc $(LDFLAGS) $(TARGET) ../../../../../../Bin/wasm/Noesis.bc ../../../../../../Bin/wasm/NoesisApp.bc -o $(basename $(TARGET)).html --shell-file shell.html

-include $(INTERMEDIATE)/App.xaml.d $(INTERMEDIATE)/Main.d $(INTERMEDIATE)/MainWindow.xaml.d $(INTERMEDIATE)/ViewModel.d

clean:
	@echo ==== [Samples.Buttons] Cleaning '$(CONFIG)' configuration ====
	$(call RMTREE,$(INTERMEDIATE))
	$(call RM,$(TARGET))
	$(call RM,$(TARGET).js)
	$(call RM,$(TARGET).wasm)
	$(call RM,$(TARGET).wast)
	$(call RM,$(TARGET).html)
