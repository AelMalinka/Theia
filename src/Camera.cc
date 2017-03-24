/*	Copyright 2016 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#include "Camera.hh"

#include <glm/gtc/matrix_transform.hpp>

using namespace Entropy::Theia;
using namespace std;
using namespace glm;

Point Camera::_aspect(16.0 / 9.0);
set<Camera *> Camera::_cameras;

Camera::Camera()
	: _pos(0.0, 0.0, 10.0), _look_at(0.0, 0.0, 0.0), _up(0.0, 1.0, 0.0),
	_fov(glm::radians(45.0)), _near(0.0), _far(10.0),
	_view(), _proj()
{
	_cameras.insert(this);

	update_view();
	update_proj();
}

Camera::~Camera()
{
	_cameras.erase(this);
}

void Camera::setPosition(const Vertex &v)
{
	_pos = v;

	update_view();
}

void Camera::setLookAt(const Vertex &v)
{
	_look_at = v;

	update_view();
}

void Camera::setUp(const Vertex &v)
{
	_up = v;

	update_proj();
}

void Camera::setFov(const Point &v)
{
	_fov = glm::radians(v);

	update_proj();
}

void Camera::setClipping(const Point &near, const Point &far)
{
	_near = near;
	_far = far;

	update_proj();
}

void Camera::setAspect(const int width, const int height)
{
	_aspect = width / height;

	for(auto &&i : _cameras) {
		i->update_proj();
	}
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

const Point &Camera::Fov() const
{
	return _fov;
}

const Point &Camera::Near() const
{
	return _near;
}

const Point &Camera::Far() const
{
	return _far;
}

const Matrix &Camera::View() const
{
	return _view;
}

const Matrix &Camera::Projection() const
{
	return _proj;
}

const Point &Camera::Aspect()
{
	return _aspect;
}

void Camera::addObject(Drawable &o)
{
	_objs.insert(&o);

	o.UpdateView(*this);
	o.UpdateProjection(*this);
}

void Camera::removeObject(Drawable &o)
{
	_objs.erase(&o);
}

void Camera::update_view()
{
	_view = glm::lookAt(_pos, _look_at, _up);

	for(auto &&i : _objs) {
		i->UpdateView(*this);
	}
}

void Camera::update_proj()
{
	_proj = glm::perspective(_fov, _aspect, _near, _far);

	for(auto &&i : _objs) {
		i->UpdateProjection(*this);
	}
}
