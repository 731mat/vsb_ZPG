#version 330

in vec4 ex_worldPosition;
in vec3 ex_worldNormal;

out vec4 out_Color;
uniform vec3 lightPosition;

void main () {

float dot_product = max(dot(normalize(lightPosition - ex_worldPosition.xyz), normalize(ex_worldNormal)), 0.0);

vec4 diffuse = dot_product * vec4( 0.385, 1.647, 0.812, 1.0);
//vec4 ambient = vec4( 1.1, 0.1, 0.9, 1.0);
vec4 ambient = vec4( 0.1, 0.1, 0.1, 1.0);

 vec4 L = vec4(normalize(lightPosition - ex_worldPosition.xyz),1.0);
 vec4 V = normalize(ex_worldPosition);
 vec4 N = vec4(normalize(ex_worldNormal),1.0);

 float specularTerm = 0;

   // calculate specular reflection only if
   // the surface is oriented to the light source
   if(dot(N, L) > 0)
   {
      // half vector
      vec4 H = normalize(L + V);
      specularTerm = pow(dot(N, H), 3);
   }
   vec3 p = vec3(1, 1, 1) * vec3(0, 1, 0) * specularTerm;
 vec4 specular =    vec4(p,1.0);
//vec4  specular = vec4( 0.385, 1.647, 0.812, 1.0) * vec4( 0.1, 0.1, 0.1, 1.0) * pow(dot_product,h);
out_Color = ambient + diffuse;// + specular;
}
