/*	Copyright 2017 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#include "Drawables.hh"

using namespace Entropy::Theia;
using namespace std;

Drawables::Drawables(Screen &s)
	: _screen(s), _draws()
{
	_screen.addCallback(bind(&Drawables::UpdateScreen, this, placeholders::_1));
}

Drawables::~Drawables() = default;

void Drawables::Update(const chrono::duration<double> &dt)
{
	for(auto &&d : _draws) {
		d.Update(dt);
	}
}

void Drawables::UpdateScreen(const Screen &s)
{
	for(auto &&d : _draws) {
		d.UpdateScreen(s);
	}
}

void Drawables::UpdateCamera(const Camera &c)
{
	for(auto &&d : _draws) {
		d.UpdateCamera(c);
	}
}

void Drawables::addDrawable(const shared_ptr<Drawable> &o)
{
	_draws.push_back(o);
	NewDrawable(o);
}

/*void Drawables::removeDrawables(const shared_ptr<Drawable> &o)
{
	_draws.erase(_draws.find(o));
}*/

void Drawables::clearDrawables()
{
	_draws.clear();
}

void Drawables::NewDrawable(const shared_ptr<Drawable> &o)
{
	o->UpdateScreen(_screen);
}

Screen &Drawables::getScreen()
{
	return _screen;
}
