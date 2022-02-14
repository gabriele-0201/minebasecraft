#include "World.h"
//#include "GLC.h"

int main(void) {

    /*
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    glfwSetCursorPosCallback(window, func);
    glfwSetScrollCallback(window, Camera::mouseScrollCb);
    */

    // Setting al the start stuff

    GLFWwindow* window;

    World world {window, 1};

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


    /* Loop until the user closes the window */
    // GameLoop
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        GLCall(glClear(GL_COLOR_BUFFER_BIT));

        shader.bind();
        //shader.setUnifor4f("uColor", r, 0.0f, 0.0f, 0.5f);

        renderer.draw(va, ib, shader);

        if(r > 1.0f)
            incr *= -1;
        else if(r < 0.0f)
            incr *= -1;

        r += incr;

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
