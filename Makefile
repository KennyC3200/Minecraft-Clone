UNAME_S = $(shell uname -s)

CXX = clang++
CXXFLAGS = -std=c++20 -g -Wall -Wextra -Wfloat-conversion
CXXFLAGS += -Ilib/glad/include -Ilib/glfw/include -Ilib/stb -Ilib/imgui -Ilib/imgui/backends -Ilib/fast_noise_lite
LDFLAGS = lib/glad/src/glad.o lib/glfw/src/libglfw3.a lib/glm/build/glm/libglm.a -lm

# Profiling
CXXFLAGS += -I/opt/homebrew/include
LDFLAGS += -L/opt/homebrew/lib -lprofiler

# GLFW required frameworks on OSX
ifeq ($(UNAME_S), Darwin)
	LDFLAGS += -framework OpenGL -framework IOKit -framework CoreVideo -framework Cocoa
endif

SRC = $(shell find src -name "*.cpp")
OBJ = $(patsubst %.cpp, %.o, $(SRC))
BIN = bin

IMGUI_SRC = lib/imgui/imgui.cpp lib/imgui/imgui_demo.cpp lib/imgui/imgui_draw.cpp lib/imgui/imgui_tables.cpp lib/imgui/imgui_widgets.cpp
IMGUI_SRC += lib/imgui/backends/imgui_impl_glfw.cpp lib/imgui/backends/imgui_impl_opengl3.cpp
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

TEST = block_data
TEST_SRC = tests/$(TEST).cpp

test:
	$(CXX) -o tests/$(TEST) $(TEST_SRC) $(CXXFLAGS)

runtest: test
	./tests/$(TEST)

cleantest:
	rm -rf tests/$(TEST)
