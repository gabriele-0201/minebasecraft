cmake_minimum_required(VERSION 3.17)

set(CMAKE_BUILD_TYPE)
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")

project(minebasecraft)

include_directories("code/header/graphics" "code/header/mc" "code/header/noise")

add_executable(${PROJECT_NAME} code/src/minebasecraft.cpp
    
    code/src/graphics/ElementBuffer.cpp
    code/src/graphics/GLC.cpp
    code/src/graphics/Renderer.cpp
    code/src/graphics/Shader.cpp
    code/src/graphics/stb_image.cpp
    code/src/graphics/Texture.cpp
    code/src/graphics/VertexArray.cpp
    code/src/graphics/VertexBuffer.cpp
    code/src/graphics/VertexBufferLayout.cpp

    code/src/mc/Block.cpp
    code/src/mc/PieceOfWorld.cpp
    code/src/mc/Player.cpp
    code/src/mc/World.cpp

    code/src/noise/noiseutils.cpp

)

target_link_libraries(${PROJECT_NAME} 
    
    GL
    GLEW
    glfw
    noise

)