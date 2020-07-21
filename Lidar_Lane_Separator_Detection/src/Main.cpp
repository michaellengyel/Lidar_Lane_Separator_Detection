#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include "IOHandler.h"
#include "Scan.h"
#include "Preprocessor.h"
#include "Detector.h"
#include "Visualization.h"

#include "../vendor/GLM/glm/glm.hpp"
#include "../vendor/GLM/glm/gtc/matrix_transform.hpp"
#include "../vendor/GLM/glm/gtc/type_ptr.hpp"

const char *vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";

int main() {

	// Declaring data container and handling classes
	IOHandler ioHandler("res/1.csv");
	Scan scan;

	// Declaring data processing classes
	Preprocessor preprocessor(scan, ioHandler);
	Detector detector(scan);
	detector.algorithm();

	// Declaring data and results visualization classes
	Visualization visualization(scan);

	// ********** Start of GLFW test code **********

	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit())
		return -1;

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(640, 480, "LSD Visulization", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	// Calling glewInit(must be after valid glfw rendering context)
	GLenum err = glewInit();
	if (GLEW_OK != err)
	{
		/* Problem: glewInit failed, something is seriously wrong. */
		fprintf(stderr, "Error: %s\n", glewGetErrorString(err));

	}

	float vertices[] = {
		-0.5f, -0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
		0.0f,  0.5f, 0.0f
	};

	unsigned int VBO;
	glGenBuffers(1, &VBO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	unsigned int vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);



	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		/* Set background color to white */
		glClearColor(0.0f, 0.0f, 0.0, 1.0f);

		/* Render here */
		glClear(GL_COLOR_BUFFER_BIT);

		visualization.render(scan);


		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}

	glfwTerminate();

	// ********** End of GLFW test code **********


	return 0;
}