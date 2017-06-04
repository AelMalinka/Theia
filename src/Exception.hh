/*	Copyright 2017 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#if !defined ENTROPY_THEIA_EXCEPTION_INC
#	define ENTROPY_THEIA_EXCEPTION_INC

#	include <Entropy/Exception.hh>

#	ifdef _WIN32
#		include <windows.h>
#	endif

#	include <epoxy/gl.h>
#	include <GL/glu.h>
#	include <GLFW/glfw3.h>

	namespace Entropy
	{
		namespace Theia
		{
			ENTROPY_EXCEPTION_BASE(Exception, "Theia Exception");
			ENTROPY_ERROR_INFO(GlError, const GLubyte *);
			ENTROPY_ERROR_INFO(GlErrorCode, GLenum);
		}
	}

#	define CHECK_GL_ERRORS(x) \
		{ GLenum status = glGetError(); \
			if(status != GL_NO_ERROR) \
				::boost::throw_exception(::boost::enable_error_info(Exception(x)) << \
				::boost::throw_function(BOOST_CURRENT_FUNCTION) << \
				::boost::throw_file(__FILE__) << \
				::boost::throw_line((int)__LINE__) << \
				::Entropy::Theia::GlErrorCode(status) << \
				::Entropy::Theia::GlError(gluErrorString(status))); \
		}

#	define CHECK_GL_ERRORS_WITH(x, z) \
		{ GLenum status = glGetError(); \
			if(status != GL_NO_ERROR) \
				::boost::throw_exception(::boost::enable_error_info(Exception(x)) << \
				::boost::throw_function(BOOST_CURRENT_FUNCTION) << \
				::boost::throw_file(__FILE__) << \
				::boost::throw_line((int)__LINE__) << \
				::Entropy::Theia::GlErrorCode(status) << \
				::Entropy::Theia::GlError(gluErrorString(status)) << \
				z);\
		}

#endif
