#pragma once

#include<glad/glad.h>
#include<string>
#include<fstream>
#include<sstream>
#include<iostream>
#include<cerrno>

std::string get_file_contents(const char* filement);

class Shader
{
	public:
		GLuint ID;
		Shader(const char* vertexFiled, const char* fragmentFile);

		void Activate();
		void Delete();
	private:
		// Checks if the different Shaders have compiled properly
		void compileErrors(unsigned int shader, const char* type);
};