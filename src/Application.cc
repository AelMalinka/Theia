/*	Copyright 2017 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#include "Application.hh"

#include <functional>

using namespace Entropy::Theia;
using namespace std;

Application::Application()
	: Entropy::Tethys::Application(), _window("Theia Application", 640, 360)
{
	_window->addCallbacks([this](const Event &ev) {
		this->onEvent(ev);
	});
}

Application::Application(const string &name)
	: Entropy::Tethys::Application(), _window(name, 640, 360)
{
	_window->addCallbacks([this](const Event &ev) {
		this->onEvent(ev);
	});
}

Application::Application(int ArgC, char *ArgV[])
	: Entropy::Tethys::Application(ArgC, ArgV), _window(ArgV[0], 640, 360)
{
	_window->addCallbacks([this](const Event &ev) {
		this->onEvent(ev);
	});
}

Application::~Application() = default;

void Application::operator () ()
{
	_window->Show();
	Add(*_window);

	Entropy::Tethys::Application::operator () ();
}

DefaultedList<Window> &Application::Windows()
{
	return _window;
}

const DefaultedList<Window> &Application::Windows() const
{
	return _window;
}
