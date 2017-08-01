/*	Copyright 2016 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#include "Texture.hh"

#include <Entropy/PNG.hh>
#include "Bind.hh"

using namespace Entropy::Theia::GL;
using namespace std;

const Texture::Type Texture::Texture2D(GL_TEXTURE_2D);

const Texture::Filter Texture::Linear(GL_LINEAR);
const Texture::Filter Texture::Nearest(GL_NEAREST);

const Texture::Repeat Texture::ClampEdge(GL_CLAMP_TO_EDGE);

const Texture::Format Texture::R(GL_RED);
const Texture::Format Texture::RGBA(GL_RGBA);

const Texture::Internal Texture::RGBA8(GL_RGBA8);
const Texture::Internal Texture::Red(GL_RED);

const Texture::Size Texture::UnsignedByte(GL_UNSIGNED_BYTE);

Texture::Texture(const Type &t, const string &name)
	: _tex(0), _type(t)
{
	glGenTextures(1, &_tex);
	Bind b(*this);
	PNG image(name);
	glTexImage2D(t.Value(), 0, RGBA8.Value(), image.Width(), image.Height(), 0, RGBA.Value(), UnsignedByte.Value(), image.data());
	CHECK_GL_ERRORS_WITH("failed to load texture data", PNGFileName(name));
}

Texture::Texture(const Type &t, const Texture::Format &f, const Texture::Internal &i, const GLuint width, const GLuint height, void *data, const Texture::Size &s)
	: _tex(0), _type(t)
{
	glGenTextures(1, &_tex);
	Bind b(*this);
	glTexImage2D(t.Value(), 0, i.Value(), width, height, 0, f.Value(), s.Value(), data);
	CHECK_GL_ERRORS("failed to load texture data");
}

Texture::~Texture()
{
	glDeleteTextures(1, &_tex);
}

void Texture::generateMipmaps()
{
	Bind b(*this);
	glGenerateMipmap(_type.Value());
	CHECK_GL_ERRORS("failed to load texture data");
}

void Texture::setUpscale(const Filter &f)
{
	Bind b(*this);
	glTexParameteri(_type.Value(), GL_TEXTURE_MAG_FILTER, f.Value());
	CHECK_GL_ERRORS("failed to set upscale value");
}

void Texture::setDownscale(const Filter &f)
{
	Bind b(*this);
	glTexParameteri(_type.Value(), GL_TEXTURE_MIN_FILTER, f.Value());
	CHECK_GL_ERRORS("failed to set downscale value");
}

void Texture::setRepeat(const Repeat &r)
{
	Bind b(*this);
	glTexParameteri(_type.Value(), GL_TEXTURE_WRAP_S, r.Value());
	glTexParameteri(_type.Value(), GL_TEXTURE_WRAP_T, r.Value());
	CHECK_GL_ERRORS("failed to set texture repeat values");
}

GLenum Texture::GlType() const
{
	return _type.Value();
}

const GLuint &Texture::Handle() const
{
	return _tex;
}

Texture::Type::Type(const GLenum &v)
	: _val(v)
{}

const GLenum &Texture::Type::Value() const
{
	return _val;
}

bool Texture::Type::operator == (const Type &o) const
{
	return _val == o._val;
}

bool Texture::Type::operator != (const Type &o) const
{
	return _val != o._val;
}

Texture::Filter::Filter(const GLint &v)
	: _val(v)
{}

const GLint &Texture::Filter::Value() const
{
	return _val;
}

bool Texture::Filter::operator == (const Filter &o) const
{
	return _val == o._val;
}

bool Texture::Filter::operator != (const Filter &o) const
{
	return _val != o._val;
}

Texture::Format::Format(const GLenum &v)
	: _val(v)
{}

const GLenum &Texture::Format::Value() const
{
	return _val;
}

bool Texture::Format::operator == (const Format &o) const
{
	return _val == o._val;
}

bool Texture::Format::operator != (const Format &o) const
{
	return _val != o._val;
}

Texture::Internal::Internal(const GLint &v)
	: _val(v)
{}

const GLint &Texture::Internal::Value() const
{
	return _val;
}

bool Texture::Internal::operator == (const Internal &o) const
{
	return _val == o._val;
}

bool Texture::Internal::operator != (const Internal &o) const
{
	return _val != o._val;
}

Texture::Repeat::Repeat(const GLenum &v)
	: _val(v)
{}

const GLenum &Texture::Repeat::Value() const
{
	return _val;
}

bool Texture::Repeat::operator == (const Repeat &o) const
{
	return _val == o._val;
}

bool Texture::Repeat::operator != (const Repeat &o) const
{
	return _val != o._val;
}

Texture::Size::Size(const GLenum &v)
	: _val(v)
{}

const GLenum &Texture::Size::Value() const
{
	return _val;
}

bool Texture::Size::operator == (const Size &o) const
{
	return _val == o._val;
}

bool Texture::Size::operator != (const Size &o) const
{
	return _val != o._val;
}
