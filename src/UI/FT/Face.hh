/*	Copyright 2017 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#if !defined ENTROPY_THEIA_UI_FT_FACE_INC
#	define ENTROPY_THEIA_UI_FT_FACE_INC

#	include "Library.hh"
#	include <Entropy/SharedData.hh>

	namespace Entropy
	{
		namespace Theia
		{
			namespace UI
			{
				namespace FT
				{
					ENTROPY_ERROR_INFO(CharCode, FT_ULong);
					ENTROPY_EXCEPTION(FailedGlyphLoad, "Failed to load glyph", UI::Exception);

					class Face :
						private SharedData<Library>
					{
						public:
							explicit Face(const std::string &path, const FT_Long slot = 0);
							~Face();
							void setPixelSizes(const FT_UInt height, const FT_UInt width = 0);
							void loadChar(const FT_ULong ch, const FT_UInt32 flags = FT_LOAD_RENDER);
							FT_GlyphSlot &Glyph();
						private:
							FT_Face _handle;
					};
				}
			}
		}
	}

#endif
