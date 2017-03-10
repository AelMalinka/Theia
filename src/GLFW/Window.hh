/*	Copyright 2017 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#if !defined ENTROPY_GLFW_THEIA_WINDOW_INC
#	define ENTROPY_GLFW_THEIA_WINDOW_INC

#	include "Glfw.hh"

#	include "../Drawable.hh"

	namespace Entropy
	{
		namespace Theia
		{
			namespace GLFW
			{
				class Window :
					public Drawable
				{
					public:
						Window(const std::string &, const int, const int);
						virtual ~Window();
						virtual void Show();
						virtual void Hide();
						virtual void Close();
						virtual void toggleFullscreen();
						virtual void disableCursor();
						virtual void enableCursor();
						virtual bool isFullscreen() const;
						virtual bool isVisible() const;
						virtual bool isDone() const;
						virtual void operator () ();
					public:
						virtual void Key(const int key, const int scan, const int action, const int modifiers) = 0;
						virtual void Mouse(const int button, const int action, const int modifiers) = 0;
						virtual void Move(double xpos, double ypos) = 0;
					protected:
						virtual void _create_window(const std::string &);
						virtual GLFWmonitor *_get_monitor() const;
						virtual const GLFWvidmode *_get_mode() const;
					private:
						GLFWwindow *_handle;
						std::tuple<int, int , int, int> _size_pos;
						std::chrono::high_resolution_clock::time_point _last;
					private:
						static Glfw _glfw;
				};
			}
		}
	}

#endif
