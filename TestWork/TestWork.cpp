#include <iostream>
#include <fstream>
#include <list>
#include "string.h"


//
sbr::string toLower( const sbr::string& s )
{
	sbr::string res{ s };
	for ( auto& e : res )
		e = tolower(e);
	return res;
}


//
int main()
{
	try
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
				sbr::string lvc( toLower( lv ) );
				sbr::string rvc( toLower( rv ) );
				return lvc > rvc;
			} );

		for ( sbr::string& e : container )
			std::cout << e << '\n';
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what();
		return 2;
	}
	catch (...)
	{
		return 3;
	}
    return 0;
}
