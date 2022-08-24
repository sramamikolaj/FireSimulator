#ifndef VBO_CLASS_H
#define VBO_CLASS_H

#include<glad/glad.h>

class VBO
{
public:
	VBO(GLfloat* vertices, GLsizeiptr size);

	GLuint ID;

	void Bind();
	void Unbind();
	void Delete();
};

#endif