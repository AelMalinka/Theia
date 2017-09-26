/*	Copyright 2017 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#include <cstdlib>
#include <vector>
#include "Application.hh"
#include "UI/Text.hh"

using namespace std;
using namespace Entropy::Theia;
using namespace Entropy::Theia::UI;

int main(int ArgC, char *ArgV[])
{
	try
	{
		Application app(ArgC, ArgV);

		app.Windows()->addCallbacks([&app](const Event &ev) {
			if(ev.Id() == Events::Key::Id) {
				const Events::Key &k = dynamic_cast<const Events::Key &>(ev);

				if(k.Action() == GLFW_PRESS && k.Code() == GLFW_KEY_ESCAPE) {
					app.Windows()->Close();
				}
			}
		});

		auto a = make_shared<Text>("Hello Theia!", FT::Font("data/NotoSansUI-Regular.ttf"));
		auto b = make_shared<Text>("This is made with OpenGL!", FT::Font("data/NotoSansUI-Regular.ttf"));

		a->setPosition(ScreenVertex(300, 150));
		b->setPosition(ScreenVertex(20, 20));

		a->setColor(Vertex(1.0, 0.5, 0.5));
		b->setColor(Vertex(0.5, 0.5, 1.0));

		app.Windows()->Scenes()->addDrawable(a);
		app.Windows()->Scenes()->addDrawable(b);

		app();

		return EXIT_SUCCESS;
	}
	catch(exception &e)
	{
		cerr << e << endl;
	}

	return EXIT_FAILURE;
}
