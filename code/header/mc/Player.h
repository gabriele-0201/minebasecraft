#ifndef PLAYER_H
#define PLAYER_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <GLFW/glfw3.h>

class Player {

    private:

        glm::mat4 viewMatrix;

        glm::vec3 cameraPos;
        glm::vec3 cameraFront;
        glm::vec3 cameraUp;
        
        float speed;
        float deltaTime;
        
        // mouse stuff
        float lastx;
        float lasty;
        float yaw;
        float pitch;
        
        
    public: 

        const float fov = 45.0f;

        /**
         * Default up vector is the y normalized
         */
        Player(GLFWwindow* window, glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f));

        glm::mat4 inline getViewMatrix() const { return viewMatrix; };

        void processKeyInput(GLFWwindow* window);

        /**
         * Mouse movement callback
         */
        void mouseMovCb(double xpos, double ypos);

        void setDeltaTime(float t);
        float getDeltaTime();

        /**
         * mouse scroll callback
         */
        //void mouseScrollCb(GLFWwindow* window, double xoffset, double yoffset);
        
        

};

#endif