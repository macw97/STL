#include "pch.h"
#include "../Vector/Vector.h"

TEST(ConstructorTest, DefaultWithSize)
{
	Vector<int> a(10);
	EXPECT_EQ(a.size(), 0);
}
TEST(ConstructorTest, AutoValues)
{
	Vector<int> a(5, 25);
	EXPECT_EQ(a[3], 25);
	EXPECT_EQ(a[0], 25);
}
TEST(ConstructorTest, Copy)
{
	Vector<int> a(5,3);
	Vector<int> b(a);
	EXPECT_EQ(a.size(), b.size());
	EXPECT_EQ(a[0], b[0]);
}
TEST(ConstructorTest, Default)
{
	Vector<int> a;
	a.push_back(5);
	a.push_back(25);
	a.push_back(125);
	EXPECT_EQ(a.size(), 3);
	EXPECT_EQ(a[1], 25);
	EXPECT_EQ(a[2], 125);
}
TEST(ConstructorTest, Move)
{
	Vector<int> a(5);
	for (int i = 0; i <25; i++)
	{
		a.push_back(i);
	}
	Vector<int> b=std::move(a);
	EXPECT_EQ(b.size(), 25);
	EXPECT_EQ(b[10], 10);
}
TEST(Operator, equal)
{
	Vector<char> a(3);
	a.push_back('a');
	a.push_back('b');
	a.push_back('c');
	Vector<char> b(a);
	EXPECT_TRUE(a == b);
	EXPECT_FALSE(a != b);
}
TEST(Operator, copy)
{
	Vector<char> a(10);
	for (int i = 0; i < 10; i++)
	{
		a.push_back('a' + i);
	}
	Vector<char> b = a;
	EXPECT_EQ(a[5], 'f');
}
TEST(Getter, at)
{
	Vector<char> a(1);
	a.push_back('a');
	a.push_back('b');
	EXPECT_ANY_THROW(a.at(3));
	EXPECT_EQ(a.at(1), 'b');
}
TEST(Destructor, pop_back)
{
	Vector<char> a(10);
	for (int i = 0; i < 10; i++)
	{
		a.push_back('a' + i);
	}
	a.pop_back();
	a.pop_back();
	EXPECT_EQ(a.size(), 8);
	a.push_back('a');
	EXPECT_EQ(a[8], 'a');
}
TEST(Destructor, clear)
{
	Vector<char> a(10);
	for (int i = 0; i < 10; i++)
	{
		a.push_back('a' + i);
	}
	a.clear();
	EXPECT_EQ(a.size(), 0);
}
TEST(Assignment, assign)
{
	Vector<int> a(5);
	a.assign(5,5);
	EXPECT_EQ(a[4], 5);
}
TEST(Assignment, pointer_assign)
{
	Vector<char> a;
	for (int i = 0; i < 15; i++)
	{
		a.push_back('a' + i);
	}
	Vector<char> b;
	b.assign(a.begin() + 2, a.begin() + 10);
	EXPECT_EQ(b.at(0), 'c');
	EXPECT_EQ(b.size(), 8);
}


int main(int argc, char* argv[])
{
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}