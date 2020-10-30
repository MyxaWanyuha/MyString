#include <iostream>
#include <fstream>
#include <list>
#include <vector>
#include <algorithm>
#include "MemLeakTest.h"
#include "string.h"

std::istream& operator>>(std::istream& in, sbr::string& s)
{
	//bad, but I don't know how to do it right
	const int buffSz = 100;
	char buff[buffSz];
	in.getline(buff, buffSz, '\n');
	s = buff;
	return in;
}

sbr::string toLower(const sbr::string& s)
{
	sbr::string res{ s };
	for (size_t i = 0; i < res.length(); ++i)
		res[i] = tolower(res[i]);
	return res;
}

int main()
{
	//MemoryLeakTest();
	std::ifstream ifs("test.txt");
	if (!ifs.is_open())
	{
		std::cerr << "File not open\n";
		return 1;
	}

	sbr::string s;
	std::list<sbr::string> container;
	while (ifs >> s)
		container.push_back(s);
	ifs.close();

	container.sort(
		[](const sbr::string& lv, const sbr::string& rv)
		{
			sbr::string lvc(std::move(toLower(lv)));
			sbr::string rvc(std::move(toLower(rv)));
			return lvc > rvc;
		});

	for (auto& e : container)
		std::cout << e << '\n';

    return 0;
}
