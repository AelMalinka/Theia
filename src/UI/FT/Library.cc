/*	Copyright 2017 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#include "Library.hh"

using namespace Entropy::Theia::UI::FT;
using namespace Entropy::Theia::UI;

Library::Library()
{
	if(FT_Init_FreeType(&_handle))
		ENTROPY_THROW(Exception("Failed to initialize freetype library"));
}

Library::~Library()
{
	FT_Done_FreeType(_handle);
}

FT_Library &Library::Handle()
{
	return _handle;
}
