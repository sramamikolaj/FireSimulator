#ifndef FIRE_CLASS_H
#define FIRE_CLASS_H

#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include"VBO.h"
#include"shaderClass.h"
#include"VAO.h"
#include<iostream>
#include<cmath>

#include <stdlib.h>
#include <time.h>

typedef enum {
	Off,
	Starting,
	On,
	Stopping
}State;

class Fire
{


private:
	Shader* shaderProgram;
	
	VAO VAO1;

	//Fire parameters
	float fireWidth; //nie wiem jak ma dokladnie dzialac jeszcze
	float fireHeight;

	int circles, rows, radius;

	//Window parameters
	int windowHeight;
	int windowWidth;

	GLfloat pointVertex[15][15][540];
	int pointVertexArraySize;



	void fillArray(int);

public:
	Fire(int w, int h, int fireSize);
	~Fire();

	void activate(); //activate fire
	void deactivate(); //deactivate fire
	void changeSize(int changeBy); //change fire size
	void update(); //update sparks position
	void render(); //render sparks (czy potrzebne?)
	Shader* getShaderProgram() { return shaderProgram; }
};



#endif