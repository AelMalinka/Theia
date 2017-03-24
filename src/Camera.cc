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
	: _pos(0.0, 0.0, 10.0), _look_at(0.0, 0.0, 0.0), _up(0.0, 1.0, 0.0), _fov(glm::radians(45.0)), _near(0.0), _far(10.0)
{
	_cameras.insert(this);
	_view = glm::lookAt(_pos, _look_at, _up);
	_proj = glm::perspective(_fov, _aspect, _near, _far);
}

Camera::~Camera()
{
	_cameras.erase(this);
}

void Camera::Position(const Vertex &v)
{
	_pos = v;
	_view = glm::lookAt(_pos, _look_at, _up);
}

void Camera::LookAt(const Vertex &v)
{
	_look_at = v;
	_view = glm::lookAt(_pos, _look_at, _up);
}

void Camera::Up(const Vertex &v)
{
	_up = v;
	_view = glm::lookAt(_pos, _look_at, _up);
}

const Matrix &Camera::View() const
{
	return _view;
}

void Camera::Fov(const Point &v)
{
	_fov = glm::radians(v);
	_proj = glm::perspective(_fov, _aspect, _near, _far);
}

void Camera::Aspect(const Point &v)
{
	_aspect = v;
	_proj = glm::perspective(_fov, _aspect, _near, _far);
}

void Camera::Clipping(const Point &near, const Point &far)
{
	_near = near;
	_far = far;
	_proj = glm::perspective(_fov, _aspect, _near, _far);
}

const Matrix &Camera::Projection() const
{
	return _proj;
}

void Camera::setAspect(const int width, const int height)
{
	_aspect = width / height;

	for(auto &&i : _cameras) {
		i->_proj = glm::perspective(i->_fov, _aspect, i->_near, i->_far);
	}
}
