/*	Copyright 2017 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#if !defined ENTROPY_THEIA_SCENE_INC
#	define ENTROPY_THEIA_SCENE_INC

#	include "Drawables.hh"
#	include "Camera.hh"
#	include <Entropy/DefaultedList.hh>

	namespace Entropy
	{
		namespace Theia
		{
			class Scene :
				public Drawables
			{
				public:
					Scene(Screen &);
					virtual ~Scene();
				protected:
					virtual void NewDrawable(const std::shared_ptr<Drawable> &);
				public:
					Camera &getCamera();
					const Camera &getCamera() const;
					DefaultedList<Camera>::iterator addCamera();
					void changeCamera(const DefaultedList<Camera>::iterator &);
					void removeCamera(const DefaultedList<Camera>::iterator &);
					void clearCameras();
				protected:
					virtual void ChangedCamera();
				private:
					DefaultedList<Camera> _cameras;
			};
		}
	}

#endif
