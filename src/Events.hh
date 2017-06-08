/*	Copyright 2017 (c) Michael Thomas (malinka) <malinka@entropy-development.com> 
	Distributed under the terms of the GNU Affero General Public License v3
*/

#if !defined ENTROPY_THEIA_EVENTS_INC
#	define ENTROPY_THEIA_EVENTS_INC

#	include "Event.hh"

	namespace Entropy
	{
		namespace Theia
		{
			namespace Events
			{
				// 2017-06-06 AMR TODO: typing?
				class Key :
					public Event
				{
					public:
						static constexpr std::size_t Id = 10;
						Key(const int, const int, const int);
						virtual ~Key();
						const int &Code() const;
						const int &Action() const;
						const int &Modifiers() const;
						bool hasShift() const;
						bool hasControl() const;
						bool hasAlt() const;
					private:
						int _key;
						int _action;
						int _mods;
				};

				class Mouse :
					public Event
				{
					public:
						static constexpr std::size_t Id = 11;
						Mouse(const Dimension, const Dimension);
						virtual ~Mouse();
						const Dimension &X() const;
						const Dimension &Y() const;
					private:
						 Dimension _x;
						 Dimension _y;
				};

				class Resize :
					public Event
				{
					public:
						static constexpr std::size_t Id = 12;
						Resize(const ScreenDimension, const ScreenDimension);
						const ScreenDimension &Width() const;
						const ScreenDimension &Height() const;
					private:
						ScreenDimension _width;
						ScreenDimension _height;
				};
			}
		}
	}

#endif
