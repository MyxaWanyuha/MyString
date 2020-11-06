#pragma once
#include <cstddef>
#include <iterator>//std::distance
namespace sbr
{
	template<typename T>
	class Iterator
	{
	public:
		Iterator(T* ptr) : m_ptr(ptr) {}
		Iterator(const Iterator<T>& other) = default;
		~Iterator() {}
		Iterator<T>& operator=(const Iterator<T>& other) = default;
		Iterator<T>& operator=(Iterator* ptr) { m_ptr = ptr; return (*this); }

		bool operator==(const Iterator<T>& other) const { return m_ptr == other.m_ptr; }
		bool operator!=(const Iterator<T>& other) const { return m_ptr != other.m_ptr; }

		Iterator<T>& operator+=(const std::ptrdiff_t& movement) { m_ptr += movement; return *this; }
		Iterator<T>& operator-=(const std::ptrdiff_t& movement) { m_ptr -= movement; return *this; }

		Iterator<T>& operator++() { ++m_ptr; return *this; }
		Iterator<T>& operator--() { --m_ptr; return *this; }
		Iterator<T> operator++(int) { auto temp(*this); ++m_ptr; return temp; }
		Iterator<T> operator--(int) { auto temp(*this); --m_ptr; return temp; }

		Iterator<T> operator+(const std::ptrdiff_t& movement) 
		{
			auto oldPtr = m_ptr;
			m_ptr += movement;
			auto temp(*this);
			m_ptr = oldPtr;
			return temp;
		}
		Iterator<T> operator-(const std::ptrdiff_t& movement) { return operator+(-movement); }

		std::ptrdiff_t operator-(const Iterator<T>& rawIterator) { return std::distance(rawIterator.m_ptr, this->m_ptr); }

		operator bool() const { return m_ptr; }

		T&		 operator*()		{ return *m_ptr; }
		const T& operator*()  const { return *m_ptr; }
		T*		 operator->()		{ return  m_ptr; }
		const T* operator->() const { return  m_ptr; }



	protected:
		T* m_ptr;
	};

	template<typename T>
	class ReverseIterator : public Iterator<T>
	{
	public:
		ReverseIterator(T* ptr = nullptr) :Iterator<T>(ptr) {}
		ReverseIterator(const Iterator<T>& rawIterator) { this->m_ptr = rawIterator.getPtr(); }
		ReverseIterator(const ReverseIterator<T>& other) = default;
		~ReverseIterator() {}

		ReverseIterator<T>& operator=(const ReverseIterator<T> & other) = default;
		ReverseIterator<T>& operator=(const Iterator<T>& other) { this->m_ptr = other.m_ptr; return (*this); }
		ReverseIterator<T>& operator=(T* ptr) { this->setPtr(ptr); return (*this); }
		ReverseIterator<T>& operator+=(const std::ptrdiff_t& movement) { this->m_ptr -= movement; return (*this); }
		ReverseIterator<T>& operator-=(const std::ptrdiff_t& movement) { this->m_ptr += movement; return (*this); }
		ReverseIterator<T>& operator++() { --this->m_ptr; return (*this); }
		ReverseIterator<T>& operator--() { ++this->m_ptr; return (*this); }
		ReverseIterator<T> operator++(int) { auto temp(*this); --this->m_ptr; return temp; }
		ReverseIterator<T> operator--(int) { auto temp(*this); ++this->m_ptr; return temp; }
		ReverseIterator<T> operator+(const int& movement) 
		{
			auto oldPtr = this->m_ptr;
			this->m_ptr -= movement;
			auto temp(*this); this->m_ptr = oldPtr;
			return temp;
		}
		ReverseIterator<T> operator-(const int& movement) { auto oldPtr = this->m_ptr; this->m_ptr += movement; auto temp(*this); this->m_ptr = oldPtr; return temp; }

		std::ptrdiff_t  operator-(const ReverseIterator<T> & other) { return std::distance(this->m_ptr, other .m_ptr); }
										 
		Iterator<T>  base() { Iterator<T> forwardIterator(this->m_ptr); ++forwardIterator; return forwardIterator; }
	};
}
