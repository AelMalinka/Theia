/*	Copyright 2017 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#include "Glfw.hh"

#include "../Events.hh"

using namespace Entropy::Theia;
using namespace std;

void error_cb(int, const char *);
void APIENTRY debug_cb(GLenum, GLenum, GLuint, GLenum, GLsizei, const GLchar *, const void *);

Glfw::Glfw()
{
	if(!glfwInit())
		ENTROPY_THROW(GlfwException("Failed to initialize"));

	glfwSetErrorCallback(error_cb);

#	ifdef DEBUG
		glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);
#	endif

	// 2017-03-09 AMR TODO: allow user to override, possibly move to window?
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	glfwWindowHint(GLFW_AUTO_ICONIFY, GLFW_FALSE);
	glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);
}

Glfw::~Glfw()
{
	glfwTerminate();
}

bool Glfw::isDebug() const
{
	GLint flags;
	glGetIntegerv(GL_CONTEXT_FLAGS, &flags);

	return flags & GL_CONTEXT_FLAG_DEBUG_BIT;
}

void Glfw::setDebug(const function<void(const Events::Debug &)> &cb)
{
	if(isDebug()) {
		glEnable(GL_DEBUG_OUTPUT);
		glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
		glDebugMessageCallback(debug_cb, &cb);
		glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, GL_TRUE);
		CHECK_GL_ERRORS("Failed to set debug callback");
	}
}

void APIENTRY debug_cb(GLenum src, GLenum type, GLuint id, GLenum sev, GLsizei len, const char *msg, const void *data)
{
	using namespace Entropy::Theia::Events;

	const function<void(const Debug &)> &f = *reinterpret_cast<const function<void(const Debug &)> *>(data);

	Debug ev(Debug::Source(src), Debug::Type(type), id, Debug::Severity(sev), string(msg, len));
	f(ev);
}

void error_cb(int error, const char *desc)
{
	ENTROPY_THROW(
		GlfwException(desc) <<
		GlfwErrorCode(error)
	);
}
