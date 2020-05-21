# GNU Make project for 'Samples.Inventory'

# Parallel builds can be enabled using the environment variable MAKEFLAGS (eg: MAKEFLAGS="-j 4")
# For parallel execution in Windows, Make 4.0 or better is required

include ../../../../../Config/Common.makeprops
include ../../../../../Config/Profile/Profile.makeprops
include ../../../../../Config/Release/Release.makeprops
include ../../../../../Config/Debug/Debug.makeprops

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

ifeq ($(CONFIG), Profile)
  TARGET_DIR = ../../../../../../Bin/linux_x86_64
  TARGET = ../../../../../../Bin/linux_x86_64/Samples.Inventory
  INTERMEDIATE = build/Profile
  LIB_DIRS = 
  LIBS = -lNoesisApp -lNoesis
  LIBS_DEPS = ../../../../../../Bin/linux_x86_64/libNoesisApp.so ../../../../../../Bin/linux_x86_64/libNoesis.so
  INCLUDES = -I../../../../../../Include -I../../../../App/ApplicationLauncher/Include -I../../../../App/Display/Include -I../../../../App/DisplayLauncher/Include -I../../../../App/Interactivity/Include -I../../../../App/Launcher/Include -I../../../../App/Providers/Include -Ibuild/Profile
  DEFINES = -DNS_BUILD -DNS_CONFIG=Profile -DNS_VERSION=3.0.0 -DNS_APP_FRAMEWORK -DNS_LICENSE -DNS_PROFILE -DNS_MINIMUM_LOG_LEVEL=2
  CFLAGS = $(CFLAGS_PROFILE)
  CXXFLAGS = $(CXXFLAGS_PROFILE)
  LDFLAGS = $(LDFLAGS_PROFILE)
else ifeq ($(CONFIG), Release)
  TARGET_DIR = ../../../../../../Bin/linux_x86_64
  TARGET = ../../../../../../Bin/linux_x86_64/Samples.Inventory
  INTERMEDIATE = build/Release
  LIB_DIRS = 
  LIBS = -lNoesisApp -lNoesis
  LIBS_DEPS = ../../../../../../Bin/linux_x86_64/libNoesisApp.so ../../../../../../Bin/linux_x86_64/libNoesis.so
  INCLUDES = -I../../../../../../Include -I../../../../App/ApplicationLauncher/Include -I../../../../App/Display/Include -I../../../../App/DisplayLauncher/Include -I../../../../App/Interactivity/Include -I../../../../App/Launcher/Include -I../../../../App/Providers/Include -Ibuild/Release
  DEFINES = -DNS_BUILD -DNS_CONFIG=Release -DNS_VERSION=3.0.0 -DNS_APP_FRAMEWORK -DNS_LICENSE
  CFLAGS = $(CFLAGS_RELEASE)
  CXXFLAGS = $(CXXFLAGS_RELEASE)
  LDFLAGS = $(LDFLAGS_RELEASE)
else ifeq ($(CONFIG), Debug)
  TARGET_DIR = ../../../../../../Bin/linux_x86_64
  TARGET = ../../../../../../Bin/linux_x86_64/Samples.Inventory
  INTERMEDIATE = build/Debug
  LIB_DIRS = 
  LIBS = -lNoesisApp -lNoesis
  LIBS_DEPS = ../../../../../../Bin/linux_x86_64/libNoesisApp.so ../../../../../../Bin/linux_x86_64/libNoesis.so
  INCLUDES = -I../../../../../../Include -I../../../../App/ApplicationLauncher/Include -I../../../../App/Display/Include -I../../../../App/DisplayLauncher/Include -I../../../../App/Interactivity/Include -I../../../../App/Launcher/Include -I../../../../App/Providers/Include -Ibuild/Debug
  DEFINES = -DNS_BUILD -DNS_CONFIG=Debug -DNS_VERSION=3.0.0 -DNS_APP_FRAMEWORK -DNS_LICENSE -DNS_DEBUG -DNS_PROFILE -DNS_MINIMUM_LOG_LEVEL=1
  CFLAGS = $(CFLAGS_DEBUG)
  CXXFLAGS = $(CXXFLAGS_DEBUG)
  LDFLAGS = $(LDFLAGS_DEBUG)
