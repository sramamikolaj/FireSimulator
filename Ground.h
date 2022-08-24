#ifndef GROUND_CLASS_H
#define GROUND_CLASS_H

#include<stb/stb_image.h>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include"VBO.h"
#include"shaderClass.h"
#include"VAO.h"
#include"String"

class Ground
{
private:
	Shader* shaderProgram;
	VAO VAO1;
	VBO* VBO1;
	GLfloat vertices[20][20][30];
	GLuint texture;

	void initArrays();
	void initTexture(const char* texPath);
public:
	Ground(const char* texture);
	~Ground();

	void activateShader();
	void update(); 
	void render(); 
	Shader* getShaderProgram() { return shaderProgram; }
};

#endif