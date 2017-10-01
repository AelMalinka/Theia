/*	Copyright 2017 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#if !defined ENTROPY_THEIA_UI_FT_FONT_INC
#	define ENTROPY_THEIA_UI_FT_FONT_INC

#	include "Face.hh"
#	include <Entropy/SharedData.hh>
#	include "../../Types.hh"
#	include "../../GL/Texture.hh"
#	include <map>
#	include <memory>

	namespace Entropy
	{
		namespace Theia
		{
			namespace UI
			{
				namespace FT
				{
					namespace detail
					{
						struct font
						{
							font();
						};
					}

					class Font :
						private SharedData<detail::font>
					{
						public:
							class Character;
						public:
							explicit Font(const std::string &, const std::size_t = 127, const FT_UInt = 48, const FT_Long = 0, const FT_UInt = 0);
							Font(const Font &);
							Font(Font &&);
							Character &operator [] (const std::size_t);
							const Character &operator [] (const std::size_t) const;
						private:
							// 2017-09-25 AMR TODO: texture copying?
							std::map<std::size_t, std::shared_ptr<Character>> _characters;
						public:
							class Character
							{
								public:
									explicit Character(const FT_GlyphSlot);
									GL::Texture &getTexture();
									ScreenDimension Advance() const;
									const ScreenVertex &Size() const;
									const ScreenVertex &Bearing() const;
								private:
									GL::Texture _tex;
									ScreenVertex _size;
									ScreenVertex _bearing;
									ScreenDimension _advance;
							};
					};
				}
			}
		}
	}

#endif
