/*	Copyright 2017 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#include "Element.hh"

using namespace Entropy::Theia::UI;
using namespace Entropy::Theia;
using namespace std;

Element::Element()
	: _pos(0, 0), _color(0.0, 0.0, 0.0), _scale(1.0)
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
	_color = c;
}

void Element::setScale(const Dimension &s)
{
	_scale = s;
}

const ScreenVertex &Element::Position() const
{
	return _pos;
}

const Vertex &Element::Color() const
{
	return _color;
}

const Dimension &Element::Scale() const
{
	return _scale;
}
