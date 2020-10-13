#include <algorithm>
#include "string.h"

namespace sbr
{
	string::string(const string& s)
	{
		copy(s.c_str(), s.clen);
	}

	string::string(string&& s) noexcept
	{
		str = s.str;
		clen = s.clen;
		s.str = nullptr;
	}

	string::string(const char* cs)
	{
		copy(cs, strlen(cs) + 1);
	}

	string& string::operator=(const string& s)
	{
		delete[] str;
		copy(s.c_str(), s.clen);
		return *this;
	}

	string& string::operator=(string&& s) noexcept
	{
		str = s.str;
		clen = s.clen;
		s.str = nullptr;
		return *this;
	}

	const char& string::operator[](std::size_t position) const
	{
		if (position >= clen)
			throw std::exception("Out of bounds of an array");
		return str[position];
	}

	char& string::operator[](std::size_t position)
	{
		return const_cast<string&>(*this)[position];
	}

	void string::copy(const char* s, size_t len)
	{
		str = new char[len];
		clen = len;
		strcpy_s(str, len, s);
	}

	std::ostream& operator<<(std::ostream& os, const sbr::string& s)
	{
		os << s.c_str();
		return os;
	}

	sbr::string operator+(const sbr::string& ls, const sbr::string& rs)
	{
		auto nlen = ls.length() + rs.length() + 1;
		auto nstr = new char[nlen];
		nstr[0] = '\0';
		strcat_s(nstr, nlen, ls.str);
		strcat_s(nstr, nlen, rs.str);
		return string(nstr);
	}
}