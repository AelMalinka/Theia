/*	Copyright 2016 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3'
*/

#if !defined ENTROPY_THEIA_GL_TEXTURE_INC
#	define ENTROPY_THEIA_GL_TEXTURE_INC

#	include "../Exception.hh"

	namespace Entropy
	{
		namespace Theia
		{
			namespace GL
			{
				class Texture
				{
					public:
						class Type;
						class Filter;
						class Format;
						class Internal;
						class Repeat;
						class Size;
						static const Size UnsignedByte;
					public:
						Texture(const Type &, const Format &, const Internal &, const GLuint, const GLuint, void *, const Size & = UnsignedByte);
						Texture(const Type &, const std::string &);
						~Texture();
						GLenum GlType() const;
						const GLuint &Handle() const;
					public:
						void generateMipmaps();
						void setUpscale(const Filter &);
						void setDownscale(const Filter &);
						void setRepeat(const Repeat &);
					public:
						static const Type Texture2D;
						static const Filter Linear;
						static const Filter Nearest;
						static const Format R;
						static const Format RGBA;
						static const Internal Red;
						static const Internal RGBA8;
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
						class Filter
						{
							public:
								explicit Filter(const GLint &);
								const GLint &Value() const;
								bool operator == (const Filter &) const;
								bool operator != (const Filter &) const;
							private:
								GLint _val;
						};
						class Format
						{
							public:
								explicit Format(const GLenum &);
								const GLenum &Value() const;
								bool operator == (const Format &) const;
								bool operator != (const Format &) const;
							private:
								GLenum _val;
						};
						class Internal
						{
							public:
								explicit Internal(const GLint &);
								const GLint &Value() const;
								bool operator == (const Internal &) const;
								bool operator != (const Internal &) const;
							private:
								GLint _val;
						};
						class Repeat
						{
							public:
								explicit Repeat(const GLenum &);
								const GLenum &Value() const;
								bool operator == (const Repeat &) const;
								bool operator != (const Repeat &) const;
							private:
								GLenum _val;
						};
						class Size
						{
							public:
								explicit Size(const GLenum &);
								const GLenum &Value() const;
								bool operator == (const Size &) const;
								bool operator != (const Size &) const;
							private:
								GLenum _val;
						};
					private:
						GLuint _tex;
						Type _type;
				};

				ENTROPY_ERROR_INFO(TextureFile, std::string);
				ENTROPY_ERROR_INFO(TextureType, Texture::Type);
			}
		}
	}

#endif
