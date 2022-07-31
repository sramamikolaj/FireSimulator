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
	for (int i = 0; i < size; i++)
	{
		float posX = float(i) / 100;
		pointVertex[i * 6 + j] = posX;
		j++;
		pointVertex[i * 6 + j] = -0.5;
		j++;
		pointVertex[i * 6 + j] = 0;
		j++;
		pointVertex[i * 6 + j] = -1 * posX;
		j++;
		pointVertex[i * 6 + j] = -0.5;
		j++;
		pointVertex[i * 6 + j] = 0;
		j = 0;
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
	//jeśli wyszło poza ekran to wyzeruj
	if (pointVertex[1] > 0.7) { 
		for (int i = 0; i < pointVertexArraySize; i++)
		{
			pointVertex[i * 3 + 1] = -0.5;
		}
	}
	//jeśli nie to leć w górę
	else { 
		for (int i = 0; i < pointVertexArraySize; i++)
		{
			float rand = float(std::rand() % 750) / 410000;
			pointVertex[i * 3 + 1] += rand;
		}
	}
}
void Fire::render()
{
	// Generates Vertex Buffer Object and links it to vertices
	
	VBO VBO1 = VBO(pointVertex, sizeof(pointVertex));
	VAO1.LinkVBO(VBO1, 0);

	int vertexColorLocation = glGetUniformLocation(shaderProgram->ID, "ourColor");

	glPointSize(10);
	glUniform4f(vertexColorLocation, 1.0f, 0.0f, 0.0f, 1.0f);
	glDrawArrays(GL_POINTS, 0, pointVertexArraySize);

	
	VBO1.Delete();
	
	//////////////////////////
	

}