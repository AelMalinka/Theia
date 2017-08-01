/*	Copyright 2017 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#if !defined ENTROPY_THEIA_WINDOW_INC
#	define ENTROPY_THEIA_WINDOW_INC

#	include <vector>
#	include <functional>
#	include <chrono>
#	include <Entropy/Tethys/UV/Timer.hh>

#	include "IWindow.hh"
#	include "Utility/DefaultedList.hh"
#	include "Scene.hh"

	namespace Entropy
	{
		namespace Theia
		{
			class Window :
				public Tethys::UV::Timer
			{
				public:
					template<typename ...F>
					Window(const std::string &, const std::size_t, const std::size_t, F && ...);
					template<typename ...F>
					explicit Window(const std::shared_ptr<IWindow> &, F && ...);
					virtual ~Window();
				public:
					virtual void operator () ();
					virtual void Draw();
					virtual void Show();
					virtual void Hide();
					virtual void Close();
					virtual void Fullscreen();
					virtual bool isDone() const;
					virtual bool isFullscreen() const;
					virtual bool isVisible() const;
					virtual void onEvent(const Event &);
				public:
					virtual void setFoV(const Dimension &);
					virtual void setNearClipping(const Dimension &);
					virtual void setFarClipping(const Dimension &);
				public:
					DefaultedList<Scene> &Scenes();
					const DefaultedList<Scene> &Scenes() const;
					DefaultedList<Scene>::iterator addScene();
					template<typename ...F>
					void addCallbacks(F && ...);
				private:
					void make_window(const std::string &, const std::size_t, const std::size_t);
				private:
					std::shared_ptr<IWindow> _window;
					std::shared_ptr<DefaultedList<Scene>> _scene;
					std::vector<std::function<void(const Event &)>> _cbs;
					std::chrono::high_resolution_clock::time_point _last;
			};
		}
	}

#	include "Window.impl.hh"

#endif
