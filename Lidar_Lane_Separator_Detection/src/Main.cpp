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

	// Making projection Matrix
	glm::mat4 projection = glm::ortho(-2.0f, 2.0f, -1.5f, 1.5f, -1.0f, 1.0f);


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