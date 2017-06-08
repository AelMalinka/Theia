/*	Copyright 2017 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#include "Scene.hh"

using namespace Entropy::Theia;
using namespace std;

Scene::Scene(Screen &s)
	: Drawables(s), _cameras(s)
{
	_cameras->addCallback(bind(&Scene::UpdateCamera, this, placeholders::_1));
}

Scene::~Scene() = default;

void Scene::NewDrawable(const shared_ptr<Drawable> &d)
{
	d->UpdateCamera(*_cameras);
	Drawables::NewDrawable(d);
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
	_cameras.emplace_front(getScreen());
	auto i = _cameras.begin();

	i->addCallback([this](const Camera &c) {
		this->UpdateCamera(c);
	});

	return i;
}

void Scene::changeCamera(const DefaultedList<Camera>::iterator &i)
{
	_cameras.setDefault(i);
	ChangedCamera();
}

void Scene::removeCamera(const DefaultedList<Camera>::iterator &i)
{
	_cameras.erase(i);
	// 2017-06-06 AMR TODO: only call when actually changed
	ChangedCamera();
}

void Scene::clearCameras()
{
	_cameras.clear(getScreen());
	_cameras->addCallback([this](const Camera &c) {
		this->UpdateCamera(c);
	});

	ChangedCamera();
}

void Scene::ChangedCamera()
{
	UpdateCamera(*_cameras);
}
