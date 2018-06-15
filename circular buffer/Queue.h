#include "stdafx.h"
#pragma once

struct QueueIsNullptr
{
	std::string message;
	QueueIsNullptr(const char* c_text)
	{
		message = c_text;
	}
};

struct QueueOverflow
{
	std::string message;
	QueueOverflow(const char* c_text)
	{
		message = c_text;
	}
};

template <typename Type>
class Queue
{
private:
	Type* arr;
	size_t first, last;
	size_t size, capacity;
public:
	class Iterator {
	public:
		Iterator(Queue &queue) {
			this->queue = &queue;
			current = -1;
			count = 0;
		}
		~Iterator() {
			current = -1;
			count = 0;
			queue = nullptr;
		}
		inline void start() {
			current = queue->first;
		}
		inline void next() {
			current = (current + 1) % queue->capacity;
			count++;
		}
		inline bool finish() {
			return count == queue->size;
		}
		inline Type getValue() {
			return queue->arr[current];
		}

	private:
		Queue * queue;
		int current;
		int count;
	};

	explicit Queue(size_t size);
	Queue(const Queue&);

	Type getElement();
	Type takeElement();
	void pushback(const Type& element);

	inline void clear();
	inline bool isEmpty()				{ return size == 0; }
	inline size_t getSize() const		{ return size; }
	inline size_t getCapacity() const	{ return capacity; }

	Iterator iterator() { return Iterator(*this); }

	~Queue();
};

template <typename Type>
Queue<Type>::Queue(size_t capacity)
{
	this->capacity = capacity;
	size = 0;
	first = 0;
	last = -1;
	arr = new Type[capacity];
}

template <typename Type>
Queue<Type>::Queue(const Queue &q)
{
	capacity = q.capacity;
	size = q.size;
	first = q.first;
	last = q.last;
	arr = new Type[capacity];
	for (size_t i = 0; i < capacity; i++)
	{
		arr[i] = q.arr[i];
	}
}

template <typename Type>
inline Type Queue<Type>::getElement()
{
	if (isEmpty()) throw QueueIsNullptr("Queue is nullptr");
	return arr[first];
}

template <typename Type>
inline Type Queue<Type>::takeElement()
{
	if (isEmpty()) throw QueueIsNullptr("Queue is empty");
	size--;
	first++;
	if (first == capacity) {
		first = 0;
		return arr[capacity - 1];
	}
	else {
		return arr[first - 1];
	}
}

template <typename Type>
inline void Queue<Type>::pushback(const Type & element)
{
	if (size == capacity) throw QueueOverflow("Queue overflow");
	if (last == capacity - 1) last = -1;
	arr[++last] = element;
	size++;
}

template <typename Type>
inline void Queue<Type>::clear()
{
	first = size = 0;
	last = -1;
}

template <typename Type>
Queue<Type>::~Queue() { delete[] arr; }