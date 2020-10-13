#pragma once
#include <ostream>
#include <exception>
/*
����������� ����� ������������ �����, �������:
1. ������� �� C++11 ��� ����� ���� ��������� ���������. �� ���������� � ����� ������
�����-���� ������ ���������� ������������ �����, ����������� ��� ����� ���������� STL.
2. ����� ����������� �����������, �������� ������������ � ������������ move-���������.
� ������ ���� "�������" �������� �������� ���� �����.
3. ������������ ������ ������������� �������, ��������� ������� �������� ������ �
������������ ����� (������� malloc()/free() ��� ��������� new/delete).

�������� ������ � �������������� ����� ������ ����� � ������-���� ���������� STL.
��������� ������ ��������� ������ �����, ����� �������� ��� � �������, ��������
������������������� ��� ����� ��������.

���������-������ �������� �� ��������� ������.
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
