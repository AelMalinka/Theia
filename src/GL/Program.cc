/*	Copyright 2016 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#include "Program.hh"

using namespace Entropy::Theia::GL;
using namespace Entropy::Log;
using namespace std;

using Entropy::Theia::Log;

Program::Program()
	: _program(0)
{
	_program = glCreateProgram();
	if (_program == 0)
		ENTROPY_THROW(Exception("failed to create program"));

	ENTROPY_LOG(Log, Severity::Debug) << "Program " << Handle() << " created";
}

Program::~Program()
{
	glDeleteProgram(_program);
	ENTROPY_LOG(Log, Severity::Debug) << "Program " << Handle() << " deleted";
}

void Program::Attach(const Shader &shader)
{
	ENTROPY_LOG(Log, Severity::Debug) << "Attaching shader " << shader.Handle() << " to program " << Handle();
	glAttachShader(_program, shader.Handle());
	CHECK_GL_ERRORS("failed to attach shader");
}

void Program::Link()
{
	ENTROPY_LOG(Log, Severity::Debug) << "Linking program " << Handle();
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
