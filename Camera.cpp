#include"Camera.h"



Camera::Camera(int width, int height, glm::vec3 position)
{
	Camera::width = width;
	Camera::height = height;
	Position = position;
}

void Camera::Matrix(float FOVdeg, float nearPlane, float farPlane, Shader& shader, const char* uniform)
{
	glm::mat4 view = glm::mat4(1.0f);
	glm::mat4 projection = glm::mat4(1.0f);

	view = glm::lookAt(Position, Position + Orientation, Up);
	projection = glm::perspective(glm::radians(FOVdeg), (float)width / height, nearPlane, farPlane);

	glUniformMatrix4fv(glGetUniformLocation(shader.ID, uniform), 1, GL_FALSE, glm::value_ptr(projection * view));
}



void Camera::Inputs(GLFWwindow* window)
{
	std::cout << "Position: x=" << Position.x << ", y=" << Position.y << " z=" << Position.z << std::endl;
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		if ((Position + (speed * Orientation)).y > 0.08) Position += speed * Orientation;
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		if ((Position + (speed * -glm::normalize(glm::cross(Orientation, Up)))).y > 0.08) Position += speed * -glm::normalize(glm::cross(Orientation, Up));

	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		if ((Position + (speed * -Orientation)).y > 0.08) Position += speed * -Orientation;
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		if ((Position + (glm::normalize(glm::cross(Orientation, Up)))).y > 0.08) Position += speed * glm::normalize(glm::cross(Orientation, Up));
	}
	
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
	{
		if (Position.y < 2.0) {
			if ((Position + (speed * Up)).y > 0.08) Position += speed * Up;
		}
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
	{
		if (Position.y >= 0.10) {
			if ((Position + (speed * Up)).y > 0.08) Position -= speed * Up;	
		}
	}

	// mouse inputs
	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
	{
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

		if (firstClick)
		{
			glfwSetCursorPos(window, (width / 2), (height / 2));
			firstClick = false;
		}

		double mouseX;
		double mouseY;

		glfwGetCursorPos(window, &mouseX, &mouseY);


		float rotX = sensitivity * (float)(mouseY - (height / 2)) / height;
		float rotY = sensitivity * (float)(mouseX - (width / 2)) / width;

		glm::vec3 newOrientation = glm::rotate(Orientation, glm::radians(-rotX), glm::normalize(glm::cross(Orientation, Up)));

		if (abs(glm::angle(newOrientation, Up) - glm::radians(90.0f)) <= glm::radians(85.0f))
		{
			Orientation = newOrientation;
		}

		Orientation = glm::rotate(Orientation, glm::radians(-rotY), Up);

		glfwSetCursorPos(window, (width / 2), (height / 2));
	}
	else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE)
	{
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		firstClick = true;
	}
}

void Camera::resetPosition()
{
	if (Position.z >= 1.70)
		Position.z = 1.69;
	if (Position.z <= -1.70)
		Position.z = -1.69;
	if (Position.x >= 1.70)
		Position.x = 1.69;
	if (Position.x <= -1.70)
		Position.x = -1.69;
}
