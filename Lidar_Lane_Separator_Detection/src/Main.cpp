#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include "IOHandler.h"
#include "Scan.h"
#include "Preprocessor.h"
#include "Detector.h"
#include "Visualization.h"

#include "Shader.h"

#include "../vendor/GLM/glm/glm.hpp"
#include "../vendor/GLM/glm/gtc/matrix_transform.hpp"
#include "../vendor/GLM/glm/gtc/type_ptr.hpp"

void processInput(GLFWwindow *window);

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

	// Calling glewInit (must be after valid glfw rendering context)
	GLenum err = glewInit();
	if (GLEW_OK != err)
	{
		/* Problem: glewInit failed, something is seriously wrong. */
		fprintf(stderr, "Error: %s\n", glewGetErrorString(err));

	}

	// build and compile our shader zprogram
	// ------------------------------------
	Shader ourShader("shaders/5.1.transform.vs", "shaders/5.1.transform.fs");
	
	/* Creating vertex shader */
	float vertices[] = {
		-1.0f, 0.0f, 0.0f,
		0.5f, -0.5f, 0.0f,
		0.0f,  0.5f, 0.0f,
		0.34, -0.11, 0.01,
		-0.5, 0.7, -0.9,
		-0.8, 0.5, 0,
		0.3, 0.3, 0.2,
		-0.2, 0.7, 0.32,
		0.28, -0.53, 0.25,
		0.93, 0.33, 0.52,
		-0.35, 0.17, -0.19,
		0.48, -0.85, -0.18,
		-0.28, 0.57, 0,
		0.93, -0.33, 0.82,
		-0.42, -0.7, 0.32,
		0.28, -0.53, 0.25,
		0.53, 0.3, -0.52,
	};

	unsigned int VBO, VAO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// texture coord attribute
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	/* Adding use of shaders */
	ourShader.use();

	/* Handling maths */
	glm::vec4 vec(1.0f, 0.0f, 0.0f, 1.0f);
	glm::mat4 trans = glm::mat4(1.0f);
	trans = glm::translate(trans, glm::vec3(1.0f, 1.0f, 0.0f));
	vec = trans * vec;
	std::cout << vec.x << vec.y << vec.z << std::endl;

	//glm::mat4 trans = glm::mat4(1.0f);
	trans = glm::rotate(trans, glm::radians(90.0f), glm::vec3(0.0, 0.0, 1.0));
	trans = glm::scale(trans, glm::vec3(0.5, 0.5, 0.5));

	unsigned int transformLoc = glGetUniformLocation(ourShader.ID, "transform");
	glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{

		// input
		// -----
		processInput(window);

		/* Set background color to white */
		glClearColor(0.8f, 0.8f, 0.8, 1.0f);

		/* Render here */
		glClear(GL_COLOR_BUFFER_BIT);

		//visualization.render(scan);


		// create transformations
		glm::mat4 transform = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
		transform = glm::translate(transform, glm::vec3(0.5f, -0.5f, 0.0f));
		transform = glm::rotate(transform, (float)glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f));

		// get matrix's uniform location and set matrix
		ourShader.use();
		unsigned int transformLoc = glGetUniformLocation(ourShader.ID, "transform");
		glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));

		// render container
		glBindVertexArray(VAO);
		glPointSize(5);
		glDrawArrays(GL_POINTS, 0, 90); // <- Set Number of points to be rendered from VAO here

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}

	glfwTerminate();

	// ********** End of GLFW test code **********


	return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}