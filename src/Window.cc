/*	Copyright 2017 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#include "Window.hh"

#include "GLFW/Window.hh"

using namespace Entropy::Theia;
using namespace std;

struct GlfwWindow :
	public GLFW::Window
{
	GlfwWindow(Entropy::Theia::Window *, const std::string, const std::size_t, const std::size_t);
	void Draw();
	void Key(const int, const int, const int, const int);
	void Mouse(const int, const int, const int);
	void Move(const double, const double);
	void Resize(const int, const int);
	private:
		Entropy::Theia::Window *_win;
};

Window::~Window() = default;

void Window::operator () ()
{
	(*_window)();
}

DefaultedList<Scene> &Window::Scenes()
{
	return _scene;
}

const DefaultedList<Scene> &Window::Scenes() const
{
	return _scene;
}

void Window::make_window(const string &name, const size_t width, const size_t height)
{
	_window = make_shared<GlfwWindow>(this, name, width, height);
}

void Window::Draw()
{
	(*Scenes())();
}

void Window::Show()
{
	_window->Show();
}

void Window::Hide()
{
	_window->Hide();
}

void Window::Close()
{
	_window->Close();
}

void Window::toggleFullscreen()
{
	_window->toggleFullscreen();
}

void Window::disableCursor()
{
	_window->disableCursor();
}

void Window::enableCursor()
{
	 _window->enableCursor();
}

bool Window::isFullscreen() const
{
	return _window->isFullscreen();
}

bool Window::isVisible() const
{
	return _window->isVisible();
}

bool Window::isDone() const
{
	return _window->isDone();
}

void Window::Key(const int key, const int scan, const int action, const int modifiers)
{
	for(auto &&f : _key_cbs) {
		f(key, scan, action, modifiers);
	}
}

void Window::Mouse(const int button, const int action, const int modifiers)
{
	for(auto &&f : _mouse_cbs) {
		f(button, action, modifiers);
	}
}

void Window::Move(const double x, const double y)
{
	for(auto &&f : _move_cbs) {
		f(x, y);
	}
}

void Window::Resize(const int width, const int height)
{
	for(auto &&f : _resize_cbs) {
		f(width, height);
	}
}

void Window::setCallback(const std::function<void(const int, const int, const int, const int)> &f)
{
	_key_cbs.push_back(f);
}

void Window::setCallback(const std::function<void(const int, const int, const int)> &f)
{
	_mouse_cbs.push_back(f);
}

void Window::setCallback(const std::function<void(const double, const double)> &f)
{
	_move_cbs.push_back(f);
}

void Window::setCallback(const std::function<void(const int, const int)> &f)
{
	_resize_cbs.push_back(f);
}

GlfwWindow::GlfwWindow(Entropy::Theia::Window *win, const std::string name, const std::size_t width, const std::size_t height)
	: GLFW::Window(name, width, height), _win(win)
{}

void GlfwWindow::Draw()
{
	_win->Draw();
}

void GlfwWindow::Key(const int key, const int code, const int action, const int modifiers)
{
	_win->Key(key, code, action, modifiers);
}

void GlfwWindow::Mouse(const int key, const int action, const int modifiers)
{
	_win->Mouse(key, action, modifiers);
}

void GlfwWindow::Move(const double x, const double y)
{
	_win->Move(x, y);
}

void GlfwWindow::Resize(const int width, const int height)
{
	GLFW::Window::Resize(width, height);
	_win->Resize(width, height);
}
