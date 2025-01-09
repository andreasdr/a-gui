#
BIN = bin
LIB_DIR = lib
OBJ := obj
OBJ_DEBUG = obj-debug

# determine platform
OSSHORT := $(shell sh -c 'uname -o 2>/dev/null')
OS := $(shell sh -c 'uname -s 2>/dev/null')
MACHINE := $(shell sh -c 'uname -m 2>/dev/null')

#
NAME = agui
EXT_NAME = agui-ext
MINITSCRIPT_NAME = minitscript
ifeq ($(OS), Darwin)
	LIB_EXT = .dylib
else ifeq ($(OSSHORT), Msys)
	LIB_EXT = .dll
else
	LIB_EXT = .so
endif
LIB := lib$(NAME)$(LIB_EXT)
EXT_LIB := lib$(NAME)-ext$(LIB_EXT)
MINITSCRIPT_LIB  := libminitscript$(LIB_EXT)
LIBS_LDFLAGS =
MAIN_LDFLAGS =
LDFLAG_LIB := $(NAME)
LDFLAG_EXT_LIB := $(EXT_NAME)
LDFLAG_MINITSCRIPT_LIB := $(MINITSCRIPT_NAME)

SUBDIRS := $(MINITSCRIPT_NAME)

#
CPPVERSION = -std=c++2a
OFLAGS =
EXTRAFLAGS = -DRAPIDJSON_HAS_STDSTRING
INCLUDES = -Isrc -Iext -Iext/vhacd/include/ -Iext/cpp-spline/src -Iext/minitscript/src -I.

#
CXX := $(CXX) -fPIC

# set platform specific flags
ifeq ($(OS), Darwin)
	# MacOSX
	EXTRAFLAGS := $(EXTRAFLAGS) -DHAVE_UNISTD_H
	ifeq ($(MACHINE), x86_64)
		INCLUDES := $(INCLUDES) -Iext/fbx/macosx/include -Iext/glfw3/include -Iext/freetype/include
		LIBS_LDFLAGS := -framework Cocoa -framework IOKit -framework Carbon -framework OpenAL -Lext/glfw3/lib/macosx/x64 -lglfw.3 -lGLEW -lGL -Lext/freetype/lib/macosx/x64 -lfreetype.6
	else ifeq ($(MACHINE), arm64)
		INCLUDES := $(INCLUDES) -Iext/glfw3/include -Iext/freetype/include
		LIBS_LDFLAGS := -framework Cocoa -framework IOKit -framework Carbon -framework OpenAL -Lext/glfw3/lib/macosx/arm64 -lglfw.3 -lGLEW -lGL -Lext/freetype/lib/macosx/arm64 -lfreetype.6
	endif
else ifeq ($(OS), FreeBSD)
	# FreeBSD
	INCLUDES := $(INCLUDES) -I/usr/local/include -I/usr/local/include/freetype2
	LIBS_LDFLAGS := -L/usr/local/lib -ldl -lglfw -lGLEW -lGL -lopenal -lexecinfo
else ifeq ($(OS), NetBSD)
	# NetBSD
	INCLUDES := $(INCLUDES) -I/usr/X11R7/include -I/usr/pkg/include -I/usr/pkg/include/freetype2
	LIBS_LDFLAGS := -L/usr/X11R7/lib -L/usr/pkg/lib -lglfw -lGLEW -lGL -lopenal -lexecinfo -lfreetype
else ifeq ($(OS), OpenBSD)
	# OpenBSD
	INCLUDES := $(INCLUDES) -I/usr/X11R6/include -I/usr/local/include -I/usr/local/include/freetype2
	LIBS_LDFLAGS := -L/usr/X11R6/lib -L/usr/local/lib -lm -lstdc++ -ldl -lglfw -lGLEW -lGL -lopenal -lfreetype
else ifeq ($(OS), Haiku)
	# Haiku
	INCLUDES := $(INCLUDES) -I/boot/system/develop/headers -I/boot/system/develop/headers/freetype2
	LIBS_LDFLAGS := -lnetwork -lglfw -lGLEW -lGL -lopenal -lfreetype
