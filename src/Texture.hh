/*	Copyright 2016 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3'
*/

#if !defined ENTROPY_THEIA_TEXTURE_INC
#	define ENTROPY_THEIA_TEXTURE_INC

#	include "Exception.hh"

	namespace Entropy
	{
		namespace Theia
		{
			class Texture
			{
				public:
					enum Type
					{
						Texture2D,
					};
				public:
					Texture(const Type &, const std::string &);
					~Texture();
					GLenum GlType() const;
					const GLuint &Handle() const;
				private:
					GLenum type() const;
				private:
					GLuint _tex;
					Type _type;
			};

			ENTROPY_ERROR_INFO(TextureFile, std::string);
			ENTROPY_ERROR_INFO(TextureType, Texture::Type);
		}
	}

#endif
