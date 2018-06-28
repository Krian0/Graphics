#version 410

in vec2 vTexCoord;
in vec3 vNormal;
in vec4 vPosition;

uniform sampler2D diffuseTexture;
uniform sampler2D specularTexture;
uniform sampler2D normalTexture;

uniform vec3 Ia;				//Ambient
uniform vec3 Id;				//Diffuse
uniform vec3 Is;				//Specular

uniform vec3 Ka;				//Ambient Material
uniform vec3 Kd;				//Diffuse Material
uniform vec3 Ks;				//Specular Material

uniform vec3 lightDirection;
uniform vec3 cameraPosition;
uniform float specularPower;	//Material Specular Power

out vec4 FragColour;

void main()
{
	vec3 N = normalize(vNormal);
	vec3 L = normalize(lightDirection);

	vec3 texDiffuse = texture(diffuseTexture, vTexCoord).rgb;
	vec3 texSpecular = texture(specularTexture, vTexCoord).rgb;
	vec3 texNormal = texture(normalTexture, vTexCoord).rgb;

	float lambertTerm = max(0, min(1, dot(N, -L)));

	vec3 V = normalize(cameraPosition - vPosition.xyz);
	vec3 R = reflect(L, N);

	float specularTerm = pow(max(0, dot(R, V)), specularPower);

	vec3 ambient = Ia * Ka;
	vec3 diffuse = Id * Kd * lambertTerm;
	vec3 specular = Is * Ks * specularTerm;

	FragColour = vec4(ambient + diffuse + specular, 1);
}