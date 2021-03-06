#version 330 core
layout (location = 0) in vec3 aPos;

out vec4 vertexColor; // specify a color output to the fragment shader
  
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform vec4 color;

void main()
{
    gl_Position = projection * view * model * vec4(aPos, 5.0f);
	vertexColor = color; // set the color of the points
} 