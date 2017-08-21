/*	Copyright 2017 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#if !defined ENTROPY_THEIA_GLFW_GLFW_INC
#	define ENTROPY_THEIA_GLFW_GLFW_INC

#	include "../Context.hh"

	namespace Entropy
	{
		namespace Theia
		{
			ENTROPY_EXCEPTION(GlfwException, "GLFW Exception", Exception);
			ENTROPY_ERROR_INFO(GlfwErrorCode, int);

			class Glfw :
				public Context
			{
				public:
					Glfw();
					~Glfw();
					bool isDebug() const;
					void setDebug(const std::function<void(const Events::Debug &)> &);
			};
		}
	}

#endif
