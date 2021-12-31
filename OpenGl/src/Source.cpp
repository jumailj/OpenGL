#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "Renderer.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"



void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

struct ShaderProgramSource {
    std::string vertexShource;
    std::string fragmentSource;
};

static ShaderProgramSource ParseShader(const std::string& filePath) {

    std::ifstream stream(filePath);
    std::string line;
    std::stringstream ss[2];

    enum class ShaderType {
        NONE = -1, VERTEX = 0, FRAGMENT = 1
    };
    ShaderType type = ShaderType::NONE;

    while (std::getline(stream, line)) 
    {
        if (line.find("#shader") != std::string::npos) 
        {
            if (line.find("vertex") != std::string::npos) 
            {
                type = ShaderType::VERTEX;

            }
            else if (line.find("fragment") != std::string::npos) 
            {
                type = ShaderType::FRAGMENT;
            }
        }
        else 
        {
            ss[(int)type] << line << '\n';

        }

    }

    return { ss[0].str(), ss[1].str() };
}


static unsigned int CompileShader( unsigned int type,const std::string& source) {

    unsigned int id = glCreateShader(type);
    const char* src = source.c_str();
    glShaderSource(id, 1, &src, NULL);
    glCompileShader(id); 
    
    // error hadling...
    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    if ( result == GL_FALSE) {

        int lenght;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &lenght);
        char* message = (char*)malloc(lenght * sizeof(char));
        glGetShaderInfoLog(id, lenght, &lenght, message);

       // logger::GetCoreLogger()->error("{0} FAILD TO COMPILE: {1}", (type == GL_VERTEX_SHADER) ? "[VERTEX SHADER]" : "[FRAGMENT SHADER]", message);


        glDeleteShader(id);
        return 0;
    }

    return id;
}

static unsigned int ShaderCreate(const std::string& vertexShader, const std::string& fragmentShader) {

    unsigned int program = glCreateProgram();

    unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
    unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);

    glValidateProgram(program);

    // delete shader. / * detach shader * / DEBUG purpose.
    glDeleteShader(vs);
    glDeleteShader(fs);

    return program;
}


int main()
{

    //logger::Init(); // initilizing logger;

    if (!glfwInit()) {
        std::cout << " glew not init" << std::endl;
    }
    else {
      //logger::GetCoreLogger()->info("GLFW INIT");
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE); // COMPAT VERSION;

    glfwSwapInterval(1);


    GLFWwindow* window = glfwCreateWindow(800,600, "OpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
        }   
        else
        {

       //logger::GetCoreLogger()->info("GLFW WINDOW CREATED");

        }


    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);// gladInit();


    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }
    else {
       //logger::GetCoreLogger()->info("GLAD INIT");
    }

    // build and compile our shader program
// ------------------------------------
// vertex shader
    //unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    //glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    //glCompileShader(vertexShader);


    //// fragment shader
    //unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    //glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    //glCompileShader(fragmentShader);


    //// link shaders
    //unsigned int shaderProgram = glCreateProgram();
    //glAttachShader(shaderProgram, vertexShader);
    //glAttachShader(shaderProgram, fragmentShader);
    //glLinkProgram(shaderProgram);


    //glDeleteShader(vertexShader);
    //glDeleteShader(fragmentShader);


    /*
    float vertices[] = {
         0.5f,  0.5f, 0.0f, // left
         0.5f, -0.5f, 0.0f, // right
        -0.0f,  0.5f, 0.0f,  // top
         // second triangle
         0.5f, -0.5f, 0.0f,
        -0.5f, -0.5f, 0.0f,
        -0.5f,  0.5f, 0.0f
    };
    */
    {
        float positions[] = {
            0.5f, 0.5f, 0.0f,
            0.5f,-0.5f, 0.0f,
           -0.5f,-0.5f, 0.0f,
           -0.5f, 0.5f, 0.0f
        };

        unsigned int indices[] = {
             0,1,3,
             1,2,3
        };



        unsigned int VAO;

        // vertex array;
        GLCall(glGenVertexArrays(1, &VAO));
        GLCall(glBindVertexArray(VAO));

        // verter buffer);
        VertexBuffer VB(positions, sizeof(float) * 4 * 3);

        GLCall(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0));
        GLCall(glEnableVertexAttribArray(0));

        // index buffer)
        IndexBuffer IB(indices, 6);



        // vertex and fragment shader;
        ShaderProgramSource source = ParseShader("res/shaders/Basic.shader");
        unsigned int shader = ShaderCreate(source.vertexShource, source.fragmentSource);
        GLCall(glUseProgram(shader));

        int location = glGetUniformLocation(shader, "u_Color");
        ASSERT(location != -1);



        GLCall(glBindVertexArray(0));
        GLCall(glUseProgram(0));
        GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
        GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));



        float r = 0.0f;
        float increment = 0.05f;

        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        while (!glfwWindowShouldClose(window))
        {
            processInput(window);

            GLCall(glClear(GL_COLOR_BUFFER_BIT));


            GLCall(glUseProgram(shader));
            GLCall(glClearColor(0.2f, 0.3f, 0.3f, 1.0f));


            GLCall(glBindVertexArray(VAO));

            IB.Bind();


            glUniform4f(location, r, 0.3f, 0.8f, 1.0f);
            GLCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0)); // spcificing index data. (not vertex buffer);

            if (r > 1.0f)
                increment = -0.05f;
            else if (r < 0.0f)
                increment = 0.05f;

            r += increment;




            //  float timeValue = glfwGetTime();
            //  float greenValue = sin(timeValue) / 2.0f + 0.5f;
            //  int vertexContolrLocation = glGetUniformLocation(shader, "ourColor");
            //  GLCall(glUniform4f(vertexContolrLocation, 0.3f, greenValue, 0.7f, 1.0f));




            glfwSwapBuffers(window);
            glfwPollEvents();
        }


        GLCall(glDeleteVertexArrays(1, &VAO));
        // GLCall(glDeleteBuffers(1, &buffer));
        GLCall(glDeleteProgram(shader));


        glfwDestroyWindow(window);

        glfwTerminate();

    }

    return 0;
}


void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}



void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}