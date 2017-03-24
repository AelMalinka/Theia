/*	Copyright 2016 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#if !defined ENTROPY_THEIA_CAMERA_INC
#	define ENTROPY_THEIA_CAMERA_INC

#	include "Drawable.hh"

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
					void Fov(const Point &);
					void Aspect(const Point &);
					void Clipping(const Point &, const Point &);
					const Matrix &View() const;
					const Matrix &Projection() const;
				public:
					void addObject(Drawable &);
					void removeObject(Drawable &);
				public:
					static void setAspect(const int, const int);
				private:
					void update_view();
					void update_proj();
				private:
					Vertex _pos;
					Vertex _look_at;
					Vertex _up;
					Point _fov;
					Point _near;
					Point _far;
					Matrix _view;
					Matrix _proj;
					std::set<Drawable *> _objs;
				private:
					static Point _aspect;
					static std::set<Camera *> _cameras;
			};
		}
	}

#endif
