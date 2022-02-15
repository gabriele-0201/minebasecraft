cmake_minimum_required(VERSION 3.17)

project(minebasecraft)

include_directories("code/src" "code/header/graphics" "code/src/graphics" 
                    "code/header/mc" "code/src/mc")


add_library (World STATIC
    code/header/mc/World.h
    code/src/mc/World.cpp
    code/header/mc/Enums.h
)

add_library (Player STATIC
    code/header/mc/Player.h
    code/src/mc/Player.cpp
)

add_library (PieceOfWorld STATIC
    code/header/mc/PieceOfWorld.h
    code/src/mc/PieceOfWorld.cpp
    code/header/mc/Enums.h
)

add_library (Block STATIC
    code/header/mc/Block.h
    code/src/mc/Block.cpp
)

add_library(GLC STATIC
    code/header/graphics/GLC.h
    code/src/graphics/GLC.cpp
)

add_library(Renderer STATIC
    code/header/graphics/Renderer.h
    code/src/graphics/Renderer.cpp
)

add_library(ElementBuffer STATIC
    code/header/graphics/ElementBuffer.h
    code/src/graphics/ElementBuffer.cpp
)

add_library(Shader STATIC
    code/header/graphics/Shader.h
    code/src/graphics/Shader.cpp
)

add_library(stbImage STATIC
    code/header/graphics/stb_image.h
    code/src/graphics/stb_image.cpp
)

add_library(Texture STATIC
    code/header/graphics/Texture.h
    code/src/graphics/Texture.cpp
)

add_library(VertexArray STATIC
    code/header/graphics/VertexArray.h
    code/src/graphics/VertexArray.cpp
)

add_library(VertexBuffer STATIC
    code/header/graphics/VertexBuffer.h
    code/src/graphics/VertexBuffer.cpp
)

add_library(VertexBufferLayout STATIC
    code/header/graphics/VertexBufferLayout.h
    code/src/graphics/VertexBufferLayout.cpp
)


add_executable(${PROJECT_NAME} code/src/minebasecraft.cpp)

target_link_libraries(World
    PieceOfWorld
    GLC 
    VertexArray
    VertexBuffer
    VertexBufferLayout
    ElementBuffer
)

target_link_libraries(Renderer 
    World
    Player
    VertexArray
    Shader
)

target_link_libraries(${PROJECT_NAME} 
    GL 
    glfw 
    GLEW 

    World
    Player
    GLC 
    Renderer
)