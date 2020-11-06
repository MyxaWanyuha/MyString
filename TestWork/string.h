#pragma once
#include <ostream>
#include "Iterator.h"

namespace sbr
{
	class string
	{
	public:
		//Create "" string
		string();
		
		string(const string& s);

		string(string&& s) noexcept;

		string(const char* cs);

		string(const char c);

		~string() { free(m_str); };

		Iterator<char> begin() const { return Iterator<char>(&m_str[0]); }
		Iterator<char> end() const { return Iterator<char>(&m_str[m_clen]); }

		Iterator<const char> cbegin() const { return Iterator<const char>(&m_str[0]); }
		Iterator<const char> cend() const { return Iterator<const char>(&m_str[m_clen]); }

		ReverseIterator<char> rbegin() const { return ReverseIterator<char>(&m_str[m_clen - 1]); }
		ReverseIterator<char> rend() const { return ReverseIterator<char>(&m_str[-1]); }

		ReverseIterator<const char> crbegin() const { return ReverseIterator<const char>(&m_str[m_clen - 1]); }
		ReverseIterator<const char> crend() const { return ReverseIterator<const char>(&m_str[-1]); }

		const char* c_str() const noexcept { return m_str; };

		std::size_t length() const noexcept { return m_clen - 1; }

		void swap(string& rs) noexcept;

		string operator+=(const string& rs);

		string& operator=(const string& s);

		string& operator=(string&& s) noexcept;

		const char& operator[](std::size_t position) const;
		char& operator[](std::size_t position);

	private:
		//Create new buffer and copy s to buffer
		void reallocAndCopy(const char* s, std::size_t len);
		static char* newRealloc(void* mem, std::size_t size);
		
		//c-string
		char* m_str = nullptr;
		//string length + 0 terminator
		std::size_t m_clen = 0;
	};

	std::ostream& operator<<(std::ostream& os, const string& s);
	string operator+(const string& ls, const string& rs);
	bool operator==(const sbr::string& ls, const sbr::string& rs);
	bool operator>(const sbr::string& ls, const sbr::string& rs);
	bool operator<(const sbr::string& ls, const sbr::string& rs);
	bool operator!=(const sbr::string& ls, const sbr::string& rs);
	bool operator>=(const sbr::string& ls, const sbr::string& rs);
	bool operator<=(const sbr::string& ls, const sbr::string& rs);
}


