#version 330

in vec4 ex_worldPosition;
in vec3 ex_worldNormal;

uniform vec3 lightPosition;
uniform vec3 viewPosition;
uniform vec3 lightArray[5];
out vec4 out_Color;

void main () {

float dot_product = max(dot(normalize(lightArray[0] - ex_worldPosition.xyz), normalize(ex_worldNormal)), 0.0);

vec4 diffuse = dot_product * vec4( 0.385, 1.0, 0.812, 1.0);
//vec4 ambient = vec4( 1.1, 0.1, 0.9, 1.0);
vec4 ambient = vec4( 0.1, 0.1, 0.1, 1.0);
float distanceFromLight = length(lightArray[0] - vec3(ex_worldPosition));

vec3 V = normalize(viewPosition - vec3(ex_worldPosition));
vec3 R = normalize(reflect(normalize(ex_worldPosition.xyz - lightArray[0]), normalize(ex_worldNormal)));
float specularTerm = pow(max(dot(R, V),0.0), 64);

vec3 p = vec3(1,1,1) * specularTerm;
vec4 specular =    vec4(p,1.0);

vec3 surfaceToLight = normalize(vec3(distanceFromLight));

out_Color = ambient + diffuse + specular;
//out_Color = specular;
//out_Color = vec4(lightArray[0],1.0f);
}
