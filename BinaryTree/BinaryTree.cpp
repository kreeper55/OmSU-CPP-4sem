#include "stdafx.h"
#include "BinaryTree.h"

BinaryTree::BinaryTree() {
	root = new Node();
}

BinaryTree::BinaryTree(int value) {
	root = new Node(value);
}

BinaryTree::BinaryTree(const BinaryTree& other) {
	root = copyR(other.root);
}

BinaryTree::BinaryTree(BinaryTree&& other) {
	stolenR(other);
}

BinaryTree& BinaryTree::operator=(const BinaryTree& other)
{
	copy(other);
	return *this;
}

BinaryTree& BinaryTree::operator=(BinaryTree && other)
{
	if (this == &other) return *this;
	stolenR(other);
	return *this;
}

//public
bool BinaryTree::isPositive() {
	return isPositiveR(root);
}
// private
bool BinaryTree::isPositiveR(Node* current) {
	if (current == 0x0) return true;
	if (current->value > 0) { 
		true && isPositiveR(current->left) && isPositiveR(current->right); 
	}
	else return false;
}

// public
int BinaryTree::getEvenElem() {
	return getEvenElemR(root);
}
// private
int BinaryTree::getEvenElemR(Node* current) {
	if (current == 0x0) return 0;
	return  (1 - current->value % 2) + getEvenElemR(current->left) + getEvenElemR(current->right);
}

// public 
double BinaryTree::getAverage() {
	int sum = 0;
	int count = 0;
	getAverageR(root, count, sum);
	if (count == 0) throw BTreeIsEmpty("Error! BinaryTree is empty");
	return (double)sum / count;
}
// private
void BinaryTree::getAverageR(Node* current, int& count, int& sum) {
	if (current == 0x0) return;
	getAverageR(current->left, count, sum);
	getAverageR(current->right, count, sum);
	count++;
	sum += current->value;
}

// public 
void BinaryTree::deleteAllLeaves() {
	deleteAllLeavesR(root);
}
// private
bool BinaryTree::deleteAllLeavesR(Node*& current) {
	if (current == 0x0) return false;
	if (current->left == 0x0 && current->right == 0x0) {
		delete current;
		return true;
	}
	else {
		if (deleteAllLeavesR(current->left))
			current->left = 0x0;
		if (deleteAllLeavesR(current->right))
			current->right = 0x0;
		return false;
	}
}

std::vector<int> BinaryTree::find(int value) {
	if (this->root == 0x0) throw BTreeIsEmpty("Binary tree is empty");
	std::vector<int> way;
	if (findR(root, way, value)) {
		return way;
	}
}

bool BinaryTree::findR(Node* current, std::vector<int> &sequence, int value) {
	if (current == 0x0) {
		sequence.pop_back();
		return false;
	}
	if (current->value == value) {
		return true;
	}
	sequence.push_back(0);
	if (findR(current->left, sequence, value)) {
		return true;
	}
	sequence.push_back(1);
	if (findR(current->right, sequence, value)) {
		return true;
	}
	if (sequence.size() == 0) throw InvalidWayTreeException("BTree is empty");
	sequence.pop_back();
	return false;
}

// private
void BinaryTree::stolenR(BinaryTree& current) {
	root = current.root;
	current.root = nullptr;
}

// public
void BinaryTree::copy(const BinaryTree& tree) {
	if (this == &tree) return;
	clear();
	copyR(tree.root);
}
// private
BinaryTree::Node* BinaryTree::copyR(Node* current) {
	if (current == 0x0) return 0x0;
	return new Node(current->value, copyR(current->left), copyR(current->right));
}

// public 
void BinaryTree::clear() {
	clearR(root);
}
// private
void BinaryTree::clearR(Node*& current) {
	if (current == 0x0) return;
	clearR(current->left);
	clearR(current->right);
	//current->value = 0;
	delete current;
	current = 0x0;
}

BinaryTree::~BinaryTree() {
	clear();
	delete root;
}

// public
void BinaryTree::add(const std::vector<int> sequence, int value) {
	if (addR(sequence, value, 0, root))
		return;
}
// private
bool BinaryTree::addR(const std::vector<int> sequence, int value, int index, Node*& current) {
	if (sequence.size() == index) {
		if (current == 0x0) {
			current = new Node(value);
			return true;
		}
		else {
			current->value = value;
		}
		return true;
	}
	if (current == 0x0) {
		throw InvalidWayTreeException("bad way");
	}
	if (sequence[index] == 0) {
		if (addR(sequence, value, ++index, current->left)) 
			return true;
	}
	if (sequence[index] == 1) {
		if (addR(sequence, value, ++index, current->right))
			return true;
	}
	return false;
}

// output вывод
// public
std::ostream& operator<<(std::ostream& stream, const BinaryTree& tree) {
	BinaryTree::outputR(stream, tree.root);
	return stream;
}
// private
void BinaryTree::outputR(std::ostream& stream, const Node* current) {
	if (current == 0x0) { return; }
	outputR(stream, current->left);
	stream << current->value << " ";
	outputR(stream, current->right);
}

// public OPERATOR==
bool operator==(const BinaryTree& leftTree, const BinaryTree& rightTree) {
	if (&leftTree == &rightTree) { return true; }
	return equalsR(leftTree.root, rightTree.root);
}
// private 
bool equalsR(const BinaryTree::Node* left, const BinaryTree::Node* right) {
	if (left == 0x0 || right == 0x0)
		return (left == right);
	return	(left->value == right->value) &&
			(equalsR(left->left, right->left)) &&
			(equalsR(left->right, right->right));
}