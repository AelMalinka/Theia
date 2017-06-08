/*	Copyright 2017 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#include <cstdlib>
#include <vector>

#include "GLFW/Window.hh"
#include "Object.hh"
#include "Events.hh"
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
	protected:
		void UpdateModel();
		void UpdateCamera(const Camera &);
		void UpdateScreen(const Screen &);
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
		void onEvent(const Event &);
	private:
		MyObject _obj;
		chrono::high_resolution_clock::time_point _last;
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
	: GLFW::Window(name, 640, 360), _obj(), _last(chrono::high_resolution_clock::now())
{}

void MyWindow::Draw()
{
	using namespace std::chrono;

	auto t = high_resolution_clock::now();

	_obj.Update(duration_cast<duration<double>>(t - _last));
	_obj.Draw();

	_last = t;
}

void MyWindow::onEvent(const Event &ev)
{
	if(ev.Id() == Events::Key::Id) {
		const Events::Key &k = dynamic_cast<const Events::Key &>(ev);

		if(k.Action() == GLFW_PRESS) {
			switch(k.Code()) {
				case GLFW_KEY_ESCAPE:
					Close();
				break;
				case GLFW_KEY_F:
					Fullscreen();
				break;
			}
		}
	}

	GLFW::Window::onEvent(ev);
}

MyObject::MyObject()
	: Object(), _program(), _vbo(Buffer::Vertex), _vao()
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

void MyObject::UpdateModel()
{
	_program.SetUniform("model"s, Model());
}

void MyObject::UpdateCamera(const Camera &)
{}

void MyObject::UpdateScreen(const Screen &)
{}
