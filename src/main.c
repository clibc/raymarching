#include <stdio.h>
#include <stdlib.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "defs.h"

int main(void)
{
    GLFWwindow* window;

    if(!glfwInit()){
        ERROR("Failed to initialize glfw!");
        exit(-1);
    }

    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);

    if(!window){
        glfwTerminate();
        ERROR("Failed to create window!");
        exit(-1);
    }

    glfwMakeContextCurrent(window);

    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    
    glfwTerminate();
    return 0;
}
