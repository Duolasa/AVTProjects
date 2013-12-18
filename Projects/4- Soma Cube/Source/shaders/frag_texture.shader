#version 330 core

in vec3 ex_textCoord;
out vec4 out_Color;
uniform sampler2D gsampler;
void main(void)
{ 
	vec2 textCoor = vec2(ex_textCoord.x * 1, ex_textCoord.y);
 
 out_Color = texture(gsampler, textCoor) - vec4(0.1,0.1,0.1,0.1) ;
//	out_Color = vec4(textCoor, ex_Color.z,ex_Color.w);
}