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
			namespace detail
			{
				template<typename F, typename Arg>
				void call_each(F f, Arg arg)
				{
					f(arg);
				}

				template<typename F, typename Arg, typename ...Args>
				void call_each(F f, Arg arg, Args ...args)
				{
					f(arg);
					call_each(f, args...);
				}
			}

			template<typename ...F>
			Window::Window(const std::string &name, const std::size_t width, const std::size_t height, F ...f)
				: _window(), _scene(), _key_cbs(), _mouse_cbs(), _move_cbs(), _resize_cbs()
			{
				make_window(name, width, height);
				setCallbacks(f...);
			}

			template<typename ...F>
			Window::Window(const std::shared_ptr<IWindow> &win, F ...f)
				: _window(win), _scene(), _key_cbs(), _mouse_cbs(), _move_cbs(), _resize_cbs()
			{
				setCallbacks(f...);
			}

			template<typename ...F>
			void Window::setCallbacks(F ...f)
			{
				detail::call_each([this](auto &&f){
					this->setCallback(f);
				}, f...);
			}
		}
	}

#endif
