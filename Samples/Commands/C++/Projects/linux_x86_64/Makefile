# GNU Make project for 'Samples.Commands'

# Parallel builds can be enabled using the environment variable MAKEFLAGS (eg: MAKEFLAGS="-j 4")
# For parallel execution in Windows, Make 4.0 or better is required

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
  TARGET_DIR = ../../../../../../Bin/linux_x86_64
  TARGET = ../../../../../../Bin/linux_x86_64/Samples.Commands
  INTERMEDIATE = build/Debug
  LIB_DIRS = 
  LIBS = -lNoesis -lNoesisApp
  LIBS_DEPS = ../../../../../../Bin/linux_x86_64/libNoesisApp.so ../../../../../../Bin/linux_x86_64/libNoesis.so
  INCLUDES = -I../../../../../../Include -I../../../../App/ApplicationLauncher/Include -I../../../../App/Display/Include -I../../../../App/DisplayLauncher/Include -I../../../../App/Launcher/Include -I../../../../App/Providers/Include -Ibuild/Debug
  DEFINES = -DNS_BUILD -DNS_CONFIG=Debug -DNS_VERSION=3.1.0 -DNS_APP_FRAMEWORK -DNS_LICENSE -DNS_DEBUG -DNS_PROFILE -DNS_MINIMUM_LOG_LEVEL=1
  CFLAGS = $(CFLAGS_COMMON) -D_DEBUG
  CXXFLAGS = $(CXXFLAGS_COMMON) -D_DEBUG
  LDFLAGS = $(LDFLAGS_COMMON) $(CXXFLAGS)
else ifeq ($(CONFIG), Profile)
  TARGET_DIR = ../../../../../../Bin/linux_x86_64
  TARGET = ../../../../../../Bin/linux_x86_64/Samples.Commands
  INTERMEDIATE = build/Profile
  LIB_DIRS = 
  LIBS = -lNoesis -lNoesisApp
  LIBS_DEPS = ../../../../../../Bin/linux_x86_64/libNoesisApp.so ../../../../../../Bin/linux_x86_64/libNoesis.so
  INCLUDES = -I../../../../../../Include -I../../../../App/ApplicationLauncher/Include -I../../../../App/Display/Include -I../../../../App/DisplayLauncher/Include -I../../../../App/Launcher/Include -I../../../../App/Providers/Include -Ibuild/Profile
  DEFINES = -DNS_BUILD -DNS_CONFIG=Profile -DNS_VERSION=3.1.0 -DNS_APP_FRAMEWORK -DNS_LICENSE -DNS_PROFILE -DNS_MINIMUM_LOG_LEVEL=2
  CFLAGS = $(CFLAGS_COMMON) -Ofast -DNDEBUG -ffunction-sections -fdata-sections -fno-asynchronous-unwind-tables -U_FORTIFY_SOURCE
  CXXFLAGS = $(CXXFLAGS_COMMON) -Ofast -DNDEBUG -ffunction-sections -fdata-sections -fno-asynchronous-unwind-tables -U_FORTIFY_SOURCE
  LDFLAGS = $(LDFLAGS_COMMON) $(CXXFLAGS) -fuse-ld=gold -Wl,-O3,--gc-sections,--icf=all
else ifeq ($(CONFIG), Release)
  TARGET_DIR = ../../../../../../Bin/linux_x86_64
  TARGET = ../../../../../../Bin/linux_x86_64/Samples.Commands
  INTERMEDIATE = build/Release
  LIB_DIRS = 
  LIBS = -lNoesis -lNoesisApp
  LIBS_DEPS = ../../../../../../Bin/linux_x86_64/libNoesisApp.so ../../../../../../Bin/linux_x86_64/libNoesis.so
  INCLUDES = -I../../../../../../Include -I../../../../App/ApplicationLauncher/Include -I../../../../App/Display/Include -I../../../../App/DisplayLauncher/Include -I../../../../App/Launcher/Include -I../../../../App/Providers/Include -Ibuild/Release
  DEFINES = -DNS_BUILD -DNS_CONFIG=Release -DNS_VERSION=3.1.0 -DNS_APP_FRAMEWORK -DNS_LICENSE
  CFLAGS = $(CFLAGS_COMMON) -Ofast -flto=jobserver -DNDEBUG -ffunction-sections -fdata-sections -fno-asynchronous-unwind-tables -U_FORTIFY_SOURCE -fomit-frame-pointer
  CXXFLAGS = $(CXXFLAGS_COMMON) -Ofast -flto=jobserver -DNDEBUG -ffunction-sections -fdata-sections -fno-asynchronous-unwind-tables -U_FORTIFY_SOURCE -fomit-frame-pointer
  LDFLAGS = $(LDFLAGS_COMMON) $(CXXFLAGS) -fuse-ld=gold -Wl,-O3,--gc-sections,--icf=all
else
  $(error Invalid configuration '$(CONFIG)')
endif

PCH =
PCHFLAGS =
DATA = $(INTERMEDIATE)/MainWindow.xaml.bin.h $(INTERMEDIATE)/App.xaml.bin.h $(INTERMEDIATE)/Aero\ Matics\ Regular.ttf.bin.h

.SUFFIXES:
.DELETE_ON_ERROR:
.PHONY: all prebuild data clean

all: prebuild $(TARGET)

prebuild:
	@echo ==== [Samples.Commands] Building '$(CONFIG)' configuration ====

data: $(DATA)

$(INTERMEDIATE):
	$(Q)$(call MKDIR,$(INTERMEDIATE))

$(TARGET_DIR):
	$(Q)$(call MKDIR,$(TARGET_DIR))

$(INTERMEDIATE)/%.o: ../../../../Samples/Commands/Src/%.cpp $(PCH) | $(INTERMEDIATE) data
	@echo [CXX] [Samples/Commands] $(notdir $<)
	$(Q)$(CXX) $(CXXFLAGS) $(PCHFLAGS) $(INCLUDES) $(DEFINES) -march=x86-64 -msse2 -mfpmath=sse -m64 -fPIC -c -MMD -MF $(basename $@).d.tmp -MP -o $@ $< && $(call MV,$(basename $@).d.tmp,$(basename $@).d)

	$(Q)$(call FIXSLASHES,$(@:.o=.d))

$(INTERMEDIATE)/%.o: ../../../../Samples/Commands/Src/%.c | $(INTERMEDIATE) data
	@echo [CC] [Samples/Commands] $(notdir $<)
	$(Q)$(CC) $(CFLAGS) $(INCLUDES) $(DEFINES) -march=x86-64 -msse2 -mfpmath=sse -m64 -fPIC -c -MMD -MF $(basename $@).d.tmp -MP -o $@ $< && $(call MV,$(basename $@).d.tmp,$(basename $@).d)

	$(Q)$(call FIXSLASHES,$(@:.o=.d))

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
	$(Q)$(call RMTREE,$(INTERMEDIATE))
	$(Q)$(call RM,$(TARGET))
	$(Q)$(call RM,$(TARGET).debug)
