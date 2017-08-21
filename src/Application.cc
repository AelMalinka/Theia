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

#	ifdef DEBUG
		auto &w = *_window;
		_window->getContext().setDebug([&w](const Events::Debug &ev) {
			w.onEvent(ev);
		});
#	endif
}

Application::Application(const string &name)
	: Entropy::Tethys::Application(), _window(name, 640, 360)
{
	_window->addCallbacks([this](const Event &ev) {
		this->onEvent(ev);
	});

#	ifdef DEBUG
		auto &w = *_window;
		_window->getContext().setDebug([&w](const Events::Debug &ev) {
			w.onEvent(ev);
		});
#	endif
}

Application::Application(int ArgC, char *ArgV[])
	: Entropy::Tethys::Application(ArgC, ArgV), _window(ArgV[0], 640, 360)
{
	_window->addCallbacks([this](const Event &ev) {
		this->onEvent(ev);
	});

#	ifdef DEBUG
		auto &w = *_window;
		_window->getContext().setDebug([&w](const Events::Debug &ev) {
			w.onEvent(ev);
		});
#	endif
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

void Application::onEvent(const Event &ev)
{
	if(ev.Id() == Events::Debug::Id) {
		onDebug(dynamic_cast<const Events::Debug &>(ev));
	}
}

void Application::onDebug(const Events::Debug &d)
{
	using namespace Entropy::Theia::Events;

	Log::Severity sev;

	switch(d.getSeverity()) {
		case Debug::Severity::High:
			sev = Log::Severity::Error;
		break;
		case Debug::Severity::Medium:
			sev = Log::Severity::Warning;
		break;
		case Debug::Severity::Low:
			sev = Log::Severity::Info;
		break;
		case Debug::Severity::Notification:
			sev = Log::Severity::Debug;
		break;
		default:
			sev = Log::Severity::Info;
	}

	auto rec = Log.open_record(boost::log::keywords::severity = sev);
	if(rec) {
		boost::log::record_ostream strm(rec);

		strm << "GL Debug: ";

		switch(d.getSource()) {
			case Debug::Source::Api:
				strm << "API: ";
			break;
			case Debug::Source::WindowSystem:
				strm << "Window System: ";
			break;
			case Debug::Source::ShaderCompiler:
				strm << "Shader Compiler: ";
			break;
			case Debug::Source::ThirdParty:
				strm << "Third Party: ";
			break;
			case Debug::Source::Application:
				strm << "Application: ";
			break;
			case Debug::Source::Other:
				strm << "Other: ";
			break;
			default:
				strm << "Unknown: ";
		}

		switch(d.getType()) {
			case Debug::Type::Error:
				strm << "Error: ";
			break;
			case Debug::Type::DeprecatedBehavior:
				strm << "Deprecated Behavior: ";
			break;
			case Debug::Type::UndefinedBehavior:
				strm << "Undefined Behavior: ";
			break;
			case Debug::Type::Portability:
				strm << "Portability: ";
			break;
			case Debug::Type::Performance:
				strm << "Performance: ";
			break;
			case Debug::Type::Marker:
				strm << "Marker: ";
			break;
			case Debug::Type::PushGroup:
				strm << "Push Group: ";
			break;
			case Debug::Type::PopGroup:
				strm << "Pop Group: ";
			break;
			case Debug::Type::Other:
				strm << "Other: ";
			break;
			default:
				strm << "Unknown: ";
		}

		strm << d.getMessage() << " (" << d.getId() << ")";
		strm.flush();

		Log.push_record(boost::move(rec));
	}
}
