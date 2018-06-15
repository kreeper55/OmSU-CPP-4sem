#pragma once
#include "stdafx.h"
#include "Iterator.h"

struct HashTableIsEmptyException {
	std::string message;
	HashTableIsEmptyException(const char* cMessage) {
		message = cMessage;
	}
};

struct ValueIsntFoundException {
	std::string message;
	ValueIsntFoundException(const char* cMessage) {
		message = cMessage;
	}
};


template <typename TKey, typename TValue>
class LinkedHashTable {
public:
	class LinkedIterator : public Iterator<TKey, TValue>
	{
	public:
		LinkedIterator(Data<TKey, TValue> *first) {
			this->begin = first;
			this->start();
		}

		~LinkedIterator() {
			delete this->begin;
			delete this->current;
		}

		void start() override   {
			this->current = this->begin;
		}

		void next() override  {
			this->current = this->current->next;
		}

		TValue getValue() override  {
			return this->current->value;
		}

		bool isEmpty() override  {
			return this->current == nullptr;
		}

		Data<TKey, TValue>* getTable() override {
			return this->current;
		}
	};


	LinkedHashTable();
	LinkedHashTable(int size);

	TValue getValue(TKey key);
	void put(TKey key, TValue value);
	void remove(TKey key);

	void clear();

	inline bool isEmpty()		{ return list_size == 0; }
	inline int size() const		{ return table_size; }

	TKey search(TValue value);

	LinkedIterator* iterator() {
		LinkedIterator* iterator = new LinkedIterator(list_begin);
		iterator->start();
		return iterator;
	}

	~LinkedHashTable();
private:
	inline int hash(TKey key) const { return key % table_size; }
	static const int DEFAULT_SIZE = 8;
	Data<TKey, TValue>* list_begin;
	Data<TKey, TValue>* list_end;
	size_t list_size;

	Data<TKey, TValue>** table;
	size_t table_size;
};



template <typename TKey, typename TValue>
LinkedHashTable<TKey, TValue>::LinkedHashTable() {	
	list_size = 0;
	this->table_size = DEFAULT_SIZE;
	list_begin = new Data<TKey, TValue>;
	list_end = list_begin;
	this->table = new Data<TKey, TValue>*[table_size];
	for (size_t i = 0; i < table_size; i++) {
		table[i] = nullptr;
	}
}

template <typename TKey, typename TValue>
LinkedHashTable<TKey, TValue>::LinkedHashTable(int size) {
	list_size = 0;
	this->table_size = size;
	list_begin = new Data<TKey, TValue>;
	list_end = list_begin;
	this->table = new Data<TKey, TValue>*[size];
	for (size_t i = 0; i < table_size; i++) {
		table[i] = nullptr;
	}
}

template <typename TKey, typename TValue>
TValue LinkedHashTable<TKey, TValue>::getValue(TKey key) {
	if (list_size == 0)
		throw HashTableIsEmptyException("Hash Table Is Empty");

	TValue result;

	int temp_hash = hash(key);

	if (table[temp_hash]->next != nullptr) {
		Data<TKey, TValue> *current = table[temp_hash];
		while (current->key != key)
			current = current->next;
		result = current->value;
	}
	else {
		if (table[temp_hash]->key == key)
			result = table[temp_hash]->value;
		else
			throw ValueIsntFoundException("Value Isn't Found");
	}
	return result;
}

template <typename TKey, typename TValue>
void LinkedHashTable<TKey, TValue>::put(TKey key, TValue value) {

	int temp_hash = hash(key);
	if (table[temp_hash] == nullptr) {
		table[temp_hash] = new Data<TKey, TValue>;
		table[temp_hash]->key = key;
		table[temp_hash]->value = value;
		table[temp_hash]->next = nullptr;
	}
	else {
		Data<TKey, TValue> *last = table[temp_hash];
		while (last->next != nullptr)
			last = last->next;

		Data<TKey, TValue> *new_data = new Data<TKey, TValue>;
		new_data->key = key;
		new_data->value = value;
		new_data->next = nullptr;
		table[temp_hash]->next = new_data;
	}

	if (list_size != 0) {
		Data<TKey, TValue> *current = new Data<TKey, TValue>;
		current->key = key;
		current->value = value;
		current->next = nullptr;
		list_end->next = current;
		list_end = current;
	}
	else {
		Data<TKey, TValue> *current = new Data<TKey, TValue>;
		current->key = key;
		current->value = value;
		current->next = nullptr;
		list_begin = current;
		list_end = list_begin;
	}
	list_size++;
}

template <typename TKey, typename TValue>
void LinkedHashTable<TKey, TValue>::remove(TKey key) {
	if (list_size == 0)	throw HashTableIsEmptyException("Hash Table Is Empty");

	if (list_begin->key == key) {
		Data<TKey, TValue> *buffer = list_begin;
		list_begin = buffer->next;
		delete buffer;
	}
	else {
		Data<TKey, TValue> *current = list_begin;
		while ((current->next != nullptr) && (current->next->key != key))
			current = current->next;

		if (current->next == nullptr)	throw ValueIsntFoundException("Value Isn't Found");

		if (current->next->next == nullptr) {
			delete current->next;
			current->next = nullptr;
			list_end = current;
		}
		else {
			Data<TKey, TValue> *buffer = current->next->next;
			delete current->next;
			current->next = buffer;
		}
	}

	int temp_hash = hash(key);

	if (table[temp_hash]->next == nullptr) {
		table[temp_hash]->value = 0;
		table[temp_hash]->key = 0;
		table[temp_hash]->next = nullptr;
	}
	else {

		if (table[temp_hash]->key == key) {
			Data<TKey, TValue> *buffer = table[temp_hash];
			table[temp_hash] = buffer->next;
			delete buffer;
		}
		else {
			Data<TKey, TValue> *current_data = table[temp_hash];
			while ((current_data->next != nullptr) && (current_data->next->key != key))
				current_data = current_data->next;

			if (current_data->next == nullptr)	throw ValueIsntFoundException("Value Isn't Found");

			if (current_data->next->next == nullptr) {
				delete current_data->next;
				current_data->next = nullptr;
			}
			else {
				Data<TKey, TValue> *buffer = current_data->next->next;
				delete current_data->next;
				current_data->next = buffer;
			}
		}
	}
}

template <typename TKey, typename TValue>
void LinkedHashTable<TKey, TValue>::clear() {
	for (size_t i = 0; i < table_size; i++) {
		Data<TKey, TValue> *current = table[i];
		Data<TKey, TValue> *temp = current;
		while (current != nullptr) {
			temp = current;
			current = current->next;
			delete temp;
		}
		delete current;
		this->table[i] = nullptr;
	}

	Data<TKey, TValue> *current = list_begin;
	Data<TKey, TValue> *temp = current;
	while (current != list_end) {
		temp = current;
		current = current->next;
		delete temp;
	}
	delete current;

	list_size = 0;
}

template <typename TKey, typename TValue>
TKey LinkedHashTable<TKey, TValue>::search(TValue value) {
	Data<TKey, TValue> *current = list_begin;
	while (current != nullptr) {
		if (current->value == value) {
			return current->key;
		}
		current = current->next;
	}

	throw ValueIsntFoundException("Value Isn't Found");
}


template <typename TKey, typename TValue>
LinkedHashTable<TKey, TValue>::~LinkedHashTable() {
	this->clear();
	table_size = 0;
}
