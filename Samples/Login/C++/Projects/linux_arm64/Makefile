# GNU Make project for 'Samples.Login'

# Parallel builds can be enabled using the environment variable MAKEFLAGS (eg: MAKEFLAGS="-j 4")
# For parallel execution in Windows, Make 4.0 or better is required

CC = aarch64-linux-gnu-gcc
CXX = aarch64-linux-gnu-g++
AR = aarch64-linux-gnu-ar

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
  TARGET_DIR = ../../../../../../Bin/linux_arm64
  TARGET = ../../../../../../Bin/linux_arm64/Samples.Login
  INTERMEDIATE = build/Debug
  LIB_DIRS = 
  LIBS = -lNoesis -lNoesisApp
  LIBS_DEPS = ../../../../../../Bin/linux_arm64/libNoesisApp.so ../../../../../../Bin/linux_arm64/libNoesis.so
  INCLUDES = -I../../../../../../Include -I../../../../App/ApplicationLauncher/Include -I../../../../App/Display/Include -I../../../../App/DisplayLauncher/Include -I../../../../App/Interactivity/Include -I../../../../App/Launcher/Include -I../../../../App/MediaElement/Include -I../../../../App/Providers/Include -Ibuild/Debug
  DEFINES = -DNS_BUILD -DNS_CONFIG=Debug -DNS_VERSION=3.1.0 -DNS_APP_FRAMEWORK -DNS_LICENSE -DNS_DEBUG -DNS_PROFILE -DNS_MINIMUM_LOG_LEVEL=1
  CFLAGS = $(CFLAGS_COMMON) -D_DEBUG
  CXXFLAGS = $(CXXFLAGS_COMMON) -D_DEBUG
  LDFLAGS = $(LDFLAGS_COMMON) $(CXXFLAGS)
else ifeq ($(CONFIG), Profile)
  TARGET_DIR = ../../../../../../Bin/linux_arm64
  TARGET = ../../../../../../Bin/linux_arm64/Samples.Login
  INTERMEDIATE = build/Profile
  LIB_DIRS = 
  LIBS = -lNoesis -lNoesisApp
  LIBS_DEPS = ../../../../../../Bin/linux_arm64/libNoesisApp.so ../../../../../../Bin/linux_arm64/libNoesis.so
  INCLUDES = -I../../../../../../Include -I../../../../App/ApplicationLauncher/Include -I../../../../App/Display/Include -I../../../../App/DisplayLauncher/Include -I../../../../App/Interactivity/Include -I../../../../App/Launcher/Include -I../../../../App/MediaElement/Include -I../../../../App/Providers/Include -Ibuild/Profile
  DEFINES = -DNS_BUILD -DNS_CONFIG=Profile -DNS_VERSION=3.1.0 -DNS_APP_FRAMEWORK -DNS_LICENSE -DNS_PROFILE -DNS_MINIMUM_LOG_LEVEL=2
  CFLAGS = $(CFLAGS_COMMON) -Ofast -DNDEBUG -ffunction-sections -fdata-sections -fno-asynchronous-unwind-tables -U_FORTIFY_SOURCE
  CXXFLAGS = $(CXXFLAGS_COMMON) -Ofast -DNDEBUG -ffunction-sections -fdata-sections -fno-asynchronous-unwind-tables -U_FORTIFY_SOURCE
  LDFLAGS = $(LDFLAGS_COMMON) $(CXXFLAGS) -fuse-ld=gold -Wl,-O3,--gc-sections,--icf=all
else ifeq ($(CONFIG), Release)
  TARGET_DIR = ../../../../../../Bin/linux_arm64
  TARGET = ../../../../../../Bin/linux_arm64/Samples.Login
  INTERMEDIATE = build/Release
  LIB_DIRS = 
  LIBS = -lNoesis -lNoesisApp
  LIBS_DEPS = ../../../../../../Bin/linux_arm64/libNoesisApp.so ../../../../../../Bin/linux_arm64/libNoesis.so
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
DATA = $(INTERMEDIATE)/App.xaml.bin.h $(INTERMEDIATE)/MainWindow.xaml.bin.h $(INTERMEDIATE)/Resources.xaml.bin.h $(INTERMEDIATE)/Login.mp3.bin.h $(INTERMEDIATE)/Fail.mp3.bin.h $(INTERMEDIATE)/Aero\ Matics\ Regular.ttf.bin.h

.SUFFIXES:
.DELETE_ON_ERROR:
.PHONY: all prebuild data clean

all: prebuild $(TARGET)

prebuild:
	@echo ==== [Samples.Login] Building '$(CONFIG)' configuration ====

data: $(DATA)

$(INTERMEDIATE):
	$(Q)$(call MKDIR,$(INTERMEDIATE))

$(TARGET_DIR):
	$(Q)$(call MKDIR,$(TARGET_DIR))

