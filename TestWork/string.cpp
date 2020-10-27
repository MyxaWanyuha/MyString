#include "string.h"
#include <stdexcept>
#include "cstrfunctions.h"

namespace sbr
{
	string::string() : m_clen(1)
	{
		m_str = new_realloc(nullptr, 1);
		m_str[0] = '\0';
	}

	string::string(const string& s)
	{
		reallocAndCopy(s.c_str(), s.m_clen);
	}

	string::string(string&& s) noexcept
	{
		m_str = s.m_str;
		m_clen = s.m_clen;
		s.m_str = nullptr;
	}

	string::string(const char* cs)
	{
		reallocAndCopy(cs, sbr::strlen(cs) + 1);
	}

	string::string(const char c)
	{
		m_str = new_realloc(m_str, 2);
		m_str[0] = c;
		m_str[1] = '\0';
		m_clen = 2;
	}

	string& string::operator=(const string& s)
	{
		if (this == &s)
			return *this;
		std::free(m_str);
		m_str = nullptr;
		reallocAndCopy(s.c_str(), s.m_clen);
		return *this;
	}

	string& string::operator=(string&& s) noexcept
	{
		if (this == &s)
			return *this;
		std::free(m_str);
		m_str = s.m_str;
		m_clen = s.m_clen;
		s.m_str = nullptr;
		return *this;
	}

	const char& string::operator[](std::size_t position) const
	{
		if (position >= m_clen || position < 0)
			throw std::out_of_range("Out of bounds of an array");
		return m_str[position];
	}

	char& string::operator[](std::size_t position)
	{
		return const_cast<char&>(static_cast<const string&>(*this)[position]);
	}

	string string::operator+=(const string& rs)
	{
		auto newLen = m_clen + rs.length();
		m_str = new_realloc(m_str, newLen);
		m_clen = newLen;
		sbr::strcat(m_str, rs.m_str);
		return *this;
	}

	void string::reallocAndCopy(const char* s, size_t len)
	{
		m_str = new_realloc(m_str, len);
		m_clen = len;
		sbr::strcpy(m_str, s);
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

	sbr::string operator+(const sbr::string& ls, const sbr::string& rs)
	{
		sbr::string res(ls);
		res += rs;
		return string(std::move(res));
	}

	std::ostream& operator<<(std::ostream& os, const sbr::string& s)
	{
		os << s.c_str();
		return os;
	}

	inline bool operator==(const sbr::string& ls, const sbr::string& rs)
	{
		if (ls.length() != rs.length())
			return false;
		return sbr::strcmp(ls.c_str(), rs.c_str()) == 0;
	}

	inline bool operator>(const sbr::string& ls, const sbr::string& rs)
	{
		if (ls.length() > rs.length())
			return true;
		return sbr::strcmp(ls.c_str(), rs.c_str()) > 0;
	}

	inline bool operator<(const sbr::string& ls, const sbr::string& rs)
	{
		if (ls.length() < rs.length())
			return true;
		return sbr::strcmp(ls.c_str(), rs.c_str()) < 0;
	}

	inline bool operator!=(const sbr::string& ls, const sbr::string& rs) { return !(ls == rs); }

	inline bool operator>=(const sbr::string& ls, const sbr::string& rs) { return  (ls == rs) || (ls > rs); }

	inline bool operator<=(const sbr::string& ls, const sbr::string& rs) { return  (ls == rs) || (ls < rs); }

}