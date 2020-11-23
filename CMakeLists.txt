cmake_minimum_required (VERSION 3.8)


project ("LearnOpenGL")

message(${PROJECT_SOURCE_DIR})

include_directories(${PROJECT_SOURCE_DIR}/include)


add_executable(LearnOpenGL "main.cpp" "glad.c" "include/shader/Shader.h"  "include/shader/Shader.cpp" "include/stb_image.h")


target_link_libraries(LearnOpenGL PRIVATE ${PROJECT_SOURCE_DIR}/lib/glfw3.lib)