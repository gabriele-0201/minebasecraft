#ifndef WORLD_H
#define WORLD_H

#include <unordered_map>
#include <unordered_set>
#include <memory>
#include <libnoise/noise.h>
#include <time.h>
#include <future>

#include "noiseutils.h"

#include "Enums.h"
#include "PieceOfWorld.h"
#include "HashTuples.h"
#include "GLC.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "ElementBuffer.h"
  
class World { 

    private:

        GLFWwindow* win;

        // Someway store chunkssss
        std::unordered_map<std::tuple<int, int>, PieceOfWorld, HashTuples::hash2tuple> terrain;
        std::unordered_set<std::tuple<int, int, int>, HashTuples::hash3tuple> terrainBlocks;

        std::vector<std::pair<int, int>> getNearPieceOfWorld(int x, int z, int distance);
        std::pair<int, int> currentPos;

        module::RidgedMulti mountainTerrain;
        module::Billow baseFlatTerrain;
        module::ScaleBias flatTerrain;
        module::Perlin terrainType;
        module::Select terrainSelector;
        module::Turbulence finalTerrain;
        noise::module::Perlin perl;

        int renderingBlockDistance = 15;
        int viewBlockDistance = 15;

    public:

        World(GLFWwindow* win, unsigned int seed);

        void render();

        /**
         * Return a vector containing two vectors:
         * 1 - contains all the vertex to be used in the buffer
         * 2 - contains all the indeces that is used to draw the stuff int the same index buffer
         */
        //std::vector<float> getAllVertecies();
        // TODO CHANGE
        //std::vector<std::vector<unsigned int>> getAllIndicies();

        // This will update also the chunks that will be rendered each frame
        void updatePos(int x, int z);

        /**
         * Check if in a determinate position there is a block or not
         */
        bool isBlock(glm::vec2 posOfPiece, glm::vec3 posOfBlock);
        //bool isBlock(glm::vec3 pos);

        /**
         * Remove the block in the specified position
         */
        void breakBlock(glm::vec2 posOfPiece, glm::vec3 posOfBlock);
        //void breakBlock(glm::vec3 pos);

        /**
         * Add a specified block in a specified position
         */
        void addBlock(glm::vec2 posOfPiece, glm::vec3 posOfBlock, TypeOfBlock type);

        std::vector<std::shared_ptr<VertexArray> > getAllVertexArrays();
        std::vector<std::shared_ptr<ElementBuffer> > getAllElementBuffers();
};

#endif