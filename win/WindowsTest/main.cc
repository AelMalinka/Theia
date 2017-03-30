#include <cstdlib>
#include <iostream>
#include <vector>

#include "GLFW/Window.hh"
#include "Object.hh"
#include "Program.hh"
#include "Bind.hh"
#include "Array.hh"

using namespace std;
using namespace Entropy::Theia;

const size_t MAX_BUFFSIZE = 4096;

class MyObject :
	public Object
{
	public:
		MyObject();
		void Draw();
	private:
		Vertex _color;
		Program _program;
		Buffer _vbo;
		Array _vao;
};

class MyWindow :
	public GLFW::Window
{
	public:
		explicit MyWindow(const string &);
	private:
		void Draw();
		void Key(const int, const int, const int, const int);
		void Mouse(const int, const int, const int);
		void Move(const double, const double);
	private:
		MyObject _obj;
		Camera _cam;
};

int APIENTRY WinMain(HINSTANCE, HINSTANCE, LPSTR str, int)
{
	char moduleName[MAX_BUFFSIZE];
	GetModuleFileName(nullptr, moduleName, MAX_BUFFSIZE);

	try
	{
		MyWindow win(moduleName);

		win.Show();
		while (!win.isDone()) {
			win();
		}
	}
	catch (exception &e)
	{
		MessageBox(nullptr, e.what(), "Error!", MB_ICONEXCLAMATION | MB_OK);
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}

MyWindow::MyWindow(const string &name)
	: GLFW::Window(name, 640, 360), _obj(), _cam()
{
	_cam.addObject(_obj);
}

void MyWindow::Draw()
{
	_obj();
}

void MyWindow::Key(const int key, const int, const int action, const int)
{
	if (action == GLFW_PRESS) {
		switch (key) {
			case GLFW_KEY_ESCAPE:
				Close();
			break;
			case GLFW_KEY_F:
				toggleFullscreen();
			break;
		}
	}
}

void MyWindow::Mouse(const int, const int, const int)
{}

void MyWindow::Move(const double, const double)
{}

void MyObject::Draw()
{
	Bind p(_program), a(_vao);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
}

MyObject::MyObject()
	: Object(_program, "model"s, "view"s, "projection"s), _color(1.0, 0.0, 0.0), _program(), _vbo(Buffer::Vertex), _vao()
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

		"uniform vec3 in_color;"
		"out vec4 out_color;"

		"void main() {"
			"out_color = vec4(in_color, 1.0);"
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

	_program.Attach(vert);
	_program.Attach(frag);
	_program.Link();

	_program.SetUniform("in_color"s, _color);

	_vbo.Data(vertices, Buffer::Static);
	_vao.Bind(_program, _vbo, "in_position"s, 2, GL_FLOAT);
}
