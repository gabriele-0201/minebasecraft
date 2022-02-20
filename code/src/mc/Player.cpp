#ifndef PLAYER_CPP
#define PLAYER_CPP

#include "Player.h"

Player::Player(GLFWwindow* window, World& _w, glm::vec3 up) : w{_w}{

    cameraPos = glm::vec3(0.0f, 10.0f, 0.0f);
    cameraFront = glm::vec3(0.0f, 0.0f, 1.0f);
    cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
        
    speed = 3.0f;
    deltaTime = 0.0f;
        
    lastx = 400.0f;
    lasty = 300.0f;
    yaw = 0;
    pitch = 0;

    intervalOfCheck = 0.1;
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
}

void Player::setDeltaTime (float t) {
    deltaTime = t;
}

float Player::getDeltaTime() {
    return deltaTime;
}

void Player::breakBlock() {

    float multiplayer = intervalOfCheck;
    float maxDistance = 6 * Block::DIMBLOCK;
    while(glm::length((cameraFront * multiplayer)) <= maxDistance) {
        
        glm::vec3 blockPos = cameraPos + (cameraFront * multiplayer);
        if(w.isBlock(blockPos)) {
            w.breakBlock(blockPos);
            break;
        }

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