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

Box::Box(const ScreenDimension l, const ScreenDimension h)
	: SharedData<detail::box>(), Element(), _length(l), _height(h)
{}

Box::~Box() = default;

const ScreenVertex Box::Size() const
{
	return ScreenVertex(_length, _height);
}

void Box::setSize(const ScreenDimension l, const ScreenDimension h)
{
	_length = l;
	_height = h;
}

void Box::Draw()
{
	ScreenDimension
		x = Position().x,
		y = Position().y,
		l = Position().x + (_length * Scale()),
		h = Position().y + (_height * Scale())
	;

	vector<ScreenDimension> vertices = {
		x, h,
		l, h,
		x, y,
		l, y
	};

	Buffer buf(Buffer::Vertex);
	buf.Data(vertices, Buffer::Stream);
	shared()->array.Bind(shared()->program, buf, "in_position"s, 2, GL_INT);
	shared()->program.SetUniform("in_color"s, FullColor());

	Bind p(shared()->program), a(shared()->array);
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
