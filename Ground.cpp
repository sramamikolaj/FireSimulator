#include "Ground.h"



Ground::Ground(int w, int h)
{
	windowHeight = h;
	windowWidth = w;
	VAO1.Bind();
	initArrays();
	
	//VAO1.LinkVBO(*VBO1, 0);
	


	shaderProgram = new Shader("default.vert", "default.frag");

	//Texture temp stuff
	GLfloat textCords[] =
	{
		0.0f, 0.0f, // Lower left corner
		0.0f, 1.0f, // Lower right corner
		1.0f, 1.0f, // Upper corner
		1.0f, 0.0f, // Lower left corner
		0.0f, 0.0f, // Lower right corner
		0.0f, 1.0f	// Upper corner
	};

	int widthImg, heightImg, numColCh;
	const char* reason = "[unknown reason]";
	unsigned char* bytes = stbi_load("D:/Visual Studio/FireSimulator/grass.jpg", &widthImg, &heightImg, &numColCh, 0);
	reason = stbi_failure_reason();
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

	////////////////
}

Ground::~Ground()
{
	VBO1->Delete();
	VAO1.Delete();
	shaderProgram->Delete();
	//glDeleteTextures(1, &texture);
}

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
				0.1f+ xOffset, 0, -0.1f + yOffset, 1.0f, 0.0f, // Lower left corner
				-0.1f+ xOffset, 0, -0.1f + yOffset, 0.0f, 0.0f, // Lower right corner
				0.1f+ xOffset, 0, 0.1f + yOffset, 1.0f, 1.0f, // Upper corner
				-0.1f+ xOffset, 0, 0.1f + yOffset, 0.0f, 1.0f, // Lower left corner
				-0.1f+ xOffset, 0, -0.1f + yOffset, 0.0f, 0.0f, // Lower right corner
				0.1f+ xOffset, 0, 0.1f + yOffset, 1.0f, 1.0f	// Upper corner
			};
			std::copy(values, values + 30, vertices[i][j]);
		}
	}
	
	
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
	for (int j = 0; j < 20; j++)
	{
		for (int i = 0; i < 20; i++)
		{
			VAO1.Bind();

			VBO1 = new VBO(vertices[i][j], sizeof(vertices[i][j]));
			VAO1.LinkAttrib(*VBO1, 0, 3, GL_FLOAT, 5 * sizeof(float), (void*)0);
			VAO1.LinkAttrib(*VBO1, 1, 2, GL_FLOAT, 5 * sizeof(float), (void*)(3 * sizeof(float)));

			GLuint tex0Uni = glGetUniformLocation(shaderProgram->ID, "tex0");
			activateShader();
			glUniform1i(tex0Uni, 0);
			glBindTexture(GL_TEXTURE_2D, texture);

			glDrawArrays(GL_TRIANGLES, 0, 6);
		}
	}
	

	
}
