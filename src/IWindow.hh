/*	Copyright 2017 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#if !defined ENTROPY_THEIA_IWINDOW_INC
#	define ENTROPY_THEIA_IWINDOW_INC

	namespace Entropy
	{
		namespace Theia
		{
			class IWindow
			{
				public:
					virtual void Show() = 0;
					virtual void Hide() = 0;
					virtual void Close() = 0;
					// 2017-05-29 AMR TODO: these are setup currently to match glfw, do we want it like this?
					virtual void toggleFullscreen() = 0;
					virtual void disableCursor() = 0;
					virtual void enableCursor() = 0;
					virtual bool isFullscreen() const = 0;
					virtual bool isVisible() const = 0;
					virtual bool isDone() const = 0;
					virtual void operator () () = 0;
				public:
					virtual void Draw() = 0;
					// 2017-05-29 AMR TODO: these are setup currently to match glfw, do we want it like this?
					virtual void Key(const int, const int, const int, const int) = 0;
					virtual void Mouse(const int, const int, const int) = 0;
					virtual void Move(const double, const double) = 0;
					virtual void Resize(const int, const int) = 0;
			};

		}
	}

#endif
