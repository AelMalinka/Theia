/*	Copyright 2017 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#include <cstdlib>
#include <vector>

#include "GLFW/Window.hh"
#include "Object.hh"
#include "GL/Program.hh"
#include "GL/Array.hh"
#include "GL/Bind.hh"

using namespace std;
using namespace Entropy::Theia;
using namespace Entropy::Theia::GL;

string vert_code =
	"#version 130\n"

	"uniform mat4 model;"

	"in vec2 in_position;"

	"void main() {"
		"gl_Position = model * vec4(in_position, 0.0, 1.0);"
	"}"
;

string frag_code =
	"#version 130\n"

	"out vec4 out_color;"

	"void main() {"
		"out_color = vec4(1.0, 0.0, 0.0, 1.0);"
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
		void UpdateView(const Camera &);
		void UpdateProjection(const Camera &);
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
	: GLFW::Window(name, 640, 360), _obj()
{}

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
}

MyObject::MyObject()
	: Object(_program, "model"s, ""s, ""s), _program(), _vbo(Buffer::Vertex), _vao()
{
	Shader vert(Shader::Vertex, vert_code);
	Shader frag(Shader::Fragment, frag_code);

	_program.Attach(vert);
	_program.Attach(frag);
	_program.Link();

	_vbo.Data(vertices, Buffer::Static);

	_vao.Bind(_program, _vbo, "in_position"s, 2, GL_FLOAT);
}

void MyObject::Draw()
{
	Bind p(_program), a(_vao);
	glDrawArrays(GL_TRIANGLES, 0, 3);
}

void MyObject::Update(const chrono::duration<double> &dt)
{
	Rotate(dt.count() * 10, Vertex(0.0, 0.0, 1.0));

	Object::Update(dt);
}

void MyWindow::Mouse(const int, const int, const int)
{}

void MyWindow::Move(const double, const double)
{}

void MyObject::UpdateView(const Camera &)
{}

void MyObject::UpdateProjection(const Camera &)
{}
