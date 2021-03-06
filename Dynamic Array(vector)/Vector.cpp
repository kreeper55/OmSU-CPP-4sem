// Dynamic Array(vector).cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "Vector.h"
using namespace std;

int main()
{
	Vector<int> vector1(5);
	vector1.reserve(1);
	try
	{
		cout << vector1[34];
	}
	catch (IndexOutOfRange& e)
	{
		cout << e.message << endl;
	}

	Vector<int> vector2(7, 5, 16);
	
	cout << "vector 1 :" << endl;
	cin >> vector1;
	cout << "vector 1 :" << endl;
	cout << vector1;
	
	Vector<int> vector(0);
	vector.output();
    vector = vector1 + vector1;
	vector.output();
	cout << endl << "vector 2 :" << endl;
	vector2.output();
	cout << endl;

	try
	{
		if (vector1 == vector2)
		{
			cout << endl << "poxodu ==" << endl;
		}
		if (vector1 != vector2)
		{
			cout << endl << "ne ravni poxodu" << endl;
		}
	}
	catch (SizeDifference &e)
	{
		cout << e.message << endl;
	}

	Vector<int> vector4(1);
	vector4 = vector2 + vector1;
	vector4.output();

	
	cout << endl << "popback : " << vector1.popback() << endl << "pushback : ";
	vector1.output();
	cout << endl;

	vector1.pushback(666);
	vector1.output();
	cout << endl;

	vector1.pushback(7);
	vector1.output();
	cout << endl;

	vector1.pushback(3);
	vector1.output();
	cout << endl;


	cout << "vector 1 :" << endl;
	vector1.output();
	cout << endl << "vector 2 :" << endl;
	vector2.output();
	cout << endl;
	


	vector1 = std::move(vector2);

	cout << endl << "vector 1 :" << endl;
	vector1.output();
	cout << endl << "vector 2 :" << endl;
	vector2.output();
	cout << endl;

	cout << endl << "after methods resize for vector2 :" << endl;
	vector2.resize(10);
	cout << "vector 1 :" << endl;
	vector1.output();
	cout << endl << "vector 2 :" << endl;
	vector2.output();
	cout << endl;

	cout << endl << "-----------------------------------------------------------------------------------------" << endl;
	cout << endl << "after methods reserve4 for vector2 :" << endl;
	vector2.reserve(4);
	vector2.output();

	cout << endl << "after costructor copy : " << endl;
	Vector<int> vector3 (std::move(vector2));
	cout << "vector 2 :" << endl;
	vector2.output();
	cout << endl << "vector 3 :" << endl;
	vector3.output();
	cout << endl;
	
	cout << endl << "after methods resize12 for vector3 :" << endl;
	vector3.resize(12);
	vector3.output();

	cout << endl << "after methods resize5 for vector3 :" << endl;
	vector3.resize(5);
	vector3.output();

	vector3.reserve(2);
	vector3.output();

    system("pause");
    return 0;
}

