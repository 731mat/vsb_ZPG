#version 330

in vec3 in_Position;
in vec3 normal;

out vec4 ex_worldPosition;
out vec3 ex_worldNormal;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;
uniform mat4 normalMatrix; 

void main () {

  gl_Position = ( projectionMatrix *  viewMatrix * modelMatrix ) * vec4 (in_Position, 1.0);
  //gl_Position = vec4(in_Position, 1.0f);
  ex_worldPosition = modelMatrix * vec4(in_Position, 1.0);
  //ex_worldNormal = vec3((modelMatrix)*vec4(normal, 1.0));
  ex_worldNormal = normal;

}
