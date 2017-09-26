/*	Copyright 2017 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#include "Font.hh"

using namespace Entropy::Theia::UI::FT;
using namespace Entropy::Theia::GL;
using namespace Entropy::Theia;
using namespace Entropy;
using namespace std;

Font::Font(const string &path, const size_t count, const FT_UInt height, const FT_Long slot, const FT_UInt width)
	: SharedData<detail::font>()
{
	Face face(path, slot);
	face.setPixelSizes(height, width);

	for(auto x = 0u; x < count; x++) {
		try
		{
			face.loadChar(x);
			_characters.insert(make_pair(x, make_shared<Character>(face.Glyph())));
		}
		catch(FailedGlyphLoad &e)
		{
			ENTROPY_LOG(Log, Severity::Info) << "Failed to load character " << e.get<CharCode>();
		}
	}
}

Font::Font(const Font &) = default;
Font::Font(Font &&) = default;

Font::Character &Font::operator [] (const size_t code)
{
	if(_characters.find(code) == _characters.end())
		ENTROPY_THROW(UI::Exception("Character not found in font"));
	return *_characters.find(code)->second;
}

const Font::Character &Font::operator [] (const size_t code) const
{
	if(_characters.find(code) == _characters.end())
		ENTROPY_THROW(UI::Exception("Character not found in font"));
	return *_characters.find(code)->second;
}

Font::Character::Character(const FT_GlyphSlot face) :
	_tex(
		Texture::Texture2D,
		Texture::R,
		Texture::Red,
		face->bitmap.width,
		face->bitmap.rows,
		face->bitmap.buffer
	),
	_size(face->bitmap.width, face->bitmap.rows),
	_bearing(face->bitmap_left, face->bitmap_top),
	_advance(face->advance.x)
{
	_tex.setRepeat(Texture::ClampEdge);
	_tex.setUpscale(Texture::Linear);
	_tex.setDownscale(Texture::Linear);
}

Texture &Font::Character::getTexture()
{
	return _tex;
}

ScreenDimension Font::Character::Advance() const
{
	return _advance;
}

const ScreenVertex &Font::Character::Size() const
{
	return _size;
}

const ScreenVertex &Font::Character::Bearing() const
{
	return _bearing;
}

using namespace Entropy::Theia::UI::FT::detail;

// 2017-09-25 AMR TODO: possibly refactor for enable/disable in draw calls
font::font()
{
	// 2017-09-25 AMR NOTE: allow texture 1 byte in size
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	// 2017-09-25 AMR NOTE: alpha is required
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}
