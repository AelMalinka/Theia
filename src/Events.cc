/*	Copyright 2017 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#include "Events.hh"

using namespace Entropy::Theia;
using namespace Entropy::Theia::Events;
using namespace std;

constexpr std::size_t Debug::Id;
constexpr std::size_t Show::Id;
constexpr std::size_t Hide::Id;
constexpr std::size_t Close::Id;
constexpr std::size_t Resize::Id;
constexpr std::size_t Key::Id;
constexpr std::size_t Mouse::Id;

Debug::Debug(const Debug::Source &s, const Debug::Type &t, const unsigned int i, const Debug::Severity &v, const string &m)
	: Event(Id), _severity(v), _source(s), _type(t), _id(i), _message(m)
{}

const Debug::Source &Debug::getSource() const
{
	return _source;
}

const Debug::Type &Debug::getType() const
{
	return _type;
}

const unsigned int &Debug::getId() const
{
	return _id;
}

const Debug::Severity &Debug::getSeverity() const
{
	return _severity;
}

const string &Debug::getMessage() const
{
	return _message;
}

Show::Show(IWindow &win)
	: Event(Id), _win(win)
{}

IWindow &Show::Window() const
{
	return _win;
}

Hide::Hide(IWindow &win)
	: Event(Id), _win(win)
{}

IWindow &Hide::Window() const
{
	return _win;
}

Close::Close(IWindow &win)
	: Event(Id), _win(win)
{}

const IWindow &Close::Window() const
{
	return _win;
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

Key::Key(const int k, const int a, const int m)
	: Event(Id), _key(k), _action(a), _mods(m)
{}

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

const Dimension &Mouse::X() const
{
	return _x;
}

const Dimension &Mouse::Y() const
{
	return _y;
}
