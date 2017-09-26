/*	Copyright 2017 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#include "Face.hh"

using namespace Entropy::Theia::UI::FT;
using namespace Entropy::Theia::UI;
using namespace std;

Face::Face(const string &path, const FT_Long slot)
	: SharedData<Library>()
{
	if(FT_New_Face(shared()->Handle(), path.c_str(), slot, &_handle))
		ENTROPY_THROW(Exception("Failed to load font face"));
}

Face::~Face()
{
	FT_Done_Face(_handle);
}

void Face::setPixelSizes(const FT_UInt height, const FT_UInt width)
{
	FT_Set_Pixel_Sizes(_handle, width, height);
}

void Face::loadChar(const FT_ULong ch, const FT_UInt32 flags)
{
	if(FT_Load_Char(_handle, ch, flags))
		ENTROPY_THROW(FailedGlyphLoad() <<
			CharCode(ch)
		);
}

FT_GlyphSlot &Face::Glyph()
{
	return _handle->glyph;
}
