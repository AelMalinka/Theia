/*	Copyright 2017 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#include "Application.hh"

#include <functional>

using namespace Entropy::Theia;
using namespace std;

Application::Application()
	: Entropy::Application(), _window("Theia Application", 640, 360)
{
	// 2017-06-04 AMR NOTE: ambiguous conversion from lambda(double, double) to function<void(double, double)> or function<void(int, int)>
	function<void(const int, const int, const int, const int)> kb = [this](int k, int c, int a, int m) {
		this->Key(k, c, a, m);
	};
	function<void(const int, const int, const int)> ms = [this](int b, int a, int m) {
		this->Mouse(b, a, m);
	};
	function<void(const double, const double)> mv = [this](double x, double y) {
		this->Move(x, y);
	};
	function<void(const int, const int)> rz = [this](int w, int h) {
		this->Resize(w, h);
	};

	_window->setCallbacks(kb, ms, mv, rz);
}

Application::Application(int ArgC, char *ArgV[])
	: Entropy::Application(ArgC, ArgV), _window(ArgV[0], 640, 360)
{
	function<void(const int, const int, const int, const int)> kb = [this](int k, int c, int a, int m) {
		this->Key(k, c, a, m);
	};
	function<void(const int, const int, const int)> ms = [this](int b, int a, int m) {
		this->Mouse(b, a, m);
	};
	function<void(const double, const double)> mv = [this](double x, double y) {
		this->Move(x, y);
	};
	function<void(const int, const int)> rz = [this](int w, int h) {
		this->Resize(w, h);
	};

	_window->setCallbacks(kb, ms, mv, rz);
}

Application::~Application() = default;

void Application::operator () ()
{
	bool done = false;

	_window->Show();
	while(!done) {
		(*_window)();

		done = true;
		for(auto &&w : _window) {
			if(!w.isDone())
				done = false;
		}
	}
}

DefaultedList<Window> &Application::Windows()
{
	return _window;
}

const DefaultedList<Window> &Application::Windows() const
{
	return _window;
}
