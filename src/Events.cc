/*	Copyright 2017 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#include "Events.hh"

using namespace Entropy::Theia;
using namespace Entropy::Theia::Events;

constexpr std::size_t Key::Id;
constexpr std::size_t Mouse::Id;
constexpr std::size_t Resize::Id;

Key::Key(const int k, const int a, const int m)
	: Event(Id), _key(k), _action(a), _mods(m)
{}

Key::~Key() = default;

const int &Key::Code() const
{
	return _key;
}

const int &Key::Action() const
{
	return _action;
}

const int &Key::Modifiers() const
{
	return _mods;
}

bool Key::hasShift() const
{
	return _mods & GLFW_MOD_SHIFT;
}

bool Key::hasControl() const
{
	return _mods & GLFW_MOD_CONTROL;
}

bool Key::hasAlt() const
{
	return _mods & GLFW_MOD_ALT;
}

Mouse::Mouse(const Dimension x, const Dimension y)
	: Event(Id), _x(x), _y(y)
{}

Mouse::~Mouse() = default;

const Dimension &Mouse::X() const
{
	return _x;
}

const Dimension &Mouse::Y() const
{
	return _y;
}

Resize::Resize(const ScreenDimension w, const ScreenDimension h)
	: Event(Id), _width(w), _height(h)
{}

const ScreenDimension &Resize::Width() const
{
	return _width;
}

const ScreenDimension &Resize::Height() const
{
	return _height;
}
