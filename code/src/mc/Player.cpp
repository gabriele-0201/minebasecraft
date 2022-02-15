#ifndef PLAYER_CPP
#define PLAYER_CPP

#include "Player.h"

Player::Player(GLFWwindow* window, glm::vec3 up) {

    cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
    cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
    cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
        
    deltaTime = 0.0f;
    lastFrame = 0.0f;
        
    lastx = 400.0f;
    lasty = 300.0f;
    yaw = -90;
    pitch = 0;
}

void Player::processKeyInput(GLFWwindow* window) {

    float cameraSpeed = 2.5f * deltaTime; 
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        cameraPos += cameraSpeed * cameraFront;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        cameraPos -= cameraSpeed * cameraFront;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;

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