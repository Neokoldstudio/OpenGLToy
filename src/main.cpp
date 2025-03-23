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

	GLfloat vertices[] =
	{
//POSITION	  X					Y			         Z   |COLOR	R      G      B		| U     V coordinates 
			-0.5f,            -0.5f,               0.0f,        1.0f, 0.0f, 0.0f,    0.0f, 0.0f, 
			-0.5f,             0.5f,               1.0f,        0.0f, 1.0f, 0.0f,    0.0f, 1.0f,
			 0.5f,             0.5f,               0.0f,        0.0f, 0.0f, 1.0f,    1.0f, 1.0f,
		     0.5f,            -0.5f,               0.0f,        1.0f, 1.0f, 1.0f,    1.0f, 0.0f
	};

	GLuint indices[] =
	{
		0, 2, 1,
		0, 3, 2
	};

	int width = 800; 
	int height = 800;
	float fov = 45.0f;

	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);//make sure glfw is aware of the opengGL version, here, the major one
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);//same, but with the minor version. OpenGL version here is 4.6
	glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);//using CORE profile, so that we only use the modern functions of GLFW

	int nbIndices = sizeof(indices) / sizeof(int);

	GLFWwindow* window = glfwCreateWindow(width,height,"GLWindow", NULL, NULL);//create a window object
	if (window == NULL) {//errors handling in case the window fails
		std::cout << "Failed to create window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);//make the window part of the current context, essentially telling it to use the window object

	gladLoadGL();

	glViewport(0, 0, width, height);//creating a viewport

    Shader shaderProgram("./src/Shaders/default.vert", "./src/Shaders/default.frag");//initializing and setup of the vertex+fragment shader couple

	//------------------VERTEX ARRAY, BUFFER AND ELEMENT ID SET UP---------------//
	VAO VAO1;
	VAO1.Bind();

	VBO VBO1(vertices, sizeof(vertices));
	EBO EBO1(indices, sizeof(indices));

	VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 8*sizeof(float), (void*)0);
	VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 8*sizeof(float), (void*)(3*sizeof(float)));
	VAO1.LinkAttrib(VBO1, 2, 2, GL_FLOAT, 8*sizeof(float), (void*)(6*sizeof(float)));


	VAO1.Unbind();
	VBO1.Unbind();
	EBO1.Unbind();
	//---------------------------------------------------------------------------//

	//Texture
	Texture image("./src/perlin.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	image.texUnit(shaderProgram, "text0", 0); //pass the texture as a uniform to the shader;

	glEnable(GL_DEPTH_TEST);

	Camera camera(width, height, fov, glm::vec3(0.0f,0.0f,0.2f));

	//Main loop
	while (!glfwWindowShouldClose(window)) {
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);//color of the background -> replace the default openGL clear color
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);//clearing the back buffer and the depth buffer
		shaderProgram.Activate();//activating the shader program

		camera.Inputs(window);
		camera.Matrix(0.1f, 100.0f, shaderProgram, "camMatrix");

		image.Bind();//bind texture
		VAO1.Bind();
		glDrawElements(GL_TRIANGLES, nbIndices, GL_UNSIGNED_INT, 0);

		glfwSwapBuffers(window); //swapping the front and the back buffers
		glfwPollEvents();
	}


	//cleaning up
	VAO1.Delete();
	VBO1.Delete();
	EBO1.Delete();
	image.Delete();
	shaderProgram.Delete();

	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}