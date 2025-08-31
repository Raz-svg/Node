cmake_minimum_required(VERSION 3.10)
project(Node)

set(CMAKE_CXX_STANDARD 17)

# ======================
# Add executable
# ======================
add_executable(${PROJECT_NAME}
        window.cpp
        app.cpp
        window.h
        vertex_shader.vert
)

# ======================
# Add GLAD
# ======================
add_library(glad src/glad.c)
target_include_directories(glad PUBLIC include)

# ======================
# Find and link GLFW
# ======================
find_package(glfw3 3.3 REQUIRED)

# ======================
# Link everything together
# ======================
target_link_libraries(${PROJECT_NAME} PRIVATE glfw glad)

# On Linux also link OpenGL + dl
if (UNIX)
    find_package(OpenGL REQUIRED)
    target_link_libraries(${PROJECT_NAME} PRIVATE OpenGL::GL dl)
endif()
