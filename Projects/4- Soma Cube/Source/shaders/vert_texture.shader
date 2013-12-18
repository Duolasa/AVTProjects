#version 330 core

in vec4 in_Position;
in vec3 in_textCoord;
out vec3 ex_textCoord;

uniform mat4 ModelMatrix;

layout(std140) uniform SharedMatrices
{
	mat4 ViewMatrix;
	mat4 ProjectionMatrix;
};

void main(void)
{
	ex_textCoord = in_textCoord;
	gl_Position = ProjectionMatrix * ViewMatrix * ModelMatrix * in_Position;
}
