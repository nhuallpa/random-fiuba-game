BUILD ?= build
SOURCE ?= src
TIME_FILE ?= build/times

#TODO: cambiar por tomar version >= 4.6
CXX = g++-4.6

override LIBRARY += yaml-cpp Box2D SDL2 SDL2_image SDL2_ttf SDL2_mixer
override INCLUDE-HEADERS += $(SOURCE)
override CPPFLAGS += -O0 -g3 -Wall -Weffc++ -fmessage-length=0 -std=c++0x $(addprefix -I,$(INCLUDE-HEADERS)) #-DDEBUG
override LDFLAGS += $(addprefix -L,$(INCLUDE-LIBRARY))

SOURCES := $(patsubst ./%.cpp,%.cpp,$(shell find $(SOURCE) -mindepth 2 -type f -name *.cpp -print))
MAIN_SOURCES := $(patsubst ./%,%,$(shell find $(SOURCE) -maxdepth 1 -type f -name *.cpp -print))
EXECUTABLE := $(patsubst $(SOURCE)/%.cpp,%,$(MAIN_SOURCES))

# default rule
.PHONY: all
all: $(EXECUTABLE)

# file names
OBJ := $(addprefix $(BUILD)/, $(SOURCES:.cpp=.o))
MAIN_OBJ := $(addprefix $(BUILD)/, $(MAIN_SOURCES:.cpp=.o))
DEPS := $(addprefix $(BUILD)/, $(SOURCES:.cpp=.d)) $(addprefix $(BUILD)/, $(MAIN_SOURCES:.cpp=.d))

# commands, to be expanded where run
TIMER = ./timer.sh $(TIME_FILE) "$@"
MKDEP = ./mkdep.sh "$(@:.o=.d)"

# include dependencies
-include $(DEPS)

# clean rules
.PHONY: build
build: all clean-obj clean-dep

.PHONY: clean
clean: clean-build clean-obj

.PHONY: clean-all
clean-all: clean-build clean-obj clean-dep

.PHONY: clean-exe
clean-build:
	@rm -f $(EXECUTABLE)
	@echo "  Deleted executables"

.PHONY: clean-obj
clean-obj:
	@-find $(BUILD) -name "*.o" -delete
	@rm -f $(TIME_FILE)
	@echo "  Deleted object files"

.PHONY: clean-dep
clean-dep:
	@-find $(BUILD) -name "*.d" -delete
	@echo "  Deleted dependency files"

# object rules
$(BUILD)/%.o: %.cpp
	@echo "  Compiling $@"
	@mkdir -p $(@D)
	@$(TIMER) $(CXX) $(CPPFLAGS) $(CXXFLAGS) -c           "$<" -o "$@"
	@$(MKDEP) $(CXX) $(CPPFLAGS) $(CXXFLAGS) -MM -MT "$@" "$<" -o "$(@:.o=.d)"

$(EXECUTABLE): $(OBJ) $(MAIN_OBJ)
	@echo "  Linking $@"
	@$(TIMER) $(CXX) $(CPPFLAGS) $(CXXFLAGS) $(LDFLAGS) $(OBJ) $(BUILD)/$(SOURCE)/$@.o $(addprefix -l,$(LIBRARY))  -o $@
	@sort -r -o $(TIME_FILE) $(TIME_FILE)

# help
.PHONY: help
help:
	@echo "Targets disponibles:"
	@echo "  [all]: Crea los ejecutables."
	@echo "  build: Crea los ejecutables y elimina archivos intermedios."
	@echo "  clean: Elimina archivos compilados."
	@echo "  clean-all: Elimina todos los archivos generados."
