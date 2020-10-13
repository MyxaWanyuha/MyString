#pragma once
#include <ostream>
#include <exception>
/*
–еализовать класс динамических строк, который:
1. Ќаписан на C++11 без каких либо сторонних библиотек. Ќе использует в своей основе
какую-либо другую реализацию динамических строк, контейнеров или умных указателей STL.
2. »меет конструктор копировани€, оператор присваивани€ и поддерживает move-сематнику.
” класса есть "внешний" оператор сложени€ двух строк.
3. ѕоддерживает строки произвольного размера, использу€ базовые операции работы с
динамическим хипом (функции malloc()/free() или операторы new/delete).

Ќаписать пример с использованием этого класса строк и какого-либо контейнера STL.
ѕрограмма должна принимать список строк, затем выдавать его в пор€дке, обратном
лексикографическому без учета регистра.

ѕрограмма-пример работает из командной строки.
*/

namespace sbr
{
	class string
	{
	public:
		string() :str(new char[1]{ '\0' }), clen(1) {}

		string(const string& s);

		string(string&& s) noexcept;

		string(const char* cs);

		~string() { delete[] str; };

		const char* c_str() const noexcept { return str; };

		int length() const noexcept { return clen - 1; }

		string& operator=(const string& s);

		string& operator=(string&& s) noexcept;

		const char& operator[](std::size_t position) const;
		char& operator[](std::size_t position);

		friend std::ostream& operator<<(std::ostream& os, const string& s);

		friend string operator+(const string& ls, const string& rs);

	private:
		void copy(const char* s, std::size_t len);
		char* str;	//c-string
		std::size_t clen;//str + \0
	};
}
