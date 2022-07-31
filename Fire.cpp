#include "Fire.h"

Fire::Fire(int w, int h)
{
	windowHeight = h;
	windowWidth = w;
	fireSize = 10; //temp?
	pointVertexArraySize = 0;

	//TEMP - potem pewnie do funkcji jakiejs
	int size = 100;

	int j = 0;

	pointVertexArraySize = size;

	for (int i = 0; i < size; i++)
	{
		float posX = float(i) / 100;
		pointVertex[i*6+j] = posX;
		j++;
		pointVertex[i*6+j] = -0.5;
		j++;
		pointVertex[i*6+j] = 0;
		j++;
		pointVertex[i * 6 + j] = -1 * posX;
		j++;
		pointVertex[i * 6 + j] = -0.5;
		j++;
		pointVertex[i * 6 + j] = 0;
		j = 0;
	}
	//
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
	////////TEMP STUFF//////////



	

	Shader shaderProgram("spark.vert", "spark.frag");

	VAO VAO1;
	VAO1.Bind();
	// Generates Vertex Buffer Object and links it to vertices
	VBO VBO1(pointVertex, sizeof(pointVertex));
	VAO1.LinkVBO(VBO1, 0);

	shaderProgram.Activate();


	VBO1 = VBO(pointVertex, sizeof(pointVertex));
	VAO1.LinkVBO(VBO1, 0); // Links VBO to VAO
	VAO1.Bind();

	int vertexColorLocation = glGetUniformLocation(shaderProgram.ID, "ourColor");
	glPointSize(10);
	glUniform4f(vertexColorLocation, 1.0f, 0.0f, 0.0f, 1.0f);
	glDrawArrays(GL_POINTS, 0, pointVertexArraySize);

	VAO1.Delete();
	VBO1.Delete();
	shaderProgram.Delete();
	//////////////////////////

}