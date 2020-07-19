#include <iostream>

#include "IOHandler.h"
#include "Scan.h"
#include "Preprocessor.h"
#include "Detector.h"
#include "Visualization.h"

#include <GLFW/glfw3.h>

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
	window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		/* Render here */
		glClear(GL_COLOR_BUFFER_BIT);

		glBegin(GL_TRIANGLES);
		glVertex2f(-0.5f, -0.5f);
		glVertex2f(0.0f, 0.5f);
		glVertex2f(0.5f, -0.5f);
		glEnd();

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}

	glfwTerminate();

	// ********** End of GLFW test code **********


	return 0;
}