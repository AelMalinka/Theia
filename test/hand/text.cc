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

		auto text = make_shared<Text>("Hello Theia!", FT::Font("data/NotoSansUI-Regular.ttf"));

		text->setPosition(ScreenVertex(10, 10));
		text->setColor(Vertex(1.0, 1.0, 1.0));

		app.Windows()->setFoV(90.0);
		app.Windows()->setNearClipping(0.0);
		app.Windows()->setFarClipping(10.0);

		app.Windows()->Scenes()->getCamera().setPosition(Vertex(0.0, 0.0, 10.0));
		app.Windows()->Scenes()->getCamera().setLookAt(Vertex(0.0, 0.0, 0.0));
		app.Windows()->Scenes()->getCamera().setUp(Vertex(0.0, 1.0, 0.0));

		app.Windows()->Scenes()->addDrawable(text);

		app();

		return EXIT_SUCCESS;
	}
	catch(exception &e)
	{
		cerr << e << endl;
	}

	return EXIT_FAILURE;
}
