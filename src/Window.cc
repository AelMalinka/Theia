/*	Copyright 2017 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#include "Window.hh"

#include "GLFW/Window.hh"

using namespace Entropy::Theia;
using namespace std;
using namespace std::chrono;

struct GlfwWindow :
	public GLFW::Window
{
	GlfwWindow(Entropy::Theia::Window *, const std::string, const std::size_t, const std::size_t);
	void Draw();
	void onEvent(const Event &);
	private:
		Entropy::Theia::Window *_win;
};

Window::~Window() = default;

void Window::operator () ()
{
	if(!_window->isDone())
		(*_window)();
	else
		Stop();
}

DefaultedList<Scene> &Window::Scenes()
{
	return *_scene;
}

const DefaultedList<Scene> &Window::Scenes() const
{
	return *_scene;
}

DefaultedList<Scene>::iterator Window::addScene()
{
	_scene->emplace_back(*_window);
	return --_scene->end();
}

void Window::make_window(const string &name, const size_t width, const size_t height)
{
	_window = make_shared<GlfwWindow>(this, name, width, height);
	_scene = make_shared<DefaultedList<Scene>>(*_window);
}

void Window::Draw()
{
	auto tp = high_resolution_clock::now();
	auto dt = duration_cast<duration<double>>(tp - _last);
	_last = tp;

	Scenes()->Update(dt);
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

void Window::Fullscreen()
{
	_window->Fullscreen();
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

Context &Window::getContext()
{
	return _window->getContext();
}

const Context &Window::getContext() const
{
	return _window->getContext();
}

void Window::onEvent(const Event &ev)
{
	for(auto &&f : _cbs) {
		f(ev);
	}
}

void Window::setFoV(const Dimension &v)
{
	_window->setFoV(v);
}

void Window::setNearClipping(const Dimension &v)
{
	_window->setNearClipping(v);
}

void Window::setFarClipping(const Dimension &v)
{
	_window->setFarClipping(v);
}

GlfwWindow::GlfwWindow(Entropy::Theia::Window *win, const std::string name, const std::size_t width, const std::size_t height)
	: GLFW::Window(name, width, height), _win(win)
{}

void GlfwWindow::Draw()
{
	_win->Draw();
}

void GlfwWindow::onEvent(const Event &ev)
{
	_win->onEvent(ev);
	GLFW::Window::onEvent(ev);
}
