#include <iostream>
//#define GL_SILENCE_DEPRECATION
#define GLFW_DLL
#include <GLFW/glfw3.h>
//#include <GLUT/glut.h>
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

    int major, minor, revision;
    glfwGetVersion(&major, &minor, &revision);

    // Output GLFW version number
    std::cout << "GLFW version: " << major << "." << minor << "." << revision << std::endl;

    GLFWwindow* window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Test window", NULL, NULL);
    glfwMakeContextCurrent(window);
    if (!window) {
        cout << "Error creating the window.\n";
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    
    glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
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