#include <iostream>
#include "string.h"

void print(const sbr::string& s)
{
    std::cout << s.c_str() << ' ' << s.length() << '\n';
}
int main()
{
    sbr::string s("12");
    sbr::string s2("34");
    auto s3 = s + s2;
    auto s4 = "" + s;
    auto s5 = s + "sd";
    s5[6];
    print(s);
    print(s2);
    print(s3);
    print(s4);
    print(s5);
}