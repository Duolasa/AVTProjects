#version 330 core

in float NdotL;
in vec3 ReflectVec;
in vec3 ViewVec;

in vec3 ex_warmColor;
in vec3 ex_coolColor;

in vec3 normalVec;
in vec3 lightVec;
in vec3 cameraDir;

in vec4 ex_Color;
out vec4 out_Color;

void main(void)
{
  vec3 c1 = vec3(0.6, 0.6, 0.0);
  vec3 c2 = vec3(0.0, 0.0, 0.6);
  float DiffuseWarm = 0.4;
  float DiffuseCool = 0.8;

  vec4 _OutlineColor = vec4(0.0, 0.0, 0.0, 1.0);
  float _LitOutlineThickness = 0.1;
  float _UnlitOutlineThickness = 0.2;

  vec3 kcool = min(ex_coolColor+DiffuseCool*vec3(ex_Color), 1.0);
  vec3 kwarm = min(ex_warmColor+DiffuseWarm*vec3(ex_Color), 1.0);
  vec3 kfinal = mix(kcool, kwarm, NdotL);

  vec3 nreflect = normalize(ReflectVec);
  vec3 nview = normalize(ViewVec);

  float spec = max(dot(nreflect, nview), 0.0);
  spec = pow(spec, 32.0);

  out_Color = vec4(min(kfinal+spec, 1.0), 1.0);

  //if (dot(cameraDir, normalVec) < mix(_UnlitOutlineThickness, _LitOutlineThickness, max(0.0, dot(normalVec, lightVec))))
  //{
  //  out_Color = vec4(1.0, 1.0, 1.0, 1.0) * _OutlineColor; 
  //}
}
