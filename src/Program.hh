/*	Copyright 2016 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#if !defined ENTROPY_THEIA_PROGRAM_INC
#	define ENTROPY_THEIA_PROGRAM_INC

#	include "Shader.hh"
#	include <array>

	namespace Entropy
	{
		namespace Theia
		{
			ENTROPY_ERROR_INFO(AttributeName, std::string);

			class Program
			{
				public:
					Program();
					Program(const Program &) = delete;
					~Program();
					void Attach(const Shader &);
					void Link();
					template<typename T>
					void SetUniform(const std::string &, const T &);
					void FragmentOut(const std::string &, const GLuint);
					const GLuint &Handle() const;
				private:
					GLuint _program;
			};
		}
	}

#	include "Program.impl.hh"
	
#endif
