/*	Copyright 2016 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#include "Buffer.hh"

using namespace Entropy::Theia;

const Buffer::Type Buffer::Vertex(GL_ARRAY_BUFFER);
const Buffer::Type Buffer::Element(GL_ELEMENT_ARRAY_BUFFER);

const Buffer::Usage Buffer::Static(GL_STATIC_DRAW);
const Buffer::Usage Buffer::Dynamic(GL_DYNAMIC_DRAW);
const Buffer::Usage Buffer::Stream(GL_STREAM_DRAW);

Buffer::Buffer(const Type &t)
	: _buffer(0), _type(t), _count(0)
{
	glGenBuffers(1, &_buffer);
}

Buffer::~Buffer()
{
	glDeleteBuffers(1, &_buffer);
}

const size_t &Buffer::size() const
{
	return _count;
}

const GLenum &Buffer::GlType() const
{
	return _type.Value();
}

const GLuint &Buffer::Handle() const
{
	return _buffer;
}

Buffer::Type::Type(const GLenum &val)
	: _val(val)
{}

const GLenum &Buffer::Type::Value() const
{
	return _val;
}

bool Buffer::Type::operator == (const Buffer::Type &t) const
{
	return _val == t._val;
}

bool Buffer::Type::operator != (const Buffer::Type &t) const
{
	return _val != t._val;
}

Buffer::Usage::Usage(const GLenum &val)
	: _val(val)
{}

const GLenum &Buffer::Usage::Value() const
{
	return _val;
}

bool Buffer::Usage::operator == (const Usage &u) const
{
	return _val == u._val;
}

bool Buffer::Usage::operator != (const Usage &u) const
{
	return _val != u._val;
}
