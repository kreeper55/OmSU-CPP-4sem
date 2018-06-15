#pragma once

template <typename TKey, typename TValue>
struct Data {
	TKey key;
	TValue value;
	Data* next;
};

template <typename TKey, typename TValue>
class Iterator
{
public:
	virtual void start() = 0;
	virtual void next() = 0;
	virtual bool isEmpty() = 0;
	virtual TValue getValue() = 0;
	virtual Data<TKey, TValue>* getTable() = 0;
protected:
	Data<TKey, TValue>* begin;
	Data<TKey, TValue>* current;
};