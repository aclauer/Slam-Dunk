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
/*
std::string get_file_contents(const char* filename) {
    std::ifstream file(filename, std::ios::binary);

    if (!file) {
        throw std::runtime_error("Unable to open file: " + std::string(filename) + "\n");
    }

    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}
*/

/*
std::string get_file_contents(const char* path) {
    // Open the file in binary mode
    std::ifstream file(path, std::ios::binary);
    printf("%s\n", path);

    // Check if the file was opened successfully
    if (!file) {
        throw std::runtime_error("Failed to open file");
    }

    // Read the contents of the file into a stringstream
    std::stringstream ss;
    ss << file.rdbuf();

    // Convert the stringstream to a string and return it
    return ss.str();
}
*/

/*
std::string get_file_contents(const char* path) {
    // Open the file in read-only mode with the O_BINARY flag
    int fd = open(path, O_RDONLY);

    // Check if the file was opened successfully
    if (fd == -1) {
        throw std::runtime_error("Failed to open file");
    }

    // Get the size of the file
    off_t size = lseek(fd, 0, SEEK_END);
    lseek(fd, 0, SEEK_SET);

    // Allocate a buffer to hold the file contents
    char* buffer = new char[size];

    // Read the contents of the file into the buffer
    ssize_t bytes_read = read(fd, buffer, size);

    // Check if the file was read successfully
    if (bytes_read == -1) {
        close(fd);
        delete[] buffer;
        throw std::runtime_error("Failed to read file");
    }

    // Close the file descriptor
    close(fd);

    // Convert the buffer to a string and return it
    std::string contents(buffer, bytes_read);
    delete[] buffer;
    return contents;
}
*/

std::string get_file_contents(const char* filename)
{
	std::ifstream in(filename, std::ios::binary);
	if (in)
	{
		std::string contents;
		in.seekg(0, std::ios::end);
		contents.resize(in.tellg());
		in.seekg(0, std::ios::beg);
		in.read(&contents[0], contents.size());
		in.close();
		return(contents);
	}
    printf("Throwing error thingy.\n");
	throw(errno);
}

// Shader constructor
Shader::Shader(const char* vertexFile, const char* fragmentFile) {
    printf("Shader1\n");
    // TODO: For some reason get_file_contents is not working, hard code for now.
    std::string vertexCode = get_file_contents(vertexFile);
    printf("Shader here??\n");
    std::string fragmentCode = get_file_contents(fragmentFile);

    printf("Shader2\n");
    const char* vertexSource = vertexCode.c_str();
    const char* fragmentSource = fragmentCode.c_str();


/*
    const char* vertexCode = "#version 330 core\n"
        "layout (location = 0) in vec3 aPos;\n"
        "void main()\n"
        "{\n"
        "   gl_Position = vec4(aPos.x, aPos.y, aPos.Z, 1.0);\n"
        "}\n";

    const char* fragmentCode = "#version 330 core\n"
        "out vec4 FragColor;\n"
        "void main()\n"
        "{\n"
        "    FragColor = vec4(0.8f, 0.3f, 0.02f, 1.0f);\n"
        "}\n";
*/        

    printf("Shader3\n");
    // Create vertex shader object with corresponding source code
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexSource, NULL);
    //glShaderSource(vertexShader, 1, &vertexCode, NULL);

    glCompileShader(vertexShader);

    printf("Shader4\n");
    // Create fragment shader object with corresponding source code
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
    //glShaderSource(fragmentShader, 1, &fragmentCode, NULL);

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