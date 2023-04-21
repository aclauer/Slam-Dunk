#include <iostream>
#include <math.h>
#define GLFW_DLL
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <GL/gl.h>

#include"resources/shaderClass.h"
#include"resources/VBO.h"
#include"resources/VAO.h"
#include"resources/EBO.h"

using namespace std;

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 400;

int main() {
    cout << "Starting...\n";

    // Initialize glfw
    if (!glfwInit()) {
        cout << "Error initializing glfw.";
        return -1;
    }

    GLfloat vertices[] = {
        -0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f,
        0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f,
        0.0f, 0.5f * float(sqrt(3)) * 2 / 3, 0.0f,
        -0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f,
        0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f,
        0.0f, -0.5f * float(sqrt(3)) / 3, 0.0f,
    };

    GLuint indices[] = {
        0, 3, 5,
        3, 2, 4,
        5, 4, 1
    };

    // Create and check window
    GLFWwindow* window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Test window", NULL, NULL);
    if (!window) {
        cout << "Error creating the window.\n";
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    // Initilize glew
    if (glewInit() != GLEW_OK) {
        cout << "Problem initializing glew\n";
        return -1;
    }

    glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    
    Shader shaderProgram("shaders/default.vert", "shaders/default.frag");
    
    VAO VAO1;
    VAO1.Bind();

    VBO VBO1(vertices, sizeof(vertices));
    EBO EBO1(indices, sizeof(indices));

    VAO1.LinkVBO(VBO1, 0);
    VAO1.Unbind();
    VBO1.Unbind();
    EBO1.Unbind();

    // Color in the test window.
    glClearColor(0.0f, 0.13f, 0.17f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glfwSwapBuffers(window);

    // main loop
    while (!glfwWindowShouldClose(window)) {
        //printf("In main loop\n");
        glClearColor(0.50f, 0.13f, 0.17f, 1.0f);
        //printf("1\n");
        glClear(GL_COLOR_BUFFER_BIT);
        //printf("2\n");
        shaderProgram.Activate();
        //printf("3\n");
        VAO1.Bind();
        //printf("4\n");
        glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);
        //printf("5\n");

        glfwSwapBuffers(window);
        //printf("6\n");
        glfwPollEvents();
    }
    
    VAO1.Delete();
    VBO1.Delete();
    EBO1.Delete();
    shaderProgram.Delete();

    cout << "Time to be done!\n";
    glfwTerminate();

    return 0;
}
