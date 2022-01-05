#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "Renderer.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"


void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);






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



        // verter buffer);

        // vertex array;
        VertexBuffer vb(positions, sizeof(float) * 4 * 3);

        VertexArray va;

        VertexBufferLayout layout;
        layout.Push<float>(3);

        va.AddBuffer(vb,layout);


        // index buffer)
        IndexBuffer ib(indices, 6);


        Shader shader("res/shaders/Basic.shader");
        shader.Bind();
        shader.SetUniform4f("u_Color", 0.8f, 0.3f, 0.8f, 1.0f);



        va.UnBind();
        shader.UnBind();

        vb.UnBind();
        vb.UnBind();



        float r = 0.0f;
        float increment = 0.05f;

        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        while (!glfwWindowShouldClose(window))
        {
            processInput(window);

            GLCall(glClear(GL_COLOR_BUFFER_BIT));


            shader.Bind();
            shader.SetUniform4f("u_Color", r , 0.3f, 0.3f, 1.0f);

  
            va.Bind();
            ib.Bind();
            


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


        glfwDestroyWindow(window);
        glfwTerminate();


    std::cout << " calling exit" << std::endl;
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