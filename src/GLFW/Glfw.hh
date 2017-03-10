/*	Copyright 2017 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#if !defined ENTROPY_THEIA_GLFW_GLFW_INC
#	define ENTROPY_THEIA_GLFW_GLFW_INC

#	include "../Exception.hh"

	namespace Entropy
	{
		namespace Theia
		{
			ENTROPY_EXCEPTION(GlfwException, "GLFW Exception", Exception);
			ENTROPY_ERROR_INFO(GlfwErrorCode, int);

			class Glfw
			{
				public:
					Glfw();
					~Glfw();
			};
		}
	}

#endif
