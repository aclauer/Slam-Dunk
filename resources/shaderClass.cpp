#include"shaderClass.h"

// Function that reads in source code from file.
/*
std::string get_file_contents(const char* filename) {
    printf("File contents\n");
    std::ifstream in(filename, std::ios::binary);
    printf("F1\n");
    if (in) {
        printf("F2\n");
        std::string contents;
        in.seekg(0, std::ios::end);
        printf("F3\n");
        contents.resize(in.tellg());
        in.seekg(0, std::ios::beg);
        printf("F4\n");
        in.read(&contents[0], contents.size());
        printf("F5\n");
        in.close();
        return(contents);
    }
    throw(errno);
}
*/

std::string get_file_contents(const char* filename) {
    std::ifstream file(filename, std::ios::binary);

    if (!file) {
        throw std::runtime_error("Unable to open file: " + std::string(filename) + "\n");
    }

    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

// Shader constructor
Shader::Shader(const char* vertexFile, const char* fragmentFile) {
    printf("Shader1\n");
    std::string vertexCode = get_file_contents(vertexFile);
    printf("Shader here??\n");
    std::string fragmentCode = get_file_contents(fragmentFile);

    printf("Shader2\n");
    const char* vertexSource = vertexCode.c_str();
    const char* fragmentSource = fragmentCode.c_str();

    printf("Shader3\n");
    // Create vertex shader object with corresponding source code
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexSource, NULL);
    glCompileShader(vertexShader);

    printf("Shader4\n");
    // Create fragment shader object with corresponding source code
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
    glCompileShader(fragmentShader);

    printf("Shader5\n");
    ID = glCreateProgram();
    glAttachShader(ID, vertexShader);
    glLinkProgram(ID);

    printf("Shader6\n");
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    printf("Shader7\n");
}

void Shader::Activate() {
    glUseProgram(ID);
}

void Shader::Delete() {
    glDeleteProgram(ID);
}