#ifndef __CSTRFUNCTIONS_H_
#define __CSTRFUNCTIONS_H_

namespace sbr
{
    int strcmp( const char* s1, const char* s2 ) noexcept;
    void strcpy( char* dest, const char* src ) noexcept;
    char* strcat( char* dest, const char* src ) noexcept;
    size_t strlen( const char* str ) noexcept;
}

#endif	// __CSTRFUNCTIONS_H_
