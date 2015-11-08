#version 330

in vec4 ex_worldPosition;
in vec3 ex_worldNormal;

uniform vec3 lightPosition;
uniform vec3 viewPosition;

out vec4 out_Color;

void main () {

float dot_product = max(dot(normalize(lightPosition - ex_worldPosition.xyz), normalize(ex_worldNormal)), 0.0);

vec4 diffuse = dot_product * vec4( 0.385, 1.0, 0.812, 1.0);
//vec4 ambient = vec4( 1.1, 0.1, 0.9, 1.0);
vec4 ambient = vec4( 0.1, 0.1, 0.1, 1.0);


vec3 V = normalize(viewPosition - vec3(ex_worldPosition));
vec3 R = normalize(reflect(normalize(ex_worldPosition.xyz - lightPosition), normalize(ex_worldNormal)));
float specularTerm = pow(max(dot(R, V),0.0), 10);

vec3 p = vec3(1,1,1) * specularTerm;
vec4 specular =    vec4(p,1.0);

out_Color = ambient + diffuse + specular;//out_Color = vec4(lightPosition,1.0f);
}
