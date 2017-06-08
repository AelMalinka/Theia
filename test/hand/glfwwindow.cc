/*	Copyright 2017 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#include <cstdlib>
#include <vector>
#include "Events.hh"
#include "GLFW/Window.hh"
#include "GL/Program.hh"
#include "GL/Array.hh"
#include "GL/Bind.hh"

using namespace std;
using namespace Entropy::Theia;
using namespace Entropy::Theia::GL;

string vert_code =
	"#version 130\n"

	"in vec2 in_position;"

	"void main() {"
		"gl_Position = vec4(in_position, 0.0, 1.0);"
	"}"
;

string frag_code =
	"#version 130\n"

	"out vec4 out_color;"

	"void main() {"
		"out_color = vec4(0.0, 0.0, 1.0, 1.0);"
	"}"
;

vector<float> vertices = {
	-0.8f, -0.8f,
	0.8f, -0.8f,
	0.0f, 0.8f
};

class MyWindow :
	public GLFW::Window
{
	public:
		MyWindow(const string &);
	private:
		void Draw();
		void onEvent(const Event &);
	private:
		Program _program;
		Buffer _vbo;
		Array _vao;
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

		return EXIT_SUCCESS;
	}
	catch(exception &e)
	{
		cerr << e << endl;
		return EXIT_FAILURE;
	}
}

MyWindow::MyWindow(const string &name)
	: GLFW::Window(name, 640, 360), _program(), _vbo(Buffer::Vertex), _vao()
{
	Shader vert(Shader::Vertex, vert_code);
	Shader frag(Shader::Fragment, frag_code);

	_program.Attach(vert);
	_program.Attach(frag);
	_program.Link();

	_vbo.Data(vertices, Buffer::Static);

	_vao.Bind(_program, _vbo, "in_position"s, 2, GL_FLOAT);
}

void MyWindow::Draw()
{
	Bind p(_program), a(_vao);
	glDrawArrays(GL_TRIANGLES, 0, 3);
}

void MyWindow::onEvent(const Event &ev)
{
	if(ev.Id() == Events::Key::Id) {
		auto k = dynamic_cast<const Events::Key &>(ev);

		if(k.Action() == GLFW_PRESS) {
			switch(k.Code()) {
				case GLFW_KEY_ESCAPE:
					Close();
				break;
				case GLFW_KEY_F:
					Fullscreen();
				break;
				case GLFW_KEY_J:
					disableCursor();
				break;
				case GLFW_KEY_K:
					enableCursor();
				break;
			}
		}
	}

	GLFW::Window::onEvent(ev);
}
