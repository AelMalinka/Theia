/*	Copyright 2017 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#if !defined ENTROPY_GLFW_THEIA_WINDOW_INC
#	define ENTROPY_GLFW_THEIA_WINDOW_INC

#	include "Glfw.hh"

#	include "../IWindow.hh"
#	include "../Utility/SharedData.hh"

	namespace Entropy
	{
		namespace Theia
		{
			namespace GLFW
			{
				class Window :
					private SharedData<Glfw>,
					public IWindow
				{
					public:
						Window(const std::string &, const int, const int);
						virtual ~Window();
						virtual void operator () ();
						virtual void Show();
						virtual void Hide();
						virtual void Close();
						virtual void Fullscreen();
						virtual bool isDone() const;
						virtual bool isVisible() const;
						virtual bool isFullscreen() const;
						// 2017-06-06 AMR TODO: decide on interface for cursor
						virtual void disableCursor();
						virtual void enableCursor();
						virtual void onEvent(const Event &);
					protected:
						virtual void _create_window(const std::string &);
						virtual GLFWmonitor *_get_monitor() const;
						virtual const GLFWvidmode *_get_mode() const;
					private:
						GLFWwindow *_handle;
						std::tuple<int, int, int, int> _size_pos;
				};
			}
		}
	}

#endif
