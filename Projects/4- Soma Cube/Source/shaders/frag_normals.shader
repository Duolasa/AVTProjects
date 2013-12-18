#version 330 core

//in vec4 ex_Color;
in vec4 ex_Normal;
out vec4 out_Color;

void main(void)
{
	vec3 N = normalize(vec3(ex_Normal));
	//N = normalize(vec3(1,0,0));
	vec3 Color;
	Color.r = N.x - N.y - N.z;
	Color.g = N.y - N.x - N.z;
	Color.b = N.z - N.x - N.y;
	Color = normalize(Color);
	out_Color = vec4(Color, 1.0);
	//out_Color = ex_Normal;
}
