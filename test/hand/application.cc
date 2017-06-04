/*	Copyright 2017 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#include <cstdlib>
#include <iostream>
#include <vector>
#include "Application.hh"
#include "Object.hh"
#include "Array.hh"
#include "Bind.hh"
#include "Utility/SharedData.hh"

using namespace std;

using Entropy::Theia::Object;
using Entropy::Theia::SharedData;
using Entropy::Theia::Program;
using Entropy::Theia::Array;
using Entropy::Theia::Bind;
using Entropy::Theia::Shader;
using Entropy::Theia::Buffer;

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
	public Entropy::Theia::Application
{
	public:
		Application(const int, char *[]);
	private:
		void Key(const int, const int, const int, const int);
};

int main(int ArgC, char *ArgV[])
{
	try
	{
		Application app(ArgC, ArgV);
		app();

		return EXIT_SUCCESS;
	}
	catch(exception &e)
	{
		cerr << e << endl;
	}

	return EXIT_FAILURE;
}

void MyObject::Draw()
{
	Bind p(shared()->program), a(shared()->array);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
}

void Application::Key(const int key, const int, const int action, const int)
{
	if(action == GLFW_PRESS) {
		switch(key) {
			case GLFW_KEY_ESCAPE:
				Windows()->Close();
			break;
			case GLFW_KEY_F:
				Windows()->toggleFullscreen();
			break;
		}
	}
}

Application::Application(const int ArgC, char *ArgV[])
	: Entropy::Theia::Application(ArgC, ArgV)
{
	Windows()->Scenes()->emplace_back<MyObject>();
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
