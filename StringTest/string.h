#pragma once
#include <ostream>

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

		const char* c_str() const noexcept { return m_str; };

		int length() const noexcept { return m_clen - 1; }

		string operator+=(const string& rs);

		string& operator=(const string& s);

		string& operator=(string&& s) noexcept;

		const char& operator[](std::size_t position) const;
		char& operator[](std::size_t position);

	private:
		//Create new buffer and copy s to buffer
		void reallocAndCopy(const char* s, std::size_t len);
		static char* new_realloc(void* mem, std::size_t size);
		
		//c-string
		char* m_str = nullptr;
		//string length + 0 terminator
		std::size_t m_clen = 0;
	};
	
	std::ostream& operator<<(std::ostream& os, const string& s);
	string operator+(const string& ls, const string& rs);
	extern bool operator==(const sbr::string& ls, const sbr::string& rs);
	extern bool operator>(const sbr::string& ls, const sbr::string& rs);
	extern bool operator<(const sbr::string& ls, const sbr::string& rs);
	extern bool operator!=(const sbr::string& ls, const sbr::string& rs);
	extern bool operator>=(const sbr::string& ls, const sbr::string& rs);
	extern bool operator<=(const sbr::string& ls, const sbr::string& rs);
}


