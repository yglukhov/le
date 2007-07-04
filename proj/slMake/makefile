################################################################################
# slMake
################################################################################

# Function targetIn <target_list>
# returns empty string if target is not in <target_list>
targetIn = $(filter $(1),$(MAKECMDGOALS))

SHELL_CMD_PRINT = echo
SHELL_CMD_LOG = echo slMake:
SHELL_CMD_WARNING = echo slMake [warning]:

ifdef _WINDOWS
_SL_END_SHELL_CMD = ;
else
_SL_END_SHELL_CMD = ; # space after semicolon
endif

################################################################################
# Some targets are performed not in the makefile dir, so do not do
# includes or anything that requires current dir to be makefile dir
ifeq (,$(call targetIn,_SL_COLLECT_SOURCES _SL_NORMALIZE_PATH))

INCLUDE_LIST = $(strip $(wildcard *.target) $(wildcard *.targets) $(wildcard *.config) $(wildcard *.configs))

ifeq ($(INCLUDE_LIST),)
$(error No target descriptions. MAKECMDGOALS: $(MAKECMDGOALS))
endif

ifndef CONFIGURATION
ifdef configuration
CONFIGURATION = $(configuration)
else
CONFIGURATION = release
endif
endif

_SL_TMP_CONFIG_FILE = .config.slMake.tmp

ifndef MAKE_FILE
	# This is the root call of make, so start searching in SRCROOT
	export MAKE_FILE = $(CURDIR)/makefile
endif

ifdef _SL_BEGIN_CLEAN

ifeq ($(CONFIGURATION),all)
override CONFIGURATION = release debug
endif

_SHELL_PERFORM_CLEAN_COMMAND = \
$(MAKE) -n config.$@.$(iConf) CONFIGURATION=$(iConf) '_SL_PRODUCT_NAME=$@' > "$(_SL_TMP_CONFIG_FILE)" $(_SL_END_SHELL_CMD)	\
$(MAKE) _SL_ACTUAL_CLEAN $(_SL_END_SHELL_CMD)


PERFORM_BUILD = @$(foreach iConf,$(CONFIGURATION),$(_SHELL_PERFORM_CLEAN_COMMAND))

else

PERFORM_BUILD = \
@$(SHELL_CMD_LOG) Building target: $@, configuration: $(CONFIGURATION) $(_SL_END_SHELL_CMD) \
$(MAKE) -n config.$@.$(CONFIGURATION) '_SL_PRODUCT_NAME=$@' > "$(_SL_TMP_CONFIG_FILE)" $(_SL_END_SHELL_CMD) \
$(SHELL_CMD_LOG) "Collecting sources" $(_SL_END_SHELL_CMD) \
$(MAKE) _SL_PREBUILD_SOURCES $(_SL_END_SHELL_CMD) \
$(MAKE) _SL_COLLECT_DEPS_AND_OBJS $(_SL_END_SHELL_CMD) \
$(MAKE) _SL_BUILD_DEPENDENCIES $(_SL_END_SHELL_CMD) \
$(MAKE) _SL_ACTUAL_BUILD $(_SL_END_SHELL_CMD)

endif

_DEFAULT_TARGET :
	@$(MAKE) $(all)

################################################################################
# Generate configuration
################################################################################
config.slMake.release :
	# $@
	SL_DEBUGGING_SYMBOLS = NO

config.slMake.debug :
	# $@
	SL_DEBUGGING_SYMBOLS = YES

