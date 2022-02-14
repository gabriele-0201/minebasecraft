#ifndef GLC_H
#define GLC_H

#include<GL/glew.h>

#include<GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include<iostream>

/**
 * If the assertion return false than exit the program
 */
#define ASSERT(x) if(!(x)) exit(EXIT_FAILURE);

//When calling a gl function before clear all previous possible error and then
//use the assert to output the error and maybe also exit the program
#define GLCall(x) GLClearError();\
    x;\
    ASSERT(GLLogCall(#x, __FILE__, __LINE__))

void GLClearError();
bool GLLogCall(const char* function, const char* file, int line);

#endif
