/*	Copyright 2016 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#include "Program.hh"

using namespace std;
using namespace Entropy::Theia;

Program::Program()
	: _program(0)
{
	_program = glCreateProgram();
	if (_program == 0)
		ENTROPY_THROW(Exception("failed to create program"));
}

Program::~Program()
{
	glDeleteProgram(_program);
}

void Program::Attach(const Shader &shader)
{
	glAttachShader(_program, shader.Handle());
	CHECK_GL_ERRORS("failed to attach shader");
}

void Program::Link()
{
	glLinkProgram(_program);
	CHECK_GL_ERRORS("failed to link program");
}

const GLuint &Program::Handle() const
{
	return _program;
}
