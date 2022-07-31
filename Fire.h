#ifndef FIRE_CLASS_H
#define FIRE_CLASS_H

#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include"VBO.h"
#include"shaderClass.h"
#include"VAO.h"
#include<iostream>

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
	int fireSize; //nie wiem jak ma dokladnie dzialac jeszcze

	//Window parameters
	int windowHeight;
	int windowWidth;

	GLfloat pointVertex[800];
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
};



#endif