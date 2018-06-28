#version 410

layout(location = 0) in vec4 Position;
layout(location = 1) in vec4 Normal;
layout(location = 2) in vec2 TexCoord;

out vec2 vTexCoord;
out vec4 vPosition;
out vec3 vNormal;

uniform mat4 ProjectionViewModel;
uniform mat4 ModelMatrix;


void main()
{
	vTexCoord = TexCoord;
	vPosition = ModelMatrix * Position;
	vNormal = (ModelMatrix * Normal).xyz;
	gl_Position = ProjectionViewModel * Position;
}