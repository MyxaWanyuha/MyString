#pragma once
#include "string.h"
//Visual Studio shows how much memory used
void MemoryLeakTest()
{
	while (true)
	{
		{
			sbr::string s;
		}

		{
			const char cc = 'c';
			char c = 'c';
			sbr::string s(c);
			sbr::string sc(cc);
			sbr::string s2('s');
		}

		{
			const char cs[] = "Just a string";
			sbr::string s{ cs };
		}

		{
			const char cs[] = "Just a string";
			sbr::string s{ cs };
			sbr::string s2{ s };
		}

		{
			const char cs[] = "Just a string";
			sbr::string s{ cs };
			sbr::string s2{ std::move(s) };
		}

		{
			sbr::string s1("string1");
			sbr::string s2("string2");
			sbr::string s3{ s1 + s2 };
		}

		{
			sbr::string s('s');
			s += 'a';
		}

		{
			sbr::string s1("string1");
			sbr::string s2("string2");
			s1 += s2;
			const char cs[] = "string1string2";
		}

		{
			const char cs[] = "Just a string";
			sbr::string s1{ cs };
			sbr::string s2 = s1;
		}

		{
			const char cs[] = "Just a string";
			sbr::string s1{ cs };
			sbr::string s2 = std::move(s1);
		}

		{
			const char cs[] = "Just a string";
			sbr::string s1{ cs };
			s1 += "s";
		}

		{
			const char cs[] = "Just a string";
			sbr::string s1{ cs };
			sbr::string s2 = s1;
			auto s3 = s1 + s2;
			s3 += s3 + s1 + s2;
			s1 = s2 = s3 = "testing";
		}
	}
}