#include "cstrfunctions.h"


//
int sbr::strcmp( const char* s1, const char* s2 ) noexcept
{
    while (*s1 && (*s1 == *s2))
    {
        s1++;
        s2++;
    }
    return *(const unsigned char*)s1 - *(const unsigned char*)s2;
}


//
void sbr::strcpy( char* dest, const char* src ) noexcept
{
    while ((*dest++ = *src++));
}


//
char* sbr::strcat( char* dest, const char* src ) noexcept
{
    char* rdest = dest;
    while (*dest)
        dest++;
    while (*dest++ = *src++);
    return rdest;
}

size_t sbr::strlen( const char* str ) noexcept
{
    const char* s;
    for (s = str; *s; ++s);
    return (s - str);
}