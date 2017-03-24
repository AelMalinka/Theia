/*	Copyright 2017 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#if !defined ENTROPY_THEIA_DRAWABLE_INC
#	define ENTROPY_THEIA_DRAWABLE_INC

#	include "Exception.hh"

#	include <chrono>

	namespace Entropy
	{
		namespace Theia
		{
			class Camera;

			class Drawable
			{
				public:
					virtual void Draw(const std::chrono::duration<double> &) = 0;
					virtual void UpdateView(const Camera &) = 0;
					virtual void UpdateProjection(const Camera &) = 0;
			};
		}
	}

#	include "Camera.hh"

#endif
