/*	Copyright 2017 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#if !defined ENTROPY_THEIA_EVENT_INC
#	define ENTROPY_THEIA_EVENT_INC

#	include "Types.hh"

	namespace Entropy
	{
		namespace Theia
		{
			class Event
			{
				public:
					Event(const std::size_t &);
					virtual ~Event();
					const std::size_t &Id() const;
				private:
					const std::size_t &_id;
			};
		}
	}

#endif
