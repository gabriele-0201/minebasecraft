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

        VertexArray(const VertexArray&) = delete;
        void operator=(const VertexArray&) = delete;

        /**
         * Maybe usefull but when some change but I do not want to recreate the entire vertex array
         */
        void bindVb(const VertexBuffer& vb, const VertexBufferLayout& layout);

        void bind() const;
        void unbind() const;


};

#endif