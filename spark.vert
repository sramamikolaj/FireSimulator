#version 330 core
layout (location = 0) in vec3 aPos;

// Inputs the matrices needed for 3D viewing with perspective
uniform mat4 camMatrix;


void main()
{
   gl_Position = camMatrix * vec4(aPos, 1.0);
}