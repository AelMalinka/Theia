/*	Copyright 2016 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#if !defined ENTROPY_THEIA_BUFFER_INC
#	define ENTROPY_THEIA_BUFFER_INC

#	include "Exception.hh"

	namespace Entropy
	{
		namespace Theia
		{
			class Buffer
			{
				public:
					class Type
					{
						public:
							explicit Type(const GLenum &);
							const GLenum &Value() const;
							bool operator == (const Type &) const;
							bool operator != (const Type &) const;
						private:
							GLenum _val;
					};
					class Usage
					{
						public:
							explicit Usage(const GLenum &);
							const GLenum &Value() const;
							bool operator == (const Usage &) const;
							bool operator != (const Usage &) const;
						private:
							GLenum _val;
					};
					static const Type Vertex;
					static const Type Element;
					static const Usage Static;
					static const Usage Dynamic;
					static const Usage Stream;
				public:
					Buffer(const Type &);
					Buffer(const Buffer &) = delete;
					~Buffer();
					template<typename C>
					void Data(const C &, const Usage &);
					const std::size_t &size() const;
					const GLenum &GlType() const;
					const GLuint &Handle() const;
				private:
					GLuint _buffer;
					Type _type;
					std::size_t _count;
			};

			ENTROPY_ERROR_INFO(UsageInfo, Buffer::Usage);
			ENTROPY_ERROR_INFO(TypeInfo, Buffer::Type);
		}
	}

#	include "Buffer.impl.hh"

#endif
