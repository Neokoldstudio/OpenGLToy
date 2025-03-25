#version 460 core

out vec4 FragColor;

in vec3 color; //must match the name of the output in the vertex shader
in vec2 texCoord;
in vec3 Pos;
in vec3 Normal;

uniform sampler2D tex0;

uniform vec4 lightColor;

uniform vec3 lightPos;
uniform vec3 camPos;

void main(){
	vec3 normal = normalize(Normal);
	vec3 lightDirection = normalize(lightPos - Pos);

	float ambiant = 0.20f;
	float diffuse = max(dot(normal, lightDirection), 0.0f);
	float specularLight = 0.5f;
	vec3 viewDirection = normalize(camPos-Pos);
	vec3 reflectionDirection = reflect(-lightDirection, normal);
	float specAmount = pow(max(dot(viewDirection,reflectionDirection), 0.0f), 10.0f);
	float specular = specAmount * specularLight;

	FragColor = texture(tex0, texCoord) * lightColor * (diffuse+ambiant + specular);
}
