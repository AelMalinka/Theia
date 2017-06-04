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

	GLint status;
	glGetProgramiv(_program, GL_LINK_STATUS, &status);

	if(status != GL_TRUE) {
		GLint len = 0;
		glGetProgramiv(_program, GL_INFO_LOG_LENGTH, &len);
		GLchar *buf = new GLchar [len];
		glGetProgramInfoLog(_program, len, &len, buf);
		ENTROPY_THROW(Exception("Failed to link program") <<
			InfoLog(buf)
		);
	}
}

const GLuint &Program::Handle() const
{
	return _program;
}
