/*	Copyright 2017 (c) Michael Thomas (malinka) <malinka@entropy-development.com>'
	Distributed under the terms of the GNU Affero General Public License v3
*/

#include <cstdlib>
#include <iostream>
#include <vector>
#include "Application.hh"
#include "Object.hh"
#include "GL/Array.hh"
#include "GL/Bind.hh"
#include "Utility/SharedData.hh"

using namespace std;
using namespace Entropy::Theia;
using namespace Entropy::Theia::GL;

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
};

class Application :
	public ::Entropy::Theia::Application
{
	public:
		Application(const int, char *[]);
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

::Application::Application(const int ArgC, char *ArgV[])
	: ::Entropy::Theia::Application(ArgC, ArgV)
{
	// 2017-06-04 AMR NOTE: testing by ref and directly with Windows() are same instances
	auto &&win = *Windows();
	win.setCallbacks([&win](auto k, auto, auto a, auto) {
		if(a == GLFW_PRESS) {
			switch(k) {
				case GLFW_KEY_ESCAPE:
					win.Close();
				break;
				case GLFW_KEY_F:
					win.toggleFullscreen();
				break;
			}
		}
	});

	Windows()->Scenes()->emplace_back<MyObject>();
}

void MyObject::Draw()
{
	Bind p(shared()->program), a(shared()->array);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
}

MyObject::MyObject()
	: SharedData<detail::shared_data>(), Object(shared()->program, "model"s, "view"s, "projection"s)
{}

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
			"gl_Position = projection * model * view * vec4(in_position, 0.0, 1.0);"
		"}"
	;
	string frag_code =
		"#version 130\n"

		"out vec4 out_color;"

		"void main() {"
			"out_color = vec4(1.0, 1.0, 0.0, 1.0);"
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
