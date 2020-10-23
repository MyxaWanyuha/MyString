#include "pch.h"
#include "string.h"
#include <stdexcept>
#include "cstrfunctions.h"
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
		copy(cs, sbr::strlen(cs) + 1);
	}

	string& string::operator=(const string& s)
	{
		hashCRC32 = s.hashCRC32;
		delete[] str;
		copy(s.c_str(), s.clen);
		return *this;
	}

	string& string::operator=(string&& s) noexcept
	{
		hashCRC32 = s.hashCRC32;
		str = s.str;
		clen = s.clen;
		s.str = nullptr;
		return *this;
	}

	const char& string::operator[](std::size_t position) const
	{
		if (position >= clen || position < 0)
			throw std::out_of_range("Out of bounds of an array");
		return str[position];
	}

	char& string::operator[](std::size_t position)
	{
		return const_cast<char&>(static_cast<const string&>(*this)[position]);
	}

	string string::operator+=(const string& rs)
	{
		hashCRC32 = -1;
		*this = *this + rs;
		return *this;
	}

	bool operator==(const sbr::string& ls, const sbr::string& rs)
	{
		if (-1 == ls.hashCRC32)
			ls.hashCRC32 = Crc32(reinterpret_cast<unsigned char*>(ls.str), ls.clen);
		if (-1 == rs.hashCRC32)
			rs.hashCRC32 = Crc32(reinterpret_cast<unsigned char*>(rs.str), rs.clen);
		return ls.hashCRC32 == rs.hashCRC32;
	}

	bool operator>(const sbr::string& ls, const sbr::string& rs)
	{
		if (ls.clen > rs.clen)
			return true;
		return sbr::strcmp(ls.str, rs.str) > 0;
	}

	bool operator<(const sbr::string& ls, const sbr::string& rs)
	{
		if (ls.clen < rs.clen)
			return true;
		return sbr::strcmp(ls.str, rs.str) < 0;
	}

	void string::copy(const char* s, size_t len)
	{
		str = new char[len];
		clen = len;
		sbr::strcpy(str, s);
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
		sbr::strcat(nstr, ls.str);
		sbr::strcat(nstr, rs.str);
		return string(nstr);
	}
}