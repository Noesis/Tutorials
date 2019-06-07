# GNU Make project for 'Samples.Commands'

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
  TARGET = ../../../../../../Bin/linux_x86_64/Samples.Commands
  INTERMEDIATE = build/Profile
  LIB_DIRS = 
  LIBS = -lNoesisApp -lNoesis
  LIBS_DEPS = ../../../../../../Bin/linux_x86_64/libNoesisApp.so ../../../../../../Bin/linux_x86_64/libNoesis.so
  INCLUDES = -I../../../../Core/NSTL/Include -I../../../../App/ApplicationLauncher/Include -I../../../../../../3rdParty/EASTL/local/include -I../../../../Drawing/Types/Include -I../../../../Math/Utils/Include -I../../../../App/Display/Include -I../../../../App/Launcher/Include -I../../../../Core/Nullable/Include -I../../../../App/DisplayLauncher/Include -I../../../../Gui/CachedFontProvider/Include -I../../../../Math/VectorMath/Include -I../../../../Gui/Providers/Include -I../../../../Samples/Commands/Include -I../../../../Gui/Core/Include -I../../../../Core/Kernel/Include -I../../../../App/Providers/Include -I../../../../../../Include -I../../../../Gui/DependencySystem/Include -Ibuild/Profile
  DEFINES = -DNS_BUILD -DNS_CONFIG=Profile -DNS_VERSION=2.2.3 -DNS_APP_FRAMEWORK -DNS_PROFILE -DNS_MINIMUM_LOG_LEVEL=2
  CFLAGS = $(CFLAGS_PROFILE)
  CXXFLAGS = $(CXXFLAGS_PROFILE)
  LDFLAGS = $(LDFLAGS_PROFILE)
else ifeq ($(CONFIG), Release)
  TARGET_DIR = ../../../../../../Bin/linux_x86_64
  TARGET = ../../../../../../Bin/linux_x86_64/Samples.Commands
  INTERMEDIATE = build/Release
  LIB_DIRS = 
  LIBS = -lNoesisApp -lNoesis
  LIBS_DEPS = ../../../../../../Bin/linux_x86_64/libNoesisApp.so ../../../../../../Bin/linux_x86_64/libNoesis.so
  INCLUDES = -I../../../../Core/NSTL/Include -I../../../../App/ApplicationLauncher/Include -I../../../../../../3rdParty/EASTL/local/include -I../../../../Drawing/Types/Include -I../../../../Math/Utils/Include -I../../../../App/Display/Include -I../../../../App/Launcher/Include -I../../../../Core/Nullable/Include -I../../../../App/DisplayLauncher/Include -I../../../../Gui/CachedFontProvider/Include -I../../../../Math/VectorMath/Include -I../../../../Gui/Providers/Include -I../../../../Samples/Commands/Include -I../../../../Gui/Core/Include -I../../../../Core/Kernel/Include -I../../../../App/Providers/Include -I../../../../../../Include -I../../../../Gui/DependencySystem/Include -Ibuild/Release
  DEFINES = -DNS_BUILD -DNS_CONFIG=Release -DNS_VERSION=2.2.3 -DNS_APP_FRAMEWORK
  CFLAGS = $(CFLAGS_RELEASE)
  CXXFLAGS = $(CXXFLAGS_RELEASE)
  LDFLAGS = $(LDFLAGS_RELEASE)
