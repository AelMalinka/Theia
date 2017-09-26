/*	Copyright 2017 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#include <cstdlib>
#include <iostream>
#include <vector>

#include <Entropy/Theia/Application.hh>
#include <Entropy/Theia/Object.hh>
#include <Entropy/Theia/GL/Array.hh>
#include <Entropy/Theia/GL/Bind.hh>
#include <Entropy/Theia/Utility/SharedData.hh>
#include <Entropy/Theia/UI/Text.hh>

using namespace std;
using namespace Entropy::Theia;
using namespace Entropy::Theia::GL;

const size_t MAX_BUFFSIZE = 4096;

namespace detail
{
	struct shared_data
	{
		shared_data();
		Program program;
		Array array;
	};
}

class MyObject :
	private SharedData<detail::shared_data>,
	public Object
{
	public:
		MyObject();
		void Draw();
	private:
		void UpdateModel();
		void UpdateCamera(const Camera &);
		void UpdateScreen(const Screen &);
};

class Application :
	public Entropy::Theia::Application
{
	public:
		explicit Application(const string &);
	protected:
		void onEvent(const Entropy::Event &);
};

int APIENTRY WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	char moduleName[MAX_BUFFSIZE];
	GetModuleFileName(nullptr, moduleName, MAX_BUFFSIZE);

	try
	{
		::Application app(moduleName);
		app();

		return EXIT_SUCCESS;
	}
	catch (exception &e)
	{
		MessageBox(nullptr, e.what(), "Error!", MB_ICONEXCLAMATION | MB_OK);
		return EXIT_FAILURE;
	}
}

void ::Application::onEvent(const Entropy::Event &ev)
{
	if (ev.Id() == Events::Key::Id) {
		const Events::Key &k = dynamic_cast<const Events::Key &>(ev);

		if (k.Action() == GLFW_PRESS) {
			switch (k.Code()) {
				case GLFW_KEY_ESCAPE:
					Windows()->Close();
				break;
				case GLFW_KEY_F:
					Windows()->Fullscreen();
				break;
			}
		}
	}
}

void MyObject::Draw()
{
	Bind p(shared()->program), a(shared()->array);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
}

detail::shared_data::shared_data()
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
		-1.0, 1.0f,
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

::Application::Application(const string &name)
	: Entropy::Theia::Application(name)
{
	auto a = make_shared<UI::Text>("Hello Theia!"s, UI::FT::Font("data/NotoSansUI-Regular.ttf"s));
	auto b = make_shared<UI::Text>("This is made with OpenGL!"s, UI::FT::Font("data/NotoSansUI-Regular.ttf"s));

	a->setPosition(ScreenVertex(300, 150));
	b->setPosition(ScreenVertex(20, 20));

	a->setColor(Vertex(1.0, 0.5, 0.5));
	b->setColor(Vertex(0.5, 0.5, 1.0));
	
	Windows()->Scenes()->addDrawable(a);
	Windows()->Scenes()->addDrawable(b);

	Windows()->Scenes()->emplaceDrawable<MyObject>();
}

MyObject::MyObject()
	: SharedData<detail::shared_data>(), Object()
{}

void MyObject::UpdateModel()
{
	shared()->program.SetUniform("model"s, Model());
}

void MyObject::UpdateCamera(const Camera &c)
{
	shared()->program.SetUniform("view"s, c.View());
}

void MyObject::UpdateScreen(const Screen &s)
{
	shared()->program.SetUniform("projection"s, s.Perspective());
}