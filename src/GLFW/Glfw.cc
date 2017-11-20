/*	Copyright 2017 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#include "Glfw.hh"

#include "../Events.hh"

#ifdef HAVE_CONFIG_H
#	include "config.h"
#endif

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

#	ifdef HAVE_OPENGL_CORE
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#	endif

	glfwWindowHint(GLFW_AUTO_ICONIFY, GLFW_FALSE);
	glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);
}

Glfw::~Glfw()
{
	glfwTerminate();
}

bool Glfw::isDebug() const
{
#	ifdef HAVE_OPENGL_CORE
		GLint flags;
		glGetIntegerv(GL_CONTEXT_FLAGS, &flags);
		CHECK_GL_ERRORS("Failed to get Context Flags");

		return flags & GL_CONTEXT_FLAG_DEBUG_BIT;
#	else
		return false;
#	endif
}

void Glfw::setDebug(const function<void(const Events::Debug &)> &cb)
{
	if(isDebug()) {
		_cb = cb;
		glEnable(GL_DEBUG_OUTPUT);
		glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
		glDebugMessageCallback(debug_cb, &_cb);
		glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, GL_TRUE);
#		ifdef DEBUG
			glDebugMessageInsert(GL_DEBUG_SOURCE_APPLICATION, GL_DEBUG_TYPE_OTHER, 10, GL_DEBUG_SEVERITY_NOTIFICATION, -1, "OpenGL Logging Initialized");
#		endif
		CHECK_GL_ERRORS("Failed to set debug callback");
	}
}

void APIENTRY debug_cb(GLenum src, GLenum type, GLuint id, GLenum sev, GLsizei len, const char *msg, const void *data)
{
	using namespace Entropy::Theia::Events;
	using Entropy::Log::Severity;

	const function<void(const Debug &)> *f = static_cast<const function<void(const Debug &)> *>(data);

	if(f && *f) {
		Debug ev(Debug::Source(src), Debug::Type(type), id, Debug::Severity(sev), string(msg, len));
		(*f)(ev);
	} else {
		ENTROPY_LOG(Log, Severity::Debug) << "GL Debug:" << msg;
	}
}

void error_cb(int error, const char *desc)
{
	ENTROPY_THROW(
		GlfwException(desc) <<
		GlfwErrorCode(error)
	);
}
