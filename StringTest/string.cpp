#include "pch.h"
#include "string.h"
#include <stdexcept>
#include "cstrfunctions.h"

namespace sbr
{
	string::string() : clen(1)
	{
		str = new_realloc(nullptr, 1);
		str[0] = '\0';
	}

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

	string::string(const char c)
	{
		str = new_realloc(str, 2);
		str[0] = c;
		str[1] = '\0';
		clen = 2;
	}

	string& string::operator=(const string& s)
	{
		std::free(str);
		copy(s.c_str(), s.clen);
		return *this;
	}

	string& string::operator=(string&& s) noexcept
	{
		std::free(str);
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
		auto newLen = clen + rs.length();
		str = new_realloc(str, newLen);
		clen = newLen;
		sbr::strcat(str, rs.str);
		return *this;
	}

	bool operator==(const sbr::string& ls, const sbr::string& rs)
	{
		if (ls.clen != rs.clen)
			return false;
		return sbr::strcmp(ls.str, rs.str) == 0;
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
		str = new_realloc(str, len);
		clen = len;
		sbr::strcpy(str, s);
	}

	char* string::new_realloc(void* mem, std::size_t size)
	{
		if (size == 0)
			size = 1;
		char* res = nullptr;
		while (true)
		{
			if (res = static_cast<char*>(std::realloc(mem, size)))
				return res;

			std::new_handler globalHandler = std::set_new_handler(0);
			std::set_new_handler(globalHandler);
			if (globalHandler)
				(*globalHandler)();
			else
				throw std::bad_alloc();
		}
	}

	std::ostream& operator<<(std::ostream& os, const sbr::string& s)
	{
		os << s.c_str();
		return os;
	}

	sbr::string operator+(const sbr::string& ls, const sbr::string& rs)
	{
		sbr::string res(ls);
		res += rs;
		return string(std::move(res));
	}
}