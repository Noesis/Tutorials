# GNU Make project for 'Samples.BrushShaders'

# Parallel builds can be enabled using the environment variable MAKEFLAGS (eg: MAKEFLAGS="-j 4")
# For parallel execution in Windows, Make 4.0 or better is required

CC = aarch64-linux-gnu-gcc
CXX = aarch64-linux-gnu-g++
AR = aarch64-linux-gnu-ar

CFLAGS_COMMON = -g -pipe -Wall -Werror -Wfatal-errors -Wtype-limits -Wno-maybe-uninitialized -fvisibility=hidden -fmerge-all-constants
CXXFLAGS_COMMON = $(CFLAGS_COMMON) -std=c++11 -fno-exceptions -frtti -fvisibility-inlines-hidden -fno-threadsafe-statics
LDFLAGS_COMMON = -Wextra
SHADERFLAGS_COMMON = -I../../../Packages/Render -I../../../Tools/ShaderCompiler/Include -lang=glsl

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
  BIN2H = ../../../Tools/Bin2h/bin2h.py
  SHADERC = ../../../Tools/ShaderCompiler/Bin/Linux/ShaderCompiler
  CP = cp "$(1)" "$(2)"
  MV = mv "$(1)" "$(2)"
  RM = rm -f "$(1)"
  RMTREE = rm -rf "$(1)"
  FIXSLASHES = 
else
  DEVNUL = NUL
  WHICH = where
  MKDIR = mkdir "$(subst /,\,$(1))" 2> nul || exit 0
  BIN2H = ..\..\..\Tools\Bin2h\bin2h.exe
  SHADERC = ..\..\..\Tools\ShaderCompiler\Bin\Windows\ShaderCompiler.exe
  CP = copy /Y "$(subst /,\,$(1))" "$(subst /,\,$(2))" > nul
  MV = move /Y "$(subst /,\,$(1))" "$(subst /,\,$(2))" > nul
  RM = del /Q "$(subst /,\,$(1))" 2> nul || exit 0
  RMTREE = rmdir /S /Q "$(subst /,\,$(1))" 2> nul || exit 0
  SED = ..\..\..\Tools\sed\sed.exe
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
  TARGET_DIR = ../../../../Bin/linux_arm64
  TARGET = ../../../../Bin/linux_arm64/Samples.BrushShaders
  INTERMEDIATE = build/Debug
  LIB_DIRS = 
  LIBS = -lNoesis -lNoesisApp
  LIBS_DEPS = ../../../../Bin/linux_arm64/libNoesis.so ../../../../Bin/linux_arm64/libNoesisApp.so
  INCLUDES = -I../../../../Include -I../../../Packages/App/ApplicationLauncher/Include -I../../../Packages/App/Display/Include -I../../../Packages/App/DisplayLauncher/Include -I../../../Packages/App/Launcher/Include -I../../../Packages/App/Providers/Include -I../../../Packages/Render/RenderContext/Include -Ibuild/Debug
  DEFINES = -DNS_BUILD -DNS_CONFIG=Debug -DNS_VERSION=0.0.0 -DNS_APP_FRAMEWORK -DNS_LICENSE -DNS_DEBUG -DNS_PROFILE -DNS_MINIMUM_LOG_LEVEL=1
  CFLAGS = $(CFLAGS_COMMON) -D_DEBUG
  CXXFLAGS = $(CXXFLAGS_COMMON) -D_DEBUG
  LDFLAGS = $(LDFLAGS_COMMON) $(CXXFLAGS)
  SHADERFLAGS = $(SHADERFLAGS_COMMON) -Od -g
