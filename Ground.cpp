#include "Ground.h"

//Constructor - values initialiation and call of other init unctions
Ground::Ground(const char* texture)
{
	VAO1.Bind();
	initArrays();
	initTexture(texture);
	shaderProgram = new Shader("Resources/Shaders/default.vert", "Resources/Shaders/default.frag");
}

//Destructor - delete components
Ground::~Ground()
{
	VBO1->Delete();
	VAO1.Delete();
	shaderProgram->Delete();
	glDeleteTextures(1, &texture);
}

//Initialize texture that will be use to ground square - whole ground is made out of man squares
void Ground::initTexture(const char* texPath) {
	int widthImg, heightImg, numColCh;
	unsigned char* bytes = stbi_load(texPath, &widthImg, &heightImg, &numColCh, 0);
	glGenTextures(1, &texture);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, widthImg, heightImg, 0, GL_RGB, GL_UNSIGNED_BYTE, bytes);
	glGenerateMipmap(GL_TEXTURE_2D);
	stbi_image_free(bytes);
}

//Initialize array of vertices (vertices + texture coordinates) of squares that make ground 
void Ground::initArrays()
{
	for (int i = 0; i < 20; i++)
	{
		for (int j = 0; j < 20; j++)
		{
			float xOffset = 0.2 * float(i) - 2.0f;
			float yOffset = 0.2 * float(j) - 2.0f;
			GLfloat values[] =
			{
				0.1f+ xOffset, 0, -0.1f + yOffset,	 1.0f, 0.0f,
				-0.1f+ xOffset, 0, -0.1f + yOffset,	 0.0f, 0.0f, 
				0.1f+ xOffset, 0, 0.1f + yOffset,	 1.0f, 1.0f,
				-0.1f+ xOffset, 0, 0.1f + yOffset,	 0.0f, 1.0f,
				-0.1f+ xOffset, 0, -0.1f + yOffset,	 0.0f, 0.0f, 
				0.1f+ xOffset, 0, 0.1f + yOffset,	 1.0f, 1.0f
			};
			std::copy(values, values + 30, vertices[i][j]);
		}
	}
}

//Activate ground shader
void Ground::activateShader()
{
	shaderProgram->activate();
}

//No updates needed for ground
void Ground::update()
{
}

//Render all ground squares
void Ground::render()
{
	activateShader();
	GLuint tex0Uni = glGetUniformLocation(shaderProgram->ID, "tex0");
	for (int j = 0; j < 20; j++)
	{
		for (int i = 0; i < 20; i++)
		{
			VAO1.Bind();
			VBO1 = new VBO(vertices[i][j], sizeof(vertices[i][j]));
			VAO1.LinkAttrib(*VBO1, 0, 3, GL_FLOAT, 5 * sizeof(float), (void*)0);
			VAO1.LinkAttrib(*VBO1, 1, 2, GL_FLOAT, 5 * sizeof(float), (void*)(3 * sizeof(float)));
			glUniform1i(tex0Uni, 0);
			glBindTexture(GL_TEXTURE_2D, texture);
			glDrawArrays(GL_TRIANGLES, 0, 6);
		}
	}
}
