cmake_minimum_required(VERSION 3.17)

project(minebasecraft)

include_directories(code/header/graphics)
include_directories(code/src/graphics)

include_directories(code/header/mc)
include_directories(code/src/mc)

include_directories(code/src)

/** MC **/

add_library (World
    code/header/mc/World.h
    code/src/mc/World.cpp
    code/header/mc/Enums.h
)

add_library (PieceOfWorld
    code/header/mc/PieceOfWorld.h
    code/src/mc/PieceOfWorld.cpp
    code/header/mc/Enums.h
)

add_library (Block
    code/header/mc/Block.h
    code/src/mc/Block.cpp
)

/** GRAPHICS */

add_library(GLC
    code/header/graphics/GLC.h
    code/src/graphics/GLC.cpp
)

add_executable(${PROJECT_NAME} code/src/minebasecraft.cpp)

target_link_libraries(${PROJECT_NAME} 
    GL 
    glfw 
    GLEW 

    World
)

target_link_libraries(World
    PieceOfWorld
)