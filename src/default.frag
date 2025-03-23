#version 460 core

out vec4 FragColor;

in vec3 color; //must match the name of the output in the vertex shader
in vec2 texCoord;

uniform sampler2D tex0;

void main(){
	FragColor = texture(tex0, texCoord);
}
