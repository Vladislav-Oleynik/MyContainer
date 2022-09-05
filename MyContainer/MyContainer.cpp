#include "pch.h"
#include <iostream>
#include <vector>

template <class T>
class MyVector {
private:

	size_t m_length;
	size_t m_capacity;
	T *m_data;

public:

	MyVector() : m_length(0), m_capacity(0), m_data(nullptr) {}

	MyVector(const size_t length) : m_length(length), m_capacity(length)
	{
		m_data = new T[m_length];
	}

	MyVector(const MyVector& myvector) : m_length(myvector.m_length), m_capacity(myvector.m_capacity)
	{
		m_data = new T[m_length];
		for (const T& val : myvector)
			push_back(val);
	}

	MyVector(const size_t length, const T& val) : m_length(length), m_capacity(length)
	{
		m_data = new T[length];
		for (int i = 0; i < length; ++i)
		{
			m_data[i] = val;
		}
	}

	~MyVector()
	{
		delete[] m_data;
	}

	class MyIterator {
	private:
		T* current;

	public:
		MyIterator(T* first) : current(first) {}

		T& operator+ (int n) { return *(current + n); }
		T& operator- (int n) { return *(current - n); }

		T& operator++ () { return *++current; }
		T& operator-- () { return *--current; }
		T& operator++ (int) { return *current++; }
		T& operator-- (int) { return *current--; }
		T& operator== (const MyIterator& it) { return current == it.current; }
		T& operator!= (const MyIterator& it) { return current != it.current; }

		T& operator* () { return *current; }
	};

	MyIterator begin()
	{
		return m_data;
	};

	MyIterator end()
	{
		return m_data + m_length;
	};

	T& front()
	{
		return m_data[0];
	}

	T& back()
	{
		return m_data[m_length - 1];
	}

	void reserve(size_t capacity)
	{
		if (m_data == nullptr)
		{
			m_length = 0;
			m_capacity = 0;
		}

		T* new_data = new T[capacity];
		size_t new_length = capacity < m_length ? capacity : m_length;

		for (size_t i = 0; i < new_length; i++)
			new_data[i] = m_data[i];

		m_capacity = capacity;
		delete[] m_data;
		m_data = new_data;
	}

	void push_back(const T& value)
	{
		resize_capacity();
		m_data[m_length++] = value;
	}

	void resize_capacity()
	{
		if (m_length >= m_capacity)
			reserve(m_capacity + m_capacity / 2);
	}

	void pop_back()
	{
		--m_length;
	}

	void clear()
	{
		delete[] m_data;
		m_data = nullptr;
		m_length = 0;
		m_capacity = 0;
	}

	void shrink_to_fit()
	{
		reserve(m_length);
	}

	bool empty()
	{
		return m_data == nullptr;
	}

	size_t size() const
	{
		return m_length;
	}

	size_t capacity() const
	{
		return m_capacity;
	}

	T& operator[](const size_t index)
	{
		return m_data[index];
	}
};

int main()
{
	MyVector<int> mv(10);
	mv.push_back(5);
	std::cout << "Size: " << mv.size() << std::endl;
	std::cout << "Capacity: " << mv.capacity() << std::endl;
	mv.shrink_to_fit();
	std::cout << "Size: " << mv.size() << std::endl;
	std::cout << "Capacity: " << mv.capacity() << std::endl;
	for (size_t i = 0; i < mv.size(); i++)
	{
		std::cout << "mv[" << i << "]: " << mv[i] << std::endl;
	}
	auto it = MyVector<int>::MyIterator(mv.begin());
	*it = 10;
	std::cout << mv.back() << std::endl;
	for (size_t i = 0; i < mv.size(); i++)
	{
		std::cout << "mv[" << i << "]: " << mv[i] << std::endl;
	}
	mv.push_back(8);
	std::cout << "Size: " << mv.size() << std::endl;
	for (size_t i = 0; i < mv.size(); i++)
	{
		std::cout << "mv[" << i << "]: " << mv[i] << std::endl;
	}
	std::cout << "Size: " << mv.size() << std::endl;
	std::cout << "Capacity: " << mv.capacity() << std::endl;
	mv[mv.size()] = 7;
	for (size_t i = 0; i <= mv.size(); i++)
	{
		std::cout << "mv[" << i << "]: " << mv[i] << std::endl;
	}
	std::cout << "Size: " << mv.size() << std::endl;
	std::cout << "Capacity: " << mv.capacity() << std::endl;
	mv.pop_back();
	std::cout << "Size: " << mv.size() << std::endl;
	std::cout << "Capacity: " << mv.capacity() << std::endl;
	std::cout << "Back: " << mv.back() << std::endl;
	for (size_t i = 0; i < mv.size(); i++)
	{
		mv.pop_back();
	}
	std::cout << mv.empty();
	std::cout << "Size: " << mv.size() << std::endl;
	std::cout << "Capacity: " << mv.capacity() << std::endl;
	/*std::vector<int> vect(10);
	vect.push_back(5);
	for (int i = 0; i < vect.size(); i++)
	{
		std::cout << "Size[" << i << "]" << vect[i] << std::endl;
	}
	std::cout << "Size: " << vect.size() << std::endl;
	std::cout << "Capacity: " << vect.capacity() << std::endl;
	vect.shrink_to_fit();
	for (int i = 0; i < vect.size(); i++)
	{
		std::cout << "Size[" << i << "]" << vect[i] << std::endl;
	}
	std::cout << "Size: " << vect.size() << std::endl;
	std::cout << "Capacity: " << vect.capacity() << std::endl;*/
	/*std::cout <<"Size: "<< vect.size() << std::endl;
	std::cout << "Capacity: " << vect.capacity() << std::endl;
	vect.push_back(3);
	std::cout << "Size: " << vect.size() << std::endl;
	std::cout << "Capacity: " << vect.capacity() << std::endl;
	for (int i = 0; i <= 100; i++)
	{
		std::cout << "Size[" << i <<"]"<< vect[i] << std::endl;
	}
	std::cout << "Test: "<<vect.back()<< std::endl;*/
	system("pause");
}