else ifeq ($(CONFIG), Debug)
  TARGET_DIR = ../../../../../../Bin/linux_x86_64
  TARGET = ../../../../../../Bin/linux_x86_64/Samples.Commands
  INTERMEDIATE = build/Debug
  LIB_DIRS = 
  LIBS = -lNoesisApp -lNoesis
  LIBS_DEPS = ../../../../../../Bin/linux_x86_64/libNoesisApp.so ../../../../../../Bin/linux_x86_64/libNoesis.so
  INCLUDES = -I../../../../Core/NSTL/Include -I../../../../App/ApplicationLauncher/Include -I../../../../../../3rdParty/EASTL/local/include -I../../../../Drawing/Types/Include -I../../../../Math/Utils/Include -I../../../../App/Display/Include -I../../../../App/Launcher/Include -I../../../../Core/Nullable/Include -I../../../../App/DisplayLauncher/Include -I../../../../Gui/CachedFontProvider/Include -I../../../../Math/VectorMath/Include -I../../../../Gui/Providers/Include -I../../../../Samples/Commands/Include -I../../../../Gui/Core/Include -I../../../../Core/Kernel/Include -I../../../../App/Providers/Include -I../../../../../../Include -I../../../../Gui/DependencySystem/Include -Ibuild/Debug
  DEFINES = -DNS_BUILD -DNS_CONFIG=Debug -DNS_VERSION=2.2.3 -DNS_APP_FRAMEWORK -DNS_DEBUG -DNS_PROFILE -DNS_MINIMUM_LOG_LEVEL=1
  CFLAGS = $(CFLAGS_DEBUG)
  CXXFLAGS = $(CXXFLAGS_DEBUG)
  LDFLAGS = $(LDFLAGS_DEBUG)
else
  $(error Invalid configuration '$(CONFIG)')
endif

PCH =
PCHFLAGS =
DATA = $(INTERMEDIATE)/MainWindow.xaml.bin.h $(INTERMEDIATE)/App.xaml.bin.h $(INTERMEDIATE)/Aero\ Matics\ Regular.ttf.bin.h

.SUFFIXES:
.PHONY: all prebuild data clean

all: prebuild $(TARGET)

prebuild:
	@echo ==== [Samples.Commands] Building '$(CONFIG)' configuration ====

data: $(DATA)

$(INTERMEDIATE):
	$(call MKDIR,$(INTERMEDIATE))

$(TARGET_DIR):
	$(call MKDIR,$(TARGET_DIR))

$(INTERMEDIATE)/%.o: ../../../../Samples/Commands/Src/%.cpp $(PCH) | $(INTERMEDIATE) data
	@echo [CXX] [Samples/Commands] $(notdir $<)
	$(Q)$(CXX) $(CXXFLAGS) $(PCHFLAGS) $(INCLUDES) $(DEFINES) -march=x86-64 -msse2 -mfpmath=sse -m64 -fPIC -c -MMD -MP -o $@ $<
	$(call FIXSLASHES,$(@:.o=.d))

$(INTERMEDIATE)/%.o: ../../../../Samples/Commands/Src/%.c | $(INTERMEDIATE) data
	@echo [CC] [Samples/Commands] $(notdir $<)
	$(Q)$(CC) $(CFLAGS) $(INCLUDES) $(DEFINES) -march=x86-64 -msse2 -mfpmath=sse -m64 -fPIC -c -MMD -MP -o $@ $<
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

$(TARGET): $(LIBS_DEPS) $(INTERMEDIATE)/Main.o | $(TARGET_DIR)
	@echo [LD] $(notdir $@)
	+$(Q)$(CXX) $(LDFLAGS) -march=x86-64 -msse2 -mfpmath=sse -m64 -pie -Wl,-rpath,\$$ORIGIN -Wl,-rpath,../../../../../../Bin/linux_x86_64 -L../../../../../../Bin/linux_x86_64 $(LIB_DIRS) -o $(TARGET) @$(CONFIG).rsp $(LIBS)
	@echo [STRIP] $(notdir $@)
	$(Q)objcopy --only-keep-debug $(TARGET) $(TARGET).debug
	$(Q)strip --strip-unneeded $(TARGET)
	$(Q)objcopy --add-gnu-debuglink=$(TARGET).debug $(TARGET)

-include $(INTERMEDIATE)/Main.d

clean:
	@echo ==== [Samples.Commands] Cleaning '$(CONFIG)' configuration ====
	$(call RMTREE,$(INTERMEDIATE))
	$(call RM,$(TARGET))
	$(call RM,$(TARGET).debug)
