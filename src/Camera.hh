/*	Copyright 2016 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#if !defined ENTROPY_THEIA_CAMERA_INC
#	define ENTROPY_THEIA_CAMERA_INC

#	include "Drawable.hh"

#	include <set>

	namespace Entropy
	{
		namespace Theia
		{
			// 2017-03-24 AMR FIXME: don't keep aspect global
			class Camera
			{
				public:
					Camera();
					~Camera();
					void setPosition(const Vertex &);
					void setLookAt(const Vertex &);
					void setUp(const Vertex &);
					void setFov(const Point &);
					void setClipping(const Point &, const Point &);
				public:
					const Vertex &Position() const;
					const Vertex &LookAt() const;
					const Vertex &Up() const;
					const Point &Fov() const;
					const Point &Near() const;
					const Point &Far() const;
					const Matrix &View() const;
					const Matrix &Projection() const;
				public:
					void addObject(Drawable &);
					void removeObject(Drawable &);
				public:
					static const Point &Aspect();
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
