#pragma once

template <typename Type>
struct Node {
	Type value;
	Node* next;
	Node* prev;
};

template <typename Type>
class AbstractIterator {
public:
	virtual void start() = 0;
	virtual void next() = 0;
	virtual Type getValue() = 0;
	virtual bool finished() = 0;
	virtual void previous() = 0;
	virtual Node<Type>* getNode() = 0;
};