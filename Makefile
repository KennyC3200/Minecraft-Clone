UNAME_S = $(shell uname -s)

CXX = clang++
CXXFLAGS = -std=c++20 -g -Wall -Wextra -Wfloat-conversion
CXXFLAGS += -I lib/glad/include -I lib/glfw/include -I lib/stb -I lib/cglm/include -I lib/imgui -I lib/imgui/backends
LDFLAGS = lib/glad/src/glad.o lib/glfw/src/libglfw3.a lib/glm/build/glm/libglm.a -lm

# GLFW required frameworks on OSX
ifeq ($(UNAME_S), Darwin)
	LDFLAGS += -framework OpenGL -framework IOKit -framework CoreVideo -framework Cocoa
endif

SRC = $(shell find src -name "*.cpp")
SRC += lib/imgui/imgui.cpp lib/imgui/imgui_demo.cpp lib/imgui/imgui_draw.cpp lib/imgui/imgui_tables.cpp lib/imgui/imgui_widgets.cpp
SRC += lib/imgui/backends/imgui_impl_glfw.cpp lib/imgui/backends/imgui_impl_opengl3.cpp
OBJ = $(patsubst %.cpp, %.o, $(SRC))
BIN = bin

.PHONY: all clean

all: dirs libs game

dirs:
	mkdir -p ./$(BIN)

libs:
	cd lib/glm && cmake -DGLM_BUILD_TESTS=OFF -DBUILD_SHARED_LIBS=OFF -B build . && cmake --build build -- all
	cd lib/glad && $(CXX) -o src/glad.o -I include -c src/glad.c 
	cd lib/glfw && cmake . && make

run: all
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
	rm -rf $(BIN) $(OBJ)
