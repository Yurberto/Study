#pragma once
#include "lib.h"

template <typename T>
class List
{
public:
	List();
	~List();

	
	void push_back(T data);
	void push_front(T data);
	void pop_back();
	void pop_front();

	void insert(T data, const int index);
	void remove_at(const int index);


	void clear();
	int getSize();

	T& operator[](const int index);
private:
	template <typename T>
	class Node
	{
	public:
		Node(T data = T(), Node<T>* pNext = nullptr, Node<T>* pPrev = nullptr)
		{
			this->data = data;
			this->pNext = pNext;
			this->pPrev = pPrev;
		}

		Node<T>* pNext;
		Node<T>* pPrev;

		T data;
	};

	Node<T>* head;
	Node<T>* tail;

	int size;

	void checkIndex(int index);
};

template<typename T>
inline void List<T>::push_back(T data)
{
	if (head == nullptr)
	{
		head = new Node<T>(data);
	}
	else if(head->pNext == nullptr)
	{
		tail = new Node<T>(data, nullptr, head);
		head->pNext = tail;
	}
	else
	{
		Node<T>* temp = tail;
		temp->pNext = tail = new Node<T>(data, nullptr, tail);
	}
	size++;
}

template <typename T>
inline void List<T>::pop_back()
{
	Node<T>* temp = tail;
	tail = tail->pPrev;
	delete temp;
	size--;
}

template <typename T>
inline void List<T>::push_front(T data)
{
	Node<T>* temp = head;
	temp->pPrev = head = new Node<T>(data, head);
	size++;
}

template <typename T>
inline void List<T>::pop_front()
{
	Node<T>* temp = head;
	head = head->pNext;
	delete temp;
	size--;
}



template <typename T>
inline void List<T>::insert(T data, const int index)
{
	if (index < 0 || index > size) { throw; }

	
	if (index == 0) { push_front(data); }

	else if (index == size) { push_back(data); }

	
	else if (index <= size / 2)
	{
		Node<T>* current = head;
		for (int i = 0; i < index - 1; i++)
		{
			current = current->pNext;
		}
		Node<T>* next = current->pNext;
		next->pPrev = current->pNext = new Node<T>(data, next, current);
		size++;
	}
	
	else
	{
		Node<T>* current = tail;
		for (int i = size; i > index + 1; i--)
		{
			current = current->pPrev;
		}
		Node<T>* previos = current->pPrev;
		previos->pNext = current->pPrev = new Node<T>(data, current, previos);
		size++;
	}
	
	
}

template<typename T>
inline void List<T>::remove_at(const int index)
{
	checkIndex(index);
	if (index == 0) { pop_front(); }

	else if (index == size - 1) { pop_back(); }

	else if (index <= size / 2)
	{
		Node<T>* current = head;
		for (int i = 0; i < index - 1; i++)
		{
			current = current->pNext;
		}
		Node<T>* temp = current->pNext;
		current->pNext = temp->pNext;
		current->pNext->pPrev = current;
		delete temp;
		size--;
	}
	else
	{
		Node<T>* current = tail;
		for (int i = size; i > index + 2; i--)
		{
			current = current->pPrev;
		}
		Node<T>* temp = current->pPrev;
		current->pPrev = temp->pPrev;
		current->pPrev->pNext = current;
		delete temp;
		size--;
	}
	
}



template <typename T>
int List<T>::getSize()
{
	return size;
}

template <typename T> 
inline void List<T>::clear()
{
	for (; size != 0; )
	{
		pop_front();
	}
}

template<typename T>
inline T& List<T>::operator[](const int index)
{
	checkIndex(index);

	if (index <= size / 2)
	{
		Node<T>* current = head;

		for (int i = 0; i < index; i++)
		{
			current = current->pNext;
		}
		return current->data;
	}
	else
	{
		Node<T>* current = tail;
		for (int i = size; i > index + 1; i--)
		{
			current = current->pPrev;
		}
		return current->data;
	}
	
}


template <typename T>
List<T>::List()
{
	head = tail = nullptr;
	size = 0;
}

template <typename T>
List<T>::~List()
{
	clear();
}


template<typename T>
inline void List<T>::checkIndex(int index)
{
	if (index < 0 || index >= size)
	{
		throw;
	}
}