UNAME_S := $(shell uname -s)

CXX := clang++

# Compiling flags
CXXFLAGS := -std=c++20
CXXFLAGS += -g
CXXFLAGS += -Wall
CXXFLAGS += -Wextra
CXXFLAGS += -Wfloat-conversion
CXXFLAGS += -Wunused
CXXFLAGS += -O3

# Libraries includes
CXXFLAGS += -Ilib/glad/include
CXXFLAGS += -Ilib/glfw/include
CXXFLAGS += -Ilib/stb
CXXFLAGS += -Ilib/imgui
CXXFLAGS += -Ilib/imgui/backends
CXXFLAGS += -Ilib/fast_noise_lite

# Linking
LDFLAGS := lib/glad/src/glad.o
LDFLAGS += lib/glfw/src/libglfw3.a
LDFLAGS += lib/glm/build/glm/libglm.a -lm

# GLFW required frameworks on OSX
ifeq ($(UNAME_S), Darwin)
	LDFLAGS += -framework OpenGL
	LDFLAGS += -framework IOKit
	LDFLAGS += -framework CoreVideo
	LDFLAGS += -framework Cocoa
endif

SRC = $(shell find src -name "*.cpp")
OBJ = $(patsubst %.cpp, %.o, $(SRC))
BIN = bin

# dear imgui
IMGUI_SRC := lib/imgui/imgui.cpp
IMGUI_SRC += lib/imgui/imgui_demo.cpp
IMGUI_SRC += lib/imgui/imgui_draw.cpp
IMGUI_SRC += lib/imgui/imgui_tables.cpp
IMGUI_SRC += lib/imgui/imgui_widgets.cpp
IMGUI_SRC += lib/imgui/backends/imgui_impl_glfw.cpp
IMGUI_SRC += lib/imgui/backends/imgui_impl_opengl3.cpp
IMGUI_OBJ = $(patsubst %.cpp, %.o, $(IMGUI_SRC))
SRC += $(IMGUI_SRC)

.PHONY: all clean

all: dirs libs game

dirs:
	mkdir -p ./$(BIN)

libs:
	cd lib/glm && cmake -DGLM_BUILD_TESTS=OFF -DBUILD_SHARED_LIBS=OFF -B build . && cmake --build build -- all
	cd lib/glad && $(CXX) -o src/glad.o -I include -c src/glad.c
	cd lib/glfw && cmake . && make

run: dirs game
	$(BIN)/game

game: $(OBJ)
	$(CXX) -o $(BIN)/game $^ $(LDFLAGS)

%.o: %.cpp %.h
	$(CXX) -o $@ -c $< $(CXXFLAGS)

%.o: %.cpp
	$(CXX) -o $@ -c $< $(CXXFLAGS)

%.o: lib/imgui/%.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

%.o: lib/imgui/backends/%.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

clean:
	rm -rf $(BIN) $(filter-out $(IMGUI_OBJ), $(OBJ))

deepclean:
	rm -rf $(BIN) $(OBJ)
