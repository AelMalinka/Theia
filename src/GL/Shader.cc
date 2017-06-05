/*	Copyright 2016 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#include "Shader.hh"

using namespace Entropy::Theia::GL;
using namespace std;

const Shader::Type Shader::Vertex(GL_VERTEX_SHADER);
const Shader::Type Shader::Fragment(GL_FRAGMENT_SHADER);
const Shader::Type Shader::Geometry(GL_GEOMETRY_SHADER);
const Shader::Type Shader::Compute(GL_COMPUTE_SHADER);

Shader::Shader(const Type &type, const string &code)
	: _shader(0)
{
	_shader = glCreateShader(type.Value());

	const GLchar *co = code.data();
	const GLchar **c = &co;

	glShaderSource(_shader, 1, c, NULL);
	glCompileShader(_shader);

	GLint status;
	glGetShaderiv(_shader, GL_COMPILE_STATUS, &status);

	if (_shader == 0 || status != GL_TRUE)
	{
		char buff[1024];
		glGetShaderInfoLog(_shader, 1024, NULL, buff);

		ENTROPY_THROW(
			Exception("Shader failed to compile") <<
			ShaderLog(buff)
		);
	}
}

Shader::~Shader()
{
	glDeleteShader(_shader);
}

const GLuint &Shader::Handle() const
{
	return _shader;
}

Shader::Type::Type(const GLenum &v)
	: _val(v)
{}

const GLenum &Shader::Type::Value() const
{
	return _val;
}

bool Shader::Type::operator == (const Type &o) const
{
	return o._val == _val;
}

bool Shader::Type::operator != (const Type &o) const
{
	return o._val != _val;
}
