/*	Copyright 2017 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#if !defined ENTROPY_THEIA_DRAWABLE_INC
#	define ENTROPY_THEIA_DRAWABLE_INC

#	include "Exception.hh"

#	include "Program.hh"
#	include <chrono>
#	include <glm/glm.hpp>

	namespace Entropy
	{
		namespace Theia
		{
			class Camera;

			using Vertex = glm::vec3;
			using Dimension = Vertex::value_type;
			using Matrix = glm::mat4;

			// 2017-03-24 AMR FIXME: find out if per object time keeping is too much pain
			class Drawable
			{
				public:
					Drawable(Program &, const std::string &, const std::string &, const std::string &);
					virtual ~Drawable();
					virtual void operator () ();
				protected:
					virtual void Draw() = 0;
					virtual void Update(const std::chrono::duration<double> &);
					virtual void UpdateModel(const Matrix &);
				public:
					virtual void UpdateView(const Camera &);
					virtual void UpdateProjection(const Camera &);
				private:
					Program &_program;
					std::string _model;
					std::string _view;
					std::string _proj;
					std::chrono::high_resolution_clock::time_point _last;
			};
		}
	}

#	include "Camera.hh"

#endif
