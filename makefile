CXX = clang #g++
TARGET_EXEC ?= game
TEST_TARGET_EXEC ?= test

BUILD_DIR ?= build
SRC_DIRS ?= src imgui
TEST_SRC_DIRS ?= tests

SRCS := $(shell find $(SRC_DIRS) -name *.cpp ! -name 'Main.cpp' ! -name 'TestsMain.cpp')
OBJS := $(SRCS:%=$(BUILD_DIR)/%.o)
DEPS := $(OBJS:.o=.d)

TEST_SRCS := $(shell find $(TEST_SRC_DIRS) -name *.cpp ! -name 'Main.cpp' ! -name 'TestsMain.cpp' ) 
TEST_OBJS := $(TEST_SRCS:%=$(BUILD_DIR)/%.o)
TEST_DEPS := $(TEST_OBJS:.o=.d)

CPPFLAGS ?= -Wall -Wextra -std=c++20 -pedantic -Wshadow -Wconversion -O3 -fPIC -g -fprofile-instr-generate=build/default.profraw -fcoverage-mapping  #-g for debug, TODO : remove later or implement a make debug command instead
LIBS := -lgtest -lpthread -lstdc++ -lm -lSDL2 -lfmt
INCLUDES := -I../ -Iimgui/ -Iimgui/backends/ -Isrc/UI -Isrc/Ressources -Isrc/GameData -Isrc/Buildings -Isrc/Jellyfishs

LDFLAGS :=
TESTLDFLAGS := -fprofile-instr-generate


$(BUILD_DIR)/$(TARGET_EXEC): $(OBJS) $(BUILD_DIR)/Main.o
	@echo Linking "$@ ( $(foreach f, $^,$(subst $(BUILD_DIR)/$(SRC_DIRS),,$f )))"
	$(CXX) $(OBJS) $(BUILD_DIR)/Main.o -o $@ $(LDFLAGS) $(LIBS) $(INCLUDES) 
	@echo "\n"

$(BUILD_DIR)/$(TEST_TARGET_EXEC): $(TEST_OBJS) $(OBJS) $(BUILD_DIR)/TestsMain.o
	@echo -e Linking "$@ ( $(foreach f, $^,$(subst $(BUILD_DIR)/$(TEST_SRC_DIRS),,$f )))"
	$(CXX) $(TEST_OBJS) $(OBJS) $(BUILD_DIR)/TestsMain.o -o $@ $(TESTLDFLAGS) $(LIBS) $(INCLUDES)
	@echo  "\n"


$(BUILD_DIR)/%.cpp.o: %.cpp
	@echo "\n"Compiling: $< 
	@$(MKDIR_P) $(dir $@)
	$(CXX) $(CPPFLAGS) $(CFLAGS) -MP -MMD -c $< -o $@ $(INCLUDES) 

$(BUILD_DIR)/Main.o: src/Main.cpp
	@echo "\n"Compiling main: $< 
	@$(MKDIR_P) $(dir $@)
	$(CXX) $(CPPFLAGS) $(CFLAGS) -c $< -o $@ $(INCLUDES)

$(BUILD_DIR)/TestsMain.o: $(TEST_SRC_DIRS)/TestsMain.cpp 
	@echo "\n"Compiling test main: $< 
	@$(MKDIR_P) $(dir $@)
	$(CXX) $(CPPFLAGS) $(CFLAGS) -c $< -o $@ $(INCLUDES)
# TODO : modify the makefile so that only the test executable uses -g, with -O0, and the regular exec gets -O3


.PHONY: clean
.PHONY: nLines
.PHONY: nFiles
.PHONY: genCompileCommands
.PHONY: coverage

nLines:
	find ./src -type f \( -name "*.cpp" -o -name "*.hpp" \) -exec wc -l {} +

nFiles:
	find ./src -type f \( -name "*.hpp" -o -name "*.cpp" \) | grep -c "\.hpp$$\|\.cpp$$"


genCompileCommands: #for my vscode's clangd setup
	make clean && bear -- make build -j

clean:
	$(RM) -r $(BUILD_DIR)

coverage:
	@llvm-profdata merge -o build/default.profdata build/default.profraw 
	@llvm-cov show --show-branches=count --instr-profile=build/default.profdata build/test > build/coverage.txt

-include $(DEPS)
-include $(TEST_DEPS)

MKDIR_P ?= mkdir -p

build: $(BUILD_DIR)/$(TARGET_EXEC)

tests: $(BUILD_DIR)/$(TEST_TARGET_EXEC)
	gtester -k ./$(BUILD_DIR)/$(TEST_TARGET_EXEC)