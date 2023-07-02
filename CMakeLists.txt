cmake_minimum_required(VERSION 3.8)
project(LearnOpenGL)

set(CMAKE_CXX_STANDARD 17)
set(BINS_DIR C:\\Users\\Srinj\\Desktop\\progs\\C++\\libs\\bin)
set(INCLUDES_DIR C:\\Users\\Srinj\\Desktop\\progs\\C++\\libs\\include)
set(ASSIMP_LIB "C:\\Program Files\\Assimp\\lib\\x64")
set(ASSIMP_DLL "C:\\Program Files\\Assimp\\bin\\x64")
set(ASSIMP_INCLUDE "C:\\Program Files\\Assimp\\include")

include_directories(${INCLUDES_DIR} ${CMAKE_SOURCE_DIR}/includes ${ASSIMP_INCLUDE})
add_executable(LearnOpenGL ${CMAKE_SOURCE_DIR}/src/game/main.cpp src/core/GameEngine.cpp src/core/WindowManager.cpp src/core/callbacks/Keyboard.cpp src/core/callbacks/WindowSize.cpp includes/LearnOpenGL/WindowManagerHeader.h src/core/callbacks/Error.cpp src/core/Camera.cpp src/core/Shader.cpp src/core/callbacks/CursorPos.cpp src/core/Mesh.cpp src/core/Model.cpp)

target_link_libraries(
        ${PROJECT_NAME}
        ${BINS_DIR}/glfw3.dll
        ${BINS_DIR}/glew32.dll
        opengl32
)
