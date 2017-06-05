/*	Copyright 2016 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#if !defined ENTROPY_THEIA_GL_BUFFER_IMPL
#	define ENTROPY_THEIA_GL_BUFFER_IMPL

#	include "Buffer.hh"
#	include "Bind.hh"

	namespace Entropy
	{
		namespace Theia
		{
			namespace GL
			{
				template<typename C>
				void Buffer::Data(const C &a, const Usage &u)
				{
					Bind b(*this);
					_count = a.size();
					glBufferData(_type.Value(), sizeof(typename C::value_type) * a.size(), a.data(), u.Value());
				}
			}
		}
	}

#endif
