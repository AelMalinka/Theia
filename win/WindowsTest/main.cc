/*	Copyright 2017 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#include <cstdlib>
#include <iostream>
#include <vector>

#include <Entropy/Theia/Application.hh>

using namespace std;
using namespace Entropy::Theia;

const size_t MAX_BUFFSIZE = 4096;

class MyObject
{};

class Application :
	public Entropy::Theia::Application
{
	public:
		explicit Application(const string &);
	protected:
		void onEvent(const Event &);
};

int APIENTRY WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	char moduleName[MAX_BUFFSIZE];
	GetModuleFileName(nullptr, moduleName, MAX_BUFFSIZE);

	try
	{
		::Application app(moduleName);
		app();
	}
	catch (exception &e)
	{
		MessageBox(nullptr, e.what(), "Error!", MB_ICONEXCLAMATION | MB_OK);
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}

::Application::Application(const string &name)
	: Entropy::Theia::Application(name)
{}

void ::Application::onEvent(const Event &ev)
{
	if (ev.Id() == Events::Key::Id) {
		const Events::Key &k = dynamic_cast<const Events::Key &>(ev);

		if (k.Action() == GLFW_PRESS && k.Code() == GLFW_KEY_ESCAPE) {
			Windows()->Close();
		}
	}
}