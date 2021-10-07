#include <stdio.h>
#include <stdlib.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "defs.h"
#include "shader.hpp"
#include "objs.hpp"

void handle_input(GLFWwindow* window, int key, int scancode, int action, int mods);

int main(void)
{
    GLFWwindow* window;

    if(!glfwInit()){
        ERROR("Failed to initialize GLFW!");
        exit(-1);
    }

    window = glfwCreateWindow(640, 640, "Hello World", NULL, NULL);

    if(!window){
        ERROR("Failed to create window!");
        glfwTerminate();
        exit(-1);
    }

    glfwMakeContextCurrent(window);
    glfwSetKeyCallback(window, handle_input);

    GLenum err = glewInit();
    if(err != GLEW_OK){
        ERROR("Failed to initialize GLEW!");
        glfwTerminate();
        exit(-1);
    }

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
    
    GLuint vbo_vert = 0;
    glGenBuffers(1, &vbo_vert);
    glBindBuffer(GL_ARRAY_BUFFER, vbo_vert);
    glBufferData(GL_ARRAY_BUFFER, 18 * sizeof(float), quad_vertices, GL_STATIC_DRAW);

    GLuint vbo_texture = 0;
    glGenBuffers(1, &vbo_texture);
    glBindBuffer(GL_ARRAY_BUFFER, vbo_texture);
    glBufferData(GL_ARRAY_BUFFER, 12 * sizeof(float), quad_tex_coords, GL_STATIC_DRAW);
    
    GLuint quad_shader = create_shader("./src/shaders/test_vertex.shader",
                                       "./src/shaders/test_fragment.shader");

    glUseProgram(quad_shader);
    
    while (!glfwWindowShouldClose(window))
    {
        glClearColor(1.0f, 0.0f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, vbo_vert);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

        glEnableVertexAttribArray(1);
        glBindBuffer(GL_ARRAY_BUFFER, vbo_texture);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);

        glDrawArrays(GL_TRIANGLES, 0, 6);

        glDisableVertexAttribArray(0);
        glDisableVertexAttribArray(1);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

void handle_input(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    (void)window;
    (void)scancode;
    (void)mods;

    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS){
        glfwTerminate();
        exit(0);
    }
}
