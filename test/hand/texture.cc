/*	Copyright 2017 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#include <cstdlib>
#include <iostream>
#include <vector>
#include "Application.hh"
#include "Object.hh"
#include "GL/Texture.hh"
#include "GL/Array.hh"
#include "GL/Bind.hh"
#include "Utility/SharedData.hh"

using namespace std;
using namespace Entropy::Theia;
using namespace Entropy::Theia::GL;

namespace detail {
	struct shared_data {
		shared_data();
		Program program;
		Array array;
		Texture texture;
	};
}

class Object :
	private SharedData<detail::shared_data>,
	public Entropy::Theia::Object
{
	public:
		Object();
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

void ::Application::Key(const int k, const int, const int a, const int)
{
	if(a == GLFW_PRESS) {
		switch(k) {
			case GLFW_KEY_ESCAPE:
				Windows()->Close();
			break;
		}
	}
}

void ::Object::Draw()
{
	Bind p(shared()->program), a(shared()->array), t(shared()->texture);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
}

detail::shared_data::shared_data()
	: program(), array(), texture(Texture::Texture2D, "data/purple-stars.png")
{
	string vert_code =
		"#version 130\n"

		"in vec2 in_position;"

		"out vec2 texture_position;"

		"uniform mat4 model;"
		"uniform mat4 view;"
		"uniform mat4 projection;"

		"void main() {"
			"texture_position = in_position;"
			"gl_Position = projection * model * view * vec4(in_position, 0.0, 1.0);"
		"}"
	;

	string frag_code =
		"#version 130\n"

		"in vec2 texture_position;"

		"out vec4 out_color;"

		"uniform sampler2D uni_texture;"

		"void main() {"
			"out_color = texture(uni_texture, texture_position);"
		"}"
	;

	vector<float> vertices = {
		0.0, 1.0f,
		1.0f, 1.0f,
		0.0f, 0.0f,
		1.0f, 0.0f,
	};

	Shader vert(Shader::Vertex, vert_code);
	Shader frag(Shader::Fragment, frag_code);

	program.Attach(vert);
	program.Attach(frag);
	program.Link();

	Buffer vbo(Buffer::Vertex);
	vbo.Data(vertices, Buffer::Static);
	array.Bind(program, vbo, "in_position"s, 2, GL_FLOAT);

	texture.generateMipmaps();
}

::Application::Application(const int ArgC, char *ArgV[])
	: ::Entropy::Theia::Application(ArgC, ArgV)
{
	Windows()->Scenes()->emplace_back<::Object>();
}

::Object::Object()
	: SharedData<detail::shared_data>(), Entropy::Theia::Object(shared()->program, "model"s, "view"s, "projection"s)
{}
