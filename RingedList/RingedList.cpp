// RingedList.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "RingedList.h"

using namespace std;

int main()
{
	//RingedList<int> list;
	//list.push(2);

	RingedList<char> list;
	std::cout << (list.isEmpty() ? "true" : "false") << std::endl;
	std::cout << "size is " << list.getSize() << std::endl;
	std::cout << "____________________________________PUSH_&_POP____________________________________" << std::endl;
	list.push('r');
	list.push('i');
	list.push('n');
	list.push('g');
	list.push('l');
	list.push('i');
	list.push('s');
	list.push('t');

	std::cout << (list.isEmpty() ? "true" : "false") << std::endl;
	std::cout << "size is " << list.getSize() << std::endl;

	std::cout << std::endl << std::endl;
	RingedList<char> list2(list);
	std::cout << (list2.isEmpty() ? "true" : "false") << std::endl;
	std::cout << "size is " << list2.getSize() << std::endl << std::endl;

	std::cout << list.pop() << std::endl;
	std::cout << list.pop() << std::endl;
	std::cout << list.pop() << std::endl;
	RingedList<char> list3(std::move(list));
	std::cout << "list :  " << (list.isEmpty() ? "true" : "false") << std::endl;
	std::cout << "list3 :  " << (list3.isEmpty() ? "true" : "false") << std::endl;
	std::cout << "size of list is " << list.getSize() << std::endl;
	std::cout << "size of list3 is " << list3.getSize() << std::endl;

	std::cout << std::endl << "____________________________CLEAR____________________________" << std::endl;
	list.clear();
	std::cout << (list.isEmpty() ? "true" : "false") << std::endl;
	std::cout << "size is " << list.getSize() << std::endl;
	
	std::cout << "_____________________________________________________" << std::endl;

	RingedList<int> list11;
	list11.push(1);
	list11.push(2);
	list11.push(3);
	list11.push(4);
	RingedList<int> list12 = list11;
	RingedList<int>::Iterator* it1 = list11.iterator();
	RingedList<int>::Iterator* it2 = list12.iterator();
	while (!it1->finished() || !it2->finished()) {
		std::cout << "it1 : " << it1->getValue() << "\t" << "it2 : " << it2->getValue() << std::endl;
		it1->next();
		it2->next();
	}
	it1->previous();
	list11.push(5);
	list11.push(6);

	RingedList<int> list13 = std::move(list11);
	std::cout << "list 11 size : " << list11.getSize() << std::endl;
	RingedList<int>::Iterator *it3 = list13.iterator();
	while (!it3->finished()) {
		std::cout << "it3 : " << it3->getValue() << std::endl;
		it3->next();
	}

	cout << endl << "_________________________Remove and insert__________________________" << endl;

	RingedList<int> list21;
	list21.push(1);
	list21.push(2);
	list21.push(3);
	list21.push(4);

	RingedList<int>::Iterator* iter21 = list21.iterator();
	while (!iter21->finished()) {
		cout << "iter21 : " << iter21->getValue() << endl;
		iter21->next();
	}
	cout << "remove: " << endl;
	iter21->previous();
	list21.remove(iter21);
	iter21->start();
	while (!iter21->finished()) {
		cout << "after remove iter21 : " << iter21->getValue() << endl;
		iter21->next();
	}

	cout << "insert " << endl;

	//iter21->previous(); iter21->previous();
	list21.insert(iter21, 999);
	iter21->start();
	while (!iter21->finished()) {
		cout << "after remove iter21 : " << iter21->getValue() << endl;
		iter21->next();
	}

	cout << endl << " _____________________________CLEAR_____________________________ " << endl;
	list21.clear();
	list21.insert(iter21, 836);
	iter21->start();
	while (!iter21->finished()) {
		cout << "after remove iter21 : " << iter21->getValue() << endl;
		iter21->next();
	}

	/*
	TEST_METHOD(RLCopyAndMoveOperators)
	{
	int i = 1;
	RingList<int> ringList1;
	ringList1.push(1);
	ringList1.push(2);
	ringList1.push(3);
	ringList1.push(4);

	RingList<int> ringList2 = ringList1;
	Assert::AreEqual(ringList1.getSize(), ringList2.getSize());
	RingList<int>::Iterator* it1 = ringList1.getBeginIterator();
	RingList<int>::Iterator *it2 = ringList2.getBeginIterator();
	while (!it1->finished()) {
	Assert::AreEqual(it1->getValue(), it2->getValue());
	it1->next();
	it2->next();
	}
	it1->previous();
	ringList1.push(5);
	ringList1.push(6);

	RingList<int> ringList3 = std::move(ringList1);
	Assert::IsTrue(ringList1.isEmpty());
	RingList<int>::Iterator *it3 = ringList3.getBeginIterator();
	while (!it3->finished()) {
	Assert::AreEqual(it3->getValue(), i++);
	it3->next();
	}
	}

	TEST_METHOD(RLPushPop)
	{
	RingList<char> ringList;
	ringList.push('r');
	ringList.push('i');
	ringList.push('n');
	ringList.push('g');
	ringList.push('l');
	ringList.push('i');
	ringList.push('s');
	ringList.push('t');
	ringList.push('!');
	Assert::AreEqual(ringList.pop(), '!');
	Assert::AreEqual(ringList.pop(), 't');
	ringList.push('t');

	RingList<char>::Iterator* it = ringList.getBeginIterator();
	Assert::AreEqual(ringList.pop(), 'r');
	Assert::AreEqual(ringList.pop(), 'i');

	RingList<char>::Iterator* ti = ringList.findFirstOf('s');
	Assert::AreEqual(ringList.pop(), 's');
	Assert::AreEqual(ringList.pop(), 'i');

	RingList<int> numbers;
	numbers.push(1);
	numbers.push(2);
	numbers.push(3);
	numbers.push(4);
	numbers.push(5);
	RingList<int>::Iterator* iter = numbers.findFirstOf(3);
	numbers.push(23);
	Assert::AreEqual(iter->getValue(), 23);

	delete it, ti, iter;
	}

	TEST_METHOD(RLIterator)
	{
	int counter = 1;
	RingList<int> ringList;
	ringList.push(1);
	ringList.push(2);
	ringList.push(3);
	ringList.push(4);
	ringList.push(5);
	ringList.push(6);
	ringList.push(7);

	RingList<int>::Iterator* it = ringList.getBeginIterator();
	while (!it->finished()) {
	Assert::AreEqual(it->getValue(), counter++);
	it->next();
	}

	counter = 1;
	it->start();
	while (it->getValue() != 5) {
	Assert::AreEqual(it->getValue(), counter++);
	it->next();
	}

	ringList.push(9999);
	counter = 1;
	it->start();
	while (it->getValue() != 9999) {
	Assert::AreEqual(it->getValue(), counter++);
	it->next();
	}
	Assert::AreEqual(it->getValue(), 9999);
	it->next();
	while (!it->finished()) {
	Assert::AreEqual(it->getValue(), counter++);
	it->next();
	}
	delete it;
	}

	TEST_METHOD(RLIteratorReverse)
	{
	int counter = 7;
	RingList<int> ringList;
	ringList.push(1);
	ringList.push(2);
	ringList.push(3);
	ringList.push(4);
	ringList.push(5);
	ringList.push(6);
	ringList.push(7);

	RingList<int>::Iterator* it = ringList.getBeginIterator();
	it->stop();
	while (!it->finished()) {
	Assert::AreEqual(it->getValue(), counter--);
	it->previous();
	}
	delete it;
	}

	TEST_METHOD(RLPuspPopOnIterator)
	{
	//PushTest
	int counter = 1;
	RingList<int> ringList;
	ringList.push(1);
	ringList.push(2);
	ringList.push(3);
	ringList.push(4);
	ringList.push(5);
	ringList.push(6);
	ringList.push(7);

	RingList<int>::Iterator* it = ringList.findFirstOf(5);
	ringList.push(9999);

	it->start();
	while (it->getValue() != 9999) {
	Assert::AreEqual(it->getValue(), counter++);
	it->next();
	}
	Assert::AreEqual(it->getValue(), 9999);
	it->next();
	while (!it->finished()) {
	Assert::AreEqual(it->getValue(), counter++);
	it->next();
	}

	//PopTest
	counter = 8;
	ringList.clear();
	ringList.push(3);
	ringList.push(4);
	ringList.push(5);
	ringList.push(6);
	ringList.push(7);
	ringList.push(8);
	it = ringList.findFirstOf(4);
	ringList.pop();

	it->stop();
	while (it->getValue() != 3) {
	Assert::AreEqual(it->getValue(), counter--);
	it->previous();
	}
	Assert::AreEqual(it->getValue(), 3);

	delete it;
	}

	TEST_METHOD(RLAnotherIteration)
	{
	int counter = 1;
	RingList<int> ringList;
	ringList.push(1);
	ringList.push(2);
	ringList.push(3);
	ringList.push(4);
	ringList.push(5);
	ringList.push(6);
	ringList.push(7);

	RingList<int>::Iterator* it = ringList.getBeginIterator();
	while (!it->finished()) {
	Assert::AreEqual(it->passOfValue(), counter++);
	}

	counter = 7;
	it->stop();
	while (!it->finished()) {
	Assert::AreEqual(it->passOfValue(), counter--);
	}
	}

	TEST_METHOD(RLExceptions)
	{
	RingList<int> ringList;
	Assert::ExpectException<ListIsEmptyException>([&]
	{
	ringList.pop();
	});

	Assert::ExpectException<ValueNotFoundException>([&]
	{
	ringList.findFirstOf(3);
	});

	ringList.push(1);
	ringList.push(2);
	ringList.push(3);
	ringList.push(4);
	Assert::ExpectException<ValueNotFoundException>([&]
	{
	ringList.findFirstOf(17);
	});
	}*/
	system("pause");
	return 0;
}

