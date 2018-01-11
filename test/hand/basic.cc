/*	Copyright 2017 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#include <cstdlib>
#include <vector>

#include <Entropy/SharedData.hh>

#include "Application.hh"
#include "Object.hh"
#include "GL/Array.hh"
#include "GL/Bind.hh"
#include "UI/Text.hh"

using namespace std;
using namespace Entropy;
using namespace Entropy::Theia;
using namespace Entropy::Theia::GL;
using namespace Entropy::Theia::UI;

namespace detail {
	struct shared_data {
		shared_data();
		Program program;
		Array array;
	};
}

class Object :
	private SharedData<::detail::shared_data>,
	public Theia::Object
{
	public:
		Object();
	private:
		void Draw();
		void UpdateModel();
		void UpdateCamera(const Camera &);
		void UpdateScreen(const Screen &);
};

class Application :
	public Entropy::Theia::Application
{
	public:
		Application(const int, char *[]);
	private:
		void onEvent(const Entropy::Event &e);
		DefaultedList<Scene>::iterator objects;
		DefaultedList<Scene>::iterator text;
};

int main(int ArgC, char *ArgV[])
{
	try
	{
		::Application app(ArgC, ArgV);
		app();

		return EXIT_SUCCESS;
	}
	catch(exception &e)
	{
		cerr << e << endl;
	}

	return EXIT_FAILURE;
}

void ::Application::onEvent(const Entropy::Event &ev)
{
	if(ev.Id() == Events::Key::Id) {
		const Events::Key &k = dynamic_cast<const Events::Key &>(ev);

		if(k.Action() == GLFW_PRESS) {
			switch(k.Code()) {
				case GLFW_KEY_ESCAPE:
					Windows()->Close();
				break;
				case GLFW_KEY_F:
					Windows()->Fullscreen();
				break;
				case GLFW_KEY_T:
					if(Windows()->Scenes().current() == objects) {
						Windows()->Scenes().setDefault(text);
					} else if(Windows()->Scenes().current() == text) {
						Windows()->Scenes().setDefault(objects);
					} else {
						Windows()->Scenes()->emplaceDrawable<Text>("This is very bad!", FT::Font("data/NotoSansUI-Regular.ttf"));
					}
				break;
			}
		}
	}
}

::Application::Application(const int ArgC, char *ArgV[]) :
	Entropy::Tethys::Application(ArgC, ArgV),
	Entropy::Theia::Application(ArgC, ArgV),
	objects(Windows()->addScene()),
	text(Windows()->addScene())
{
	auto a = make_shared<::Object>();
	auto b = make_shared<::Object>();
	auto c = make_shared<::Object>();

	a->Translate(Vertex(2, 2, 0));
	b->Translate(Vertex(0, 0, 0));
	c->Translate(Vertex(-2, -2, 0));

	objects->addDrawable(a);
	objects->addDrawable(b);
	objects->addDrawable(c);

	objects->getCamera().setPosition(Vertex(0, 0, 5.0));

	auto x = make_shared<Text>("Hello Theia!", FT::Font("data/NotoSansUI-Regular.ttf"));
	auto y = make_shared<Text>("This is made with Theia!", FT::Font("data/NotoSansUI-Regular.ttf"));

	x->setPosition(ScreenVertex(300, 150));
	y->setPosition(ScreenVertex(20, 20));

	x->setColor(Vertex(0.5, 1.0, 0.5));
	y->setColor(Vertex(1.0, 1.0, 0.5));

	text->addDrawable(x);
	text->addDrawable(y);

	Windows()->Scenes().setDefault(text);
}

void ::Object::Draw()
{
	Bind p(shared()->program), a(shared()->array);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
}

::detail::shared_data::shared_data()
	: program(), array()
{
	string vert_code =
		"#version 130\n"

		"uniform mat4 model;"
		"uniform mat4 view;"
		"uniform mat4 projection;"

		"in vec2 in_position;"

		"void main() {"
			"gl_Position = projection * view * model * vec4(in_position, 0.0, 1.0);"
		"}"
	;

	string frag_code =
		"#version 130\n"

		"out vec4 out_color;"

		"void main() {"
			"out_color = vec4(1.0, 1.0, 1.0, 1.0);"
		"}"
	;

	vector<float> vertices = {
		-1.0f, 1.0f,
		1.0f, 1.0f,
		-1.0f, -1.0f,
		1.0f, -1.0f,
	};

	Shader vert(Shader::Vertex, vert_code);
	Shader frag(Shader::Fragment, frag_code);

	program.Attach(vert);
	program.Attach(frag);
	program.Link();

	Buffer vbo(Buffer::Vertex);
	vbo.Data(vertices, Buffer::Static);
	array.Bind(program, vbo, "in_position"s, 2, GL_FLOAT);
}

void ::Object::UpdateModel()
{
	shared()->program.SetUniform("model"s, Model());
}

void ::Object::UpdateCamera(const Camera &c)
{
	shared()->program.SetUniform("view"s, c.View());
}

void ::Object::UpdateScreen(const Screen &s)
{
	shared()->program.SetUniform("projection"s, s.Perspective());
}

::Object::Object()
	: SharedData<::detail::shared_data>(), Theia::Object()
{}