config.slMake._basicConfiguration :
	# $@
	# Locations
	SL_BUILD_DIR = build
	SL_TEMP_DIR = $$(SL_BUILD_DIR)/intermediate
	SL_CONFIGURATION = $(CONFIGURATION)
	SL_CONFIGURATION_BUILD_DIR = $$(SL_BUILD_DIR)/$$(SL_CONFIGURATION)
	SL_CONFIGURATION_TEMP_DIR = $$(SL_TEMP_DIR)/$$(SL_CONFIGURATION)/$$(SL_TARGET_NAME)
	SL_DEPENDENCIES_DIR = $$(SL_CONFIGURATION_TEMP_DIR)/Dependencies
	SL_DEPENDENCIES_LIST_FILE = $$(SL_DEPENDENCIES_DIR)/objectDeps.txt
	SL_CONFIG_USER_FILE = $$(SL_CONFIGURATION_TEMP_DIR)/config.txt
	SL_OBJECTS_DIR = $$(SL_CONFIGURATION_TEMP_DIR)/Objects
	SL_SRC_ROOTS = $$(SL_SRC_ROOT)
	SL_COPY_HEADERS_DEPENDENCY = $$(SL_DEPENDENCIES_DIR)/headerDeps.txt

	SL_PRODUCT_DIR = $$(SL_CONFIGURATION_BUILD_DIR)
	SL_TARGET_NAME = $(_SL_PRODUCT_NAME)
	SL_PRODUCT_NAME = $(_SL_PRODUCT_NAME)
	SL_EXECUTABLE_NAME = $$(SL_PRODUCT_NAME)
	SL_EXECUTABLE_PREFIX =
	SL_EXECUTABLE_FULL_NAME = $$(SL_EXECUTABLE_PREFIX)$$(SL_EXECUTABLE_NAME).$$(SL_EXECUTABLE_EXTENSION)

	# File rules
	SOURCES_EXTENSIONS = c cp cpp
	SL_HEADER_TYPES = PUBLIC PRIVATE
	PUBLIC_HEADERS_EXTENSIONS = h htt
	PRIVATE_HEADERS_EXTENSIONS = hp
	SL_COPY_HEADERS_RECURSIVE = YES
	SL_COPY_HEADERS_DEFAULT_DIR = $$(SL_PRODUCT_DIR)/include
	SL_COPY_HEADERS_RESPECTIVE_LOCATIONS = $$(SL_COPY_HEADERS_DEFAULT_DIR)
	SL_HEADER_TYPES_TO_COPY = PUBLIC
	SL_COPY_HEADERS_ONLY_IF_NEWER = YES

	SL_IGNORE_DEPENDENCIES = NO

	SL_HEADER_SEARCH_PATHS =

config.slMake.staticLib : config.slMake._basicConfiguration
	# $@
	SL_PRODUCT_TYPE = staticLib
	SL_COPY_HEADERS = YES
ifdef _WINDOWS
	SL_EXECUTABLE_EXTENSION = lib
else
	SL_EXECUTABLE_EXTENSION = a
endif

config.slMake.dynamicLib : config.slMake._basicConfiguration
	# $@
	SL_PRODUCT_TYPE = dynamicLib
	SL_COPY_HEADERS = NO
ifdef _WINDOWS
	SL_EXECUTABLE_EXTENSION = dll
else
	SL_EXECUTABLE_EXTENSION = dylib
endif

config.slMake.executable : config.slMake._basicConfiguration
	# $@
	SL_PRODUCT_TYPE = executable
	SL_COPY_HEADERS = NO
ifdef _WINDOWS
	SL_EXECUTABLE_EXTENSION = exe
else
	SL_EXECUTABLE_EXTENSION =
endif

config.slMake.appBundle : config.slMake._basicConfiguration
	# $@
	SL_PRODUCT_TYPE = appBundle
	SL_COPY_HEADERS = NO
ifdef _WINDOWS
	SL_EXECUTABLE_EXTENSION = exe
else
	SL_EXECUTABLE_EXTENSION =
endif

config.slMake.loadableBundle : config.slMake._basicConfiguration
	# $@
	SL_PRODUCT_TYPE = loadableBundle
	SL_COPY_HEADERS = NO
ifdef _WINDOWS
	SL_EXECUTABLE_EXTENSION = dll
else
	SL_EXECUTABLE_EXTENSION =
endif


config.%.release config.%.Release : config.slMake.release config.% ;
config.%.debug config.%.Debug : config.slMake.debug config.% ;

################################################################################
clean.% : _SL_FORCE_REBUILD
	echo $*
	$(MAKE) CONFIGURATION=$(_processedConfiguration) _SL_BEGIN_CLEAN=Y $(_processedTarget)


%.debug : CONFIGURATION = debug
%.release : CONFIGURATION = release


%.debug : % ;
%.release : % ;

include $(INCLUDE_LIST)


endif # not _SL_COLLECT_SOURCES: End of part that can not be done while making
		#																_SL_COLLECT_SOURCES target

