/*	Copyright 2017 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#if !defined ENTROPY_THEIA_SCENE_INC
#	define ENTROPY_THEIA_SCENE_INC

#	include "Drawable.hh"
#	include "Camera.hh"
#	include "Utility/DefaultedList.hh"
#	include "Utility/PolymorphicList.hh"

	namespace Entropy
	{
		namespace Theia
		{
			class Scene
			{
				public:
					Scene();
					virtual ~Scene();
					virtual void operator () ();
				public:
					void reset();
					DefaultedList<Camera>::iterator addCamera();
				public:
					void clear();
					void push_front(const std::shared_ptr<Drawable> &);
					template<typename U, typename = typename std::enable_if<std::is_base_of<Drawable, U>::value>::type>
					void push_front(U &&);
					template<typename U, typename ...Args>
					void emplace_front(Args && ...);
					void push_back(const std::shared_ptr<Drawable> &);
					template<typename U, typename = typename std::enable_if<std::is_base_of<Drawable, U>::value>::type>
					void push_back(U &&);
					template<typename U, typename ...Args>
					void emplace_back(Args && ...);
				private:
					DefaultedList<Camera> _cameras;
					PolymorphicList<Drawable> _draws;
			};
		}
	}

#	include "Scene.impl.hh"

#endif
