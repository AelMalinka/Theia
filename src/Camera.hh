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
					void setFov(const Dimension &);
					void setClipping(const Dimension &, const Dimension &);
				public:
					const Vertex &Position() const;
					const Vertex &LookAt() const;
					const Vertex &Up() const;
					const Dimension &Fov() const;
					const Dimension &Near() const;
					const Dimension &Far() const;
					const Matrix &View() const;
					const Matrix &Projection() const;
				public:
					void addObject(Drawable &);
					void removeObject(Drawable &);
				public:
					static const Dimension &Aspect();
					static void setAspect(const int, const int);
				private:
					void update_view();
					void update_proj();
				private:
					Vertex _pos;
					Vertex _look_at;
					Vertex _up;
					Dimension _fov;
					Dimension _near;
					Dimension _far;
					Matrix _view;
					Matrix _proj;
					std::set<Drawable *> _objs;
				private:
					static Dimension _aspect;
					static std::set<Camera *> _cameras;
			};
		}
	}

#endif
