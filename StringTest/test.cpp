#include "pch.h"

TEST(Constructors, DefaultConstructors) 
{
	sbr::string s;
	EXPECT_EQ(s.length(), 0);
	EXPECT_EQ(strlen(s.c_str()), 0);
	EXPECT_TRUE(s == "");
}

TEST(Constructors, CharConstructor)
{
	const char cc = 'c';
	char c = 'c';
	sbr::string s(c);
	sbr::string sc(cc);
	sbr::string s2('s');

	EXPECT_EQ(s.length(), 1);
	EXPECT_TRUE(s == "c");

	EXPECT_EQ(sc.length(), 1);
	EXPECT_TRUE(sc == "c");

	EXPECT_EQ(s2.length(), 1);
	EXPECT_TRUE(s2 == "s");
}

TEST(Constructors, CharPtrConstructor)
{
	const char cs[] = "Just a string";
	sbr::string s{ cs };
	EXPECT_EQ(s.length(), 13);
	EXPECT_EQ(strlen(s.c_str()), 13);
	EXPECT_TRUE(s == cs);
}

TEST(Constructors, CopyConstructor)
{
	const char cs[] = "Just a string";
	sbr::string s{ cs };
	sbr::string s2{ s };
	EXPECT_EQ(s2.length(), 13);
	EXPECT_EQ(strlen(s2.c_str()), 13);
	EXPECT_TRUE(s2 == cs);
}

TEST(Constructors, MoveConstructor)
{
	const char cs[] = "Just a string";
	sbr::string s{ cs };
	sbr::string s2{ std::move(s) };
	EXPECT_EQ(s2.length(), 13);
	EXPECT_EQ(strlen(s2.c_str()), 13);
	EXPECT_TRUE(s2 == cs);
}

TEST(Operators, OperatorPlus)
{
	sbr::string s1("string1");
	sbr::string s2("string2");
	sbr::string s3{ s1 + s2 };
	const char cs[] = "string1string2";
	EXPECT_EQ(s3.length(), strlen(cs));
	EXPECT_EQ(strlen(s3.c_str()), strlen(cs));
	EXPECT_TRUE(s3 == cs);
}

TEST(Operators, OperatorPlusAssignChar)
{
	sbr::string s('s');
	s += 'a';

	EXPECT_EQ(s.length(), 2);
	EXPECT_TRUE(s == "sa");
}

TEST(Operators, OperatorPlusAssign)
{
	sbr::string s1("string1");
	sbr::string s2("string2");
	s1 += s2;
	const char cs[] = "string1string2";
	EXPECT_EQ(s1.length(), strlen(cs));
	EXPECT_EQ(strlen(s1.c_str()), strlen(cs));
	EXPECT_TRUE(s1 == cs);
}

TEST(Operators, OperatorAssignment)
{
	const char cs[] = "Just a string";
	sbr::string s1{ cs };
	sbr::string s2 = s1;
	EXPECT_EQ(s2.length(), strlen(cs));
	EXPECT_EQ(strlen(s2.c_str()), strlen(cs));
	EXPECT_TRUE(s2 == cs);
}

TEST(Operators, OperatorMoveAssignment)
{
	const char cs[] = "Just a string";
	sbr::string s1{ cs };
	sbr::string s2 = std::move(s1);
	EXPECT_EQ(s2.length(), strlen(cs));
	EXPECT_EQ(strlen(s2.c_str()), strlen(cs));
	EXPECT_TRUE(s2 == cs);
}

TEST(OperatorsComparers, Equal)
{
	const char cs[] = "Just a string";
	sbr::string s1{ cs };
	EXPECT_TRUE(s1 == cs);
	EXPECT_TRUE(cs == s1);
	s1 += "s";
	EXPECT_FALSE(s1 == cs);
	EXPECT_FALSE(cs == s1);
}

TEST(OperatorsComparers, NotEqual)
{
	const char cs[] = "Just a string";
	sbr::string s1{ cs };
	EXPECT_FALSE(s1 != cs);
	EXPECT_FALSE(cs != s1);
	s1 += "s";
	EXPECT_TRUE(s1 != cs);
	EXPECT_TRUE(cs != s1);
}

TEST(OperatorsComparers, More)
{
	const char cs[] = "Just a string";
	sbr::string s1{ cs };
	s1 += "s";
	EXPECT_TRUE(s1 > cs);
	EXPECT_FALSE(cs > s1);
}

TEST(OperatorsComparers, MoreEquals)
{
	const char cs[] = "Just a string";
	sbr::string s1{ cs };

	EXPECT_TRUE(s1 >= cs);
	EXPECT_TRUE(cs >= s1);
	s1 += "s";
	EXPECT_TRUE(s1 >= cs);
	EXPECT_FALSE(cs >= s1);
}

TEST(OperatorsComparers, Less)
{
	const char cs[] = "Just a string";
	sbr::string s1{ cs };
	s1 += "s";
	EXPECT_TRUE(cs < s1);
	EXPECT_FALSE(s1 < cs);
}

TEST(OperatorsComparers, LessEquals)
{
	const char cs[] = "Just a string";
	sbr::string s1{ cs };

	EXPECT_TRUE(s1 <= cs);
	EXPECT_TRUE(cs <= s1);
	s1 += "s";
	EXPECT_FALSE(s1 <= cs);
	EXPECT_TRUE(cs <= s1);
}