else
  $(error Invalid configuration '$(CONFIG)')
endif

PCH =
PCHFLAGS =
DATA = $(INTERMEDIATE)/App.xaml.bin.h $(INTERMEDIATE)/MainWindow.xaml.bin.h $(INTERMEDIATE)/Resources.xaml.bin.h $(INTERMEDIATE)/AnimatedNumber.xaml.bin.h $(INTERMEDIATE)/Background.jpg.bin.h $(INTERMEDIATE)/Character.png.bin.h $(INTERMEDIATE)/InventoryAtlas.png.bin.h $(INTERMEDIATE)/Gidole-Regular.ttf.bin.h $(INTERMEDIATE)/Sequel_Demo.ttf.bin.h

.SUFFIXES:
.DELETE_ON_ERROR:
.PHONY: all prebuild data clean

all: prebuild $(TARGET)

prebuild:
	@echo ==== [Samples.Inventory] Building '$(CONFIG)' configuration ====

data: $(DATA)

$(INTERMEDIATE):
	$(Q)$(call MKDIR,$(INTERMEDIATE))

$(TARGET_DIR):
	$(Q)$(call MKDIR,$(TARGET_DIR))

$(INTERMEDIATE)/%.o: ../../../../Samples/Inventory/Src/%.cpp $(PCH) | $(INTERMEDIATE) data
	@echo [CXX] [Samples/Inventory] $(notdir $<)
	$(Q)$(CXX) $(CXXFLAGS) $(PCHFLAGS) $(INCLUDES) $(DEFINES) -march=x86-64 -msse2 -mfpmath=sse -m64 -fPIC -c -MMD -MF $(basename $@).d.tmp -MP -o $@ $< && $(call MV,$(basename $@).d.tmp,$(basename $@).d)

	$(Q)$(call FIXSLASHES,$(@:.o=.d))

$(INTERMEDIATE)/%.o: ../../../../Samples/Inventory/Src/%.c | $(INTERMEDIATE) data
	@echo [CC] [Samples/Inventory] $(notdir $<)
	$(Q)$(CC) $(CFLAGS) $(INCLUDES) $(DEFINES) -march=x86-64 -msse2 -mfpmath=sse -m64 -fPIC -c -MMD -MF $(basename $@).d.tmp -MP -o $@ $< && $(call MV,$(basename $@).d.tmp,$(basename $@).d)

	$(Q)$(call FIXSLASHES,$(@:.o=.d))

$(INTERMEDIATE)/App.xaml.bin.h: ../../../../Samples/Inventory/Data/App.xaml | $(INTERMEDIATE)
	@echo [BIN] [Samples/Inventory] $(notdir $<)
	$(Q)$(BIN2H) "../../../../Samples/Inventory/Data/App.xaml" > "$(INTERMEDIATE)/App.xaml.bin.h" 

$(INTERMEDIATE)/MainWindow.xaml.bin.h: ../../../../Samples/Inventory/Data/MainWindow.xaml | $(INTERMEDIATE)
	@echo [BIN] [Samples/Inventory] $(notdir $<)
	$(Q)$(BIN2H) "../../../../Samples/Inventory/Data/MainWindow.xaml" > "$(INTERMEDIATE)/MainWindow.xaml.bin.h" 

$(INTERMEDIATE)/Resources.xaml.bin.h: ../../../../Samples/Inventory/Data/Resources.xaml | $(INTERMEDIATE)
	@echo [BIN] [Samples/Inventory] $(notdir $<)
	$(Q)$(BIN2H) "../../../../Samples/Inventory/Data/Resources.xaml" > "$(INTERMEDIATE)/Resources.xaml.bin.h" 

$(INTERMEDIATE)/AnimatedNumber.xaml.bin.h: ../../../../Samples/Inventory/Data/AnimatedNumber.xaml | $(INTERMEDIATE)
	@echo [BIN] [Samples/Inventory] $(notdir $<)
	$(Q)$(BIN2H) "../../../../Samples/Inventory/Data/AnimatedNumber.xaml" > "$(INTERMEDIATE)/AnimatedNumber.xaml.bin.h" 

