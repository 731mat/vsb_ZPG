#version 400

in vec3 in_Position;
in vec3 normal;
in vec2 inTexCoord;
in vec3 ex_Tangent;
//in vec3 ex_Bitangent;


out VS_OUT {
	vec4 ex_worldPosition;
	vec3 ex_worldNormal;
	vec2 ex_texCoord;
	vec3 ex_Tangent;
	//vec3 ex_Bitangent;
} vs_out;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;
uniform mat4 normalMatrix; 


void main () {
  gl_Position = ( projectionMatrix *  viewMatrix * modelMatrix ) * vec4 (in_Position, 1.0);
  //gl_Position = vec4(in_Position, 1.0f);
  vs_out.ex_worldPosition = modelMatrix * vec4(in_Position, 1.0);
  //ex_worldNormal = vec3((modelMatrix)*vec4(normal, 1.0));
 // ex_worldNormal = normal;
 vs_out.ex_worldNormal = mat3(transpose(inverse(modelMatrix))) * normal;
 vs_out.ex_texCoord = inTexCoord;
}
