#include "Fire.h"

Fire::Fire(int w, int h, int fireSize)
{
	windowHeight = h;
	windowWidth = w;
	pointVertexArraySize = 0;

	shaderProgram = new Shader("spark.vert", "spark.frag");
	shaderProgram->Activate();
	VAO1.Bind();

	srand(time(NULL));

	
	fireWidth = fireSize;
	fireHeight = 43;
	fillArray(fireSize);
}

Fire::~Fire()
{

	VAO1.Delete();
	shaderProgram->Delete();
}

void Fire::fillArray(int size)
{
	int j = 0;
	pointVertexArraySize = size;
	for (int row = 0; row < fireHeight; row++)
	{
		for (int i = 0; i < size; i++)
		{
			float posX = float(i) / 90;
			pointVertex[row][i * 6 + j] = posX;
			j++;
			pointVertex[row][i * 6 + j] = 0 + float(row)/60;
			j++;
			pointVertex[row][i * 6 + j] = 0;
			j++;
			pointVertex[row][i * 6 + j] = -1 * posX;
			j++;
			pointVertex[row][i * 6 + j] = 0 + float(row) / 60;
			j++;
			pointVertex[row][i * 6 + j] = 0;
			j = 0;
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
	for (int row = 0; row < fireHeight; row++)
	{
		//jeśli wyszło poza ekran to wyzeruj
		if (pointVertex[row][1] > 0.72) {
			for (int i = 0; i < pointVertexArraySize; i++)
			{
				pointVertex[row][i * 3 + 1] = 0;
			}
		}
		//jeśli nie to leć w górę
		else {
			for (int i = 0; i < pointVertexArraySize; i++)
			{
				float randY = float(std::rand() % 800) / 810000;
				pointVertex[row][i * 3 + 1] += randY;
				float randX = float(std::rand() % 800 -400) / 400000;
				pointVertex[row][i * 3 ] += randX;
			}
		}
	}
}
void Fire::render()
{
	// Generates Vertex Buffer Object and links it to vertices
	
	VBO VBO1 = VBO(pointVertex[0], sizeof(pointVertex[0]));

	for (int row = 0; row < fireHeight; row++)
	{
		VBO1 = VBO(pointVertex[row], sizeof(pointVertex[row]));
		VAO1.LinkVBO(VBO1, 0);
		int vertexColorLocation = glGetUniformLocation(shaderProgram->ID, "ourColor");
		glPointSize(10);

		for (int i = 1; i < pointVertexArraySize; i++)
		{
			float y = 1.0f - 10*float(i) / pointVertexArraySize - 2*pointVertex[row][1];
			glUniform4f(vertexColorLocation, 1.0f, y, 0.0f, (1 - pointVertex[row][1]) - 0.02 * i /*TYMCZASOWE RÓWNANIE JAKIEŚ*/);
			glDrawArrays(GL_POINTS, i, 1);
		}

		VBO1.Delete();
	}
	
	
	//////////////////////////

	
}