/*	Copyright 2017 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#include <cstdlib>
#include <vector>
#include <iostream>

#include <glm/gtx/string_cast.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "GLFW/Window.hh"
#include "Object.hh"
#include "Program.hh"
#include "Array.hh"
#include "Bind.hh"
#include "Camera.hh"

using namespace std;
using namespace Entropy::Theia;

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
		"out_color = vec4(0.0, 1.0, 0.0, 1.0);"
	"}"
;

vector<float> vertices = {
	-0.8f, -0.8f,
	0.8f, -0.8f,
	0.0f, 0.8f
};

class MyObject :
	public Object
{
	public:
		MyObject();
		void Draw();
		void Update(const chrono::duration<double> &);
	private:
		Program _program;
		Buffer _vbo;
		Array _vao;
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
		Camera _cam;
		MyObject _obj;
};

int main(int, char *ArgV[])
{
	try
	{
		MyWindow win(ArgV[0]);

		win.Show();
		while(!win.isDone()) {
			win();
		}
	}
	catch(exception &e)
	{
		cerr << e << endl;
		return EXIT_FAILURE;
	}
}

MyWindow::MyWindow(const string &name)
	: GLFW::Window(name, 640, 360), _cam(), _obj()
{
	_cam.addObject(_obj);
}

void MyWindow::Draw()
{
	_obj();
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
	if(action == GLFW_PRESS || action == GLFW_REPEAT) {
		auto p = _cam.Position();
		auto l = _cam.LookAt();
		switch(key) {
			case GLFW_KEY_RIGHT:
				++p.x;
				++l.x;
			break;
			case GLFW_KEY_LEFT:
				--p.x;
				--l.x;
			break;
			case GLFW_KEY_UP:
				++p.y;
				++l.y;
			break;
			case GLFW_KEY_DOWN:
				--p.y;
				--l.y;
			break;
		}
		if(p != _cam.Position() || l != _cam.LookAt()) {
			_cam.setPosition(p);
			_cam.setLookAt(l);
		}
	}
}

MyObject::MyObject()
	: Object(_program, "model"s, "view"s, "projection"s), _program(), _vbo(Buffer::Vertex), _vao()
{
	Shader vert(Shader::Vertex, vert_code);
	Shader frag(Shader::Fragment, frag_code);

	_program.Attach(vert);
	_program.Attach(frag);
	_program.Link();

	_vbo.Data(vertices, Buffer::Static);

	_vao.Bind(_program, _vbo, "in_position"s, 2, GL_FLOAT);
}

void MyObject::Update(const chrono::duration<double> &dt)
{
	Rotate(dt.count() * 10, Vertex(0.0, 0.0, 1.0));

	Object::Update(dt);
}

void MyObject::Draw()
{
	Bind p(_program), a(_vao);
	glDrawArrays(GL_TRIANGLES, 0, 3);
}

void MyWindow::Mouse(const int, const int, const int)
{}

void MyWindow::Move(const double, const double)
{}