################################################################################
# Prebuild sources: collect all the sources to compile and write the list to
# config file
################################################################################

# Function normalizePath <path>
normalizePath = $(shell $(MAKE) -C '$(1)' -f '$(MAKE_FILE)' _SL_NORMALIZE_PATH)

################################################################################
_SL_NORMALIZE_PATH :
	@$(SHELL_CMD_PRINT) $(CURDIR)

################################################################################
# Prebuild sources: collect all the sources to compile and write the list to
# config file
################################################################################
ifeq ($(MAKECMDGOALS),_SL_PREBUILD_SOURCES)

include $(_SL_TMP_CONFIG_FILE)

filesInFolderWithExtension = $(shell $(MAKE) -f '$(MAKE_FILE)' -C '$(1)' '_COLLECT_EXTENSIONS=$(2)' _SL_COLLECT_SOURCES)
filesInFoldersWithExtension = $(foreach iFolder,$(1),$(call filesInFolderWithExtension,$(iFolder),$(2)))

_SL_SOURCES = $(call filesInFoldersWithExtension,$(SL_SRC_ROOTS),$(SOURCES_EXTENSIONS))

headersInFoldersWithType = $(call filesInFoldersWithExtension,$(1),$($(2)_HEADERS_EXTENSIONS))


_SHELL_CMD_COPY_HEADERS_WITH_TYPE = \
$(SHELL_CMD_PRINT) _SL_HEADERS_$(type) = $(call headersInFoldersWithType,$(SL_SRC_ROOTS),$(type)) >> '$(_SL_TMP_CONFIG_FILE)' $(_SL_END_SHELL_CMD)


################################################################################
_SL_PREBUILD_SOURCES :
	@$(SHELL_CMD_PRINT) _SL_SOURCES = $(_SL_SOURCES) >> '$(_SL_TMP_CONFIG_FILE)'

ifeq ($(SL_COPY_HEADERS),YES)
	@$(SHELL_CMD_LOG) "Collecting headers"
	@$(foreach type,$(SL_HEADER_TYPES),$(_SHELL_CMD_COPY_HEADERS_WITH_TYPE))
endif
	@$(SHELL_CMD_PRINT) _SL_NORMLIZED_SRC_ROOTS = $(foreach iRoot,$(SL_SRC_ROOTS),$(call normalizePath,$(iRoot))) >> '$(_SL_TMP_CONFIG_FILE)'


endif # Prebuild sources

################################################################################
# Collect sources
################################################################################
ifeq ($(MAKECMDGOALS),_SL_COLLECT_SOURCES)

SOURCES = $(foreach iSourceType,$(_COLLECT_EXTENSIONS),$(wildcard *.$(iSourceType)))

