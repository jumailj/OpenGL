#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

void main(void) {

	std::cout<< glfwInit() << std::endl;
	std::cout << glewInit() << std::endl;

	system("PAUSE");
}