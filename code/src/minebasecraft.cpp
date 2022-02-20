#include "World.h"
#include "Player.h"
#include "GLC.h"
#include "Renderer.h"

Player* p = nullptr;
Renderer* r = nullptr;

void mouseMovCbGeneral(GLFWwindow* window, double xpos, double ypos) {
    ASSERT(p)
    p -> mouseMovCb(xpos, ypos);
}

void mouseButtonCbGeneral(GLFWwindow* window, int button, int action, int mods) {
    //if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS)
        //p -> addBlock();
    /*else*/ if(button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
        p -> breakBlock();
}

void winSizeCbGeneral(GLFWwindow* window, int width, int height) {
    ASSERT(r);
    r -> winSizeCb(width, height);

}

void keyCb(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_H && action == GLFW_PRESS)
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    if (key == GLFW_KEY_V && action == GLFW_PRESS)
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
}

int main(void) {

    // Setting al the start stuff

    GLFWwindow* window;

    int winHeight = 900;
    int winWidth = 1200 ;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(winWidth, winHeight, "MineBaseCraft", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    /* Adjust the update time of the screen */
    glfwSwapInterval(1);

    //Have to call this before all to make possible the call to openGL
    GLenum err = glewInit();
    if (GLEW_OK != err)
    {
      /* Problem: glewInit failed, something is seriously wrong. */
      std::cout << "Error " << glewGetErrorString(err) <<std::endl;
    }

    // THOSE maybe will go in the RENDERER

    World world {window, 1};
    Player player {window, world};
    p = &player;

    Renderer renderer {world, player};
    r = &renderer;

    // REMOVE in the future
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    
    // SET UP the callbacks
    glfwSetCursorPosCallback(window, mouseMovCbGeneral);
    glfwSetMouseButtonCallback(window, mouseButtonCbGeneral);
    glfwSetWindowSizeCallback(window, winSizeCbGeneral);
    glfwSetKeyCallback(window, keyCb);

    //glfwSetScrollCallback(window, mouseMovCb);

    glEnable(GL_DEPTH_TEST);
    float lastFrame = 0.0f;

    //glewExperimental = GL_TRUE; 
    //glewInit();


    /* Loop until the user closes the window */
    // GameLoop

    while (!glfwWindowShouldClose(window))
    {
        float currentTime = glfwGetTime();
        player.setDeltaTime(currentTime - lastFrame);
        lastFrame = currentTime;

        /* Render here */
        GLCall(glClearColor(0.0f, 0.2f, 0.2f, 1.0f));
        GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));

        player.processKeyInput(window);
        //shader.setUnifor4f("uColor", r, 0.0f, 0.0f, 0.5f);

        renderer.draw();

        /* Swap front and back buffers */
        GLCall(glfwSwapBuffers(window));

        /* Poll for and process events */
        GLCall(glfwPollEvents());
    }

    glfwTerminate();
    //closing the openGL contex will make returning error from the get error of openGL
    /*
    To solve the problem I can create a false scope using { ... }
    So the variable ..Buffer is create in the scope e the distructor is 
    called when exit the scope, so BEFORE terminate the openGL context
    */
    return 0;


    // Close all the stuff

}
