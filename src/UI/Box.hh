/*	Copyright 2018 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#if !defined ENTROPY_THEIA_UI_BOX_INC
#	define ENTROPY_THEIA_UI_BOX_INC

#	include "Element.hh"
#	include "../GL/Program.hh"
#	include "../GL/Array.hh"
#	include <vector>
#	include <initializer_list>
#	include <Entropy/SharedData.hh>

	namespace Entropy
	{
		namespace Theia
		{
			namespace UI
			{
				namespace detail
				{
					struct box
					{
						box();
						GL::Program program;
						GL::Array array;
					};
				}

				class Box :
					private SharedData<detail::box>,
					public Element
				{
					public:
						Box(const ScreenDimension, const ScreenDimension);
						virtual ~Box();
						const ScreenVertex Size() const;
						void setSize(const ScreenDimension, const ScreenDimension);
					protected:
						virtual void Draw();
						virtual void UpdateScreen(const Screen &);
					private:
						ScreenDimension _length;
						ScreenDimension _height;
				};
			}
		}
	}

#endif
