// SCOPIROVAL.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "BinaryTree.h"

using namespace std;



int main()
{
	BinaryTree bts(4);
	/*bts.add({ 0 }, 1);
	bts.add({ 1 }, 10);
	bts.add({ 0,0 }, 0);
	bts.add({ 0,1 }, 3);
	bts.add({ 0,1,0 }, 2);
	bts.add({ 1,0 }, 5);
	bts.add({ 1,0,1 }, 6);
	bts.add({ 1,1}, 11*/

	bts.print();
	cout << endl;
	bts.deleteAllLeaves();
	bts.print();
	cout << endl;
	std::vector<int> v;
	bts.add(v, 1);
	bts.print();
	bts.add(v, 2);
	bts.print();

	//cout << (bts.isBTS() ? "true" : "false") << endl;

	/*BinaryTree tree1(2);
	tree1.add({ 0 }, 226);
	BinaryTree tree3(tree1);

	BinaryTree tree2(25);
	cout << endl << (tree1 == tree3 ? "yes, they equals" : "no, they not equals") << endl; // yes
	cout << endl << (tree2 == tree3 ? "yes, they equals" : "no, they not equals") << endl; // no

	BinaryTree tree4 = tree2;
	cout << endl << (tree4 == tree2 ? "yes, they equals" : "no, they not equals") << endl; // yes

	BinaryTree tree6(24);
	tree6.add({ 0 }, 9);
	tree6.add({ 1 }, 5);
	tree6.add({ 1,0 }, 10);
	tree6.add({ 1,0,1 }, 101);
	BinaryTree tree8 = tree6;
	BinaryTree tree7(std::move(tree6));
	cout << endl << (tree7 == tree8 ? "yes, they equals" : "no, they not equals") << endl; // yes*/
	/*BinaryTree tree(5);
	tree.add({ 1 }, 7);
	tree.add({ 0 }, 2);
	tree.add({ 0, 1 }, 3);
	tree.add({ 1, 0 }, 6);
	tree.add({ 1, 1 }, 8);
	tree.add({ 0, 0 }, 1);
	tree.add({ 1, 1, 1 }, 9);
	tree.add({ 0, 1, 1 }, 4);
	BinaryTree tree2(tree);
	cout << tree2 << endl;
	try {
		tree.add({ 1,1,1,1,1,0 }, 666);
	}
	catch (InvalidWayTreeException& e) {
		cout << e.message << endl;
	}
	cout << tree << endl;*/

	/*tree.clear();
	tree.add({ 1 }, 7);
	tree.add({ 0 }, 2);
	tree.add({ 0, 1 }, 3);
	tree.add({ 1, 0 }, 6);
	cout << tree << endl;*/
	/*BinaryTree tree(0);
	try {
		vector<int> v3 = tree.find(1);
	}
	catch (InvalidWayTreeException& e) {
		cout << e.message << endl;
	}
	tree.add({ 0 }, 1);
	tree.add({ 1 }, 2);
	tree.add({ 0,0 }, 3);
	tree.add({ 0,1 }, 4);

	cout << endl << "tree( << )  : " << tree << endl;
	vector<int> v = tree.find(1);
	vector<int> v1 = tree.find(4);
	for each (int i in v) {
		cout << i << " ";
	}
	cout << endl;
	for each (int i in v1) {
		cout << i << " ";
	}
	cout << endl;
	//cout << "find 1 : " << tree.find(1)[0] << endl;
	//cout << "find 4 : " << tree.find(4)[0] << tree.find(4)[1] << endl;
	tree.add({ 1,0 }, 5);
	tree.add({ 1,1 }, 6);
	tree.add({ 0,0,0 }, 7);
	tree.add({ 0,0,1 }, 8);
	tree.add({ 0,1,0 }, 9);
	tree.add({ 0,1,1 }, 10);
	tree.add({ 1,0,0 }, 11);
	tree.add({ 1,0,1 }, 12);
	tree.add({ 1,1,0 }, 13);
	tree.add({ 1,1,1 }, 14);

	cout << endl << "tree( << )  : " << tree << endl;

	vector<int> v4 = tree.find(10);
	vector<int> v5 = tree.find(11);
	vector<int> v6 = tree.find(12);
	vector<int> v7 = tree.find(13);
	vector<int> v8 = tree.find(14);
	//vector<int> v9 = tree.find(115);
	for each (int i in v4) {
		cout << i << " ";
	}
	cout << endl;
	for each (int i in v5) {
		cout << i << " ";
	}
	cout << endl;
	for each (int i in v6) {
		cout << i << " ";
	}
	cout << endl;
	for each (int i in v7) {
		cout << i << " ";
	}
	cout << endl;
	for each (int i in v8) {
		cout << i << " ";
	}
	cout << endl;
	/*for each (int i in v9) {
		cout << i << " ";
	}*/
	cout << endl;
	/*cout << "find 10 : " << tree.find(10)[0] << tree.find(10)[1] << tree.find(10)[2] << endl;
	cout << tree << endl;

	cout << "find 5  : " << tree.find(5)[0] << tree.find(5)[1] << endl;

	cout << "find 13 : " << tree.find(13)[0] << tree.find(13)[1] << tree.find(13)[2] << endl;*/

	/*try {
		tree.find(144);
	}
	catch (InvalidWayTreeException& e) {
		cout << e.message << endl;
	}

	BinaryTree tree1(4);
	cout << "(4)get average: " << tree1.getAverage() << endl;
	cout << "(1)even : " << tree1.getEvenElem() << endl;
	//tree1.add("", 1);
	tree1.add({ 0 }, 3);
	tree1.add({ 1 }, 20);
	cout << tree1.find(20)[0] << endl;
	cout << "tree1  " << tree1 << endl;
	BinaryTree tree2(tree1);
	cout << "tree2  " << tree2 << endl;
	cout << "(9)get average: " <<  tree2.getAverage() << endl;
	cout << endl << "(2)even : " << tree2.getEvenElem() << endl;


	cout << endl << "even : " << tree2.getEvenElem() << endl;

	cout << tree2.isPositive() << endl;

	tree2.add({0,1}, 7);
	tree2.add({ 1,0 }, 44);

	cout << tree2.isPositive() << endl;

	tree2.add({1,0}, -1);
	
	cout << tree2.isPositive() << endl;*/
    return 0;
}

