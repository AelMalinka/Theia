/*	Copyright 2017 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#if !defined ENTROPY_THEIA_SCENE_IMPL
#	define ENTROPY_THEIA_SCENE_IMPL

#	include "Scene.hh"

	namespace Entropy
	{
		namespace Theia
		{
			template<typename U, typename = typename std::enable_if<std::is_base_of<Drawable, U>::value>::type>
			void Scene::push_front(U &&u)
			{
				_draws.push_front(std::move(u));

				for(auto &&c : _cameras) {
					c.addObject(_draws.front());
				}
			}

			template<typename U, typename ...Args>
			void Scene::emplace_front(Args && ...args)
			{
				_draws.emplace_front<U>(std::forward<Args>(args)...);

				for(auto &&c : _cameras) {
					c.addObject(_draws.front());
				}
			}

			template<typename U, typename = typename std::enable_if<std::is_base_of<Drawable, U>::value>::type>
			void Scene::push_back(U &&u)
			{
				_draws.push_back(std::move(u));

				for(auto &&c : _cameras) {
					c.addObject(_draws.back());
				}
			}

			template<typename U, typename ...Args>
			void Scene::emplace_back(Args && ...args)
			{
				_draws.emplace_back<U>(std::forward<Args>(args)...);

				for(auto &&c : _cameras) {
					c.addObject(_draws.back());
				}
			}
		}
	}

#endif
