/*	Copyright 2016 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#include "Texture.hh"

#include <Entropy/PNG.hh>
#include "Bind.hh"

using namespace std;
using namespace Entropy::Theia;

Texture::Texture(const Type &t, const string &name)
	: _tex(0), _type(t)
{
	glGenTextures(1, &_tex);
	Bind b(*this);
	PNG image(name);
	glTexImage2D(type(), 0, GL_RGBA8, image.Width(), image.Height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, image.data());
	CHECK_GL_ERRORS_WITH("failed to load texture data", PNGFileName(name));
	glGenerateMipmap(GL_TEXTURE_2D);
	CHECK_GL_ERRORS_WITH("failed to generate mipmap", PNGFileName(name));
}

Texture::~Texture()
{
	glDeleteTextures(1, &_tex);
}

GLenum Texture::GlType() const
{
	return type();
}

const GLuint &Texture::Handle() const
{
	return _tex;
}

GLenum Texture::type() const
{
	switch (_type)
	{
		case Texture2D:
			return GL_TEXTURE_2D;
		default:
			ENTROPY_THROW(
				Exception("Invalid Enum Value") <<
				TextureType(_type)
			);
	}
}
