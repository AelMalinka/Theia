/*	Copyright 2017 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#include "Object.hh"

#include <glm/gtc/matrix_transform.hpp>

using namespace Entropy::Theia;
using namespace std;
using namespace glm;

Object::Object()
	: _model()
{}

Object::~Object() = default;

void Object::Translate(const Vertex &val)
{
	Model() = translate(Model(), val);
}

void Object::Rotate(const Dimension &angle, const Vertex &dir)
{
	Model() = rotate(Model(), radians(angle), dir);
}

void Object::Scale(const Vertex &val)
{
	Model() = scale(Model(), val);
}

void Object::Update(const chrono::duration<double> &)
{
	UpdateModel();
	Draw();
}

Matrix &Object::Model()
{
	return _model;
}

const Matrix &Object::Model() const
{
	return _model;
}
