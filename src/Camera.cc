/*	Copyright 2016 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#include "Camera.hh"

#include <glm/gtc/matrix_transform.hpp>

using namespace Entropy::Theia;
using namespace std;
using namespace glm;

Dimension Camera::_aspect(16.0f / 9.0f);
set<Camera *> Camera::_cameras;

Camera::Camera()
	: _pos(0.0f, 0.0f, 10.0f), _look_at(0.0f, 0.0f, 0.0f), _up(0.0f, 1.0f, 0.0f),
	_fov(glm::radians(45.0f)), _near(0.0f), _far(10.0f),
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

void Camera::setFov(const Dimension &v)
{
	_fov = glm::radians(v);

	update_proj();
}

void Camera::setClipping(const Dimension &n, const Dimension &f)
{
	_near = n;
	_far = f;

	update_proj();
}

void Camera::setAspect(const int width, const int height)
{
	_aspect = static_cast<float>(width) / static_cast<float>(height);

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

const Dimension &Camera::Fov() const
{
	return _fov;
}

const Dimension &Camera::Near() const
{
	return _near;
}

const Dimension &Camera::Far() const
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

const Dimension &Camera::Aspect()
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
