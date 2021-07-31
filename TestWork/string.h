#ifndef __STRING_H_
#define __STRING_H_
#include <ostream>


namespace sbr
{
	class string
	{
	public:

		///
		class iterator
		{
		public:
			///
			iterator( char* ptr ) : ptr( ptr )						{	}

			///
			iterator	operator++();
			iterator	operator++( int i );

			///
			char&		operator*()									{	return *ptr;						}
			char*		operator->()								{	return ptr;							}

			///
			bool		operator==( const iterator& rhs )			{	return ptr == rhs.ptr;				}
			bool		operator!=( const iterator& rhs )			{	return ptr != rhs.ptr;				}
		private:
			char* ptr;
		};

		///
		class const_iterator
		{
		public:
			///
			const_iterator( char* ptr ) : ptr( ptr )				{	}
			
			///
			const_iterator	operator++();
			const_iterator	operator++( int i );

			///
			const char&		operator*()								{	return *ptr;						}
			const char*		operator->()							{	return ptr;							}

			///
			bool			operator==( const const_iterator& rhs )	{	return ptr == rhs.ptr;				}
			bool			operator!=( const const_iterator& rhs )	{	return ptr != rhs.ptr;				}
		private:
			char* ptr;
		};

		/// create "" string
		string();
		string( const string& s );
		string( string&& s ) noexcept;
		string( const char* cs );
		string( const char c );
		~string()													{	free( m_str );				}

		///
		iterator		begin() const;
		iterator		end() const;
		const_iterator	cbegin() const;
		const_iterator	cend() const;
		
		///
		const char*		c_str() const noexcept						{	return m_str;				}
		std::size_t		length() const noexcept						{	return m_clen - 1;			}

		///
		void			swap( string& rs ) noexcept;

		///
		string			operator+=( string rs );
		string&			operator=( const string& s );
		string&			operator=( string&& s ) noexcept;

		///
		const char&		operator[]( std::size_t position ) const;
		char&			operator[]( std::size_t position );

	private:
		/// create new buffer and copy s to buffer
		void			reallocAndCopy( const char* s, std::size_t len );

		///
		static char*	reallocation( void* mem, std::size_t size );
		
		/// c-string
		char* m_str = nullptr;
		/// string length + 0 terminator
		std::size_t m_clen = 0;
	};

	///
	bool			operator==( const sbr::string& ls, const sbr::string& rs );
	bool			operator>( const sbr::string& ls, const sbr::string& rs );
	bool			operator<( const sbr::string& ls, const sbr::string& rs );
	bool			operator!=( const sbr::string& ls, const sbr::string& rs );
	bool			operator>=( const sbr::string& ls, const sbr::string& rs );
	bool			operator<=( const sbr::string& ls, const sbr::string& rs );
}

///
std::ostream&		operator<<(std::ostream& os, const sbr::string& s);
sbr::string			operator+(const sbr::string& ls, const sbr::string& rs);

#endif	// __STRING_H_
