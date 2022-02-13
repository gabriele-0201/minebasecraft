#ifndef GLC_CPP
#define GLC_CPP

#include "GLC.h"

void GLClearError() {
    //get the error and do nothing
    //this is to clear the erorr because the get error
    //return an arbitrary error
    while (glGetError() != GL_NO_ERROR);
}

bool GLLogCall(const char* function, const char* file, int line) {
    while (GLenum error = glGetError()) {
        // I have to convert the error from ex to a real message
        // Error code
        std::cout << "[OpenGl Error]\n";
        std::cout << "In file " << file <<std::endl;
        std::cout << "At line: " << line <<std::endl;
        std::cout << "Error: " << error <<std::endl;
        return false;
    }
    return true;
}
#endif

