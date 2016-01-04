#version 400

in VS_OUT {
	vec4 ex_worldPosition;
	vec3 ex_worldNormal;
	vec2 ex_texCoord;
	vec3 ex_Tangent;
	//vec3 ex_Bitangent;
} fs_in;

uniform vec3 viewPosition;
uniform vec3 lightArray[5];

uniform sampler2D textura;
uniform sampler2D normalMap;
uniform bool normalMapping;
out vec4 out_Color;


vec3 CalcNormal() {
	vec3 Normal = normalize(fs_in.ex_worldNormal);
	vec3 Tangent = normalize(fs_in.ex_Tangent);
	//Gram–Schmidt process
	Tangent = normalize(Tangent - dot(Tangent, Normal) * Normal);
	vec3 Bitangent = cross(Tangent, Normal);
	vec3 BumpMapNormal = texture(normalMap, fs_in.ex_texCoord).xyz;
	//pøevod z vektoru barvy o rozsahu <0,1> do vektoru normály <-1,1>
	BumpMapNormal = 2.0 * BumpMapNormal - vec3(1.0, 1.0, 1.0);
	// Transformaèní matice TBN
	mat3 TBN = mat3(Tangent, Bitangent, Normal);
	return normalize(TBN * BumpMapNormal);
}


void main () {
	vec3 normal = (normalMapping) ? CalcNormal() : fs_in.ex_worldNormal;
	//vec3 normal = fs_in.ex_worldNormal;
	float dot_product, specularTerm;
	vec4 diffuse, ambient, specular;
	vec3 V,R;
	vec4 finalColor = vec4(0);
	for(int i = 0; i < 5; i++)
	 {
		if( i == 0) //bodové svìtlo
		{ 
			dot_product = max(dot(normalize(lightArray[i] - fs_in.ex_worldPosition.xyz), normalize(normal)), 0.0);
			diffuse = dot_product * texture(textura, fs_in.ex_texCoord ) *  vec4( 0.1, 0.1, 0.1, 1.0); // vec4( 0.1, 0.1, 0.1, 1.0);
			ambient = vec4( 0.1, 0.1, 0.1, 1.0);

			V = normalize(viewPosition - vec3(fs_in.ex_worldPosition));
			R = normalize(reflect(normalize(fs_in.ex_worldPosition.xyz - lightArray[i]), normalize(normal)));
			specularTerm = pow(max(dot(R, V),0.0), 64);
			specular =  vec4( vec3(1,1,1) * specularTerm,1.0);
			finalColor = diffuse + specular;
	 }

		if( i == 1) //smìrové svìtlo
		{
			dot_product = max(dot(normalize(lightArray[i]), normalize(normal)), 0.0);
			diffuse = dot_product * texture(textura, fs_in.ex_texCoord ) * vec4( 0.1, 0.1, 0.1, 1.0);
			ambient = vec4( 0.01, 0.01, 0.01, 1.0);

			V = normalize(viewPosition - vec3(fs_in.ex_worldPosition));
			R = normalize(reflect(normalize(fs_in.ex_worldPosition.xyz - lightArray[i]), normalize(normal)));
			 specularTerm = pow(max(dot(R, V),0.0), 466);
			specular =  vec4( vec3(1,1,1) * specularTerm,1.0);
			finalColor +=  diffuse + specular;
		}

		if( i == 2) //smìrové svìtlo
		 {
			dot_product = max(dot(normalize(lightArray[i]), normalize(normal)), 0.0);
			diffuse = dot_product * texture(textura, fs_in.ex_texCoord ) * vec4( 0.1, 0.1, 0.1, 1.0);
			ambient = vec4( 0.01, 0.01, 0.01, 1.0);

			V = normalize(viewPosition - vec3(fs_in.ex_worldPosition));
			R = normalize(reflect(normalize(fs_in.ex_worldPosition.xyz - lightArray[i]), normalize(normal)));
			 specularTerm = pow(max(dot(R, V),0.0), 466);
			specular =  vec4( vec3(1,1,1) * specularTerm,1.0);
			finalColor +=  diffuse + specular;
		}	
	}

<<<<<<< HEAD
	out_Color = ambient + finalColor; //+ texture(textura, fs_in.ex_texCoord );
	//out_Color = finalColor * int(normalMapping);
=======
		if( i == 2) //smìrové svìtlo
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
>>>>>>> origin/master
}
