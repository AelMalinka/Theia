/*	Copyright 2017 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#if !defined ENTROPY_THEIA_DRAWABLE_INC
#	define ENTROPY_THEIA_DRAWABLE_INC

#	include "Camera.hh"

#	include <chrono>

	namespace Entropy
	{
		namespace Theia
		{
			class Drawable
			{
				public:
					virtual void Draw() = 0;
					virtual void Update(const std::chrono::duration<double> &) = 0;
					virtual void UpdateModel() = 0;
					virtual void UpdateScreen(const Screen &) = 0;
					virtual void UpdateCamera(const Camera &) = 0;
			};
		}
	}

#endif
