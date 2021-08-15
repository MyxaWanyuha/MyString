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

	s1 = "test1";
	s2 = "test2";
	const char cs2[] = "test1test2";
	s3 = s1 + s2;

	EXPECT_EQ(s3.length(), strlen(cs2));
	EXPECT_EQ(strlen(s3.c_str()), strlen(cs2));
	EXPECT_TRUE(s3 == cs2);

	s3 += s3 + s1 + s2;
	const char cs3[] = "test1test2test1test2test1test2";
	EXPECT_EQ(s3.length(), strlen(cs3));
	EXPECT_EQ(strlen(s3.c_str()), strlen(cs3));
	EXPECT_TRUE(s3 == cs3);
}

TEST(Operators, OperatorPlus2)
{
	sbr::string s4("long string 123");
	const char cs4[] = "long string 123long string 123";
	s4 += s4;
	EXPECT_EQ(s4.length(), strlen(cs4));
	EXPECT_EQ(strlen(s4.c_str()), strlen(cs4));
	EXPECT_TRUE(s4 == cs4);
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


	sbr::string s3{ "" };
	const char cs2[] = "testing";
	s1 = s2 = s3 = cs2;

	EXPECT_EQ(s1.length(), strlen(cs2));
	EXPECT_EQ(strlen(s1.c_str()), strlen(cs2));
	EXPECT_TRUE(s1 == cs2);

	EXPECT_EQ(s1.length(), s2.length());
	EXPECT_EQ(strlen(s1.c_str()), strlen(s2.c_str()));
	EXPECT_TRUE(s1 == s2);

	EXPECT_EQ(s2.length(), s3.length());
	EXPECT_EQ(strlen(s2.c_str()), strlen(s3.c_str()));
	EXPECT_TRUE(s2 == s3);
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

TEST(Operators, SelfAssigment)
{
	const char cs[] = "Just a string";
	sbr::string s{ cs };
	s = std::move(s);
	EXPECT_EQ(s.length(), strlen(cs));
	EXPECT_EQ(strlen(s.c_str()), strlen(cs));
	EXPECT_TRUE(s == cs);
	s = s;
	EXPECT_EQ(s.length(), strlen(cs));
	EXPECT_EQ(strlen(s.c_str()), strlen(cs));
	EXPECT_TRUE(s == cs);
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

TEST(Iterators, CBeginCEndAndBeginEnd)
{
	sbr::string s{ "1234567890" };
	EXPECT_TRUE(*s.cbegin() == *s.begin());
	EXPECT_TRUE(*s.cend() == *s.end());
	
	s += s;
	EXPECT_TRUE(*s.cbegin() == *s.begin());
	EXPECT_TRUE(*s.cend() == *s.end());

	s = s + "a";
	EXPECT_TRUE(*s.cbegin() == *s.begin());
	EXPECT_TRUE(*s.cend() == *s.end());

	s = s + 'b';
	EXPECT_TRUE(*s.cbegin() == *s.begin());
	EXPECT_TRUE(*s.cend() == *s.end());

	auto it = s.begin();
	for (auto cit = s.cbegin(); cit != s.cend(); ++cit, ++it)
		EXPECT_TRUE(*it == *cit);

	sbr::string sCopy;
	for (const auto& e : s)
		sCopy += e;
	{
		auto sCopyIt = sCopy.begin();
		for (auto cit = s.cbegin(); cit != s.cend(); ++cit, ++sCopyIt)
			EXPECT_TRUE(*sCopyIt == *cit);
	}
	
	sbr::string s2("abcdefg");
	*s2.begin() = '1';
	EXPECT_TRUE(*s2.cbegin() == *s2.begin());
	EXPECT_TRUE(*s2.cend() == *s2.end());
}