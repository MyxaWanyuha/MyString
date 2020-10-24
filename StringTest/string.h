#pragma once
#include <ostream>

namespace sbr
{
	class string
	{
	public:
		string();
		
		string(const string& s);

		string(string&& s) noexcept;

		string(const char* cs);

		string(const char c);

		~string() { free(str); };

		const char* c_str() const noexcept { return str; };

		int length() const noexcept { return clen - 1; }

		string& operator=(const string& s);

		string& operator=(string&& s) noexcept;

		const char& operator[](std::size_t position) const;
		char& operator[](std::size_t position);

		friend std::ostream& operator<<(std::ostream& os, const string& s);

		friend string operator+(const string& ls, const string& rs);
		string operator+=(const string& rs);

		friend bool operator==(const string& ls, const string& rs);
		friend bool operator!=(const string& ls, const string& rs) { return !(ls == rs); };
		friend bool operator>=(const string& ls, const string& rs) { return  (ls == rs) || (ls > rs); }
		friend bool operator>(const string& ls, const string& rs);
		friend bool operator<=(const string& ls, const string& rs) { return  (ls == rs) || (ls < rs); }
		friend bool operator<(const string& ls, const string& rs);

	private:
		void copy(const char* s, std::size_t len);
		static char* new_realloc(void* mem, std::size_t size);

		char* str = nullptr; //c-string
		std::size_t clen = 0;//string length + \0
	};
}

