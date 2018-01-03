/*	Copyright 2017 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#include <gtest/gtest.h>
#include "Application.hh"
#include "Object.hh"

using namespace std;
using namespace Entropy::Theia;

namespace {
	class MyObject :
		public Object
	{
		public:
			MyObject(const int);
			const int &Value() const;
			void Draw() {}
			void UpdateModel() {}
			void UpdateScreen(const Screen &) {}
			void UpdateCamera(const Camera &) {}
		private:
			int _value;
	};

	TEST(SceneTests, ChangeDefault) {
		Application app;

		auto a = make_shared<MyObject>(1);
		auto b = make_shared<MyObject>(2);

		auto c = make_shared<MyObject>(3);
		auto d = make_shared<MyObject>(4);

		auto i = app.Windows()->addScene();
		auto j = app.Windows()->addScene();
		EXPECT_NE(i, j);

		i->addDrawable(a);
		i->addDrawable(b);

		j->addDrawable(c);
		j->addDrawable(d);

		EXPECT_NE(app.Windows()->Scenes().current(), i);
		EXPECT_NE(app.Windows()->Scenes().current(), j);

		app.Windows()->Scenes().setDefault(i);

		EXPECT_EQ(app.Windows()->Scenes().current(), i);
		EXPECT_NE(app.Windows()->Scenes().current(), j);

		auto x = 0;
		for(auto &u : *app.Windows()->Scenes()) {
			MyObject &o = dynamic_cast<MyObject &>(u);

			EXPECT_EQ(o.Value(), ++x);
		}

		app.Windows()->Scenes().setDefault(j);

		EXPECT_NE(app.Windows()->Scenes().current(), i);
		EXPECT_EQ(app.Windows()->Scenes().current(), j);
		for(auto &u : *app.Windows()->Scenes()) {
			MyObject &o = dynamic_cast<MyObject &>(u);

			EXPECT_EQ(o.Value(), ++x);
		}
	}

	MyObject::MyObject(const int v)
		: Object(), _value(v)
	{}

	const int &MyObject::Value() const
	{
		return _value;
	}
}