else ifeq ($(CONFIG), Profile)
  TARGET_DIR = ../../../../Bin/linux_arm64
  TARGET = ../../../../Bin/linux_arm64/Samples.BrushShaders
  INTERMEDIATE = build/Profile
  LIB_DIRS = 
  LIBS = -lNoesis -lNoesisApp
  LIBS_DEPS = ../../../../Bin/linux_arm64/libNoesis.so ../../../../Bin/linux_arm64/libNoesisApp.so
  INCLUDES = -I../../../../Include -I../../../Packages/App/ApplicationLauncher/Include -I../../../Packages/App/Display/Include -I../../../Packages/App/DisplayLauncher/Include -I../../../Packages/App/Launcher/Include -I../../../Packages/App/Providers/Include -I../../../Packages/Render/RenderContext/Include -Ibuild/Profile
  DEFINES = -DNS_BUILD -DNS_CONFIG=Profile -DNS_VERSION=0.0.0 -DNS_APP_FRAMEWORK -DNS_LICENSE -DNS_PROFILE -DNS_MINIMUM_LOG_LEVEL=2
  CFLAGS = $(CFLAGS_COMMON) -Ofast -DNDEBUG -ffunction-sections -fdata-sections -fno-asynchronous-unwind-tables -U_FORTIFY_SOURCE
  CXXFLAGS = $(CXXFLAGS_COMMON) -Ofast -DNDEBUG -ffunction-sections -fdata-sections -fno-asynchronous-unwind-tables -U_FORTIFY_SOURCE
  LDFLAGS = $(LDFLAGS_COMMON) $(CXXFLAGS) -fuse-ld=gold -Wl,-O3,--gc-sections,--icf=all
  SHADERFLAGS = $(SHADERFLAGS_COMMON)
else ifeq ($(CONFIG), Release)
  TARGET_DIR = ../../../../Bin/linux_arm64
  TARGET = ../../../../Bin/linux_arm64/Samples.BrushShaders
  INTERMEDIATE = build/Release
  LIB_DIRS = 
  LIBS = -lNoesis -lNoesisApp
  LIBS_DEPS = ../../../../Bin/linux_arm64/libNoesis.so ../../../../Bin/linux_arm64/libNoesisApp.so
  INCLUDES = -I../../../../Include -I../../../Packages/App/ApplicationLauncher/Include -I../../../Packages/App/Display/Include -I../../../Packages/App/DisplayLauncher/Include -I../../../Packages/App/Launcher/Include -I../../../Packages/App/Providers/Include -I../../../Packages/Render/RenderContext/Include -Ibuild/Release
  DEFINES = -DNS_BUILD -DNS_CONFIG=Release -DNS_VERSION=0.0.0 -DNS_APP_FRAMEWORK -DNS_LICENSE
  CFLAGS = $(CFLAGS_COMMON) -Ofast -flto=jobserver -DNDEBUG -ffunction-sections -fdata-sections -fno-asynchronous-unwind-tables -U_FORTIFY_SOURCE -fomit-frame-pointer
  CXXFLAGS = $(CXXFLAGS_COMMON) -Ofast -flto=jobserver -DNDEBUG -ffunction-sections -fdata-sections -fno-asynchronous-unwind-tables -U_FORTIFY_SOURCE -fomit-frame-pointer
  LDFLAGS = $(LDFLAGS_COMMON) $(CXXFLAGS) -fuse-ld=gold -Wl,-O3,--gc-sections,--icf=all
  SHADERFLAGS = $(SHADERFLAGS_COMMON)
else
  $(error Invalid configuration '$(CONFIG)')
endif

PCH =
PCHFLAGS =
DATA = $(INTERMEDIATE)/App.xaml.bin.h $(INTERMEDIATE)/MainWindow.xaml.bin.h $(INTERMEDIATE)/Exo-SemiBold.ttf.bin.h $(INTERMEDIATE)/fill-blue.png.bin.h $(INTERMEDIATE)/fill-gold.png.bin.h $(INTERMEDIATE)/Noise.bin.h

.SUFFIXES:
.DELETE_ON_ERROR:
.PHONY: all prebuild data clean

all: prebuild $(TARGET)

prebuild:
	@echo ==== [Samples.BrushShaders] Building '$(CONFIG)' configuration ====

data: $(DATA)

$(INTERMEDIATE):
	$(Q)$(call MKDIR,$(INTERMEDIATE))

$(TARGET_DIR):
	$(Q)$(call MKDIR,$(TARGET_DIR))

$(INTERMEDIATE)/%.o: ../../../Packages/Samples/BrushShaders/Src/%.cpp $(PCH) | $(INTERMEDIATE) data
	@echo [CXX] [Samples/BrushShaders] $(notdir $<)
	$(Q)$(CXX) $(CXXFLAGS) $(PCHFLAGS) $(INCLUDES) $(DEFINES) -fPIC -c -MMD -MF $(basename $@).d.tmp -MP -o $@ $< && $(call MV,$(basename $@).d.tmp,$(basename $@).d)

	$(Q)$(call FIXSLASHES,$(@:.o=.d))

