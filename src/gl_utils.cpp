#include "gl_utils.hpp"

#include "common.hpp"

unsigned int size_of_gl_type(GLenum type) {
	switch(type) {
		case GL_FLOAT:
			return sizeof(GLfloat);
		case GL_INT:
			return sizeof(GLint);
		case GL_UNSIGNED_INT:
			return sizeof(GLuint);

		default:
			std::stringstream ss;
			ss << "size_of_gl_type failed: unknown GL type " << type;
			throw ss.str();
	}
}