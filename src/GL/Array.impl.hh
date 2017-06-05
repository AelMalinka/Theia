/*	Copyright 2017 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#if !defined ENTROPY_THEIA_GL_ARRAY_IMPL
#	define ENTROPY_THEIA_GL_ARRAY_IMPL

#	include "Array.hh"
#	include "Bind.hh"

	namespace Entropy
	{
		namespace Theia
		{
			namespace GL
			{
				template<typename C>
				void Array::Elements(const C &a, const Buffer::Usage &u)
				{
					Buffer el(Buffer::Element);
					el.Data(a, u);

					// 2017-06-04 AMR NOTE: fix binding of element array
					GL::Bind *t = new GL::Bind(*this);
					GL::Bind e(el);
					delete t;
				}
			}
		}
	}

#endif