else ifeq ($(OS), Linux)
	# Linux
	INCLUDES := $(INCLUDES) -I/usr/include/freetype2
	LIBS_LDFLAGS := -L/usr/lib64 -ldl -lglfw -lGLEW -lGL -lopenal -lfreetype
else
	# Windows
	INCLUDES := $(INCLUDES) -I/mingw64/include -I/mingw64/include/freetype2
	LIBS_LDFLAGS := -L/mingw64/lib -lws2_32 -ldl -lglfw3 -lGLEW -lGL -lopenal -lfreetype -ldbghelp
	LDFLAG_LIB := $(NAME)$(LIB_EXT)
	LDFLAG_EXT_LIB := $(EXT_NAME)$(LIB_EXT)
	LDFLAG_MINITSCRIPT_LIB := $(MINITSCRIPT_NAME)$(LIB_EXT)
endif

CPPFLAGS := $(INCLUDES)
CFLAGS := -g $(OFLAGS) $(EXTRAFLAGS) -pipe -MMD -MP -DNDEBUG
CXXFLAGS := $(CFLAGS) $(CPPVERSION)
CXXFLAGS_DEBUG := $(CFLAGS_DEBUG) $(CPPVERSION)

LIBS := $(LIB_DIR)/$(LIB) $(LIB_DIR)/$(EXT_LIB)

# subdirs
LIBS:= make-subdirs $(LIBS)

SRC = src
TINYXML = tinyxml
LIBPNG = libpng
VORBIS = vorbis
OGG = ogg
CPPSPLINE = cpp-spline
BC7 = bc7enc_rdo

SRCS_DEBUG =

