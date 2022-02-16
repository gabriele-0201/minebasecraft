#ifndef VERTEXARRAY_H
#define VERTEXARRAY_H

#include "VertexBuffer.h"
#include "VertexBufferLayout.h"

class VertexArray {

    private:
        unsigned int id;

    public:

        VertexArray();
        ~VertexArray();

        /**
         * Maybe usefull but when some change but I do not want to recreate the entire vertex array
         */
        void bindVb(VertexBuffer& vb, VertexBufferLayout& layout);

        void bind() const;
        void unbind() const;


};

#endif