#pragma once
#include "stdafx.h"
#include "AbstractRingedList.h"

template <typename Type>
class RingedList : public AbstractRingedList<Type> {
public:
	class Iterator : public AbstractIterator<Type> {
	public:
		Iterator(RingedList<Type> &rl) {
			ptrRingList = &rl;
		}
		Iterator& operator=(RingedList<Type> &obj) {
			ptrRingList = obj;
			return *this;
		}
		~Iterator() {
			ptrRingList = nullptr;
		}
		void start()override {
			ptrRingList->current = ptrRingList->root->next;
		}
		void next() override {
			ptrRingList->current = ptrRingList->current->next;
		}
		Type getValue() override {
			return ptrRingList->current->value;
		}
		bool finished() override {
			return ptrRingList->current == ptrRingList->root;
		}
		void previous() {
			ptrRingList->current = ptrRingList->current->prev;
		}
		Node<Type>* getNode() {
			return ptrRingList->current;
		}
	private:
		RingedList *ptrRingList;
	};

	RingedList();
	RingedList(const RingedList<Type> &other);
	RingedList& operator=(const RingedList<Type> &other);

	RingedList(RingedList<Type> &&stolen);
	RingedList& operator=(RingedList<Type> &&stolen);

	void insert(AbstractIterator<Type> *iter, const Type elem);
	void remove(AbstractIterator<Type> *iter);
	void push(const Type& elem);
	Type pop();
	void clear();
	inline bool isEmpty()	{ return size == 0; }
	inline size_t getSize() { return size; }

	Iterator* iterator() override {
		Iterator* iter = new Iterator(*this);
		iter->start();
		return iter;
	}

	Iterator* findFirst(Type elem) {
		Iterator* iter = new Iterator(*this);
		iter->start();
		while (!iter->finished()) {
			if (iter->getValue() == elem) {
				return iter;
			}
			iter->next();
		}
		throw ValueNotFoundException("Value not found.");
	}

	~RingedList();
private:
	Node<Type>* root;
	Node<Type>* current;
	size_t size;

	void initRingedList() {
		Node<Type>* temp = new Node<Type>;
		root = temp;
		temp->next = root;
		temp->prev = root;
		current = root;
		size = 0;
	}
};

template <typename Type>
RingedList<Type>::RingedList() {
	initRingedList();
}

template <typename Type>
RingedList<Type>::RingedList(const RingedList<Type> &other) {
	initRingedList();

	Node<Type>* ptr = other.root->next;
	for (size_t i = 0; i < other.size; i++) {
		push(ptr->value);
		ptr = ptr->next;
	}
}

template <typename Type>
RingedList<Type>& RingedList<Type>::operator=(const RingedList<Type> &other) {
	if (this == &other) {
		return *this;
	}
	clear();
	Node<Type>* ptr = other.root->next;
	for (size_t i = 0; i < other.size; i++) {
		push(ptr->value);
		ptr = ptr->next;
	}
	delete ptr;
	return *this;
}

template <typename Type>
RingedList<Type>::RingedList(RingedList<Type> &&stolen) {
	initRingedList();
	size = stolen.size;

	root = stolen.root;
	current = stolen.current;
	stolen.size = 0;
	stolen.root = nullptr;
	stolen.current = nullptr;
}

template <typename Type>
RingedList<Type>& RingedList<Type>::operator=(RingedList<Type> &&stolen) {
	if (this->root != stolen.root) {
		clear();
		size = stolen.size;
		root = stolen.root;
		current = stolen.current;

		stolen.size = 0;
		stolen.root = nullptr;
		stolen.current = nullptr;
	}
}

template<typename Type>
inline void RingedList<Type>::insert(AbstractIterator<Type>* iter, const Type elem)
{
	Node<Type> *node = new Node<Type>;
	node->value = elem;
	Node<Type> *current = iter->getNode();
	Node<Type> *next = current->next;
	current->next = node;
	node->prev = current;
	next->prev = node;
	node->next = next;
	size++;
}

template<typename Type>
inline void RingedList<Type>::remove(AbstractIterator<Type>* iter)
{
	if (isEmpty()) throw RingedListIsEmptyException("Ringed List is empty (");
	Node<Type> *current = iter->getNode();
	iter->next();
	Node<Type> *next = current->next;
	Node<Type> *prev = current->prev;
	next->prev = prev;
	prev->next = next;
	size--;
	delete current;
}

template <typename Type>
void RingedList<Type>::push(const Type& elem) {
	Node<Type>* unit = new Node<Type>;
	unit->next = current->next;
	unit->prev = current;
	unit->value = elem;

	Node<Type>* ptr = current->next;
	ptr->prev = unit;
	current->next = unit;
	current = current->next;

	size++;
}

template <typename Type>
Type RingedList<Type>::pop() {
	if (isEmpty()) { throw RingedListIsEmptyException("RingedList is empty."); }

	Type value = current->value;
	Node<Type>* ptr = current->prev;
	ptr->next = current->next;
	current->next->prev = ptr;

	delete current;
	if (size == 1) {
		current = root;
		size = 0;
		return value;
	}
	current = ptr;
	if (current == root) {
		current = current->next;
	}

	size--;
	return value;
}

template <typename Type>
void RingedList<Type>::clear() {
	if (root == nullptr && current == nullptr) {
		return;
	}
	current = root->prev;
	while (!isEmpty()) {
		pop();
	}
	current = root;
	size = 0;
}

template <typename Type>
RingedList<Type>::~RingedList() {
	clear();
	root = nullptr;
	current = nullptr;
}