SRCS = \
	src/agui/application/Application.cpp \
	src/agui/audio/AudioBufferManager.cpp \
	src/agui/audio/Audio.cpp \
	src/agui/audio/AudioStream.cpp \
	src/agui/audio/decoder/AudioDecoderException.cpp \
	src/agui/audio/decoder/VorbisDecoder.cpp \
	src/agui/audio/PacketAudioStream.cpp \
	src/agui/audio/Sound.cpp \
	src/agui/audio/VorbisAudioStream.cpp \
	src/agui/gui/effects/GUIColorEffect.cpp \
	src/agui/gui/effects/GUIEffect.cpp \
	src/agui/gui/effects/GUIPositionEffect.cpp \
	src/agui/gui/elements/GUIButtonController.cpp \
	src/agui/gui/elements/GUIButton.cpp \
	src/agui/gui/elements/GUICheckboxController.cpp \
	src/agui/gui/elements/GUICheckbox.cpp \
	src/agui/gui/elements/GUIContextMenuController.cpp \
	src/agui/gui/elements/GUIContextMenu.cpp \
	src/agui/gui/elements/GUIContextMenuItemController.cpp \
	src/agui/gui/elements/GUIContextMenuItem.cpp \
	src/agui/gui/elements/GUIDropDownController.cpp \
	src/agui/gui/elements/GUIDropDown.cpp \
	src/agui/gui/elements/GUIDropDownOptionController.cpp \
	src/agui/gui/elements/GUIDropDownOption.cpp \
	src/agui/gui/elements/GUIGridController.cpp \
	src/agui/gui/elements/GUIGrid.cpp \
	src/agui/gui/elements/GUIGridItemController.cpp \
	src/agui/gui/elements/GUIGridItem.cpp \
	src/agui/gui/elements/GUIImageButton.cpp \
	src/agui/gui/elements/GUIInputController.cpp \
	src/agui/gui/elements/GUIInput.cpp \
	src/agui/gui/elements/GUIKnobController.cpp \
	src/agui/gui/elements/GUIKnob.cpp \
	src/agui/gui/elements/GUIMenuHeaderController.cpp \
	src/agui/gui/elements/GUIMenuHeader.cpp \
	src/agui/gui/elements/GUIMenuHeaderItemController.cpp \
	src/agui/gui/elements/GUIMenuHeaderItem.cpp \
	src/agui/gui/elements/GUIMenuItemController.cpp \
	src/agui/gui/elements/GUIMenuItem.cpp \
	src/agui/gui/elements/GUIMenuSeparator.cpp \
	src/agui/gui/elements/GUIMoveableController.cpp \
	src/agui/gui/elements/GUIMoveable.cpp \
	src/agui/gui/elements/GUIProgressBarController.cpp \
	src/agui/gui/elements/GUIProgressBar.cpp \
	src/agui/gui/elements/GUIRadioButtonController.cpp \
	src/agui/gui/elements/GUIRadioButton.cpp \
	src/agui/gui/elements/GUIScrollAreaController.cpp \
	src/agui/gui/elements/GUIScrollArea.cpp \
	src/agui/gui/elements/GUISelectBoxController.cpp \
	src/agui/gui/elements/GUISelectBox.cpp \
	src/agui/gui/elements/GUISelectBoxOptionController.cpp \
	src/agui/gui/elements/GUISelectBoxOption.cpp \
	src/agui/gui/elements/GUISelectBoxParentOptionController.cpp \
	src/agui/gui/elements/GUISelectBoxParentOption.cpp \
	src/agui/gui/elements/GUISelectorHController.cpp \
	src/agui/gui/elements/GUISelectorH.cpp \
	src/agui/gui/elements/GUISelectorHOptionController.cpp \
	src/agui/gui/elements/GUISelectorHOption.cpp \
	src/agui/gui/elements/GUISliderHController.cpp \
	src/agui/gui/elements/GUISliderH.cpp \
	src/agui/gui/elements/GUISliderVController.cpp \
	src/agui/gui/elements/GUISliderV.cpp \
	src/agui/gui/elements/GUIStyledInputController.cpp \
	src/agui/gui/elements/GUIStyledInput.cpp \
	src/agui/gui/elements/GUITabContentController.cpp \
	src/agui/gui/elements/GUITabContent.cpp \
	src/agui/gui/elements/GUITabController.cpp \
	src/agui/gui/elements/GUITab.cpp \
	src/agui/gui/elements/GUITabsContent.cpp \
	src/agui/gui/elements/GUITabsController.cpp \
	src/agui/gui/elements/GUITabs.cpp \
	src/agui/gui/elements/GUITabsHeaderController.cpp \
	src/agui/gui/elements/GUITabsHeader.cpp \
	src/agui/gui/fileio/BC7TextureReader.cpp \
	src/agui/gui/fileio/BC7TextureWriter.cpp \
	src/agui/gui/fileio/PNGTextureReader.cpp \
	src/agui/gui/fileio/PNGTextureWriter.cpp \
	src/agui/gui/fileio/TextureReader.cpp \
	src/agui/gui/GUI.cpp \
	src/agui/gui/GUIParser.cpp \
	src/agui/gui/GUIParserException.cpp \
	src/agui/gui/GUIVersion.cpp \
	src/agui/gui/misc/GUIColorTextureCanvas.cpp \
	src/agui/gui/misc/GUIDynamicColorTexture.cpp \
	src/agui/gui/misc/GUITiming.cpp \
	src/agui/gui/nodes/GUIColor.cpp \
	src/agui/gui/nodes/GUIElementController.cpp \
	src/agui/gui/nodes/GUIElementIgnoreEventsController.cpp \
	src/agui/gui/nodes/GUIElementNode.cpp \
	src/agui/gui/nodes/GUIGradientNode.cpp \
	src/agui/gui/nodes/GUIHorizontalScrollbarInternalController.cpp \
	src/agui/gui/nodes/GUIHorizontalScrollbarInternalNode.cpp \
	src/agui/gui/nodes/GUIImageNode.cpp \
	src/agui/gui/nodes/GUIInputInternalController.cpp \
	src/agui/gui/nodes/GUIInputInternalNode.cpp \
	src/agui/gui/nodes/GUILayerNode.cpp \
	src/agui/gui/nodes/GUILayoutNode_Alignment.cpp \
	src/agui/gui/nodes/GUILayoutNode.cpp \
	src/agui/gui/nodes/GUINode_AlignmentHorizontal.cpp \
	src/agui/gui/nodes/GUINode_AlignmentVertical.cpp \
	src/agui/gui/nodes/GUINodeConditions.cpp \
	src/agui/gui/nodes/GUINode.cpp \
	src/agui/gui/nodes/GUINode_Flow.cpp \
	src/agui/gui/nodes/GUINode_RequestedConstraints_RequestedConstraintsType.cpp \
	src/agui/gui/nodes/GUIPanelNode.cpp \
	src/agui/gui/nodes/GUIParentNode.cpp \
	src/agui/gui/nodes/GUIParentNode_Overflow.cpp \
	src/agui/gui/nodes/GUIScreenNode.cpp \
	src/agui/gui/nodes/GUISpaceNode.cpp \
	src/agui/gui/nodes/GUIStyledTextNodeController.cpp \
	src/agui/gui/nodes/GUIStyledTextNode.cpp \
	src/agui/gui/nodes/GUITableCellNode.cpp \
	src/agui/gui/nodes/GUITableNode.cpp \
	src/agui/gui/nodes/GUITableRowNode.cpp \
	src/agui/gui/nodes/GUITextNode.cpp \
	src/agui/gui/nodes/GUITextureBaseNode.cpp \
	src/agui/gui/nodes/GUIVerticalScrollbarInternalController.cpp \
	src/agui/gui/nodes/GUIVerticalScrollbarInternalNode.cpp \
	src/agui/gui/nodes/GUIVideoNode.cpp \
	src/agui/gui/renderer/ApplicationGL3Renderer.cpp \
	src/agui/gui/renderer/GL3Renderer.cpp \
	src/agui/gui/renderer/GUIFont.cpp \
	src/agui/gui/renderer/GUIRenderer.cpp \
	src/agui/gui/renderer/GUIShader.cpp \
	src/agui/gui/renderer/GUIShaderParameters.cpp \
	src/agui/gui/renderer/Renderer.cpp \
	src/agui/gui/scripting/GUIMinitScript.cpp \
	src/agui/gui/textures/GUITexture.cpp \
	src/agui/gui/textures/GUITextureManager.cpp \
	src/agui/gui/vbos/GUIVBOManager.cpp \
	src/agui/os/filesystem/FileSystem.cpp \
	src/agui/os/filesystem/FileSystemException.cpp \
	src/agui/os/filesystem/StandardFileSystem.cpp \
	src/agui/os/threading/Barrier.cpp \
	src/agui/utilities/Console.cpp \
	src/agui/utilities/ExceptionBase.cpp \
	src/agui/utilities/Float.cpp \
	src/agui/utilities/Hex.cpp \
	src/agui/utilities/Integer.cpp \
	src/agui/utilities/Properties.cpp \
	src/agui/utilities/RTTI.cpp \
	src/agui/utilities/StringTokenizer.cpp \
	src/agui/utilities/StringTools.cpp \
	src/agui/utilities/TextureAtlas.cpp \
	src/agui/video/decoder/MPEG1Decoder.cpp \
	src/agui/video/decoder/VideoDecoderException.cpp