$(INTERMEDIATE)/%.o: ../../../Packages/Samples/BrushShaders/Src/%.c | $(INTERMEDIATE) data
	@echo [CC] [Samples/BrushShaders] $(notdir $<)
	$(Q)$(CC) $(CFLAGS) $(INCLUDES) $(DEFINES) -fPIC -c -MMD -MF $(basename $@).d.tmp -MP -o $@ $< && $(call MV,$(basename $@).d.tmp,$(basename $@).d)

	$(Q)$(call FIXSLASHES,$(@:.o=.d))

$(INTERMEDIATE)/App.xaml.bin.h: ../../../Packages/Samples/BrushShaders/Data/App.xaml | $(INTERMEDIATE)
	@echo [BIN] [Samples/BrushShaders] $(notdir $<)
	$(Q)$(BIN2H) "../../../Packages/Samples/BrushShaders/Data/App.xaml" > "$(INTERMEDIATE)/App.xaml.bin.h"

$(INTERMEDIATE)/MainWindow.xaml.bin.h: ../../../Packages/Samples/BrushShaders/Data/MainWindow.xaml | $(INTERMEDIATE)
	@echo [BIN] [Samples/BrushShaders] $(notdir $<)
	$(Q)$(BIN2H) "../../../Packages/Samples/BrushShaders/Data/MainWindow.xaml" > "$(INTERMEDIATE)/MainWindow.xaml.bin.h"

$(INTERMEDIATE)/Exo-SemiBold.ttf.bin.h: ../../../Packages/Samples/BrushShaders/Data/Exo-SemiBold.ttf | $(INTERMEDIATE)
	@echo [BIN] [Samples/BrushShaders] $(notdir $<)
	$(Q)$(BIN2H) "../../../Packages/Samples/BrushShaders/Data/Exo-SemiBold.ttf" > "$(INTERMEDIATE)/Exo-SemiBold.ttf.bin.h"

$(INTERMEDIATE)/fill-blue.png.bin.h: ../../../Packages/Samples/BrushShaders/Data/fill-blue.png | $(INTERMEDIATE)
	@echo [BIN] [Samples/BrushShaders] $(notdir $<)
	$(Q)$(BIN2H) "../../../Packages/Samples/BrushShaders/Data/fill-blue.png" > "$(INTERMEDIATE)/fill-blue.png.bin.h"

$(INTERMEDIATE)/fill-gold.png.bin.h: ../../../Packages/Samples/BrushShaders/Data/fill-gold.png | $(INTERMEDIATE)
	@echo [BIN] [Samples/BrushShaders] $(notdir $<)
	$(Q)$(BIN2H) "../../../Packages/Samples/BrushShaders/Data/fill-gold.png" > "$(INTERMEDIATE)/fill-gold.png.bin.h"

$(INTERMEDIATE)/Noise.bin.h: ../../../Packages/Samples/BrushShaders/Src/Noise.noesisbrush | $(INTERMEDIATE)
	@echo [SHADER] [Samples/BrushShaders] $(notdir $<)
	$(Q)$(SHADERC) $(SHADERFLAGS) "../../../Packages/Samples/BrushShaders/Src/Noise.noesisbrush" -o "$(INTERMEDIATE)/Noise.bin.h"

$(TARGET): $(LIBS_DEPS) $(INTERMEDIATE)/Main.o | $(TARGET_DIR)
	@echo [LD] $(notdir $@)
	+$(Q)$(CXX) $(LDFLAGS) -pie -Wl,-rpath,\$$ORIGIN -Wl,-rpath,../../../../Bin/linux_arm64 -L../../../../Bin/linux_arm64 $(LIB_DIRS) -o $(TARGET) @$(CONFIG).rsp $(LIBS)
	@echo [STRIP] $(notdir $@)
	$(Q)aarch64-linux-gnu-objcopy --only-keep-debug $(TARGET) $(TARGET).debug
	$(Q)aarch64-linux-gnu-strip --strip-unneeded $(TARGET)
	$(Q)aarch64-linux-gnu-objcopy --add-gnu-debuglink=$(TARGET).debug $(TARGET)

-include $(INTERMEDIATE)/Main.d

clean:
	@echo ==== [Samples.BrushShaders] Cleaning '$(CONFIG)' configuration ====
	$(Q)$(call RMTREE,$(INTERMEDIATE))
	$(Q)$(call RM,$(TARGET))
	$(Q)$(call RM,$(TARGET).debug)
