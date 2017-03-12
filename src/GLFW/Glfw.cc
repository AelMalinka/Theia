/*	Copyright 2017 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#include "Glfw.hh"

using namespace Entropy::Theia;
using namespace std;

void error_cb(int, const char *);

Glfw::Glfw()
{
	if(!glfwInit())
		ENTROPY_THROW(GlfwException("Failed to initialize"));

	glfwSetErrorCallback(error_cb);

#	ifdef DEBUG
		glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);
#	endif

	// 2017-03-09 AMR TODO: allow user to override, possibly move to window?
	glfwWindowHint(GLFW_AUTO_ICONIFY, GLFW_FALSE);
	glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);
}

Glfw::~Glfw()
{
	glfwTerminate();
}

void error_cb(int error, const char *desc)
{
	ENTROPY_THROW(
		GlfwException(desc) <<
		GlfwErrorCode(error)
	);
}

