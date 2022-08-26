#include "Skybox.h"

//Constructor - initialize all needed class fields
Skybox::Skybox(std::string path, int windowWidth, int windowHeight)
{
	this->initShaders();
	this->texturesPath = path;
	this->initFacesCubemap();
	this->initWindow(windowWidth, windowHeight);
	this->initTexture();
	this->loadCubemaps();
}

//Deconstructor
Skybox::~Skybox()
{
	shaderProgram->Delete();
}


//Initialize shader made for Skybox
void Skybox::initShaders()
{
	this->shaderProgram = new Shader("Resources/Shaders/skybox.vert", "Resources/Shaders/skybox.frag");
}

//Create view and projection, bind textures and render
void Skybox::render(Camera camera)
{
	glDepthFunc(GL_LEQUAL);

	shaderProgram->activate();
	glm::mat4 view = glm::mat4(1.0f);
	glm::mat4 projection = glm::mat4(1.0f);
	view = glm::mat4(glm::mat3(glm::lookAt(camera.Position, camera.Position + camera.Orientation, camera.Up)));
	projection = glm::perspective(glm::radians(45.0f), (float)windowWidth / windowHeight, 0.1f, 100.0f);

	glUniformMatrix4fv(glGetUniformLocation(shaderProgram->ID, "view"), 1, GL_FALSE, glm::value_ptr(view));
	glUniformMatrix4fv(glGetUniformLocation(shaderProgram->ID, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
	glBindVertexArray(this->skyboxVAO);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, this->cubemapTexture);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);

	glDepthFunc(GL_LESS);
}

//Skybox shader activation
void Skybox::activateShader()
{
	shaderProgram->activate();
}

//Initialize all OpenGl needed objects
void Skybox::initTexture()
{
	glGenVertexArrays(1, &skyboxVAO);
	glGenBuffers(1, &skyboxVBO);
	glGenBuffers(1, &skyboxEBO);
	glBindVertexArray(skyboxVAO);
	glBindBuffer(GL_ARRAY_BUFFER, skyboxVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), &skyboxVertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, skyboxEBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(skyboxIndices), &skyboxIndices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	glGenTextures(1, &cubemapTexture);
	glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
}

//Load all 6 faces of Cubemap
void Skybox::loadCubemaps()
{
	for (unsigned int i = 0; i < 6; i++)
	{
		int width, height, nrChannels;
		unsigned char* data = stbi_load(this->facesCubemap[i].c_str(), &width, &height, &nrChannels, 0);
		if (data)
		{
			stbi_set_flip_vertically_on_load(false);
			glTexImage2D
			(
				GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
				0,
				GL_RGB,
				width,
				height,
				0,
				GL_RGB,
				GL_UNSIGNED_BYTE,
				data
			);
			stbi_image_free(data);
		}
		else
		{
			std::cout << "Failed to load texture: " << facesCubemap[i] << std::endl;
			stbi_image_free(data);
		}
	}
}


//Add .jpg textures from given directory path
void Skybox::initFacesCubemap()
{
	this->facesCubemap.push_back(texturesPath + "px.jpg");
	this->facesCubemap.push_back(texturesPath + "nx.jpg");
	this->facesCubemap.push_back(texturesPath + "py.jpg");
	this->facesCubemap.push_back(texturesPath + "ny.jpg");
	this->facesCubemap.push_back(texturesPath + "pz.jpg");
	this->facesCubemap.push_back(texturesPath + "nz.jpg");

}

//Assign window parameters from main function
void Skybox::initWindow(int windowWidth, int windowHeight)
{
	this->windowWidth = windowWidth;
	this->windowHeight = windowHeight;
}
