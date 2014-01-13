#version 330 core

in vec3 ex_textCoord;
out vec4 out_Color;
uniform sampler2D gsampler1;
uniform sampler2D gsampler2;
void main(void)
{ 
	vec2 textCoor = vec2(ex_textCoord.x * 1, ex_textCoord.y); 
 
 out_Color = texture(gsampler1, textCoor) * 0.5  - vec4(0.05,0.05,0.05,0.0) + (texture(gsampler2, textCoor) - vec4(0.9f, 0.9f, 0.9f, 1.0f) * 0.5 )  ;
//	out_Color = vec4(textCoor, ex_Color.z,ex_Color.w);
}