EXT_TINYXML_SRCS = \
	ext/tinyxml/tinystr.cpp \
	ext/tinyxml/tinyxml.cpp \
	ext/tinyxml/tinyxmlerror.cpp \
	ext/tinyxml/tinyxmlparser.cpp

EXT_LIBPNG_SRCS = \
	ext/libpng/pngrio.c \
	ext/libpng/pngwio.c \
	ext/libpng/pngmem.c \
	ext/libpng/pngwtran.c \
	ext/libpng/pngtrans.c \
	ext/libpng/pngerror.c \
	ext/libpng/pngpread.c \
	ext/libpng/pngget.c \
	ext/libpng/pngset.c \
	ext/libpng/pngwrite.c \
	ext/libpng/pngwutil.c \
	ext/libpng/pngread.c \
	ext/libpng/pngrutil.c \
	ext/libpng/png.c \
	ext/libpng/pngrtran.c

EXT_VORBIS_SRCS = \
	ext/vorbis/analysis.c \
	ext/vorbis/bitrate.c \
	ext/vorbis/block.c \
	ext/vorbis/codebook.c \
	ext/vorbis/envelope.c \
	ext/vorbis/floor0.c \
	ext/vorbis/floor1.c \
	ext/vorbis/info.c \
	ext/vorbis/lookup.c \
	ext/vorbis/lpc.c \
	ext/vorbis/lsp.c \
	ext/vorbis/mapping0.c \
	ext/vorbis/mdct.c \
	ext/vorbis/psy.c \
	ext/vorbis/registry.c \
	ext/vorbis/res0.c \
	ext/vorbis/sharedbook.c \
	ext/vorbis/smallft.c \
	ext/vorbis/synthesis.c \
	ext/vorbis/vorbisenc.c \
	ext/vorbis/vorbisfile.c \
	ext/vorbis/window.c

