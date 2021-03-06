// BinaryTreeSearch.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "BinaryTreeSearch.h"

using namespace std;

int main()
{
	/*
	BinaryTreeSearch tree1("Cpp");
	BinaryTreeSearch tree2("Java");
	BinaryTreeSearch tree3(tree1);

	Assert::AreEqual(tree1, tree2);
	Assert::AreNotEqual(tree2, tree3);

	BinaryTreeSearch tree4 = tree2;
	Assert::AreEqual(tree4, tree2);

	BinaryTreeSearch tree6("Python");
	BinaryTreeSearch tree7(std::move(tree6));
	Assert::IsTrue(tree7 == BinaryTreeSearch("Python"));
	*/

	BinaryTreeSearch tree1("Cpp");
	BinaryTreeSearch tree2("Java");
	BinaryTreeSearch tree3(tree1);

	cout << (tree1 == tree3 ? "true" : "false") << endl; //+
	cout << (tree2 == tree3 ? "true" : "false") << endl; //-

	BinaryTreeSearch tree4 = tree2;
	cout << (tree4 == tree2 ? "true" : "false") << endl; //+

	BinaryTreeSearch tree6("Python");
	BinaryTreeSearch tree7(std::move(tree6));
	cout << (tree7 == BinaryTreeSearch("Python") ? "true" : "false") << endl;  //+

	/*BinaryTreeSearch tree;
	BinaryTreeSearch tree1;
	tree1.clear();
	cout << (tree == tree1 ? "true" : "false") << endl;
	cout << tree.find("tree") << endl;
	tree.add("tree");
	tree.add("r");
	tree.add("tree");

	cout << tree;*/
	/*cout << tree.findWord("tree") << endl;
	cout << "before r :  " << tree.findWord("r") << endl;
	tree.removeWord("r");
	cout << "after remove r :  " << tree.findWord("r") << endl;*/
    return 0;
}

