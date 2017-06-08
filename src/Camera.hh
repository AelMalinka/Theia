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
				public:
					const Matrix &View() const;
					const Vertex &Position() const;
					const Vertex &LookAt() const;
					const Vertex &Up() const;
				protected:
					void Update();
					void RunCallbacks();
				protected:
					Matrix &View();
					Vertex &Position();
					Vertex &LookAt();
					Vertex &Up();
					Screen &getScreen();
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
