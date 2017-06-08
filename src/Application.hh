/*	Copyright 2017 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#if !defined ENTROPY_THEIA_APPLICATION_INC
#	define ENTROPY_THEIA_APPLICATION_INC

#	include <Entropy/Application.hh>

#	include "Window.hh"
#	include "Events.hh"

	namespace Entropy
	{
		namespace Theia
		{
			class Application :
				public Entropy::Application
			{
				public:
					Application();
					Application(const int, char *[]);
					virtual ~Application();
					virtual void operator () ();
					DefaultedList<Window> &Windows();
					const DefaultedList<Window> &Windows() const;
				protected:
					virtual void onEvent(const Event &) {}
				private:
					DefaultedList<Window> _window;
			};
		}
	}

#endif
