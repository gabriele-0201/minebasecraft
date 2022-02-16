#ifndef ELEMENTBUFFER_H
#define ELEMENTBUFFER_H

#include <vector>

#include "GLC.h"

class ElementBuffer {

    private:

        // Keep track if the Object is created with a default constructor
        bool defCostruct;
        unsigned int id;
        unsigned int count;

    public:

        ElementBuffer();
        ElementBuffer(unsigned int* data, unsigned int count);
        ~ElementBuffer();

        ElementBuffer(const ElementBuffer&) = delete;
        void operator=(const ElementBuffer&) = delete;

        void newIndeces(unsigned int* data, unsigned int count);
        unsigned int inline getCount() const { return count; };

        void bind() const;
        void unbind() const;

};

#endif