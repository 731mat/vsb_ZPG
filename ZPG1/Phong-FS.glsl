#version 400

in vec4 ex_worldPosition;
in vec3 ex_worldNormal;
in vec2 texCoord;

uniform vec3 viewPosition;
uniform vec3 lightArray[5];
uniform sampler2D textura;
out vec4 out_Color;


void main () {
float dot_product, specularTerm;
vec4 diffuse, ambient, specular;
vec3 V,R;
vec4 finalColor = vec4(0);
for(int i = 0; i < 3; i++) {
	if( i == 0) {
		dot_product = max(dot(normalize(lightArray[i] - ex_worldPosition.xyz), normalize(ex_worldNormal)), 0.0);
		diffuse = dot_product * vec4( 0.1, 0.1, 0.1, 1.0);
		ambient = vec4( 0.1, 0.1, 0.1, 1.0);

		V = normalize(viewPosition - vec3(ex_worldPosition));
		R = normalize(reflect(normalize(ex_worldPosition.xyz - lightArray[i]), normalize(ex_worldNormal)));
		 specularTerm = pow(max(dot(R, V),0.0), 64);
		specular =  vec4( vec3(1,1,1) * specularTerm,1.0);
		finalColor = ambient + diffuse + specular;

	}

	if( i == 1) //smìrové svìtlo
	 {
		dot_product = max(dot(normalize(lightArray[i]), normalize(ex_worldNormal)), 0.0);
		diffuse = dot_product * vec4( 0.1, 0.1, 0.1, 1.0);
		ambient = vec4( 0.1, 0.1, 0.1, 1.0);

		V = normalize(viewPosition - vec3(ex_worldPosition));
		R = normalize(reflect(normalize(ex_worldPosition.xyz - lightArray[i]), normalize(ex_worldNormal)));
		 specularTerm = pow(max(dot(R, V),0.0), 466);
		specular =  vec4( vec3(1,1,1) * specularTerm,1.0);
		finalColor += ambient + diffuse + specular;
	}
	
}
//out_Color = vec4(texCoord.x,texCoord.y,0,1);
out_Color = finalColor + texture(textura, texCoord );
}
