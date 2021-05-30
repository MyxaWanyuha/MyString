#include <iostream>
#include <fstream>
#include <list>
#include "string.h"


//
sbr::string toLower( const sbr::string& s )
{
	sbr::string res{ s };
	for ( size_t i = 0; i < res.length(); ++i )
		res[ i ] = tolower( res[ i ] );
	return res;
}


//
int main()
{
	std::ifstream ifs( "test.txt" );
	if ( !ifs.is_open() )
	{
		std::cerr << "File not open\n";
		return 1;
	}

	std::string s;
	std::list< sbr::string > container;
	while ( ifs >> s )
		container.push_back( s.c_str() );
	ifs.close();

	container.sort( 
		[]( const sbr::string& lv, const sbr::string& rv )
		{
			sbr::string lvc( std::move( toLower( lv ) ) );
			sbr::string rvc( std::move( toLower( rv ) ) );
			return lvc > rvc;
		} );

	for ( sbr::string& e : container )
		std::cout << e << '\n';

    return 0;
}
