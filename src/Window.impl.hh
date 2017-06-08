/*	Copyright 2017 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#if !defined ENTROPY_THEIA_WINDOW_IMPL
#	define ENTROPY_THEIA_WINDOW_IMPL

#	include "Window.hh"

	namespace Entropy
	{
		namespace Theia
		{
			template<typename ...F>
			Window::Window(const std::string &name, const std::size_t width, const std::size_t height, F && ...f)
				: _window(), _scene(), _cbs(), _last(std::chrono::high_resolution_clock::now())
			{
				make_window(name, width, height);
				addCallbacks(std::forward(f)...);
			}

			template<typename ...F>
			Window::Window(const std::shared_ptr<IWindow> &win, F && ...f)
				: _window(win), _scene(std::make_shared<DefaultedList<Scene>>(*_window)), _cbs(), _last(std::chrono::high_resolution_clock::now())
			{
				addCallbacks(std::forward(f)...);
			}

			template<typename ...F>
			void Window::addCallbacks(F && ...r)
			{
				std::vector<std::function<void(const Event &)>> cbs = { r... };
				for(auto &&f : cbs) {
					_cbs.push_back(f);
				}
			}
		}
	}

#endif
