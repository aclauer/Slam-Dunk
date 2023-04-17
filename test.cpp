#include <iostream>
#include <math.h>
#define GLFW_DLL
//#include <GL/glut.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <GL/gl.h>

using namespace std;

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 400;

int main() {
    cout << "Starting...\n";

    //GLFWwindow* window;

    if (!glfwInit()) {
        cout << "Error initializing glfw.";
        return -1;
    }

    if (!glewInit()) {
        cout << "Error initializing glew.";
        return -1;
    }

    int major, minor, revision;
    glfwGetVersion(&major, &minor, &revision);

    // Output GLFW version number
    //std::cout << "GLFW version: " << major << "." << minor << "." << revision << std::endl;

    cout << "Current version of GL\n";
    const GLubyte* version = glGetString(GL_VERSION);
    cout << version << "\n";

    cout << "Down here now \n";

    GLfloat vertices[] = {
        -0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f,
        0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f,
        0.0f, 0.5f * float(sqrt(3)) * 2 / 3, 0.0f
    };

    GLFWwindow* window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Test window", NULL, NULL);
    glfwMakeContextCurrent(window);
    if (!window) {
        cout << "Error creating the window.\n";
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    
    glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);

    // Controls color of test window
    glClearColor(0.50f, 0.13f, 0.17f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glfwSwapBuffers(window);

    while (!glfwWindowShouldClose(window)) {
        // Do stuff.

        glfwPollEvents();
    }

    cout << "Time to be done!\n";
    glfwTerminate();

    return 0;
}