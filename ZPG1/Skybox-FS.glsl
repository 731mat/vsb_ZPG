#version 400


in vec3 texCoord;

uniform samplerCube textura;
out vec4 out_Color;


void main () {
out_Color = texture(textura, texCoord );
//out_Color = vec4(texCoord,1.0);
}
