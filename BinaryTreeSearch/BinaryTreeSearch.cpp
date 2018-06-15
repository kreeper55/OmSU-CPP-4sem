#include "stdafx.h"
#include "BinaryTreeSearch.h"

// constructors :
BinaryTreeSearch::BinaryTreeSearch() {
	root = new Node("tree");
}

BinaryTreeSearch::BinaryTreeSearch(std::string word) {
	root = new Node(word);
}

BinaryTreeSearch::BinaryTreeSearch(const BinaryTreeSearch& other) {
	root = copy(other.root);
}

BinaryTreeSearch::BinaryTreeSearch(BinaryTreeSearch&& other) {
	stolen(other);
}

// operators=
BinaryTreeSearch& BinaryTreeSearch::operator=(const BinaryTreeSearch& other) {
	copy(other);
	return *this;
}

BinaryTreeSearch& BinaryTreeSearch::operator=(BinaryTreeSearch&& other) {
	if (this == &other) { return *this; }
	stolen(other);
	return *this;
}

//--------METHODS:
// private STOLEN
void BinaryTreeSearch::stolen(BinaryTreeSearch& tree) {
	root = tree.root;
	tree.root = nullptr;
}

// public COPY
void BinaryTreeSearch::copy(const BinaryTreeSearch& other) {
	if (this == &other) { return; }
	clear();
	root = copy(other.root);
}
// private
BinaryTreeSearch::Node* BinaryTreeSearch::copy(const Node* current) {
	if (current == 0x0) { return 0x0; }
	return new Node(current->word, current->count, copy(current->left), copy(current->right));
}

// public CLEAR
void BinaryTreeSearch::clear() {
	clear(this->root);
}
// private
void BinaryTreeSearch::clear(Node*& current) {
	if (current == 0x0) { return; }
	clear(current->left);
	clear(current->right);
	delete current;
	current = 0x0;
}

// public FIND
int BinaryTreeSearch::find(std::string word) {
	return find(word, root);
}
// private
int BinaryTreeSearch::find(std::string word, Node* current) {
	if (current == 0x0) { return 0; }
	if (current->word == word) return current->count;
	if (word < current->word) return find(word, current->left);
	if (word > current->word) return find(word, current->right);
	return 0;
}

// public ADD
void BinaryTreeSearch::add(std::string word) {
	add(word, root);
}
// private
void BinaryTreeSearch::add(std::string word, Node*& current) {
	if (current == 0x0)	{
		current = new Node(word);
		return;
	}
	if (current->word == word) {
		current->count = current->count + 1;
		return;
	}
	if (word < current->word) {
		add(word, current->left);
		return;
	}
	if (word > current->word) {
		add(word, current->right);
		return;
	}
	return;
}

// public REMOVE
void BinaryTreeSearch::remove(std::string word) {
	remove(word, root);
}
// private
void BinaryTreeSearch::remove(std::string word, Node*& current) {
	if (current == 0x0) { return; }
	if (word < current->word) {
		remove(word, current->left);
		return;
	}
	if (word > current->word) {
		remove(word, current->right);
		return;
	}
	if (word == current->word && current->count > 1) {
		current->count = current->count - 1;
		return;
	}
	if (word == current->word && current->count == 1) {
		Node* ptrCurrent = current;
		if (current->right == 0x0) {
			current = current->left;
			delete ptrCurrent;
			return;
		}
		if (current->left == 0x0) {
			current = current->right;
			delete ptrCurrent;
			return;
		}
		if (current->right == 0x0 && current->left == 0x0) {
			delete ptrCurrent;
			return;
		}
	}
	return;
}

// public GET THE NUMBER OF ALL WORDS
int BinaryTreeSearch::getNumberAllWords() {
	return getNumberAllWords(root);
}
// private
int BinaryTreeSearch::getNumberAllWords(Node* current) {
	if (current == 0x0) { return 0; }
	return root->count + getNumberAllWords(current->left) + getNumberAllWords(current->right);
}

// public OPERATOR<<
std::ostream& operator<<(std::ostream& stream, BinaryTreeSearch& tree) {
	tree.output(stream, tree.root);
	return stream;
}
// private
void BinaryTreeSearch::output(std::ostream& stream, Node* current) {
	if (current == 0x0) { return; }
	output(stream, current->left);
	stream << "x" << current->count << " " << current->word << "\t";
	output(stream, current->right);
}

// public OPERATOR==
bool operator==(const BinaryTreeSearch& leftTree, const BinaryTreeSearch& rightTree) {
	if (&leftTree == &rightTree) { return true; }
	return equalse(leftTree.root, rightTree.root);
}
// private 
bool equalse(const BinaryTreeSearch::Node* left, const BinaryTreeSearch::Node* right) {
	if ((left == 0x0 && right != 0x0) || 
		(left != 0x0 && right == 0x0))	{ return false; }
	if (left == 0x0 || right == 0x0)	{ return true; }
	return	(left->count == right->count)	&&
			(left->word == right->word)		&&
			(equalse(left->left, left->right)) &&
			(equalse(right->left, right->right));
}

// DESTRUCTOR
BinaryTreeSearch::~BinaryTreeSearch() {
	clear();
	delete root;
}