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

		auto text = make_shared<Text>("Hello Theia!", FT::Font("data/NotoSansUI-Regular.ttf"));
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
