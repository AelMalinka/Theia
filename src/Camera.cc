/*	Copyright 2016 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#include "Camera.hh"

#include <glm/gtc/matrix_transform.hpp>

using namespace Entropy::Theia;
using namespace std;
using namespace glm;

Camera::Camera(Screen &s) :
	_screen(s),
	_view(),
	_pos(Vertex(0.0, 0.0, 10.0)),
	_look_at(Vertex(0.0, 0.0, 0.0)),
	_up(Vertex(0.0, 1.0, 0.0)),
	_cbs()
{
	Update();
}

Camera::~Camera() = default;

void Camera::setPosition(const Vertex &v)
{
	position() = v;

	Update();
}

void Camera::setLookAt(const Vertex &v)
{
	lookAt() = v;

	Update();
}

void Camera::setUp(const Vertex &v)
{
	up() = v;

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
	view() = glm::lookAt(Position(), LookAt(), Up());

	RunCallbacks();
}

void Camera::RunCallbacks()
{
	for(auto &&f : _cbs) {
		f(*this);
	}
}

Matrix &Camera::view()
{
	return _view;
}

Vertex &Camera::position()
{
	return _pos;
}

Vertex &Camera::lookAt()
{
	return _look_at;
}

Vertex &Camera::up()
{
	return _up;
}
