/*	Copyright 2017 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#if !defined ENTROPY_THEIA_IWINDOW_INC
#	define ENTROPY_THEIA_IWINDOW_INC

#	include "Screen.hh"
#	include "Context.hh"

	namespace Entropy
	{
		namespace Theia
		{
			class IWindow :
				public Screen
			{
				public:
					virtual void operator () () = 0;
					virtual void Draw() = 0;
					virtual void Show() = 0;
					virtual void Hide() = 0;
					virtual void Close() = 0;
					virtual void Fullscreen() = 0;
					virtual bool isDone() const = 0;
					virtual bool isVisible() const = 0;
					virtual bool isFullscreen() const = 0;
					virtual Context &getContext() = 0;
					virtual const Context &getContext() const = 0;
					// 2017-06-06 AMR TODO: cursor
				protected:
					virtual void onEvent(const Event &) = 0;
			};

		}
	}

#endif
