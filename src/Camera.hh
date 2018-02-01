/*	Copyright 2016 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#if !defined ENTROPY_THEIA_CAMERA_INC
#	define ENTROPY_THEIA_CAMERA_INC

#	include "Screen.hh"

	namespace Entropy
	{
		namespace Theia
		{
			class Camera
			{
				public:
					Camera(Screen &);
					virtual ~Camera();
				public:
					virtual void setPosition(const Vertex &);
					virtual void setLookAt(const Vertex &);
					virtual void setUp(const Vertex &);
					virtual void addCallback(const std::function<void(Camera &)> &);
					virtual void clearCallbacks();
					virtual void RunCallbacks();
				public:
					const Matrix &View() const;
					const Vertex &Position() const;
					const Vertex &LookAt() const;
					const Vertex &Up() const;
				protected:
					void Update();
				protected:
					// 2018-01-31 AMR TODO: why do SFINAE rules fail to choose the const version when protected isn't available?
					Matrix &view();
					Vertex &position();
					Vertex &lookAt();
					Vertex &up();
				private:
					Screen &_screen;
					Matrix _view;
					Vertex _pos;
					Vertex _look_at;
					Vertex _up;
					std::vector<std::function<void(Camera &)>> _cbs;
			};
		}
	}

#endif