ifdef _WINDOWS
SUBDIRS = $(filter-out File Not Found .svn CVS,$(shell dir /A D /B))
else
isDirectory = $(shell if [ -d $(iDir) ]; then echo $(iDir); fi)
SUBDIRS = $(filter-out .svn CVS,$(foreach iDir,$(wildcard $(CURDIR)/*),$(isDirectory)))
endif


_SL_COLLECT_SOURCES :
	@$(SHELL_CMD_PRINT) $(addprefix $(CURDIR)/,$(SOURCES))
	@$(foreach iDir,$(SUBDIRS),$(MAKE) -C '$(iDir)' -f '$(MAKE_FILE)' '_COLLECT_EXTENSIONS=$(_COLLECT_EXTENSIONS)' _SL_COLLECT_SOURCES; )

endif # Collect sources

################################################################################
# Process sources list, and create dependencies and objects lists
################################################################################

# Function srcToDstPath <srcPath>
# returns translated src path
_NUMBER_LIST = 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25

srcToDstPath = $(firstword $(foreach i,$(_NUMBER_LIST),$(if $(findstring $(word $(i),$(_SL_NORMLIZED_SRC_ROOTS)),$(1)),$(patsubst $(word $(i),$(_SL_NORMLIZED_SRC_ROOTS))%,srcRoot$(i)%,$(1)))))
srcToDstHeaderPath = $(firstword $(foreach i,$(_NUMBER_LIST),$(if $(findstring $(word $(i),$(_SL_NORMLIZED_SRC_ROOTS)),$(1)),$(patsubst $(word $(i),$(_SL_NORMLIZED_SRC_ROOTS))%,$(word $(i),$(SL_COPY_HEADERS_RESPECTIVE_LOCATIONS))%,$(1)))))
dstToSrcHeaderPath = $(firstword $(foreach i,$(_NUMBER_LIST),$(if $(findstring $(word $(i),$(SL_COPY_HEADERS_RESPECTIVE_LOCATIONS)),$(1)),$(patsubst $(word $(i),$(SL_COPY_HEADERS_RESPECTIVE_LOCATIONS))%,$(word $(i),$(_SL_NORMLIZED_SRC_ROOTS))%,$(1)))))

ifeq ($(MAKECMDGOALS),_SL_COLLECT_DEPS_AND_OBJS)

include $(_SL_TMP_CONFIG_FILE)

-include $(SL_DEPENDENCIES_LIST_FILE)

ifneq ($(SL_IGNORE_DEPENDENCIES),YES)
_SL_DEPENDENCIES = $(foreach iSource,$(_SL_SOURCES),$(SL_DEPENDENCIES_DIR)/$(call srcToDstPath,$(iSource)).d)
endif

_SL_OBJECTS = $(foreach iSource,$(_SL_SOURCES),$(SL_OBJECTS_DIR)/$(call srcToDstPath,$(iSource)).o)

ifeq ($(SL_COPY_HEADERS),YES)
_SL_HEADERS_TO_COPY = $(foreach iType,$(SL_HEADER_TYPES_TO_COPY),$(foreach iHeader,$(_SL_HEADERS_$(iType)),$(call srcToDstHeaderPath,$(iHeader))))
endif

################################################################################
_SL_COLLECT_DEPS_AND_OBJS : _REMOVE_OBSOLETED_DEPENDENCIES
	@$(SHELL_CMD_LOG) Collecting dependencies
	@$(SHELL_CMD_PRINT) _SL_DEPENDENCIES = $(_SL_DEPENDENCIES) >> '$(_SL_TMP_CONFIG_FILE)'
	@$(call SHELL_CMD_MAKE_PATH,$(dir $(SL_DEPENDENCIES_LIST_FILE)))
	@$(SHELL_CMD_PRINT) _SL_PREV_DEPENDENCIES = $(_SL_DEPENDENCIES) > '$(SL_DEPENDENCIES_LIST_FILE)'
	@$(SHELL_CMD_LOG) Collecting objects
	@$(SHELL_CMD_PRINT) _SL_OBJECTS = $(_SL_OBJECTS) >> '$(_SL_TMP_CONFIG_FILE)'
	@$(SHELL_CMD_LOG) Collecting headers to copy

ifeq ($(SL_IGNORE_DEPENDENCIES),YES)
	@$(SHELL_CMD_PRINT) SL_COPY_HEADERS_DEPENDENCY = >> '$(_SL_TMP_CONFIG_FILE)'
endif

	@$(SHELL_CMD_PRINT) _SL_HEADERS_TO_COPY = $(_SL_HEADERS_TO_COPY) >> '$(_SL_TMP_CONFIG_FILE)'

	@$(SHELL_CMD_PRINT) _SL_HEADER_PATHS_COMPILER_FLAG = $(patsubst %,-I%,$(SL_HEADER_SEARCH_PATHS)) >> '$(_SL_TMP_CONFIG_FILE)'

ifeq ($(SL_PRODUCT_TYPE),staticLib)
	@$(SHELL_CMD_PRINT) _SL_PRODUCT_TYPE_COMPILER_FLAG = -static >> '$(_SL_TMP_CONFIG_FILE)'
endif

	@$(foreach iSource,$(_SL_SOURCES),$(SHELL_CMD_PRINT) $(SL_DEPENDENCIES_DIR)/$(call srcToDstPath,$(iSource)).d : $(iSource) >> '$(_SL_TMP_CONFIG_FILE)' $(_SL_END_SHELL_CMD))


_REMOVE_OBSOLETED_DEPENDENCIES : _SL_FORCE_REBUILD
	@$(if $(_SL_PREV_DEPENDENCIES),$(foreach iDep,$(filter-out $(_SL_DEPENDENCIES),$(_SL_PREV_DEPENDENCIES)),$(call SHELL_CMD_REMOVE_FILE,$(iDep)) $(_SL_END_SHELL_CMD)),$(call SHELL_CMD_REMOVE_DIR,$(SL_DEPENDENCIES_DIR)))

endif # Collect dependencies and objects

################################################################################
# Build dependencies
################################################################################

SHELL_CMD_MAKE_PATH = mkdir -p '$(1)'

_srcRootNum = $(firstword $(foreach i,$(_NUMBER_LIST),$(if $(patsubst srcRoot$(i)/%,%,$*),$(i))))
dstToSrcPath = $(word $(_srcRootNum),$(_SL_NORMLIZED_SRC_ROOTS))$(patsubst srcRoot$(_srcRootNum)%,%,$*)

ifeq ($(MAKECMDGOALS),_SL_BUILD_DEPENDENCIES)

include $(_SL_TMP_CONFIG_FILE)

_SL_BUILD_DEPENDENCIES : $(_SL_DEPENDENCIES) $(SL_COPY_HEADERS_DEPENDENCY)
ifeq ($(SL_IGNORE_DEPENDENCIES),YES)
	@$(SHELL_CMD_LOG) Ignoring dependencies
endif

SHELL_CMD_BUILD_DEPENDENCY = 	$(CC) $(_SL_HEADER_PATHS_COMPILER_FLAG) -M '$(1)' -MT $(SL_OBJECTS_DIR)/$(2).o -o '$(3)'

$(_SL_DEPENDENCIES) : $(SL_DEPENDENCIES_DIR)/%.d :
	@$(SHELL_CMD_LOG) Building dependency: $*.d
	@$(call SHELL_CMD_MAKE_PATH,$(dir $@))
	@$(call SHELL_CMD_BUILD_DEPENDENCY,$(dstToSrcPath),$*,$@)

_SHELL_CMD_ADD_HEADER_DEPENDENCY = \
$(SHELL_CMD_PRINT) $(iHeader) : $(call dstToSrcHeaderPath,$(iHeader)) >> $@ $(_SL_END_SHELL_CMD)


$(SL_COPY_HEADERS_DEPENDENCY) : _SL_FORCE_REBUILD
	@$(call SHELL_CMD_MAKE_PATH,$(dir $@))
	@$(SHELL_CMD_PRINT) _COPY_HEADERS_DUMMY = > $@
	@$(foreach iHeader,$(_SL_HEADERS_TO_COPY),$(_SHELL_CMD_ADD_HEADER_DEPENDENCY))

endif # BUILD DEPENDENCIES


SHELL_CMD_REMOVE_DIR = rm -rf '$(1)'
SHELL_CMD_REMOVE_FILE = rm -f '$(1)'


################################################################################
# Actual build
################################################################################
ifeq ($(MAKECMDGOALS),_SL_ACTUAL_BUILD)

SHELL_CMD_RENAME_DIR = mv -f '$(1)' '$(2)'

ifeq ($(SL_COPY_HEADERS_ONLY_IF_NEWER),YES)
SHELL_CMD_COPY_HEADER = cp -p '$(1)' '$(2)'
else
SHELL_CMD_COPY_HEADER = cp '$(1)' '$(2)'
endif

SHELL_CMD_BUILD_OBJECT = $(CC) $(_SL_HEADER_PATHS_COMPILER_FLAG) $(CCFLAGS) -c '$(1)' -o '$(2)'
SHELL_CMD_MOVE_FILE = mv -f '$(1)' '$(2)'

include $(_SL_TMP_CONFIG_FILE)

ifneq ($(SL_IGNORE_DEPENDENCIES),YES)
include $(_SL_DEPENDENCIES)
include $(SL_COPY_HEADERS_DEPENDENCY)
else
_FORCE_COMPILE_OBJECTS = _SL_FORCE_REBUILD
endif


SHELL_CMD_BUILD_PRODUCT = /usr/bin/libtool $(_SL_PRODUCT_TYPE_COMPILER_FLAG) -o '$(1)' $(_SL_OBJECTS)

# -arch ppc
# -Wl,-Y,1455 -mmacosx-version-min=10.4 -lstdc++.6.0.4

ifeq ($(SL_COPY_HEADERS),YES)
_SL_COPY_HEADERS = _SL_COPY_HEADERS
endif

################################################################################
# Target: _SL_ACTUAL_BUILD - clean up dependencies if needed
_SL_ACTUAL_BUILD : $(SL_PRODUCT_DIR)/$(SL_EXECUTABLE_FULL_NAME) $(_SL_COPY_HEADERS)
ifeq ($(SL_IGNORE_DEPENDENCIES),YES)
	@$(call SHELL_CMD_REMOVE_DIR,$(SL_DEPENDENCIES_DIR))
endif

	@$(call SHELL_CMD_MAKE_PATH,$(dir $(SL_CONFIG_USER_FILE)))
	@$(call SHELL_CMD_MOVE_FILE,$(_SL_TMP_CONFIG_FILE),$(SL_CONFIG_USER_FILE))
	@$(SHELL_CMD_LOG) Build complete: $(SL_TARGET_NAME)

################################################################################
$(SL_PRODUCT_DIR)/$(SL_EXECUTABLE_FULL_NAME) : $(_SL_OBJECTS)
	@$(SHELL_CMD_LOG) Linking product: $(SL_EXECUTABLE_FULL_NAME)
	@$(call SHELL_CMD_MAKE_PATH,$(dir $@))
	$(call SHELL_CMD_BUILD_PRODUCT,$@)

################################################################################
$(_SL_OBJECTS) : $(SL_OBJECTS_DIR)/%.o : $(_FORCE_COMPILE_OBJECTS)
	@$(SHELL_CMD_LOG) Building object: $*.o
	@$(call SHELL_CMD_MAKE_PATH,$(dir $@))
	$(call SHELL_CMD_BUILD_OBJECT,$(dstToSrcPath),$@)

################################################################################
_SL_COPY_HEADERS : $(_SL_HEADERS_TO_COPY)
	$(SHELL_CMD_EMPTY)

################################################################################
$(_SL_HEADERS_TO_COPY) : % : $(_FORCE_COMPILE_OBJECTS)
	@$(SHELL_CMD_LOG) Copying header $@
	@$(call SHELL_CMD_MAKE_PATH,$(dir $@))
	@$(call SHELL_CMD_COPY_HEADER,$(call dstToSrcHeaderPath,$@),$@)

endif # ACTUAL BUILD

################################################################################
_SL_FORCE_REBUILD :
	$(SHELL_CMD_EMPTY)


################################################################################
# Clean commands
################################################################################
cleanall.% : clean.all.%
	@echo cleanall.%

clean clean.all cleanall : clean.all.$(CONFIGURATION)
	@echo clean cleanall clean.all

_configuration = $(word 2,$(if $(find .,$*),$(subst ., ,$*),))
_processedConfiguration = $(if $(_configuration),$(_configuration),all)

_target = $(firstword $(subst ., ,$*))
_processedTarget = $(subst all,$(all),$(_target))



ifeq ($(MAKECMDGOALS),_SL_ACTUAL_CLEAN)

include $(_SL_TMP_CONFIG_FILE)


################################################################################
_SL_ACTUAL_CLEAN :
	@$(SHELL_CMD_LOG) Cleaning target: $(SL_TARGET_NAME).$(SL_CONFIGURATION)
	@$(foreach iDir,$(SL_COPY_HEADERS_RESPECTIVE_LOCATIONS),$(call SHELL_CMD_REMOVE_DIR,$(iDir)) $(_SL_END_SHELL_CMD))
	@$(call SHELL_CMD_REMOVE_DIR,$(SL_OBJECTS_DIR))
	@$(call SHELL_CMD_REMOVE_DIR,$(SL_DEPENDENCIES_DIR))
	@$(call SHELL_CMD_REMOVE_DIR,$(SL_CONFIGURATION_TEMP_DIR))
	@$(call SHELL_CMD_REMOVE_FILE,$(SL_PRODUCT_DIR)/$(SL_EXECUTABLE_FULL_NAME))
	@$(call SHELL_CMD_REMOVE_FILE,$(_SL_TMP_CONFIG_FILE))


endif # ACTUAL CLEAN
