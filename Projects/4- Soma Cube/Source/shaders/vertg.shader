#version 330 core

uniform mat4 ModelMatrix;

layout(std140) uniform SharedMatrices
{
	mat4 ViewMatrix;
	mat4 ProjectionMatrix;
};

uniform vec3 cameraPos;

uniform vec4 lightPosition;
uniform vec3 warmColor;
uniform vec3 coolColor;

in vec4 in_Normal;
in vec4 in_Position;
in vec4 in_Color;
out vec4 ex_Color;

out float NdotL;
out vec3 ReflectVec;
out vec3 ViewVec;

out vec3 ex_warmColor;
out vec3 ex_coolColor;

out vec3 normalVec;
out vec3 lightVec;

out vec3 cameraDir;

void main(void)
{

  mat4 ModelViewMatrix = ViewMatrix*ModelMatrix;

  vec3 ecPos = vec3(ModelViewMatrix*in_Position);
  vec3 lPos = vec3(ModelViewMatrix*lightPosition);

  normalVec = normalize(transpose(inverse(mat3(ModelViewMatrix)))*vec3(in_Normal));
  lightVec = normalize(lPos-ecPos);

  ReflectVec = normalize(reflect(-lightVec, normalVec));
  ViewVec = normalize(-ecPos);
  NdotL = (dot(normalVec, lightVec)+1.0)/2.0;

  cameraDir = normalize(mat3(ModelMatrix)*cameraPos - ecPos);

  gl_Position = ProjectionMatrix * ViewMatrix * ModelMatrix * in_Position;
  ex_Color = vec4(1);
  
  ex_warmColor = warmColor;
  ex_coolColor = coolColor;
}