$(INTERMEDIATE)/%.o: ../../../../Samples/Login/Src/%.cpp $(PCH) | $(INTERMEDIATE) data
	@echo [CXX] [Samples/Login] $(notdir $<)
	$(Q)$(CXX) $(CXXFLAGS) $(PCHFLAGS) $(INCLUDES) $(DEFINES) -fPIC -c -MMD -MF $(basename $@).d.tmp -MP -o $@ $< && $(call MV,$(basename $@).d.tmp,$(basename $@).d)

	$(Q)$(call FIXSLASHES,$(@:.o=.d))

$(INTERMEDIATE)/%.o: ../../../../Samples/Login/Src/%.c | $(INTERMEDIATE) data
	@echo [CC] [Samples/Login] $(notdir $<)
	$(Q)$(CC) $(CFLAGS) $(INCLUDES) $(DEFINES) -fPIC -c -MMD -MF $(basename $@).d.tmp -MP -o $@ $< && $(call MV,$(basename $@).d.tmp,$(basename $@).d)

	$(Q)$(call FIXSLASHES,$(@:.o=.d))

$(INTERMEDIATE)/App.xaml.bin.h: ../../../../Samples/Login/Data/App.xaml | $(INTERMEDIATE)
	@echo [BIN] [Samples/Login] $(notdir $<)
	$(Q)$(BIN2H) "../../../../Samples/Login/Data/App.xaml" > "$(INTERMEDIATE)/App.xaml.bin.h" 

$(INTERMEDIATE)/MainWindow.xaml.bin.h: ../../../../Samples/Login/Data/MainWindow.xaml | $(INTERMEDIATE)
	@echo [BIN] [Samples/Login] $(notdir $<)
	$(Q)$(BIN2H) "../../../../Samples/Login/Data/MainWindow.xaml" > "$(INTERMEDIATE)/MainWindow.xaml.bin.h" 

$(INTERMEDIATE)/Resources.xaml.bin.h: ../../../../Samples/Login/Data/Resources.xaml | $(INTERMEDIATE)
	@echo [BIN] [Samples/Login] $(notdir $<)
	$(Q)$(BIN2H) "../../../../Samples/Login/Data/Resources.xaml" > "$(INTERMEDIATE)/Resources.xaml.bin.h" 

$(INTERMEDIATE)/Login.mp3.bin.h: ../../../../Samples/Login/Data/Login.mp3 | $(INTERMEDIATE)
	@echo [BIN] [Samples/Login] $(notdir $<)
	$(Q)$(BIN2H) "../../../../Samples/Login/Data/Login.mp3" > "$(INTERMEDIATE)/Login.mp3.bin.h" 

$(INTERMEDIATE)/Fail.mp3.bin.h: ../../../../Samples/Login/Data/Fail.mp3 | $(INTERMEDIATE)
	@echo [BIN] [Samples/Login] $(notdir $<)
	$(Q)$(BIN2H) "../../../../Samples/Login/Data/Fail.mp3" > "$(INTERMEDIATE)/Fail.mp3.bin.h" 

$(INTERMEDIATE)/Aero\ Matics\ Regular.ttf.bin.h: ../../../../Samples/Login/Data/Aero\ Matics\ Regular.ttf | $(INTERMEDIATE)
	@echo [BIN] [Samples/Login] $(notdir $<)
	$(Q)$(BIN2H) "../../../../Samples/Login/Data/Aero Matics Regular.ttf" > "$(INTERMEDIATE)/Aero Matics Regular.ttf.bin.h" 

$(TARGET): $(LIBS_DEPS) $(INTERMEDIATE)/ViewModel.o $(INTERMEDIATE)/MainWindow.xaml.o $(INTERMEDIATE)/Main.o $(INTERMEDIATE)/App.xaml.o | $(TARGET_DIR)
	@echo [LD] $(notdir $@)
	+$(Q)$(CXX) $(LDFLAGS) -pie -Wl,-rpath,\$$ORIGIN -Wl,-rpath,../../../../../../Bin/linux_arm64 -L../../../../../../Bin/linux_arm64 $(LIB_DIRS) -o $(TARGET) @$(CONFIG).rsp $(LIBS)
	@echo [STRIP] $(notdir $@)
	$(Q)aarch64-linux-gnu-objcopy --only-keep-debug $(TARGET) $(TARGET).debug
	$(Q)aarch64-linux-gnu-strip --strip-unneeded $(TARGET)
	$(Q)aarch64-linux-gnu-objcopy --add-gnu-debuglink=$(TARGET).debug $(TARGET)

-include $(INTERMEDIATE)/ViewModel.d $(INTERMEDIATE)/MainWindow.xaml.d $(INTERMEDIATE)/Main.d $(INTERMEDIATE)/App.xaml.d

clean:
	@echo ==== [Samples.Login] Cleaning '$(CONFIG)' configuration ====
	$(Q)$(call RMTREE,$(INTERMEDIATE))
	$(Q)$(call RM,$(TARGET))
	$(Q)$(call RM,$(TARGET).debug)