$(INTERMEDIATE)/Background.jpg.bin.h: ../../../../Samples/Inventory/Data/Images/Background.jpg | $(INTERMEDIATE)
	@echo [BIN] [Samples/Inventory] $(notdir $<)
	$(Q)$(BIN2H) "../../../../Samples/Inventory/Data/Images/Background.jpg" > "$(INTERMEDIATE)/Background.jpg.bin.h" 

$(INTERMEDIATE)/Character.png.bin.h: ../../../../Samples/Inventory/Data/Images/Character.png | $(INTERMEDIATE)
	@echo [BIN] [Samples/Inventory] $(notdir $<)
	$(Q)$(BIN2H) "../../../../Samples/Inventory/Data/Images/Character.png" > "$(INTERMEDIATE)/Character.png.bin.h" 

$(INTERMEDIATE)/InventoryAtlas.png.bin.h: ../../../../Samples/Inventory/Data/Images/InventoryAtlas.png | $(INTERMEDIATE)
	@echo [BIN] [Samples/Inventory] $(notdir $<)
	$(Q)$(BIN2H) "../../../../Samples/Inventory/Data/Images/InventoryAtlas.png" > "$(INTERMEDIATE)/InventoryAtlas.png.bin.h" 

$(INTERMEDIATE)/Gidole-Regular.ttf.bin.h: ../../../../Samples/Inventory/Data/Fonts/Gidole-Regular.ttf | $(INTERMEDIATE)
	@echo [BIN] [Samples/Inventory] $(notdir $<)
	$(Q)$(BIN2H) "../../../../Samples/Inventory/Data/Fonts/Gidole-Regular.ttf" > "$(INTERMEDIATE)/Gidole-Regular.ttf.bin.h" 

$(INTERMEDIATE)/Sequel_Demo.ttf.bin.h: ../../../../Samples/Inventory/Data/Fonts/Sequel_Demo.ttf | $(INTERMEDIATE)
	@echo [BIN] [Samples/Inventory] $(notdir $<)
	$(Q)$(BIN2H) "../../../../Samples/Inventory/Data/Fonts/Sequel_Demo.ttf" > "$(INTERMEDIATE)/Sequel_Demo.ttf.bin.h" 

$(TARGET): $(LIBS_DEPS) $(INTERMEDIATE)/ViewModel.o $(INTERMEDIATE)/DragItemBehavior.o $(INTERMEDIATE)/MainWindow.xaml.o $(INTERMEDIATE)/DragAdornerBehavior.o $(INTERMEDIATE)/AnimatedNumber.xaml.o $(INTERMEDIATE)/DropItemBehavior.o $(INTERMEDIATE)/Main.o $(INTERMEDIATE)/App.xaml.o | $(TARGET_DIR)
	@echo [LD] $(notdir $@)
	+$(Q)$(CXX) $(LDFLAGS) -march=x86-64 -msse2 -mfpmath=sse -m64 -pie -Wl,-rpath,\$$ORIGIN -Wl,-rpath,../../../../../../Bin/linux_x86_64 -L../../../../../../Bin/linux_x86_64 $(LIB_DIRS) -o $(TARGET) @$(CONFIG).rsp $(LIBS)
	@echo [STRIP] $(notdir $@)
	$(Q)objcopy --only-keep-debug $(TARGET) $(TARGET).debug
	$(Q)strip --strip-unneeded $(TARGET)
	$(Q)objcopy --add-gnu-debuglink=$(TARGET).debug $(TARGET)

-include $(INTERMEDIATE)/ViewModel.d $(INTERMEDIATE)/DragItemBehavior.d $(INTERMEDIATE)/MainWindow.xaml.d $(INTERMEDIATE)/DragAdornerBehavior.d $(INTERMEDIATE)/AnimatedNumber.xaml.d $(INTERMEDIATE)/DropItemBehavior.d $(INTERMEDIATE)/Main.d $(INTERMEDIATE)/App.xaml.d

clean:
	@echo ==== [Samples.Inventory] Cleaning '$(CONFIG)' configuration ====
	$(Q)$(call RMTREE,$(INTERMEDIATE))
	$(Q)$(call RM,$(TARGET))
	$(Q)$(call RM,$(TARGET).debug)
