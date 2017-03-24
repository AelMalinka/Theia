/*	Copyright 2017 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#include "PolymorphicListIterator.hh"
#include <gtest/gtest.h>

using namespace Entropy::Theia;
using namespace testing;
using namespace std;

namespace {
	class A
	{
		public:
			virtual int Value() = 0;
			virtual int Value() const = 0;
	};

	class B :
		public A
	{
		int Value();
		int Value() const;
	};

	class C :
		public A
	{
		int Value();
		int Value() const;
	};

	TEST(PolymorphicListIterator, Constructors) {
		list<shared_ptr<A>> t;

		t.push_back(make_shared<B>());
		t.push_back(make_shared<C>());

		PolymorphicListIterator<A> a = t.begin();
		PolymorphicListIterator<A> b = ++t.begin();
		PolymorphicListIterator<A> c = t.end();

		EXPECT_EQ(a, t.begin());
		EXPECT_EQ(b, ++t.begin());
		EXPECT_EQ(c, t.end());

		PolymorphicListIterator<A> d(t.begin(), t.cbegin());
		PolymorphicListIterator<A> e(t.begin(), ++t.cbegin());
		PolymorphicListIterator<A> f(t.begin(), t.cend());

		EXPECT_EQ(d, t.begin());
		EXPECT_EQ(e, ++t.begin());
		EXPECT_EQ(f, t.end());

		EXPECT_EQ(a, d);
		EXPECT_EQ(b, e);
		EXPECT_EQ(c, f);

		EXPECT_NE(a, b);
		EXPECT_NE(a, c);
		EXPECT_NE(a, e);
		EXPECT_NE(a, f);

		EXPECT_NE(b, a);
		EXPECT_NE(b, c);
		EXPECT_NE(b, d);
		EXPECT_NE(b, f);

		EXPECT_NE(c, a);
		EXPECT_NE(c, b);
		EXPECT_NE(c, d);
		EXPECT_NE(c, e);
	}

	TEST(PolymorphicListIterator, Accessors) {
		list<shared_ptr<A>> t;

		t.push_back(make_shared<B>());
		t.push_back(make_shared<C>());

		PolymorphicListIterator<A> a = t.begin();
		PolymorphicListIterator<A> b = ++t.begin();

		EXPECT_EQ((*a).Value(), 10);
		EXPECT_EQ(a->Value(), 10);

		EXPECT_EQ((*b).Value(), 20);
		EXPECT_EQ(b->Value(), 20);

		EXPECT_NE((*a).Value(), 20);
		EXPECT_NE(a->Value(), 20);

		EXPECT_NE((*b).Value(), 10);
		EXPECT_NE(b->Value(), 10);

		const PolymorphicListIterator<A> c = t.begin();
		const PolymorphicListIterator<A> d = ++t.begin();

		EXPECT_EQ((*c).Value(), 15);
		EXPECT_EQ(c->Value(), 15);

		EXPECT_EQ((*d).Value(), 25);
		EXPECT_EQ(d->Value(), 25);

		EXPECT_NE((*c).Value(), 25);
		EXPECT_NE(c->Value(), 25);

		EXPECT_NE((*d).Value(), 15);
		EXPECT_NE(d->Value(), 15);
	}

	int B::Value()
	{
		return 10;
	}

	int B::Value() const
	{
		return 15;
	}

	int C::Value()
	{
		return 20;
	}

	int C::Value() const
	{
		return 25;
	}
}
