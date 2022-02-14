#ifndef CAMERA_H
#define CAMERA_H

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
        
        float deltaTime = 0.0f;
        float lastFrame = 0.0f;
        
        // mouse stuff
        float lastx = 400.0f;
        float lasty = 300.0f;
        float yaw = -90;
        float pitch = 0;
        
        float fov = 45.0f;
        
    public: 

        /**
         * Default up vector is the y normalized
         */
        Player(GLFWwindow* window, glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f));

        glm::mat4 inline getViewMatrix() const { return viewMatrix; };


        void processKeyInput(GLFWwindow* window);

        /**
         * Mouse movement callback
         */
        void mouseMovCb(GLFWwindow* window, double xpos, double ypos);

        /**
         * mouse scroll callback
         */
        static void mouseScrollCb(GLFWwindow* window, double xoffset, double yoffset);
        
        

};

#endif