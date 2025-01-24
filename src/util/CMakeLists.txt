add_library(MinecraftUtil)
target_sources(MinecraftUtil
    PUBLIC math.cpp
)
target_include_directories(MinecraftUtil
    PUBLIC ${PROJECT_SOURCE_DIR}/lib/glm
    PUBLIC ${PROJECT_SOURCE_DIR}/lib/glfw/include
)
