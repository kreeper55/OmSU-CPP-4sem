#pragma once

#include "stdafx.h"
#include "AbstractIterator.h"

struct RingedListIsEmptyException {
	std::string message;
	RingedListIsEmptyException(const char* cMessage) {
		message = cMessage;
	}
};

struct ValueNotFoundException {
	std::string message;
	ValueNotFoundException(const char* cMessage) {
		message = cMessage;
	}
};

template <typename Type>
class AbstractRingedList {
public:
	virtual ~AbstractRingedList() = default;
	virtual void insert(AbstractIterator<Type> *iter, Type value) = 0;
	virtual void remove(AbstractIterator<Type> *iter) = 0;
	virtual void push(const Type&) = 0;
	virtual Type pop() = 0;
	virtual void clear() = 0;
	virtual bool isEmpty() = 0;
	virtual size_t getSize() = 0;
	virtual AbstractIterator<Type>* iterator() = 0;
	virtual AbstractIterator<Type>* findFirst(Type) = 0;
};
