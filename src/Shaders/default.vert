#version 460 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTex;
layout (location = 3) in vec3 aNormal;

out vec3 color;

out vec2 texCoord;

out vec3 Pos;

out vec3 Normal;

uniform float scale;

uniform mat4 camMatrix;

uniform mat4 model;

void main(){
	Pos = vec3(model * vec4(aPos,1.0));
	gl_Position = camMatrix * vec4(Pos,1.0);
	color = aColor;
	texCoord = aTex;
	Normal = aNormal;
}