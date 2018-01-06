/*	Copyright 2017 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#include "Element.hh"

using namespace Entropy::Theia::UI;
using namespace Entropy::Theia;
using namespace std;

Element::Element()
	: _pos(0, 0), _color(1.0, 1.0, 1.0, 1.0), _scale(1.0)
{}

Element::~Element() = default;

void Element::Update(const chrono::duration<double> &)
{
	Draw();
}

void Element::setPosition(const ScreenVertex &p)
{
	_pos = p;
}

void Element::setColor(const Vertex &c)
{
	_color.r = c.r;
	_color.g = c.g;
	_color.b = c.b;
}

void Element::setScale(const Dimension &s)
{
	_scale = s;
}

void Element::setTransparency(const Dimension &a)
{
	_color.a = a;
}

ScreenVertex Element::Position() const
{
	return _pos;
}

Vertex Element::Color() const
{
	return Vertex(_color.r, _color.g, _color.b);
}

Dimension Element::Scale() const
{
	return _scale;
}

Dimension Element::Transparency() const
{
	return _color.a;
}

FullVertex Element::FullColor() const
{
	return _color;
}
