/*	Copyright 2016 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#include "Bind.hh"
#include "Buffer.hh"
#include "Array.hh"
#include "Program.hh"
#include "Texture.hh"

using namespace Entropy::Theia::GL;
using namespace Entropy::Log;

using Entropy::Theia::Exception;
using Entropy::Theia::Log;

GLenum buffer(const GLenum &t)
{
	switch(t)
	{
		case GL_ARRAY_BUFFER:
			return GL_ARRAY_BUFFER_BINDING;
		case GL_ELEMENT_ARRAY_BUFFER:
			return GL_ELEMENT_ARRAY_BUFFER_BINDING;
		default:
			ENTROPY_THROW(Exception("Unknown buffer type to bind"));
	}
}

GLenum texture(const GLenum &t)
{
	switch(t)
	{
		case GL_TEXTURE_2D:
			return GL_TEXTURE_BINDING_2D;
		default:
			ENTROPY_THROW(Exception("Unknown texture type to bind"));
	}
}

Bind::Bind(const Program &p)
{
	GLint o;
	glGetIntegerv(GL_CURRENT_PROGRAM, &o);

	ENTROPY_LOG(Log, Severity::Trace) << "Binding program " << p.Handle();
	glUseProgram(p.Handle());

	_clean = [o](){
		glUseProgram(o);
	};
}

Bind::Bind(const Array &a)
{
	GLint o;
	glGetIntegerv(GL_VERTEX_ARRAY_BINDING, &o);

	ENTROPY_LOG(Log, Severity::Trace) << "Binding array " << a.Handle();
	glBindVertexArray(a.Handle());

	_clean = [o]() {
		glBindVertexArray(o);
	};
}

Bind::Bind(const Buffer &b)
{
	GLint o;
	auto t = b.GlType();
	glGetIntegerv(buffer(t), &o);

	ENTROPY_LOG(Log, Severity::Trace) << "Binding buffer " << b.Handle() << " (" << b.GlType() << ")";
	glBindBuffer(t, b.Handle());

	_clean = [t, o]() {
		glBindBuffer(t, o);
	};
}

Bind::Bind(const Texture &t)
{
	GLint o;
	auto w = t.GlType();
	glGetIntegerv(texture(w), &o);

	ENTROPY_LOG(Log, Severity::Trace) << "Binding texture " << t.Handle() << " (" << t.GlType() << ")";
	glBindTexture(w, t.Handle());

	_clean = [w, o]() {
		glBindTexture(w, o);
	};
}

Bind::~Bind()
{
	_clean();
}
