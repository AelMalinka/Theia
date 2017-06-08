/*	Copyright 2016 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#include "Camera.hh"

#include <glm/gtc/matrix_transform.hpp>

using namespace Entropy::Theia;
using namespace std;
using namespace glm;

Camera::Camera(Screen &s)
	: _screen(s), _view(), _pos(), _look_at(), _up(), _cbs()
{}

Camera::~Camera() = default;

void Camera::setPosition(const Vertex &v)
{
	Position() = v;

	Update();
}

void Camera::setLookAt(const Vertex &v)
{
	LookAt() = v;

	Update();
}

void Camera::setUp(const Vertex &v)
{
	Up() = v;

	Update();
}

void Camera::addCallback(const function<void(Camera &)> &cb)
{
	_cbs.push_back(cb);
}

void Camera::clearCallbacks()
{
	_cbs.clear();
}

const Matrix &Camera::View() const
{
	return _view;
}

const Vertex &Camera::Position() const
{
	return _pos;
}

const Vertex &Camera::LookAt() const
{
	return _look_at;
}

const Vertex &Camera::Up() const
{
	return _up;
}

void Camera::Update()
{
	View() = glm::lookAt(Position(), LookAt(), Up());

	RunCallbacks();
}

void Camera::RunCallbacks()
{
	for(auto &&f : _cbs) {
		f(*this);
	}
}

Matrix &Camera::View()
{
	return _view;
}

Vertex &Camera::Position()
{
	return _pos;
}

Vertex &Camera::LookAt()
{
	return _look_at;
}

Vertex &Camera::Up()
{
	return _up;
}

Screen &Camera::getScreen()
{
	return _screen;
}
