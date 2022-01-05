#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "Renderer.h"

#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
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



        VertexBuffer vb(positions, sizeof(float) * 4 * 3);
        VertexArray va;

        VertexBufferLayout layout;
        layout.Push<float>(3);


        va.AddBuffer(vb,layout);
        IndexBuffer ib(indices, 6);


        Shader shader("res/shaders/Basic.shader");
        shader.SetUniform4f("u_Color", 0.8f, 0.3f, 0.8f, 1.0f);


        va.UnBind();
        shader.UnBind();
        vb.UnBind();
        ib.UnBind();


        Renderer renderer;

        float r = 0.0f;
        float increment = 0.05f;

        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        while (!glfwWindowShouldClose(window))
        {
            processInput(window);

            renderer.Clear();
            shader.Bind();
            shader.SetUniform4f("u_Color", r , 0.3f, 0.3f, 1.0f);
       
            renderer.Draw(va,ib,shader);

            if (r > 1.0f)
                increment = -0.05f;
            else if (r < 0.0f)
                increment = 0.05f;

            r += increment;


            glfwSwapBuffers(window);
            glfwPollEvents();
        }


        glfwDestroyWindow(window);
        glfwTerminate();

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