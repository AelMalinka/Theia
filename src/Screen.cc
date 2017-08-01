/*	Copyright 2017 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#include "Screen.hh"

#include <glm/gtc/matrix_transform.hpp>

using namespace Entropy::Theia;
using namespace std;

Screen::Screen()
	// 2017-06-07 AMR NOTE: if height is 0, aspect is NaN and there for glm asserts when we call Upate()
	: _perspective(), _orthogonal(), _size(640, 360), _clipping(0, 0), _fov(0), _cbs()
{}

Screen::~Screen() = default;

void Screen::addCallback(const function<void(Screen &)> &cb)
{
	_cbs.push_back(cb);
}

void Screen::clearCallbacks()
{
	_cbs.clear();
}

void Screen::setFoV(const Dimension v)
{
	FoV() = glm::radians(v);

	Update();
}

void Screen::setNearClipping(const Dimension v)
{
	NearClipping() = v;

	Update();
}

void Screen::setFarClipping(const Dimension v)
{
	FarClipping() = v;

	Update();
}

const Matrix &Screen::Perspective() const
{
	return _perspective;
}

const Matrix &Screen::Orthogonal() const
{
	return _orthogonal;
}

Dimension Screen::Width() const
{
	Dimension ret = get<0>(_size);
	return ret;
}

Dimension Screen::Height() const
{
	Dimension ret = get<1>(_size);
	return ret;
}

Dimension Screen::Aspect() const
{
	return Width() / Height();
}

const Dimension &Screen::NearClipping() const
{
	return get<0>(_clipping);
}

const Dimension &Screen::FarClipping() const
{
	return get<1>(_clipping);
}

const Dimension &Screen::FoV() const
{
	return _fov;
}

void Screen::Update()
{
	Dimension z = 0.0f;
	Dimension h = Height();
	Dimension w = Width();

	Perspective() = glm::perspective(FoV(), Aspect(), NearClipping(), FarClipping());
	Orthogonal() = glm::ortho(z, w, z, h);

	RunCallbacks();
}

void Screen::RunCallbacks()
{
	for(auto &&f : _cbs) {
		f(*this);
	}
}

void Screen::Resize(const ScreenDimension width, const ScreenDimension height)
{
	Width() = width;
	Height() = height;

	// 2017-06-06 AMR TODO: is this where we want this?
	glViewport(0, 0, Width(), Height());

	Update();
}

Matrix &Screen::Perspective()
{
	return _perspective;
}

Matrix &Screen::Orthogonal()
{
	return _orthogonal;
}

ScreenDimension &Screen::Width()
{
	return get<0>(_size);
}

ScreenDimension &Screen::Height()
{
	return get<1>(_size);
}

Dimension &Screen::NearClipping()
{
	return get<0>(_clipping);
}

Dimension &Screen::FarClipping()
{
	return get<1>(_clipping);
}

Dimension &Screen::FoV()
{
	return _fov;
}
