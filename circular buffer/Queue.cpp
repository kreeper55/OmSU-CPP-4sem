// circularbuffer.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "Queue.h"

using namespace std;

int main()
{
	double a;
	Queue<double> q(4);
	cout << q.getCapacity() << endl;

	try {
		cout << "try get element ..." << endl;
		a = q.getElement();
	}
	catch (QueueIsNullptr& e) {
		cout << "Ohh, " << e.message << endl;
	}

	try {
		cout << "try take element ..." << endl;
		a = q.takeElement();
	}
	catch (QueueIsNullptr& e) {
		cout << "Ohh, " << e.message << endl;
	}

	cout << "_____________" << endl;
	cout << "push, get Elem/size" << endl;

	q.pushback(1);
	cout << q.getSize() << "\t" << q.getElement() << endl;
	q.pushback(4);
	cout << q.getSize() << "\t" << q.getElement() << endl;
	q.pushback(6);
	cout << q.getSize() << "\t" << q.getElement() << endl;
	q.pushback(8);
	cout << q.getSize() << "\t" << q.getElement() << endl;

	try {
		cout << "try put element ..." << endl;
		q.pushback(9);
	}
	catch (QueueOverflow& e) {
		cout << "Ohhh, " << e.message << endl;
	}

	cout << "_____________" << endl;
	cout << "take Elem" << endl;

	cout << q.takeElement() << endl;
	cout << q.takeElement() << endl;
	cout << q.takeElement() << endl;
	cout << q.takeElement() << endl;

	try {
		cout << "try take element ..." << endl;
		a = q.takeElement();
	}
	catch (QueueIsNullptr& e) {
		cout << "Ohh, ne poluchilos'( : " << e.message << endl;
	}

	cout << "_____________" << endl;
	cout << "Clear, and take/get elem" << endl;

	q.clear();
	try {
		cout << "try take element after clear of queue ..." << endl;
		a = q.takeElement();
		a = q.getElement();
	}
	catch (QueueIsNullptr& e) {
		cout << "Ohh, ne poluchilos'( : " << e.message << endl;
	}

	cout << "_____________" << endl;
	cout << "Iterator" << endl;

	q.pushback(5);
	q.pushback(7);
	q.pushback(11);
	q.pushback(23);

	auto qiter = q.iterator();
	qiter.start();
	while (!qiter.finish()) {
		cout << qiter.getValue() << endl;
		qiter.next();
	}

	system("pause");
    return 0;
}

