#include "Fire.h"

Fire::Fire(int w, int h, int fireSize, const char* texPath)
{
	windowHeight = h;
	windowWidth = w;
	pointVertexArraySize = 0;

	shaderProgram = new Shader("spark.vert", "spark.frag");
	VAO1.Bind();

	srand(time(NULL));

	circles = 10;
	rows = 10;
	radius = 2;


	//fireWidth = fireSize;
	fireWidth = 3;
	fireHeight = 50;
	fillArray(fireWidth);
}

Fire::~Fire()
{
	VAO1.Delete();
	shaderProgram->Delete();
}

void Fire::initTexture(const char* texPath) {

}

void Fire::fillArray(int size)
{
	int j = 0;
	pointVertexArraySize = size;
	for (int circle = 1; circle <= circles; circle++)
	{
		for (int row = 0; row < rows; row++)
		{
			for (int i = 0; i < 360; i += 2)
			{
				float posX = float(circle) / (16 * circles) * cos(float(float(i) * 3.14 / 180.0));
				float posY = float(circle) / (16 * circles) * sin(float(float(i) * 3.14 / 180.0));
				pointVertex[circle - 1][row][i / 2 * 3 + j] = posX;
				j++;
				pointVertex[circle - 1][row][i / 2 * 3 + j] = float(row) / 500 * rows;
				j++;
				pointVertex[circle - 1][row][i / 2 * 3 + j] = posY;
				j = 0;
			}
		}
	}
}

void Fire::activate()
{
}

void Fire::deactivate()
{
}

void Fire::changeSize(int changeBy)
{
}

void Fire::update()
{
	for (int circle = 0; circle < circles; circle++)
	{
		for (int row = 0; row < rows; row++)
		{
			
			if (pointVertex[circle][row][1] > 0.2) {
				for (int i = 0; i < 180; i++)
				{
					pointVertex[circle][row][i * 3 + 1] = 0;
				}
			}
			else {
				for (int i = 0; i < 180; i++)
				{
					float randY = (rand() % 3) * 0.001;
					float randX = (rand() % 2) * 0.001;
					pointVertex[circle][row][i * 3 + 1] += randY;
				}
			
			}
		}
	}
}

void Fire::activateShader() 
{
	shaderProgram->Activate();
}

void Fire::render()
{
	VAO1.Bind();
	VBO VBO1 = VBO(pointVertex[0][0], sizeof(pointVertex[0][0]));
	for (int circle = 0; circle < circles; circle++)
	{
		for (int row = 0; row < rows; row++)
		{
			VBO1 = VBO(pointVertex[circle][row], sizeof(pointVertex[circle][row]));
			VAO1.LinkVBO(VBO1, 0);
			glPointSize(6);

			for (int i = 0; i < 180; i++)
			{
				float rad = sqrt(pointVertex[circle][row][i * 3] * pointVertex[circle][row][i * 3] + pointVertex[circle][row][i * 3 + 2] * pointVertex[circle][row][i * 3 + 2]);
				float yellow = 0.9 - (16 * sqrt(pointVertex[circle][row][i * 3] * pointVertex[circle][row][i * 3] + pointVertex[circle][row][i * 3 + 2] * pointVertex[circle][row][i * 3 + 2]));
				float alpha = 1.0 - 4 * pointVertex[circle][row][i * 3 + 1] - (16 * sqrt(pointVertex[circle][row][i * 3] * pointVertex[circle][row][i * 3] + pointVertex[circle][row][i * 3 + 2] * pointVertex[circle][row][i * 3 + 2]));
				int vertexColorLocation = glGetUniformLocation(shaderProgram->ID, "ourColor");
				glUniform4f(vertexColorLocation, 1.0f, yellow, 0.0f, alpha);

				glDrawArrays(GL_POINTS, i, 1);
			}
			VBO1.Delete();
		}
	}
}