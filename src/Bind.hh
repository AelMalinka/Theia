/*	Copyright 2016 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#if !defined ENTROPY_THEIA_BIND_INC
#	define ENTROPY_THEIA_BIND_INC

#	include <functional>

	namespace Entropy
	{
		namespace Theia
		{
			class Program;
			class Array;
			class Buffer;
			class Texture;

			class Bind
			{
				public:
					Bind(const Program &);
					Bind(const Array &);
					Bind(const Buffer &);
					Bind(const Texture &);
					Bind(const Bind &) = delete;
					~Bind();
				private:
					std::function<void()> _clean;
			};
		}
	}

#endif
