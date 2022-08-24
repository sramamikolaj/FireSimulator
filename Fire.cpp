#include "Fire.h"

//Constructor - values initialiation and call of other init unctions
Fire::Fire(const char* texPath)
{
	srand(time(NULL));
	shaderProgram = new Shader("Resources/Shaders/pointSprite.vert", "Resources/Shaders/pointSprite.frag");
	VAO1.Bind();
	
	circles = 10;
	layers = 10;

	fillArray();
	initTexture(texPath);

	tex0Uni = glGetUniformLocation(shaderProgram->ID, "tex0");
	vertexColorLocation = glGetUniformLocation(shaderProgram->ID, "colorFilter");
}

//Destructor - delete components
Fire::~Fire()
{
	VAO1.Delete();
	shaderProgram->Delete();
	glDeleteTextures(0, &texture);
}

//Initialize texture that will be use to create point sprites - fire sparks
void Fire::initTexture(const char* texPath) {
	int widthImg, heightImg, numColCh;
	unsigned char* bytes = stbi_load(texPath, &widthImg, &heightImg, &numColCh, 0);
	glGenTextures(1, &texture);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, widthImg, heightImg, 0, GL_RGB, GL_UNSIGNED_BYTE, bytes);
	glGenerateMipmap(GL_TEXTURE_2D);
	stbi_image_free(bytes);
}

//Fire is built out of points in circles in layers - initialie positions of these points
void Fire::fillArray()
{
	int j = 0;
	for (int circle = 1; circle <= circles; circle++)
	{
		for (int row = 0; row < layers; row++)
		{
			for (int i = 0; i < 360; i += 2)
			{
				float posX = float(circle) / (12 * circles) * cos(float(float(i) * 3.14 / 180.0));
				float posY = float(circle) / (12 * circles) * sin(float(float(i) * 3.14 / 180.0));
				pointVertex[circle - 1][row][i / 2 * 3 + j] = posX;
				j++;
				pointVertex[circle - 1][row][i / 2 * 3 + j] = float(row) / 500 * layers;
				j++;
				pointVertex[circle - 1][row][i / 2 * 3 + j] = posY;
				j = 0;
			}
		}
	}
}

//Update points positions - by random values or reset them to ground level if the reached limit
void Fire::update()
{
	for (int circle = 0; circle < circles; circle++)
	{
		for (int row = 0; row < layers; row++)
		{
			if (pointVertex[circle][row][1] > 0.2) {
				for (int i = 0; i < 180; i++)
				{
					float randLevel = ((rand() % 8) - 4) *0.01;
					pointVertex[circle][row][i * 3 + 1] = randLevel;
				}
			}
			else {
				for (int i = 0; i < 180; i++)
				{
					float randY = (rand() % 3) * 0.001;
					float randX = ((rand() % 3) -1) * 0.0005;
					float randZ = ((rand() % 3) -1) * 0.0005;
					pointVertex[circle][row][i * 3] += randX;
					pointVertex[circle][row][i * 3 + 1] += randY;
					pointVertex[circle][row][i * 3 + 2] += randZ;
				}
			}
		}
	}
}

//Fire shader activation
void Fire::activateShader() 
{
	shaderProgram->activate();
}

//Render points - each point has to be processed separately due to varied color filter and alpha value
void Fire::render()
{
	VAO1.Bind();
	VBO VBO1 = VBO(pointVertex[0][0], sizeof(pointVertex[0][0]));
	glPointSize(8);

	for (int circle = 0; circle < circles; circle++)
	{
		for (int row = 0; row < layers; row++)
		{
			VBO1 = VBO(pointVertex[circle][row], sizeof(pointVertex[circle][row]));
			VAO1.LinkVBO(VBO1, 0);
			
			for (int i = 0; i < 180; i++)
			{
				float yellow = 0.9 - (12 * sqrt(pointVertex[circle][row][i * 3] * pointVertex[circle][row][i * 3] + pointVertex[circle][row][i * 3 + 2] * pointVertex[circle][row][i * 3 + 2]));
				float alpha = 1 - 4 * pointVertex[circle][row][i * 3 + 1] - (12 * sqrt(pointVertex[circle][row][i * 3] * pointVertex[circle][row][i * 3] + pointVertex[circle][row][i * 3 + 2] * pointVertex[circle][row][i * 3 + 2]) - rand()%12*0.01);
				glUniform4f(vertexColorLocation, 1.0f, yellow, 0.0f, alpha);
				glUniform1i(tex0Uni, 1);
				glBindTexture(GL_TEXTURE_2D, texture);
				glDrawArrays(GL_POINTS, i, 1);
			}

			VBO1.Delete();
		}
	}
}