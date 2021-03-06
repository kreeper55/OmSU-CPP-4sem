// HashTable.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "HashTable.h"

using namespace std;

int main()
{
	LinkedHashTable<int, char> table(5);

	cout << "TEST PUT AND GET" << endl;

	table.put(1, 'a');
	table.put(2, 'b');
	table.put(3, 'u');
	table.put(4, 'v');

	cout << table.getValue(1) << endl;
	cout << table.getValue(2) << endl;
	cout << table.getValue(3) << endl;
	cout << table.getValue(4) << endl;


	cout << endl << "TEST CLEAR" << endl << endl;

	table.clear();
	cout << (table.isEmpty() ? "true, table is empty!!!" : "false, empty has elements") << endl;
	try {
		cout << table.getValue(1);
	}
	catch (HashTableIsEmptyException& e) {
		cout << e.message << endl;
	}

	try {
		table.remove(1);
	}
	catch (HashTableIsEmptyException& e) {
		cout << e.message << endl;
	}

	table.put(1, 'a');
	table.put(2, 'b');
	table.put(3, 'u');
	table.put(4, 'v');

	cout << "TEST REMOVE" << endl;

	table.remove(1);
	table.remove(4);

	cout << table.getValue(2) << endl;
	cout << table.getValue(3) << endl;

	try {
		cout << table.getValue(1) << endl;
	}
	catch (ValueIsntFoundException& e) {
		cout << e.message << endl;
	}
	try {
		cout << table.getValue(4) << endl;
	}
	catch (ValueIsntFoundException& error) {
		cout << error.message << endl;
	}

	cout << "TEST ITERATOR" << endl;

	table.put(0, 'f');
	table.put(3, 'z');
	table.put(-12, 'd');
	table.put(100, 'x');
	table.put(100, 'X');

	LinkedHashTable<int, char>::LinkedIterator* iterator = table.iterator();

	while (!iterator->isEmpty()) {
		cout << iterator->getValue() << endl;
		iterator->next();
	}

	cout << endl << "TEST SEARCH" << endl << endl;

	char found = 'd';
	try {
		cout << "find value = " << found << " key = " << table.search(found) << endl;
	}
	catch (ValueIsntFoundException& error) {
		cout << error.message << endl;
	}

	system("pause");
    return 0;
}

