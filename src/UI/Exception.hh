/*	Copyright 2017 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#if !defined ENTROPY_THEIA_UI_EXCEPTION
#	define ENTROPY_THEIA_UI_EXCEPTION

#	include "../Exception.hh"

	namespace Entropy
	{
		namespace Theia
		{
			namespace UI
			{
				ENTROPY_EXCEPTION(Exception, "Theia UI Exception", Theia::Exception);
			}
		}
	}

#endif
