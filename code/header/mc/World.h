#ifndef WORLD_H
#define WORLD_H

//#include <unordered_map>
#include <map>

#include "Enums.h"
#include "PieceOfWorld.h"
#include "HashPair.h"
#include "GLC.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "ElementBuffer.h"
  
class World { 

    private:

        GLFWwindow* win;

        // Someway store chunkssss
        std::map<std::pair<int, int>, PieceOfWorld> terrain;

    public:

        World(GLFWwindow* win, unsigned int seed);

        void render();

        // This will update also the chunks that will be rendered each frame
        void updatePos();

        void breakBlock();

        void addBlock(TypeOfBlock);

};

#endif