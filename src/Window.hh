/*	Copyright 2017 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#if !defined ENTROPY_THEIA_WINDOW_INC
#	define ENTROPY_THEIA_WINDOW_INC

#	include <vector>
#	include <functional>

#	include "IWindow.hh"
#	include "Utility/DefaultedList.hh"
#	include "Scene.hh"

	namespace Entropy
	{
		namespace Theia
		{
			class Window :
				public IWindow
			{
				public:
					template<typename ...F>
					Window(const std::string &, const std::size_t, const std::size_t, F ...);
					template<typename ...F>
					explicit Window(const std::shared_ptr<IWindow> &, F ...);
					virtual ~Window();
					virtual void operator () ();
					DefaultedList<Scene> &Scenes();
					const DefaultedList<Scene> &Scenes() const;
					template<typename F, typename ...R>
					void setCallbacks(F, R ...);
					void setCallbacks();
					void setCallback(const std::function<void(const int, const int, const int, const int)> &);
					void setCallback(const std::function<void(const int, const int, const int)> &);
					void setCallback(const std::function<void(const double, const double)> &);
					void setCallback(const std::function<void(const int, const int)> &);
				public:
					virtual void Show();
					virtual void Hide();
					virtual void Close();
					virtual void toggleFullscreen();
					virtual void disableCursor();
					virtual void enableCursor();
					virtual bool isFullscreen() const;
					virtual bool isVisible() const;
					virtual bool isDone() const;
				public:
					virtual void Draw();
					virtual void Key(const int, const int, const int, const int);
					virtual void Mouse(const int, const int, const int);
					virtual void Move(const double, const double);
					virtual void Resize(const int, const int);
				private:
					virtual void make_window(const std::string &, const std::size_t, const std::size_t);
				private:
					std::shared_ptr<IWindow> _window;
					DefaultedList<Scene> _scene;
					std::vector<std::function<void(const int, const int, const int, const int)>> _key_cbs;
					std::vector<std::function<void(const int, const int, const int)>> _mouse_cbs;
					std::vector<std::function<void(const double, const double)>> _move_cbs;
					std::vector<std::function<void(const int, const int)>> _resize_cbs;
			};
		}
	}

#	include "Window.impl.hh"

#endif
