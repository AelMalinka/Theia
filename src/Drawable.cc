/*	Copyright 2017 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#include "Drawable.hh"

using namespace Entropy::Theia;
using namespace std;

Drawable::Drawable(GL::Program &prog, const string &m, const string &v, const string  &p)
	: _program(prog), _model(m), _view(v), _proj(p), _last(chrono::high_resolution_clock::now())
{}

Drawable::~Drawable() = default;

void Drawable::operator () ()
{
	using namespace std::chrono;

	auto tp = high_resolution_clock::now();

	Update(duration_cast<duration<double>>(tp - _last));
	Draw();

	_last = tp;
}

void Drawable::Update(const chrono::duration<double> &)
{}

void Drawable::UpdateModel(const Matrix &v)
{
	_program.SetUniform(_model, v);
}

void Drawable::UpdateView(const Camera &c)
{
	_program.SetUniform(_view, c.View());
}

void Drawable::UpdateProjection(const Camera &c)
{
	_program.SetUniform(_proj, c.Projection());
}
