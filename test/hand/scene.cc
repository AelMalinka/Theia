/*	Copyright 2017 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#include <cstdlib>
#include <iostream>
#include <vector>
#include "GLFW/Window.hh"
#include "Scene.hh"
#include "Object.hh"
#include "Array.hh"
#include "Bind.hh"

using namespace std;
using namespace Entropy::Theia;

class MyObject :
	public Object
{
	public:
		MyObject();
		void Draw();
	private:
		struct shared_data {
			shared_data();
			Program program;
			Array vao;
		};
		static std::shared_ptr<shared_data> shared();
		static std::shared_ptr<shared_data> _shared;
};

class MyWindow :
	public GLFW::Window
{
	public:
		MyWindow(const string &);
	private:
		void Draw();
		void Key(const int, const int, const int, const int);
		void Mouse(const int, const int, const int);
		void Move(const double, const double);
	private:
		Scene _scene;
};

int main(int, char *ArgV[])
{
	try
	{
		MyWindow win(ArgV[0]);
		
		win.Show();
		while(!win.isDone())
			win();
	}
	catch(exception &e)
	{
		cerr << e << endl;
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}

void MyWindow::Key(const int key, const int, const int action, const int)
{
	if(action == GLFW_PRESS) {
		switch(key) {
			case GLFW_KEY_ESCAPE:
				Close();
			break;
			case GLFW_KEY_F:
				toggleFullscreen();
			break;
		}
	}
}

void MyObject::Draw()
{
	Bind p(shared()->program), a(shared()->vao);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
}

void MyWindow::Draw()
{
	_scene();
}

MyWindow::MyWindow(const string &name)
	: GLFW::Window(name, 640, 360), _scene()
{
	_scene.emplace_back<MyObject>();
}

MyObject::MyObject()
	: Object(shared()->program, "model"s, "view"s, "projection"s)
{}

shared_ptr<MyObject::shared_data> MyObject::_shared;

MyObject::shared_data::shared_data()
	: program(), vao()
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
			"out_color = vec4(0.0, 1.0, 1.0, 1.0);"
		"}"
	;

	vector<float> vertices = {
		-1.0f, 1.0f,
		1.0f, 1.0f,
		-1.0f, -1.0f,
		1.0f, -1.0f
	};

	Shader vert(Shader::Vertex, vert_code);
	Shader frag(Shader::Fragment, frag_code);

	program.Attach(vert);
	program.Attach(frag);
	program.Link();

	Buffer vbo(Buffer::Vertex);
	vbo.Data(vertices, Buffer::Static);
	vao.Bind(program, vbo, "in_position"s, 2, GL_FLOAT);
}

std::shared_ptr<MyObject::shared_data> MyObject::shared()
{
	if(!_shared) {
		_shared = make_shared<MyObject::shared_data>();
	}

	return _shared;
}

void MyWindow::Mouse(const int, const int, const int)
{}

void MyWindow::Move(const double, const double)
{}
