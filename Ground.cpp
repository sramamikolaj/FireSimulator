#include "Ground.h"



Ground::Ground(int w, int h)
{
	windowHeight = h;
	windowWidth = w;
	VAO1.Bind();
	initArrays();
	VBO1 = new VBO(vertices, sizeof(vertices));
	VAO1.LinkVBO(*VBO1, 0);
	shaderProgram = new Shader("default.vert", "default.frag");
}

Ground::~Ground()
{
	VBO1->Delete();
	VAO1.Delete();
	shaderProgram->Delete();
}

void Ground::initArrays()
{
	GLfloat values[] =
	{
		20.0f, 0, -10.0f, // Lower left corner
		-20.0f, 0, -10.0f, // Lower right corner
		10.5f, 0, 10.0f // Upper corner
	};
	std::copy(values, values + 9, vertices);
}

void Ground::activateShader()
{
	shaderProgram->Activate();
}

void Ground::update()
{
}

void Ground::render()
{
	VAO1.Bind();

	int vertexColorLocation = glGetUniformLocation(shaderProgram->ID, "ourColor");
	glUniform4f(vertexColorLocation, 0.18f, 0.35f, 0.18f, 1.0f);

	glDrawArrays(GL_TRIANGLES, 0, 3);
}
