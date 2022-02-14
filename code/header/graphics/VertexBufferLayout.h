#ifndef VERTEXBUFFERLAYOUT_CPP
#define VERTEXBUFFERLAYOUT_CPP

//#include "Renderer.h"
#include "GLC.h"
#include <vector>

struct VertexBufferElement {
    unsigned int type;
    unsigned int count;
    unsigned char normalized;

    static unsigned int getSizeOfType(unsigned int type) {
        switch(type) {
            case GL_FLOAT: return 4;
            case GL_UNSIGNED_INT: return 4;
            case GL_UNSIGNED_BYTE: return 1;
        }
        ASSERT(false);
        return 0;
    }
};

class VertexBufferLayout {
    private:

        std::vector<VertexBufferElement> elements;
        // Total dimension of the data in the vertexBuffer
        unsigned int stride;

    public:
        VertexBufferLayout();

        template<class T>
        void push(unsigned int count);

        inline const std::vector<VertexBufferElement>& getElements() const { return elements;};
        inline unsigned int getStride() const { return stride; }
};

#endif