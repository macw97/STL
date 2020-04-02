#include <iostream>
#include <cassert>
#include <algorithm>
#include <stdexcept>
template<typename T>
class VectorP
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


	VectorP(std::size_t capacity);
	VectorP(std::size_t capacity, const T& AutoValues);
	VectorP(VectorP const& copy);
	VectorP(VectorP&& move) noexcept;
	~VectorP();
		
	VectorP& operator=(VectorP const& copy);
	VectorP& operator=(VectorP&& move) noexcept;

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
	//inline void assign(T begin, T end);
	inline void swap(VectorP& to_swap) noexcept;
};
template<typename T>
VectorP<T>::VectorP(size_t capacity)
	: capacity(capacity = 10)
	, length(0)
	, buffer(static_cast<T*>(::operator new(sizeof(T)* capacity)))
	//Forming buffer depending on the size of type T and allocates memory by ::operator new not calling T constructor
{}
template<typename T>
VectorP<T>::VectorP(size_t capacity, const T& AutoValues)
	: capacity(capacity)
	, length(0)
	, buffer(static_cast<T*>(::operator new(sizeof(T)* capacity)))
{
	std::fill(buffer, buffer + capacity, AutoValues);
	length = capacity;
}
template<typename T>
VectorP<T>::VectorP(VectorP const& copy)
	:capacity(copy.capacity)
	, length(copy.length)
	, buffer(static_cast<T*>(::operator new(sizeof(T)*copy.capacity)))
{
	for (size_t i = 0; i < copy.length; i++)
	{
		push_back(copy.buffer[i]);
	}
}

template<typename T>
VectorP<T>::VectorP(VectorP&& move) noexcept
	:capacity(0)
	,length(0)
	,buffer(nullptr)
{
	move.swap(*this);
}

template<typename T>
VectorP<T>::~VectorP()
{
	delete[] buffer;	
}
template<typename T>
VectorP<T>& VectorP<T>::operator=(VectorP const& copy)
{
	if (&copy == this)
	{
		return *this;
	}
	VectorP tmp(copy);
	tmp.swap(*this);
		return *this;
}

template<typename T>
VectorP<T>& VectorP<T>::operator=(VectorP<T>&& move) noexcept
{
	move.swap(*this);
	return *this;
}
template<typename T>
inline T& VectorP<T>::operator[](std::size_t index)
{
	return buffer[index];
}
template<typename T>
inline T& VectorP<T>::at(size_t index)
{
	if (index >= length)
		throw std::out_of_range("Out of range");

	return buffer[index];
}
template<typename T>
inline void VectorP<T>::push_back(const T& value)
{
	resizeIfNeeded();
	internal_push_back(value);
}
template<typename T>
inline void VectorP<T>::pop_back()
{
	--length;
	buffer[length].~T();
}
template<typename T>
inline void VectorP<T>::clear()
{
	for (size_t i = 0; i < length; i++)
	{
		buffer[size - 1 - i].~T();
	}
	length = 0;
}

template<typename T>
inline void VectorP<T>::assign(size_t count, const T& value)
{
	VectorP<T> tmp(count, value);
	tmp.swap(*this);
}

/*template<typename T>
inline void VectorP<T>::assign(T begin, T end)
{
	size_t tmp_capacity = std::distance(begin, end);
	VectorP<T> tmp(tmp_capacity);
	std::for_each(begin, end, [&tmp](T const& element) {tmp.push_back(element); });
	tmp.swap(*this);
}*/
template<typename T>
inline void VectorP<T>::swap(VectorP& to_swap) noexcept
{
	using std::swap;
	swap(capacity, to_swap.capacity);
	swap(length, to_swap.length);
	swap(buffer, to_swap.buffer);
}
template<typename T>
inline void VectorP<T>::resizeIfNeeded()
{
	if (length == capacity)
	{
		std::size_t newCapacity = std::max(2.0, capacity * 1.5);
		VectorP<T> tmp(newCapacity);
		std::for_each(buffer, buffer + length, [&tmp](T const& element) {tmp.push_back(element); });
		tmp.swap(*this);
	}
}
template<typename T>
inline void VectorP<T>::internal_push_back(T const& value)
{
	new (buffer + length) T(value);
	++length;
}
