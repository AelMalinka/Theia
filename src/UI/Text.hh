/*	Copyright 2017 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#if !defined ENTROPY_THEIA_UI_TEXT_INC
#	define ENTROPY_THEIA_UI_TEXT_INC

#	include "Element.hh"
#	include "FT/Font.hh"
#	include "../GL/Program.hh"
#	include "../GL/Array.hh"

	namespace Entropy
	{
		namespace Theia
		{
			namespace UI
			{
				namespace detail
				{
					struct text
					{
						text();
						GL::Program program;
						GL::Array array;
						GL::Buffer buffer;
					};
				}

				class Text :
					private SharedData<detail::text>,
					public Element
				{
					public:
						Text(std::string &&, FT::Font &&);
						Text(std::string &&, const std::shared_ptr<FT::Font> &);
						Text(const std::string &, const FT::Font &);
						Text(const std::string &, const std::shared_ptr<FT::Font> &);
						void setValue(const std::string &);
						void setValue(std::string &&);
						const std::string &Value() const;
						const ScreenVertex Size() const;
					protected:
						void Draw();
						void UpdateScreen(const Screen &);
					private:
						std::string _value;
						std::shared_ptr<FT::Font> _font;
				};
			}
		}
	}

#endif
