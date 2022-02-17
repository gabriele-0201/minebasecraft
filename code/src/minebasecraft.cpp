#include "World.h"
#include "Player.h"
#include "GLC.h"
#include "Renderer.h"

Player* p = nullptr;

void mouseMovCbGeneral(GLFWwindow* window, double xpos, double ypos) {
    ASSERT(p)
    p -> mouseMovCb(xpos, ypos);
}

int main(void) {


    // Setting al the start stuff

    GLFWwindow* window;

    int winHeight = 480;
    int winWidth = 640 ;

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
    Player player {window};
    p = &player;

    Renderer renderer {world, player};

    // REMOVE in the future
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    
    glfwSetCursorPosCallback(window, mouseMovCbGeneral);
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
