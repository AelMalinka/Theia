/*	Copyright 2017 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#if !defined ENTROPY_THEIA_EVENT_INC
#	define ENTROPY_THEIA_EVENT_INC

#	include "Types.hh"
#	include <Entropy/Event.hh>

	namespace Entropy
	{
		namespace Theia
		{
			class Event :
				public Entropy::Event
			{
				public:
					Event(const std::size_t &);
					virtual ~Event();
					static constexpr std::size_t Last = 21;
			};
		}
	}

#endif
