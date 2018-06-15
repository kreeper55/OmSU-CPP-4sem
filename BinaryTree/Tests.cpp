#include "stdafx.h"
#include "CppUnitTest.h"
#include "../BinaryTree/BinaryTree.cpp"
#include "../BinaryTree/BinaryTree.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

bool equals(std::vector<int>& vec1, std::vector<int>& vec2) {
	if (vec1.size() != vec2.size()) {
		return false;
	}
	for (int i = 0; i < vec1.size(); i++) {
		if (vec1[i] != vec2[i]) {
			return false;
		}
	}
	return true;
}

namespace TestBinaryTree
{		
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(BTAdd) {
			BinaryTree tree(1);
			tree.add({ 0 }, 1);
			tree.add({ 1 }, 2);
			tree.add({ 10 }, 3);
			tree.add({ 11 }, 4);
			tree.add({ 10 }, 999);

			Assert::ExpectException<InvalidWayTreeException>([&]
			{
				tree.add({ 0,0,1,0,1,0,1,0,0 }, 9876);
			});
			Assert::ExpectException<InvalidWayTreeException>([&]
			{
				tree.add({ 0,1,1,0 }, 9876); 
			});
			Assert::ExpectException<InvalidWayTreeException>([&]
			{
				tree.add({ 0,0,0 }, 9876);
			});
		}
		TEST_METHOD(BTEven) {
			BinaryTree tree(9);
			tree.add({ 0 }, 1);
			tree.add({ 1 }, 2);
			tree.add({ 0,0 }, 3);
			tree.add({ 0,1 }, 4);
			tree.add({ 1,1 }, 5);
			Assert::AreEqual(tree.getEvenElem(), 2);
			tree.add({ 0,0,0 }, 8);
			tree.add({ 0,0,1 }, 110);
			tree.add({ 1,0 }, 18);
			tree.add({ 1,1 }, 77);
			Assert::AreEqual(tree.getEvenElem(), 5);

			tree.clear();
			tree.add({ }, 1);
			tree.add({ 0 }, 1);
			tree.add({ 1 }, 3);
			tree.add({ 0,1 }, 5);
			tree.add({ 1,1 }, 7);
			Assert::AreEqual(tree.getEvenElem(), 0);
		}
		TEST_METHOD(BTPositive) {
			BinaryTree tree(11);
			tree.add({ 0 }, 1);
			tree.add({ 1 }, 2);
			tree.add({ 0,0 }, 3);
			tree.add({ 0,1 }, 4);
			tree.add({ 1,1 }, 5);
			Assert::IsTrue(tree.isPositive());

			tree.add({ 0 }, -1);
			tree.add({ 0,0 }, 3);
			tree.add({ 0,1 }, -4);
			Assert::IsFalse(tree.isPositive());
		}
		TEST_METHOD(BTAverage) {
			BinaryTree tree(3);
			tree.add({ 0 }, 5);
			tree.add({ 0,1 }, 2);
			tree.add({ 0,0 }, 3);
			tree.add({ 0,0,0 }, 7);
			Assert::AreEqual((double)4, tree.getAverage());

			BinaryTree tree1(12.4);
			Assert::AreEqual((double)12, tree1.getAverage());

			tree.clear();
			Assert::ExpectException<BTreeIsEmpty>([&] {
				tree.getAverage();
			});
		}
		TEST_METHOD(BTFind) {
			BinaryTree tree(0);
			tree.add({ 0 }, 1);
			tree.add({ 1 }, 2);
			tree.add({ 0,0 }, 3);
			tree.add({ 0,1 }, 4);
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

			std::vector<int> vec1;
			vec1.push_back(1);
			vec1.push_back(0);
			vec1.push_back(1);
			Assert::IsTrue(equals(vec1, tree.find(12)));

			std::vector<int> vec2;
			vec2.push_back(0);
			vec2.push_back(1);
			Assert::IsTrue(equals(vec2, tree.find(4)));

			std::vector<int> vec3;
			Assert::IsTrue(equals(vec3, tree.find(0)));

			Assert::ExpectException<InvalidWayTreeException>([&]
			{
				tree.find(144);
			});
		}

		TEST_METHOD(TestAddException)
		{
			BinaryTree tree(10);
			tree.add({0}, 9);
			tree.add({1}, 8);
			Assert::ExpectException<InvalidWayTreeException>([&]
			{
				tree.add({ 1,1,1 }, 7);
			});
		}
		TEST_METHOD(TConstructors)
		{
			BinaryTree tree1(2);
			tree1.add({ 0 }, 226);
			BinaryTree tree3(tree1);

			BinaryTree tree2(25);
			Assert::IsTrue(tree1 == tree3);
			Assert::IsFalse(tree2 == tree3);

			BinaryTree tree4 = tree2;
			Assert::IsTrue(tree4 == tree2);

			BinaryTree tree6(24);
			tree6.add({ 0 }, 9);
			tree6.add({ 1 }, 5);
			tree6.add({ 1,0 }, 10);
			tree6.add({ 1,0,1 }, 101);
			BinaryTree tree8 = tree6;
			BinaryTree tree7(std::move(tree6));
			Assert::IsTrue(tree7 == tree8);
		}
		TEST_METHOD(TOpearatorEqualse)
		{
			BinaryTree tree1(3);
			BinaryTree tree2(5);
			Assert::IsFalse(tree1 == tree2);
			tree1.add({}, 5);
			Assert::IsTrue(tree1 == tree2);
		}

	};
}