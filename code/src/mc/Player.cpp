#ifndef PLAYER_CPP
#define PLAYER_CPP

#include "Player.h"

Player::Player(GLFWwindow* window, World& _w, glm::vec3 up) : w{_w}{

    cameraPos = glm::vec3(0.0f, 10.0f, 0.0f);
    cameraFront = glm::vec3(0.0f, 0.0f, 1.0f);
    cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
        
    speed = 10.0f;
    deltaTime = 0.0f;
        
    lastx = 400.0f;
    lasty = 300.0f;
    yaw = 0;
    pitch = 0;

    intervalOfCheck = 0.1;
    maxNBlockInteract = 8;
    selectedBlock = TypeOfBlock::SAND;
}

void Player::processKeyInput(GLFWwindow* window) {

    float cameraSpeed = speed * deltaTime; 
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        cameraPos += cameraSpeed * cameraFront;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        cameraPos -= cameraSpeed * cameraFront;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;

    // update viewMatrix
    viewMatrix = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);

    // update position in the world
    std::pair<glm::vec2, glm::vec3> position = getBlockPos(cameraPos);
    w.updatePos(position.first.x, position.first.y);
}

void Player::mouseMovCb(double xpos, double ypos) {
    float offsetx = xpos - lastx;
    float offsety = lasty - ypos;
    lastx = xpos;
    lasty = ypos;

    const float sensitivity = 0.1f;
    offsetx *= sensitivity;
    offsety *= sensitivity;

    yaw += offsetx;
    pitch += offsety;

    // check te pitch to awoid weird effects
    if(pitch > 89)
        pitch = 89;
    if(pitch < -89)
        pitch = -89;

    glm::vec3 direction;
    direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    direction.y = sin(glm::radians(pitch));
    direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    cameraFront = glm::normalize(direction);

    // update viewMatrix
    viewMatrix = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);

    // TODO update also the piece of world we calcuate each time in funtion of where are we looking

    // update position in the world
    //w.updatePos({cameraPos.x, cameraPos.y});
}

void Player::setDeltaTime (float t) {
    deltaTime = t;
}

float Player::getDeltaTime() {
    return deltaTime;
}

std::pair<glm::vec2, glm::vec3> Player::getBlockPos(glm::vec3 pos) {

    // TODO solve this problem
    if(pos.y < 0) {
        std::cout << "there is some trouble with the position for check blocks" <<std::endl;
    }

    std::pair<glm::vec2, glm::vec3> blockPos /*= {{}, {}}*/;

    int sizeSide = nBlockSide * Block::DIMBLOCK;
    blockPos.first.x = floor(pos.x / sizeSide);
    blockPos.first.y = floor(pos.z / sizeSide);
    blockPos.second.x = (int)floor(pos.x) % nBlockSide;
    blockPos.second.z = (int)floor(pos.z) % sizeSide;
    blockPos.second.y = (int)floor(pos.y);

    // TEST
    if(blockPos.second.x < 0)
        blockPos.second.x += nBlockSide;
    if(blockPos.second.z < 0)
        blockPos.second.z += nBlockSide;

    return blockPos;
}

void Player::breakBlock() {

    float multiplayer = intervalOfCheck;
    float maxDistance = maxNBlockInteract * Block::DIMBLOCK;
    while(glm::length((cameraFront * multiplayer)) <= maxDistance) {
        
        glm::vec3 blockCoord = cameraPos + (cameraFront * multiplayer);
        std::pair<glm::vec2, glm::vec3> blockPos = getBlockPos(blockCoord);
        if(w.isBlock(blockPos.first, blockPos.second)) {
            w.breakBlock(blockPos.first, blockPos.second);
            break;
        }

        multiplayer += intervalOfCheck;
    }
}

void Player::addBlock() {

    // KEEP track of the previous block and than calculate the dir (difference between the two blocks, the previuous and the final)

    float multiplayer = intervalOfCheck;
    float maxDistance = maxNBlockInteract * Block::DIMBLOCK;
    std::pair<glm::vec2, glm::vec3> previousBlock;
    while(glm::length((cameraFront * multiplayer)) <= maxDistance) {
        
        glm::vec3 blockCoord = cameraPos + (cameraFront * multiplayer);
        std::pair<glm::vec2, glm::vec3> blockPos = getBlockPos(blockCoord);

        if(w.isBlock(blockPos.first, blockPos.second)) {
            // for now only add sand
            w.addBlock(previousBlock.first, previousBlock.second, TypeOfBlock::SAND);
            break;
        }

        // can't do simple =, I have to make a deep copy
        previousBlock.first.x = blockPos.first.x;
        previousBlock.first.y = blockPos.first.y;

        previousBlock.second.x = blockPos.second.x;
        previousBlock.second.y = blockPos.second.y;
        previousBlock.second.z = blockPos.second.z;

        multiplayer += intervalOfCheck;

    }
}

/*
void Player::mouseScrollCb(GLFWwindow* window, double xoffset, double yoffset) {
    fov += (float)yoffset;
    if(fov < 1)
        fov = 1;
    if(fov > 45)
        fov = 45;
}
*/
        
#endif