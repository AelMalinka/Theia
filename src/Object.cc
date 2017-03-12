/*	Copyright 2017 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#include "Object.hh"

#include <glm/gtc/matrix_transform.hpp>

using namespace Entropy::Theia;
using namespace glm;

Object::Object()
	: _model()
{}

Object::~Object() = default;

void Object::Translate(const Vertex &val)
{
	_model = translate(_model, val);
}

void Object::Rotate(const Vertex::value_type &angle, const Vertex &dir)
{
	_model = rotate(_model, radians(angle), dir);
}

void Object::Scale(const Vertex &val)
{
	_model = scale(_model, val);
}

glm::mat4 &Object::Model()
{
	return _model;
}

const glm::mat4 &Object::Model() const
{
	return _model;
}
