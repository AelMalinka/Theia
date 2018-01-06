/*	Copyright 2018 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#include "Box.hh"

#include <cstdlib>
#include "../GL/Bind.hh"

using namespace Entropy::Theia::UI;
using namespace Entropy::Theia;
using namespace Entropy::Theia::GL;
using namespace Entropy;
using namespace std;

Box::Box(const ScreenVertex v1, const ScreenVertex v2, const ScreenVertex v3, const ScreenVertex v4)
	: SharedData<detail::box>(), Element(), _vertices{v1.x, v1.y, v2.x, v2.y, v3.x, v3.y, v4.x, v4.y}
{
	Update();
}

Box::~Box() = default;

const ScreenVertex Box::Size() const
{
	return ScreenVertex( 
		abs(_vertices[0] - _vertices[4]),
		abs(_vertices[1] - _vertices[5])
	);
}

void Box::setVertices(const ScreenVertex v1, const ScreenVertex v2, const ScreenVertex v3, const ScreenVertex v4)
{
	_vertices[0] = v1.x;
	_vertices[1] = v1.y;
	_vertices[2] = v2.x;
	_vertices[3] = v2.y;
	_vertices[4] = v3.x;
	_vertices[5] = v3.y;
	_vertices[6] = v4.x;
	_vertices[7] = v4.y;

	Update();
}

const vector<ScreenDimension> &Box::Vertices() const
{
	return _vertices;
}

void Box::Update()
{
	Buffer buf(Buffer::Vertex);
	buf.Data(Vertices(), Buffer::Static);
	shared()->array.Bind(shared()->program, buf, "in_position"s, 2, GL_INT);
}

void Box::Draw()
{
	Bind p(shared()->program), a(shared()->array);
	shared()->program.SetUniform("in_color"s, FullColor());
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
}

void Box::UpdateScreen(const Screen &s)
{
	shared()->program.SetUniform("projection"s, s.Orthogonal());
}

using namespace Entropy::Theia::UI::detail;

box::box()
	: program(), array()
{
	string vert_code =
		"#version 130\n"

		"uniform mat4 projection;"

		"in vec2 in_position;"

		"void main() {"
			"gl_Position = projection * vec4(in_position, 0.0, 1.0);"
		"}"
	;

	string frag_code =
		"#version 130\n"

		"out vec4 out_color;"

		"uniform vec4 in_color;"

		"void main() {"
			"out_color = vec4(in_color);"
		"}"
	;

	Shader vert(Shader::Vertex, vert_code);
	Shader frag(Shader::Fragment, frag_code);

	program.Attach(vert);
	program.Attach(frag);
	program.Link();
}
