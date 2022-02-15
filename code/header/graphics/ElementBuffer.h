#ifndef ELEMENTBUFFER_H
#define ELEMENTBUFFER_H

#include <vector>

#include "GLC.h"

class ElementBuffer {

    private:

        unsigned int id;
        unsigned int count;

    public:


        ElementBuffer();
        ElementBuffer(unsigned int* data, unsigned int count);
        ~ElementBuffer();

        void newIndeces(unsigned int* data, unsigned int count);
        unsigned int inline getCount() const { return count; };

        void bind() const;
        void unbind() const;

};

#endif