EXT_OGG_SRCS = \
	ext/ogg/bitwise.c \
	ext/ogg/framing.c

EXT_CPPSPLINE_SRCS = \
	ext/cpp-spline/src/Bezier.cpp \
	ext/cpp-spline/src/BSpline.cpp \
	ext/cpp-spline/src/CatmullRom.cpp \
	ext/cpp-spline/src/Curve.cpp \
	ext/cpp-spline/src/Vector.cpp

EXT_BC7_SRCS = \
	ext/bc7enc_rdo/bc7decomp.cpp \
	ext/bc7enc_rdo/bc7enc.cpp

MAIN_SRCS = \
	src/agui/tools/cli/agui-main.cpp

MAINS = $(MAIN_SRCS:$(SRC)/%-main.cpp=$(BIN)/%)
OBJS = $(SRCS:$(SRC)/%.cpp=$(OBJ)/%.o)
OBJS_DEBUG = $(SRCS_DEBUG:$(SRC)/%.cpp=$(OBJ_DEBUG)/%.o)

EXT_TINYXML_OBJS = $(EXT_TINYXML_SRCS:ext/$(TINYXML)/%.cpp=$(OBJ)/%.o)
EXT_LIBPNG_OBJS = $(EXT_LIBPNG_SRCS:ext/$(LIBPNG)/%.c=$(OBJ)/%.o)
EXT_VORBIS_OBJS = $(EXT_VORBIS_SRCS:ext/$(VORBIS)/%.c=$(OBJ)/%.o)
EXT_OGG_OBJS = $(EXT_OGG_SRCS:ext/$(OGG)/%.c=$(OBJ)/%.o)
EXT_CPPSPLINE_OBJS = $(EXT_CPPSPLINE_SRCS:ext/$(CPPSPLINE)/%.cpp=$(OBJ)/%.o)
EXT_BC7_OBJS = $(EXT_BC7_SRCS:ext/$(BC7)/%.cpp=$(OBJ)/%.o)

define cpp-command
@mkdir -p $(dir $@);
@echo Compile $<; $(CXX) $(CPPFLAGS) $(CXXFLAGS) -c -o $@ $<
endef

define cpp-command-debug
@mkdir -p $(dir $@);
@echo Compile $<; $(CXX) $(CPPFLAGS) $(CXXFLAGS_DEBUG) -c -o $@ $<
endef

define c-command
@mkdir -p $(dir $@);
@echo Compile $<; $(CXX) -x c $(CPPFLAGS) $(CFLAGS) -c -o $@ $<
endef

all: make-subdirs $(LIB_DIR)/$(LIB) $(LIB_DIR)/$(EXT_LIB)

clean-subdirs:
	@mkdir -p lib
	for dir in $(SUBDIRS); do \
		cd ext/$$dir; \
		$(MAKE) clean; \
		cd ../..; \
    done

make-subdirs:
	@mkdir -p lib
	for dir in $(SUBDIRS); do \
		cd ext/$$dir; \
		$(MAKE); \
		cd ../..; \
		cp ext/$$dir/lib/lib$$dir$(LIB_EXT) lib/; \
    done

$(LIB_DIR)/$(LIB): $(OBJS) $(OBJS_DEBUG)

$(LIB_DIR)/$(EXT_LIB): $(EXT_OBJS) $(EXT_TINYXML_OBJS) $(EXT_LIBPNG_OBJS) $(EXT_VORBIS_OBJS) $(EXT_OGG_OBJS) $(EXT_CPPSPLINE_OBJS) $(EXT_BC7_OBJS)

$(OBJS):$(OBJ)/%.o: $(SRC)/%.cpp | print-opts
	$(cpp-command)

$(OBJS_DEBUG):$(OBJ_DEBUG)/%.o: $(SRC)/%.cpp | print-opts
	$(cpp-command-debug)

