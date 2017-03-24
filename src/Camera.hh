/*	Copyright 2016 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#if !defined ENTROPY_THEIA_CAMERA_INC
#	define ENTROPY_THEIA_CAMERA_INC

#	include <glm/glm.hpp>
#	include <set>

	namespace Entropy
	{
		namespace Theia
		{
			using Vertex = glm::vec3;
			using Point = Vertex::value_type;
			using Matrix = glm::mat4;

			class Camera
			{
				public:
					Camera();
					~Camera();
					void Position(const Vertex &);
					void LookAt(const Vertex &);
					void Up(const Vertex &);
					const Matrix &View() const;
					void Fov(const Point &);
					void Aspect(const Point &);
					void Clipping(const Point &, const Point &);
					const Matrix &Projection() const;
				public:
					static void setAspect(const int, const int);
				private:
					Vertex _pos;
					Vertex _look_at;
					Vertex _up;
					Matrix _view;
					Point _fov;
					Point _near;
					Point _far;
					Matrix _proj;
				private:
					static Point _aspect;
					static std::set<Camera *> _cameras;
			};
		}
	}

#endif
