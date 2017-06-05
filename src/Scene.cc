/*	Copyright 2017 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#include "Scene.hh"

using namespace Entropy::Theia;
using namespace std;

Scene::Scene() = default;
Scene::~Scene() = default;

void Scene::operator () ()
{
	for(auto &&d : _draws) {
		d();
	}
}

void Scene::reset()
{
	_cameras.clear();
}

Camera &Scene::getCamera()
{
	return *_cameras;
}

const Camera &Scene::getCamera() const
{
	return *_cameras;
}

DefaultedList<Camera>::iterator Scene::addCamera()
{
	_cameras.emplace_front();

	for(auto &&i : _draws) {
		_cameras.front().addObject(i);
	}

	return _cameras.begin();
}

void Scene::clear()
{
	for(auto &&c : _cameras) {
		for(auto &&i : _draws) {
			c.removeObject(i);
		}
	}

	_draws.clear();
}

void Scene::push_front(const shared_ptr<Drawable> &o)
{
	_draws.push_front(o);

	for(auto &&c : _cameras) {
		c.addObject(_draws.front());
	}
}

void Scene::push_back(const shared_ptr<Drawable> &o)
{
	_draws.push_back(o);

	for(auto &&c : _cameras) {
		c.addObject(_draws.back());
	}
}
