/*	Copyright 2016 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#if !defined ENTROPY_THEIA_PROGRAM_IMPL
#	define ENTROPY_THEIA_PROGRAM_IMPL

#	include "Program.hh"
#	include "Bind.hh"

#	include <glm/glm.hpp>
#	include <glm/gtc/type_ptr.hpp>

	namespace Entropy
	{
		namespace Theia
		{
			template<>
			inline void Program::SetUniform(const std::string &where, const int &value)
			{
				Bind t(*this);
				GLint w = glGetUniformLocation(_program, where.c_str());
				glUniform1i(w, value);
				CHECK_GL_ERRORS("failed to set uniform (1i)");
			}

			template<>
			inline void Program::SetUniform(const std::string &where, const glm::vec3 &value)
			{
				Bind t(*this);
				GLint w = glGetUniformLocation(_program, where.c_str());
				glUniform3fv(w, 1, glm::value_ptr(value));
				CHECK_GL_ERRORS("failed to set uniform (3fv)");
			}

			template<>
			inline void Program::SetUniform(const std::string &where, const glm::mat4 &value)
			{
				Bind t(*this);
				GLint w = glGetUniformLocation(_program, where.c_str());
				glUniformMatrix4fv(w, 1, GL_FALSE, glm::value_ptr(value));
				CHECK_GL_ERRORS("failed to set uniform (Matrix4fv)");
			}
		}
	}

#endif
