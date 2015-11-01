#ifndef Shader_h_
#define Shader_h_

#include "ShaderLoader.h"
#include "glm/vec3.hpp" // glm::vec3
#include "glm/vec4.hpp" // glm::vec4
#include "glm/mat4x4.hpp" // glm::mat4
#include "glm/gtc/matrix_transform.hpp" // glm::translate, glm::rotate, glm::scale, glm::perspective
#include "glm/gtc/type_ptr.hpp" // glm::value_ptr
#include "glm\gtc\matrix_transform.hpp"

#include "Camera.h"
#include "opengl_helper.h"	// tohle je helper soubor na kontrolu chyb, doporuèuju používat makro GL_CHECK_ERRORS po každém glXXX volání :-)


class Shader : public ShaderLoader, AbstractObserver {

private:
	GLuint programID;
	GLuint matrixID;	//GLuint viewMatrixID;



public:
	Shader(const char *vertexFile, const char *fragmentFile);
	~Shader();
	void setShader();

	GLint getShader();
	void shaderRotate(float rotationx);
	void update(glm::vec3 vector);

	GLuint getID() { return this->programID;  }
};
#endif Shader _h_