$(EXT_TINYXML_OBJS):$(OBJ)/%.o: ext/$(TINYXML)/%.cpp | print-opts
	$(cpp-command)

$(EXT_LIBPNG_OBJS):$(OBJ)/%.o: ext/$(LIBPNG)/%.c | print-opts
	$(c-command)

$(EXT_VORBIS_OBJS):$(OBJ)/%.o: ext/$(VORBIS)/%.c | print-opts
	$(c-command)

$(EXT_OGG_OBJS):$(OBJ)/%.o: ext/$(OGG)/%.c | print-opts
	$(c-command)

$(EXT_CPPSPLINE_OBJS):$(OBJ)/%.o: ext/$(CPPSPLINE)/%.cpp | print-opts
	$(cpp-command)

$(EXT_BC7_OBJS):$(OBJ)/%.o: ext/$(BC7)/%.cpp | print-opts
	$(cpp-command)

$(LIB_DIR)/$(EXT_LIB):
	@echo Creating shared library $@
	@mkdir -p $(dir $@)
	@rm -f $@
ifeq ($(OSSHORT), Msys)
	@scripts/windows-mingw-create-library-rc.sh $@ $@.rc
	@windres $@.rc -o coff -o $@.rc.o
	$(CXX) -shared $(patsubst %$(LIB_EXT),,$^) -o $@ $@.rc.o $(LIBS_LDFLAGS) -Wl,--out-implib,$(LIB_DIR)/$(EXT_LIB).a
	@rm $@.rc
	@rm $@.rc.o
else
	$(CXX) -shared $(patsubst %$(LIB_EXT),,$^) -o $@ $(LIBS_LDFLAGS)
endif
	@echo Done $@

$(LIB_DIR)/$(LIB): $(LIB_DIR)/$(EXT_LIB)
	@echo Creating shared library $@
	@mkdir -p $(dir $@)
	@rm -f $@
ifeq ($(OSSHORT), Msys)
	@scripts/windows-mingw-create-library-rc.sh $@ $@.rc
	@windres $@.rc -o coff -o $@.rc.o
	$(CXX) -shared $(patsubst %$(LIB_EXT),,$^) -o $@ $@.rc.o $(LIBS_LDFLAGS) -Llib -l$(LDFLAG_EXT_LIB) -l$(LDFLAG_MINITSCRIPT_LIB) -Wl,--out-implib,$(LIB_DIR)/$(LIB).a
	@rm $@.rc
	@rm $@.rc.o
else
	$(CXX) -shared $(patsubst %$(LIB_EXT),,$^) -o $@ $(LIBS_LDFLAGS) -Llib -l$(LDFLAG_EXT_LIB) -l$(LDFLAG_MINITSCRIPT_LIB)
endif
	@echo Done $@

ifeq ($(OSSHORT), Msys)
$(MAINS):$(BIN)/%:$(SRC)/%-main.cpp $(LIBS)
	@mkdir -p $(dir $@);
	@scripts/windows-mingw-create-executable-rc.sh "$<" $@.rc
	@windres $@.rc -o coff -o $@.rc.o
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -o $@ $@.rc.o $< -L$(LIB_DIR) -l$(LDFLAG_EXT_LIB) -l$(LDFLAG_MINITSCRIPT_LIB) -l$(LDFLAG_LIB) $(MAIN_LDFLAGS)
	@rm $@.rc
	@rm $@.rc.o
else
$(MAINS):$(BIN)/%:$(SRC)/%-main.cpp $(LIBS)
	@mkdir -p $(dir $@);
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -o $@ $< -L$(LIB_DIR) -l$(LDFLAG_EXT_LIB) -l$(LDFLAG_MINITSCRIPT_LIB) -l$(LDFLAG_LIB) $(MAIN_LDFLAGS)
endif

mains: $(MAINS)

clean: clean-subdirs
	rm -rf obj obj-debug $(LIB_DIR) $(BIN)

print-opts:
	@echo Building with \"$(CXX) $(CPPFLAGS) $(CXXFLAGS)\"
	
.PHONY: all $(LIBS) mains clean print-opts

-include $(OBJS:%.o=%.d)
-include $(OBJS_DEBUG:%.o=%.d)
