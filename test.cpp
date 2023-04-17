#include <stdlib.h>
#include <iostream>
#define GL_SILENCE_DEPRECATION
#include <GLFW/glfw3.h>
#include <GLUT/glut.h>
//#include <OpenGL/gl3.h>
using namespace std;

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 400;

int main() {
    cout << "Starting...\n";

    int major, minor, revision;
    glfwGetVersion(&major, &minor, &revision);

    // Output GLFW version number
    std::cout << "GLFW version: " << major << "." << minor << "." << revision << std::endl;
    

    if (!glfwInit()) {
        cout << "Error initializing glfw.";
        return -1;
    }

    GLFWwindow* window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Test window", NULL, NULL);
    if (!window) {
        cout << "Error creating the window.\n";
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    
    glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    //glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
    //glClear(GL_COLOR_BUFFER_BIT);
    //glfwSwapBuffers(window);

    while (!glfwWindowShouldClose(window)) {
        // Do stuff.

        glfwPollEvents();
    }

    cout << "Time to be done!\n";
    glfwTerminate();
    return 0;
}