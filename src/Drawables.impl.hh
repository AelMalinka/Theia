/*	Copyright 2017 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#if !defined ENTROPY_THEIA_DRAWABLES_IMPL
#	define ENTROPY_THEIA_DRAWABLES_IMPL

#	include "Drawables.hh"
#	include <utility>

	namespace Entropy
	{
		namespace Theia
		{
			template<typename T, typename ...Args>
			std::shared_ptr<T> Drawables::emplaceDrawable(Args && ...args)
			{
				std::shared_ptr<T> ptr = std::make_shared<T>(std::forward<Args>(args)...);

				_draws.push_back(ptr);
				NewDrawable(std::dynamic_pointer_cast<Drawable>(ptr));

				return ptr;
			}
		}
	}

#endif
