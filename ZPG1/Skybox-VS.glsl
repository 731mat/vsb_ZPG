#version 400

in vec3 in_Position;
in vec3 normal;
in vec2 TexCoord;

out vec3 texCoord;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;
uniform mat4 normalMatrix; 

void main () 
{
  gl_Position =  projectionMatrix *  viewMatrix * vec4 (in_Position, 1.0);
  texCoord = in_Position;
}
