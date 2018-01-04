/*	Copyright 2017 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#include "Text.hh"
#include <vector>

using namespace Entropy::Theia::UI;
using namespace Entropy::Theia::GL;
using namespace Entropy::Theia;
using namespace std;

Text::Text(string &&t, FT::Font &&f)
	: Element(), _value(move(t)), _font(make_shared<FT::Font>(move(f)))
{}

Text::Text(const string &t, const FT::Font &f)
	: Element(), _value(t), _font(make_shared<FT::Font>(f))
{}

Text::Text(string &&t, const shared_ptr<FT::Font> &f)
	: Element(), _value(move(t)), _font(f)
{}

Text::Text(const string &t, const shared_ptr<FT::Font> &f)
	: Element(), _value(t), _font(f)
{}

void Text::setValue(const string &v)
{
	_value = v;
}

void Text::setValue(string &&v)
{
	_value = move(v);
}

const string &Text::Value() const
{
	return _value;
}

const ScreenVertex Text::Size() const
{
	ScreenVertex r;
	for(auto &&c : Value()) {
		auto &&f = (*_font)[c];

		r.x += (f.Size().x + f.Bearing().x) * Scale();
		if(r.y < (f.Size().y + f.Bearing().y) * Scale())
			r.y = (f.Size().y + f.Bearing().y) * Scale();
	}

	return r;
}

void Text::Draw()
{
	Bind p(shared()->program), a(shared()->array);
	shared()->program.SetUniform("in_color"s, Color());
	Dimension pos = Position().x;

	for(auto &&c : Value()) {
		auto &&f = (*_font)[c];

		Dimension x = pos + f.Bearing().x * Scale();
		Dimension y = Position().y - (f.Size().y - f.Bearing().y) * Scale();

		Dimension w = f.Size().x * Scale();
		Dimension h = f.Size().y * Scale();

		vector<Dimension> vertices = {
			x,		y + h,	0.0, 0.0,
			x,		y,		0.0, 1.0,
			x + w,	y,		1.0, 1.0,

			x,		y + h,	0.0, 0.0,
			x + w,	y,		1.0, 1.0,
			x + w,	y + h,	1.0, 0.0,
		};

		shared()->buffer.Data(vertices, Buffer::Stream);

		Bind t(f.getTexture());
		glDrawArrays(GL_TRIANGLES, 0, 6);

		pos += (f.Advance() >> 6) * Scale();
	}
}

void Text::UpdateScreen(const Screen &s)
{
	shared()->program.SetUniform("projection"s, s.Orthogonal());
}

detail::text::text()
	: program(), array(), buffer(Buffer::Vertex)
{
	string vert_code =
		"#version 130\n"

		"in vec4 in_data;"
		"out vec2 texture_position;"

		"uniform mat4 projection;"

		"void main() {"
			"gl_Position = projection * vec4(in_data.xy, 0.0, 1.0);"
			"texture_position = in_data.zw;"
		"}"
	;

	string frag_code =
		"#version 130\n"

		"in vec2 texture_position;"
		"out vec4 out_color;"

		"uniform sampler2D uni_texture;"
		"uniform vec3 in_color;"

		"void main() {"
			"out_color = vec4(in_color, texture(uni_texture, texture_position).r);"
		"}"
	;

	Shader vert(Shader::Vertex, vert_code);
	Shader frag(Shader::Fragment, frag_code);

	program.Attach(vert);
	program.Attach(frag);
	program.Link();

	Bind a(array), b(buffer);
	array.Bind(program, buffer, "in_data"s, 4, GL_FLOAT);
}
