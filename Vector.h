#pragma once
#include <cassert>
#include <algorithm>
#include <stdexcept>

template<typename T>
class Vector
{
private:
	T* buffer;
	std::size_t capacity;
	std::size_t length;
	inline void resizeIfNeeded();
	inline void internal_push_back(const T& value);
public:
	using iterator = T*;
	using const_iterator = T const*;
	using reverse_iterator = std::reverse_iterator<iterator>;
	using const_reverse_iterator = std::reverse_iterator<const_iterator>;

	Vector();
	Vector(std::size_t capacity);
	Vector(std::size_t capacity, const T& AutoValues);
	Vector(Vector const& copy);
	Vector(Vector&& move) noexcept;
	~Vector();

	Vector& operator=(Vector const& copy);
	Vector& operator=(Vector&& move) noexcept;

	inline T& operator[](std::size_t index);
	//inline const T& operator[](std::size_t index);

	std::size_t size() const { return length; }
	bool empty() const { return length == 0; }

	inline T& at(size_t index);
	inline T& front() { return buffer[0]; }
	inline const T& front() const { return buffer[0]; }
	inline T& back() { return buffer[length - 1]; }
	inline const T& back() const { return buffer[length - 1]; }

	inline iterator begin() { return buffer; }
	inline iterator end() { return buffer + length; }
	inline reverse_iterator rbegin() { return reverse_iterator(end()); }
	inline reverse_iterator rend() { return reverse_iterator(begin()); }

	inline const_iterator cbegin() const { return buffer; }
	inline const_iterator cend() const { return buffer + length; }
	inline const_reverse_iterator crbegin() const { return const_reverse_iterator(end()); }
	inline const_reverse_iterator crend() const { return const_reverse_iterator(begin()); }

	inline void push_back(T const& value);
	inline void pop_back();
	inline void clear();
	inline void assign(size_t count, const T& value);
	inline void assign(T* begin, T* end);
	inline void swap(Vector& to_swap) noexcept;
};
template<typename T>
inline Vector<T>::Vector()
	: capacity(1)
	, length(0)
	, buffer(static_cast<T*>(::operator new(sizeof(T))))
{}
template<typename T>
Vector<T>::Vector(size_t capacity)
	: capacity(capacity)
	, length(0)
	, buffer(static_cast<T*>(::operator new(sizeof(T)* capacity)))
	//Forming buffer depending on the size of type T and allocates memory by ::operator new not calling T constructor
{}
template<typename T>
Vector<T>::Vector(size_t capacity, const T& AutoValues)
	: capacity(capacity)
	, length(0)
	, buffer(static_cast<T*>(::operator new(sizeof(T)* capacity)))
{
	std::fill(buffer, buffer + capacity, AutoValues);
	length = capacity;
}
template<typename T>
Vector<T>::Vector(Vector const& copy)
	:capacity(copy.capacity)
	, length()
	, buffer(static_cast<T*>(::operator new(sizeof(T)* copy.capacity)))
{
	for (size_t i = 0; i < copy.length; i++)
	{
		push_back(copy.buffer[i]);
	}
}

template<typename T>
Vector<T>::Vector(Vector&& move) noexcept
	:capacity(0)
	, length(0)
	, buffer(nullptr)
{
	move.swap(*this);
}

template<typename T>
Vector<T>::~Vector()
{
	//delete[] buffer ; - what happens then ? Destructor is called which will
	//call delete on the buffer pointer which will call the destructor for each member.
	//These members have already been destroyed so now it would be undefined behavior
	//delete object;   - is almost equivalent to  
	//object->~Class();  
	//::operator delete(object);

	delete[] buffer;

}
template<typename T>
Vector<T>& Vector<T>::operator=(Vector const& copy)
{
	if (&copy == this)
	{
		return *this;
	}
	Vector tmp(copy);
	tmp.swap(*this);
	return *this;
}

template<typename T>
Vector<T>& Vector<T>::operator=(Vector<T>&& move) noexcept
{
	move.swap(*this);
	return *this;
}

template<typename T>
inline bool operator==(Vector<T> const& lh, Vector<T> const& rh)
{
	if (lh.size() != rh.size())
		return false;

	return std::equal(lh.cbegin(), lh.cend(), rh.cbegin(),rh.cend());
	
}

template<typename T>
inline bool operator!=(Vector<T> const& lh, Vector<T> const& rh)
{
	if (lh.size() != rh.size())
		return true;

	return !(std::equal(lh.cbegin(), lh.cend(), rh.cbegin(), rh.cend()));
}



template<typename T>
inline T& Vector<T>::operator[](std::size_t index)
{
	return buffer[index];
}



template<typename T>
inline T& Vector<T>::at(size_t index)
{
	if (index >= length)
		throw std::out_of_range("Out of range");

	return buffer[index];
}
template<typename T>
inline void Vector<T>::push_back(const T& value)
{
	resizeIfNeeded();
	internal_push_back(value);
}
template<typename T>
inline void Vector<T>::pop_back()
{
	--length;
	buffer[length].~T();
}
template<typename T>
inline void Vector<T>::clear()
{
	for (size_t i = 0; i < length; i++)
	{
		buffer[capacity - 1 - i].~T();
	}
	length = 0;
}

template<typename T>
inline void Vector<T>::assign(size_t count, const T& value)
{
	Vector<T> tmp(count, value);
	tmp.swap(*this);
}

template<typename T>
inline void Vector<T>::assign(T* begin, T* end)
{
	size_t tmp_capacity = std::distance(begin, end);
	Vector<T> tmp(tmp_capacity);
	std::for_each(begin, end, [&tmp](T const& element) {tmp.push_back(element); });
	tmp.swap(*this);
}
template<typename T>
inline void Vector<T>::swap(Vector& to_swap) noexcept
{
	using std::swap;
	swap(capacity, to_swap.capacity);
	swap(length, to_swap.length);
	swap(buffer, to_swap.buffer);
}
template<typename T>
inline void Vector<T>::resizeIfNeeded()
{
	if (length == capacity)
	{
		std::size_t newCapacity = std::max(2.0,capacity * 1.5);
		Vector<T> tmp(newCapacity);
		std::for_each(buffer, buffer + length, [&tmp](T const& element) {tmp.push_back(element); });
		tmp.swap(*this);
	}
}
template<typename T>
inline void Vector<T>::internal_push_back(T const& value)
{
	new (buffer + length) T(value);
	++length;
}