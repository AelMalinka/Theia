/*	Copyright 2016 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#if !defined ENTROPY_THEIA_ARRAY_INC
#	define ENTROPY_THEIA_ARRAY_INC

#	include "Exception.hh"

#	include "Program.hh"
#	include "Buffer.hh"

	namespace Entropy
	{
		namespace Theia
		{
			class Array
			{
				public:
					Array();
					~Array();
					void Bind(const Program &, const Buffer &, const std::string &, const std::size_t, const GLenum, const std::size_t = 0, const std::size_t = 0);
					template<typename C>
					void Elements(const C &a, const Buffer::Usage &);
					const GLuint &Handle() const;
				private:
					GLuint _vao;
			};
		}
	}

#	include "Array.impl.hh"

#endif
