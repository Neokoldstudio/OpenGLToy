#pragma once

#include<glad\glad.h>
#include<GLFW\glfw3.h>
#include<glm\glm.hpp>
#include<glm\gtc\matrix_transform.hpp>
#include<glm\gtc\type_ptr.hpp>
#include<glm\gtx\rotate_vector.hpp>
#include<glm\gtx\vector_angle.hpp>

#include"shaderClass.h"

class Camera 
{
	public:
		glm::vec3 Position;
		glm::vec3 LookAt = glm::vec3(0.0f,0.0f,-1.0f);
		glm::vec3 Up = glm::vec3(0.0f,1.0f,0.0f);
		glm::mat4 cameraMatrix = glm::mat4(1.0f);

		int width;
		int height;

		float fov = 45.0f;
		float speed = 0.01f;
		float sensitivity = 75.0f;

		bool firstClick = true;

		Camera(int width, int height, float fov, glm::vec3 position);

		void Update(GLFWwindow* window, Shader& shader);
		void UpdateMatrix(float nearPlane, float farPlane);
		void Matrix(Shader& shader, const char* uniform);
		void Inputs(GLFWwindow* window);
};