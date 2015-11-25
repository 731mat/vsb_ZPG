#version 330

in vec4 ex_worldPosition;
in vec3 ex_worldNormal;

uniform vec3 viewPosition;
uniform vec3 lightArray[5];
out vec4 out_Color;
const float cos_outer_cone_angle = 0.8;


void main () {
float dot_product, specularTerm;
vec4 diffuse, ambient, specular;
vec3 V,R;
vec4 finalColor = vec4(0);
for(int i = 0; i < 3; i++) {
	if( i == 0) {
		dot_product = max(dot(normalize(lightArray[i] - ex_worldPosition.xyz), normalize(ex_worldNormal)), 0.0);
		diffuse = dot_product * vec4( 0.0, 1.0, 0.812, 1.0);
		ambient = vec4( 0.1, 0.1, 0.1, 1.0);

		V = normalize(viewPosition - vec3(ex_worldPosition));
		R = normalize(reflect(normalize(ex_worldPosition.xyz - lightArray[i]), normalize(ex_worldNormal)));
		 specularTerm = pow(max(dot(R, V),0.0), 64);
		specular =  vec4( vec3(1,1,1) * specularTerm,1.0);
		finalColor = ambient + diffuse + specular;

	}

	if( i == 1)
	 {
		dot_product = max(dot(normalize(lightArray[i]), normalize(ex_worldNormal)), 0.0);
		diffuse = dot_product * vec4( 0.0, 1.0, 0.812, 1.0);
		ambient = vec4( 0.1, 0.1, 0.1, 1.0);

		V = normalize(viewPosition - vec3(ex_worldPosition));
		R = normalize(reflect(normalize(ex_worldPosition.xyz - lightArray[i]), normalize(ex_worldNormal)));
		 specularTerm = pow(max(dot(R, V),0.0), 64);
		specular =  vec4( vec3(1,1,1) * specularTerm,1.0);
		finalColor += ambient + diffuse + specular;
	}
	
}
out_Color = finalColor;
}
