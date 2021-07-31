#include "string.h"
#include <stdexcept>
#include "cstrfunctions.h"

using namespace sbr;


//
string::string() : m_clen( 1 )
{
	m_str = reallocation( nullptr, 1 );
	m_str[ 0 ] = '\0';
}


//
string::string( const string& s )
{
	reallocAndCopy( s.c_str(), s.m_clen );
}


//
string::string( string&& s ) noexcept
{
	m_str = s.m_str;
	m_clen = s.m_clen;
	s.m_str = nullptr;
}


//
string::string( const char* cs )
{
	reallocAndCopy( cs, sbr::strlen( cs ) + 1 );
}


//
string::string( const char c )
{
	m_str = reallocation( m_str, 2 );
	m_str[ 0 ] = c;
	m_str[ 1 ] = '\0';
	m_clen = 2;
}

string::iterator string::begin() const
{
	return iterator( &m_str[ 0 ] );
}


//
string::iterator string::end() const
{
	return iterator( &m_str[ m_clen ] );
}


//
string::const_iterator string::cbegin() const
{
	return const_iterator( &m_str[ 0 ] );
}


//
string::const_iterator string::cend() const
{
	return const_iterator( &m_str [ m_clen ] );
}


//
string& string::operator=( const string& s )
{
	if ( this == &s )
		return *this;
	std::free( m_str );
	m_str = nullptr;
	reallocAndCopy( s.c_str(), s.m_clen );
	return *this;
}


//
string& string::operator=( string&& s ) noexcept
{
	if ( this == &s )
		return *this;
	std::free( m_str );
	m_str = s.m_str;
	m_clen = s.m_clen;
	s.m_str = nullptr;
	return *this;
}


//
const char& string::operator[]( std::size_t position ) const
{
	if ( position >= m_clen || position < 0 )
		throw std::out_of_range( "Out of bounds of a string" );
	return m_str[ position ];
}


//
char& string::operator[]( std::size_t position )
{
	return const_cast< char& >( static_cast< const string& >( *this )[ position ] );
}


//
void string::swap( string& rs ) noexcept
{
	std::swap( m_str, rs.m_str );
	std::swap( m_clen, rs.m_clen );
}


//
string string::operator+=( string rs )
{
	std::size_t newLen = m_clen + rs.length();
	m_str = reallocation( m_str, newLen );
	m_clen = newLen;
	sbr::strcat( m_str, rs.m_str );
	return *this;
}


//
void string::reallocAndCopy( const char* s, size_t len )
{
	m_str = reallocation( m_str, len );
	m_clen = len;
	sbr::strcpy( m_str, s );
}


//
char* string::reallocation( void* mem, std::size_t size )
{
	//if (size == 0) size = 1; else size = size; but faster
	size = ( size == 0 ) + ( size != 0 ) * size;
	char* res = nullptr;
	while ( true )
	{
		if ( res = static_cast< char* >( std::realloc( mem, size ) ) )
			return res;

		std::new_handler globalHandler = std::set_new_handler( 0 );
		std::set_new_handler( globalHandler );
		if ( globalHandler )
			( *globalHandler )();
		else
			throw std::bad_alloc();
	}
}


//
sbr::string operator+( const sbr::string& ls, const sbr::string& rs )
{
	sbr::string res( ls );
	res += rs;
	return string( std::move( res ) );
}


//
std::ostream& operator<<( std::ostream& os, const sbr::string& s )
{
	os << s.c_str();
	return os;
}


//
string::iterator string::iterator::operator++()
{
	iterator i = *this;
	ptr++;
	return i;
}


//
bool sbr::operator==( const sbr::string& ls, const sbr::string& rs )
{
	if ( ls.length() != rs.length() )
		return false;
	return sbr::strcmp( ls.c_str(), rs.c_str() ) == 0;
}


//
bool sbr::operator<( const sbr::string& ls, const sbr::string& rs )
{
	return sbr::strcmp( ls.c_str(), rs.c_str() ) < 0;
}


//
bool sbr::operator>( const sbr::string& ls, const sbr::string& rs )
{
	return sbr::strcmp( ls.c_str(), rs.c_str() ) > 0;
}


//
bool sbr::operator!=( const sbr::string& ls, const sbr::string& rs )
{
	return !( ls == rs );
}


//
bool sbr::operator>=( const sbr::string& ls, const sbr::string& rs )
{
	return ( ls == rs ) || ( ls > rs );
}


//
bool sbr::operator<=( const sbr::string& ls, const sbr::string& rs )
{
	return  ( ls == rs ) || ( ls < rs );
}


//
string::iterator string::iterator::operator++( int i )
{
	ptr++;
	return *this;
}


//
string::const_iterator string::const_iterator::operator++()
{
	const_iterator i = *this;
	ptr++;
	return i;
}


//
string::const_iterator string::const_iterator::operator++( int i )
{
	ptr++;
	return *this;
}
