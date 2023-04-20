#include <iostream>
#include <math.h>
#define GLFW_DLL
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <GL/gl.h>

using namespace std;

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 400;

const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.Z, 1.0);\n"
"}\0";

int main() {
    cout << "Starting...\n";

    // Initialize glfw
    if (!glfwInit()) {
        cout << "Error initializing glfw.";
        return -1;
    }

    //int major, minor, revision;
    //glfwGetVersion(&major, &minor, &revision);

    GLfloat vertices[] = {
        -0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f,
        0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f,
        0.0f, 0.5f * float(sqrt(3)) * 2 / 3, 0.0f
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

    //const GLubyte* version = glGetString(GL_VERSION);
    //printf("OpenGL Version: %s\n", version);

    glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glLinkProgram(shaderProgram);

    glDeleteShader(vertexShader);

    GLuint VAO, VBO;

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);



    // Color in the test window.
    glClearColor(0.0f, 0.13f, 0.17f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glfwSwapBuffers(window);

    while (!glfwWindowShouldClose(window)) {
        // Do stuff.
        glClearColor(0.50f, 0.13f, 0.17f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    cout << "window should close\n";

    cout << "Time to be done!\n";
    glfwTerminate();

    return 0;
}
