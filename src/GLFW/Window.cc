/*	Copyright 2017 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#include "Window.hh"

#include "../Camera.hh"

using namespace Entropy::Theia;
using namespace Entropy::Theia::GLFW;
using namespace std;

void key_cb(GLFWwindow *, int, int, int, int);
void mouse_cb(GLFWwindow *, int, int, int);
void move_cb(GLFWwindow *, double, double);
void resize_cb(GLFWwindow *, int, int);

Window::Window(const string &name, const int width, const int height)
	: SharedData<Glfw>(), _handle(nullptr), _size_pos(width, height, 0, 0)
{
	_create_window(name);
}

Window::~Window()
{
	glfwDestroyWindow(_handle);
}

void Window::Show()
{
	glfwShowWindow(_handle);
}

void Window::Hide()
{
	glfwHideWindow(_handle);
}

void Window::Close()
{
	glfwSetWindowShouldClose(_handle, GLFW_TRUE);
}

void Window::toggleFullscreen()
{
	if (!isFullscreen()) {
		glfwGetWindowSize(_handle, &get<0>(_size_pos), &get<1>(_size_pos));
		glfwGetWindowPos(_handle, &get<2>(_size_pos), &get<3>(_size_pos));

		const GLFWvidmode *mode = _get_mode();

		glfwSetWindowMonitor(_handle, _get_monitor(), 0, 0, mode->width, mode->height, mode->refreshRate);
	} else {
		glfwSetWindowMonitor(_handle, nullptr, get<2>(_size_pos), get<3>(_size_pos), get<0>(_size_pos), get<1>(_size_pos), 0);
	}
}

void Window::disableCursor()
{
	glfwSetInputMode(_handle, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

void Window::enableCursor()
{
	glfwSetInputMode(_handle, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
}

bool Window::isFullscreen() const
{
	return glfwGetWindowMonitor(_handle) != nullptr;
}

bool Window::isVisible() const
{
	return glfwGetWindowAttrib(_handle, GLFW_VISIBLE) == GLFW_TRUE;
}

bool Window::isDone() const
{
	return glfwWindowShouldClose(_handle) == GLFW_TRUE;
}

void Window::operator () ()
{
	if (isVisible()) {
		if(glfwGetCurrentContext() != _handle)
			glfwMakeContextCurrent(_handle);

		glClear(GL_COLOR_BUFFER_BIT);

		Draw();

		glfwSwapBuffers(_handle);
		glfwPollEvents();
	}
}

void Window::Resize(const int width, const int height)
{
	glViewport(0, 0, width, height);
	Camera::setAspect(width, height);
}

void Window::_create_window(const string &name)
{
	const GLFWvidmode *mode = _get_mode();

	glfwWindowHint(GLFW_RED_BITS, mode->redBits);
	glfwWindowHint(GLFW_GREEN_BITS, mode->greenBits);
	glfwWindowHint(GLFW_BLUE_BITS, mode->blueBits);
	glfwWindowHint(GLFW_REFRESH_RATE, mode->refreshRate);

	_handle = glfwCreateWindow(get<0>(_size_pos), get<1>(_size_pos), name.c_str(), nullptr, nullptr);

	glfwMakeContextCurrent(_handle);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	glfwSetWindowUserPointer(_handle, this);
	glfwSetWindowAspectRatio(_handle, get<0>(_size_pos), get<1>(_size_pos));

	glfwSetKeyCallback(_handle, key_cb);
	glfwSetCursorPosCallback(_handle, move_cb);
	glfwSetMouseButtonCallback(_handle, mouse_cb);
	glfwSetFramebufferSizeCallback(_handle, resize_cb);
}

GLFWmonitor *Window::_get_monitor() const
{
	return glfwGetPrimaryMonitor();
}

const GLFWvidmode *Window::_get_mode() const
{
	return glfwGetVideoMode(_get_monitor());
}

void key_cb(GLFWwindow *handle, int key, int scan, int action, int modifiers)
{
	reinterpret_cast<Window *>(glfwGetWindowUserPointer(handle))->Key(key, scan, action, modifiers);
}

void mouse_cb(GLFWwindow *handle, int button, int action, int modifiers)
{
	reinterpret_cast<Window *>(glfwGetWindowUserPointer(handle))->Mouse(button, action, modifiers);
}

void move_cb(GLFWwindow *handle, const double x, const double y)
{
	reinterpret_cast<Window *>(glfwGetWindowUserPointer(handle))->Move(x, y);
}

void resize_cb(GLFWwindow *handle, int width, int height)
{
	reinterpret_cast<Window *>(glfwGetWindowUserPointer(handle))->Resize(width, height);
}
