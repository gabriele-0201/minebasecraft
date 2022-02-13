cmake_minimum_required(VERSION 3.17)

project(minebasecraft)

add_subdirectory(code/header)
add_subdirectory(code/src)

add_executable(${PROJECT_NAME} minebasecraft.cpp)

//add_library(GLC
    //code/header/GLC.h
    //code/src/GLC.cpp
//)

target_link_libraries(${PROJECT_NAME} 
    GL 
    glfw 
    GLEW 
)