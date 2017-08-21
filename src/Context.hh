/*	Copyright 2017 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#if !defined ENTROPY_THEIA_CONTEXT_INC
#	define ENTROPY_THEIA_CONTEXT_INC

#	include "Events.hh"
#	include <functional>

	namespace Entropy
	{
		namespace Theia
		{
			class Context
			{
				public:
					virtual bool isDebug() const = 0;
					virtual void setDebug(const std::function<void(const Events::Debug &)> &) = 0;
			};
		}
	}

#endif
