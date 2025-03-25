#include<iostream>
#include<glad\glad.h>
#include<GLFW\glfw3.h>
#include<stb\stb_image.h>
#include<glm\glm.hpp>
#include<glm\gtc\matrix_transform.hpp>
#include<glm\gtc\type_ptr.hpp>

#include"Headers/shaderClass.h"
#include"Headers/VBO.h"
#include"Headers/EBO.h"
#include"Headers/VAO.h"
#include"Headers/Texture.h"
#include"Headers/Camera.h"

int main() {

	//---------------------------------3D Object---------------------------------//
	GLfloat vertices[] =
	{ //     COORDINATES     /        COLORS          /    TexCoord   /        NORMALS       //
		-0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f, 	 0.0f, 0.0f,      0.0f, -1.0f, 0.0f, // Bottom side
		-0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	 0.0f, 5.0f,      0.0f, -1.0f, 0.0f, // Bottom side
		 0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	 5.0f, 5.0f,      0.0f, -1.0f, 0.0f, // Bottom side
		 0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,	 5.0f, 0.0f,      0.0f, -1.0f, 0.0f, // Bottom side

		-0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f, 	 0.0f, 0.0f,     -0.8f, 0.5f,  0.0f, // Left Side
		-0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	 5.0f, 0.0f,     -0.8f, 0.5f,  0.0f, // Left Side
		 0.0f, 0.8f,  0.0f,     0.92f, 0.86f, 0.76f,	 2.5f, 5.0f,     -0.8f, 0.5f,  0.0f, // Left Side

		-0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	 5.0f, 0.0f,      0.0f, 0.5f, -0.8f, // Non-facing side
		 0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	 0.0f, 0.0f,      0.0f, 0.5f, -0.8f, // Non-facing side
		 0.0f, 0.8f,  0.0f,     0.92f, 0.86f, 0.76f,	 2.5f, 5.0f,      0.0f, 0.5f, -0.8f, // Non-facing side

		 0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	 0.0f, 0.0f,      0.8f, 0.5f,  0.0f, // Right side
		 0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,	 5.0f, 0.0f,      0.8f, 0.5f,  0.0f, // Right side
		 0.0f, 0.8f,  0.0f,     0.92f, 0.86f, 0.76f,	 2.5f, 5.0f,      0.8f, 0.5f,  0.0f, // Right side

		 0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,	 5.0f, 0.0f,      0.0f, 0.5f,  0.8f, // Facing side
		-0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f, 	 0.0f, 0.0f,      0.0f, 0.5f,  0.8f, // Facing side
		 0.0f, 0.8f,  0.0f,     0.92f, 0.86f, 0.76f,	 2.5f, 5.0f,      0.0f, 0.5f,  0.8f  // Facing side
	};

	// Indices for vertices order
	GLuint indices[] =
	{
		0, 1, 2, // Bottom side
		0, 2, 3, // Bottom side
		4, 6, 5, // Left side
		7, 9, 8, // Non-facing side
		10, 12, 11, // Right side
		13, 15, 14 // Facing side
	};

	int nbIndices = sizeof(indices) / sizeof(int);

	GLfloat lightVertices[] =
	{
		-0.1f,-0.1f, 0.1f,
		-0.1f,-0.1f,-0.1f,
		 0.1f,-0.1f,-0.1f,
		 0.1f,-0.1f, 0.1f,
		-0.1f, 0.1f, 0.1f,
		-0.1f, 0.1f,-0.1f,
		 0.1f, 0.1f,-0.1f,
		 0.1f, 0.1f, 0.1f
	};

	GLuint lightIndices[] =
	{
		0,1,2,
		0,2,3,
		0,4,7,
		0,7,3,
		3,7,6,
		3,6,2,
		2,6,5,
		2,5,1,
		1,5,4,
		1,4,0,
		4,5,6,
		4,6,7
	};

	int nbLightIndices = sizeof(lightIndices) / sizeof(int);

	glm::vec4 lightColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);

	//---------------------------------------------------------------------------//

	int width = 900; 
	int height = 900;
	float fov = 45.0f;

	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);//make sure glfw is aware of the opengGL version, here, the major one
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);//same, but with the minor version. OpenGL version here is 4.6
	glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);//using CORE profile, so that we only use the modern functions of GLFW

	GLFWwindow* window = glfwCreateWindow(width,height,"GLWindow", NULL, NULL);//create a window object
	if (window == NULL) {//errors handling in case the window fails
		std::cout << "Failed to create window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);//make the window part of the current context, essentially telling it to use the window object

	gladLoadGL();//Configures OpenGL

	glViewport(0, 0, width, height);//creating a viewport

	//------------------VERTEX ARRAY, BUFFER AND ELEMENT ID SET UP : PYRAMID---------------//
    Shader shaderProgram("./src/Shaders/default.vert", "./src/Shaders/default.frag");//initializing and setup of the vertex+fragment shader couple

	VAO VAO1;
	VAO1.Bind();

	VBO VBO1(vertices, sizeof(vertices));
	EBO EBO1(indices, sizeof(indices));


	//vertex array format linking : [3 position float; 3 color float; 2 UV coordinates]
	VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 11*sizeof(float), (void*)0);
	VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 11*sizeof(float), (void*)(3*sizeof(float)));
	VAO1.LinkAttrib(VBO1, 2, 2, GL_FLOAT, 11*sizeof(float), (void*)(6*sizeof(float)));
	VAO1.LinkAttrib(VBO1, 3, 3, GL_FLOAT, 11*sizeof(float), (void*)(8*sizeof(float)));



	VAO1.Unbind();
	VBO1.Unbind();
	EBO1.Unbind();

	glm::vec3 pyramidPos = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::mat4 pyramidModel = glm::mat4(1.0f);
	pyramidModel = glm::translate(pyramidModel, pyramidPos);
	shaderProgram.Activate();
	glUniformMatrix4fv(glGetUniformLocation(shaderProgram.ID, "model"), 1, GL_FALSE, glm::value_ptr(pyramidModel));
	glUniform4f(glGetUniformLocation(shaderProgram.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);

	//-----------------------------------------LIGHT---------------------------------------//
	Shader lightShader("./src/Shaders/light.vert", "./src/Shaders/light.frag");

	VAO LightVAO;
	LightVAO.Bind();

	VBO LightVBO(lightVertices, sizeof(lightVertices));
	EBO LightEBO(lightIndices, sizeof(lightIndices));

	LightVAO.LinkAttrib(LightVBO, 0, 3, GL_FLOAT, 3 * sizeof(float), (void*)0);

	LightVAO.Unbind();
	LightVBO.Unbind();
	LightEBO.Unbind();

	glm::vec3 lightPos = glm::vec3(0.5f, 0.5f, 0.5f);
	glm::mat4 lightModel = glm::mat4(1.0f);
	lightModel = glm::translate(lightModel, lightPos);
	lightShader.Activate();
	glUniformMatrix4fv(glGetUniformLocation(lightShader.ID, "model"), 1, GL_FALSE, glm::value_ptr(lightModel));
	glUniform4f(glGetUniformLocation(lightShader.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
	shaderProgram.Activate();
	glUniform3f(glGetUniformLocation(shaderProgram.ID, "lightPos"), lightPos.x, lightPos.y, lightPos.z);


	//---------------------------------------------------------------------------------------//



	//Texture
	Texture image("./src/perlin.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	image.texUnit(shaderProgram, "text0", 0); //pass the texture as a uniform to the shader;

	glEnable(GL_DEPTH_TEST);

	Camera camera(width, height, fov, glm::vec3(0.0f,0.0f,2.0f));

	shaderProgram.Activate();
	glUniform3f(glGetUniformLocation(shaderProgram.ID, "camPos"), camera.Position.x, camera.Position.y, camera.Position.z);


	//Main loop
	while (!glfwWindowShouldClose(window)) {
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);//color of the background -> replace the default openGL clear color
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);//clearing the back buffer and the depth buffer
		shaderProgram.Activate();//activating the shader program

		camera.Update(window, shaderProgram);

		image.Bind();//bind texture
		VAO1.Bind();
		glDrawElements(GL_TRIANGLES, nbIndices, GL_UNSIGNED_INT, 0);

		lightShader.Activate();
		camera.Matrix(lightShader, "camMatrix");
		LightVAO.Bind();
		glDrawElements(GL_TRIANGLES, nbLightIndices, GL_UNSIGNED_INT, 0);


		glfwSwapBuffers(window); //swapping the front and the back buffers
		glfwPollEvents();//poll the window events (inputs, resize, etc ...)
	}


	//cleaning up
	VAO1.Delete();
	VBO1.Delete();
	EBO1.Delete();
	LightVAO.Delete();
	LightVBO.Delete();
	LightEBO.Delete();
	image.Delete();
	shaderProgram.Delete();
	lightShader.Delete();


	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}