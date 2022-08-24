#include"VAO.h"

//Constructor
VAO::VAO()
{
	glGenVertexArrays(1, &ID);
}

//Link VBO
void VAO::LinkVBO(VBO& VBO, GLuint layout)
{
	VBO.Bind();
	glVertexAttribPointer(layout, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(layout);
	VBO.Unbind();
}

//Link VBO with attribute
void VAO::LinkAttrib(VBO& VBO, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, void* offset)
{
	VBO.Bind();
	glVertexAttribPointer(layout, numComponents, type, GL_FALSE, stride, offset);
	glEnableVertexAttribArray(layout);
	VBO.Unbind();
}

//Bind VAO
void VAO::Bind()
{
	glBindVertexArray(ID);
}

//Unbind VAO
void VAO::Unbind()
{
	glBindVertexArray(0);
}

//Delete VAO
void VAO::Delete()
{
	glDeleteVertexArrays(1, &ID);
}