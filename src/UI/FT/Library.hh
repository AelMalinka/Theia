/*	Copyright 2017 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#if !defined ENTROPY_THEIA_UI_FT_LIBRARY_INC
#	define ENTROPY_THEIA_UI_FT_LIBRARY_INC

#	include "../Exception.hh"
#	include <ft2build.h>
#	include FT_FREETYPE_H

	namespace Entropy
	{
		namespace Theia
		{
			namespace UI
			{
				namespace FT
				{
					class Library
					{
						public:
							Library();
							~Library();
							FT_Library &Handle();
						private:
							FT_Library _handle;
					};
				}
			}
		}
	}

#endif
