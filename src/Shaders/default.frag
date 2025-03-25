#version 460 core

out vec4 FragColor;

in vec3 color; //must match the name of the output in the vertex shader
in vec2 texCoord;
in vec3 Pos;
in vec3 Normal;

uniform sampler2D tex0;
uniform sampler2D tex1;

uniform vec4 lightColor;

uniform vec3 lightPos;
uniform vec3 camPos;

vec4 pointLight()
{
	vec3 towardLight = (lightPos - Pos);
	float dist = length(towardLight);
	float a = 3.0;
	float b = 0.7;
	float intensity = 1.0f/ (a*dist*dist + b*dist+1.0f);

	vec3 normal = normalize(Normal);
	vec3 lightDirection = normalize(towardLight);

	//ambiant light
	float ambiant = 0.20f;

	//diffuse lighting
	float diffuse = max(dot(normal, lightDirection), 0.0f);

	//specular lighting
	float specularLight = 0.5f;
	vec3 viewDirection = normalize(camPos-Pos);
	vec3 reflectionDirection = reflect(-lightDirection, normal);
	float specAmount = pow(max(dot(viewDirection,reflectionDirection), 0.0f), 16);
	float specular = specAmount * specularLight;

	return (texture(tex0, texCoord) * (diffuse * intensity+ambiant) + texture(tex1, texCoord).r * specular * intensity) * lightColor;
}

vec4 directLight()
{
	vec3 normal = normalize(Normal);
	vec3 lightDirection = normalize(vec3(1.0f,1.0f,0.0f));

	//ambiant light
	float ambiant = 0.20f;

	//diffuse lighting
	float diffuse = max(dot(normal, lightDirection), 0.0f);

	//specular lighting
	float specularLight = 0.5f;
	vec3 viewDirection = normalize(camPos-Pos);
	vec3 reflectionDirection = reflect(-lightDirection, normal);
	float specAmount = pow(max(dot(viewDirection,reflectionDirection), 0.0f), 16);
	float specular = specAmount * specularLight;

	return (texture(tex0, texCoord) * (diffuse+ambiant) + texture(tex1, texCoord).r * specular) * lightColor;
}

vec4 spotLight()
{
	float outerCone = 0.90f;//control the cone area, Smaller numbers = bigger area
	float innerCone = 0.95f;

	vec3 normal = normalize(Normal);
	vec3 lightDirection = normalize(lightPos - Pos);

	//ambiant light
	float ambiant = 0.20f;

	//diffuse lighting
	float diffuse = max(dot(normal, lightDirection), 0.0f);

	//specular lighting
	float specularLight = 0.5f;
	vec3 viewDirection = normalize(camPos-Pos);
	vec3 reflectionDirection = reflect(-lightDirection, normal);
	float specAmount = pow(max(dot(viewDirection,reflectionDirection), 0.0f), 16);
	float specular = specAmount * specularLight;

	float angle = dot(vec3(0.0f,-1.0f,0.0f), -lightDirection);
	float intensity = clamp((angle-outerCone)/(innerCone - outerCone), 0.0f, 1.0f);

	return (texture(tex0, texCoord) * (diffuse * intensity+ambiant) + texture(tex1, texCoord).r * specular * intensity) * lightColor;
}

void main(){
	FragColor = spotLight();
}
