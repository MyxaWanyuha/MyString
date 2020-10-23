#include <cstring>
#include <stdexcept>
#include "string.h"
#include "CRC32.h"

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
			throw std::out_of_range("Out of bounds of an array");
		return str[position];
	}

	char& string::operator[](std::size_t position)
	{
		return const_cast<string&>(*this)[position];
	}

	string string::operator+=(const string& rs)
	{
		*this = *this + rs;
		return *this;
	}

	bool string::operator==(const string& rs)
	{
		if (-1 == hashCRC32)
			hashCRC32 = Crc32(reinterpret_cast<unsigned char*>(str), clen);
		if (-1 == rs.hashCRC32)
			rs.hashCRC32 = Crc32(reinterpret_cast<unsigned char*>(rs.str), rs.clen);
		return hashCRC32 == rs.hashCRC32;
	}

	bool string::operator>(const string& rs)
	{
		if (clen > rs.clen) 
			return true;
		return strcmp(str, rs.str) > 0;
	}

	bool string::operator<(const string& rs)
	{
		if (clen < rs.clen)
			return true;
		return strcmp(str, rs.str) < 0;
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