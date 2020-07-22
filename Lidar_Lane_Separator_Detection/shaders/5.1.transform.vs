#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;

out vec2 TexCoord;
out vec4 vertexColor; // specify a color output to the fragment shader
  
uniform mat4 transform;

void main()
{
    gl_Position = transform * vec4(aPos, 1.0f);
    TexCoord = vec2(aTexCoord.x, aTexCoord.y);
	vertexColor = vec4(0.5, 0.0, 0.0, 1.0); // set the output variable to a dark-red color
} 