#ifndef FIRE_CLASS_H
#define FIRE_CLASS_H

#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include"VBO.h"
#include"shaderClass.h"
#include"VAO.h"
#include<iostream>

typedef enum {
	Off,
	Starting,
	On,
	Stopping
}State;

class Fire
{


private:
	//Fire parameters
	int fireSize; //nie wiem jak ma dokladnie dzialac jeszcze

	//Window parameters
	int windowHeight;
	int windowWidth;

	GLfloat pointVertex[800];
	int pointVertexArraySize;

public:
	Fire(int w, int h);

	void activate(); //activate fire
	void deactivate(); //deactivate fire
	void changeSize(int changeBy); //change fire size
	void update(); //update sparks position
	void render(); //render sparks (czy potrzebne?)
};



#endif