#pragma once

struct InvalidWayTreeException {
	std::string message;
	InvalidWayTreeException() {
		message = "sequence are invalid";
	}

	InvalidWayTreeException(const char* cMessage) {
		message = cMessage;
	}
};

struct BTreeIsEmpty {
	std::string message;
	BTreeIsEmpty() {
		message = "Binary Tree Is Empty";
	}

	BTreeIsEmpty(const char* cMessage) {
		message = cMessage;
	}
};

class BinaryTree
{
public:
	BinaryTree();
	BinaryTree(int value);
	BinaryTree(const BinaryTree& other);
	BinaryTree(BinaryTree&& other);

	BinaryTree& operator=(const BinaryTree& other);
	BinaryTree& operator=(BinaryTree&& other);

	friend std::ostream& operator<<(std::ostream &stream, const BinaryTree &tree);
	friend bool operator==(const BinaryTree& left, const BinaryTree& right);

	void add(const std::vector<int> sequence, int value);
	bool isPositive();
	int getEvenElem();
	double getAverage();
	void deleteAllLeaves();
	std::vector<int> find(int value);

	void clear();
	void copy(const BinaryTree& tree);

	bool isBTS();
	void print();

	~BinaryTree();
private:
	struct Node {
		int value;
		Node* left;
		Node* right;
		Node(int value = 0, Node* left = nullptr, Node* right = nullptr)
			: value(value), left(left), right(right) {}
	};
	Node* root;

	bool addR(const std::vector<int> sequence, int value, int index, Node*& root);

	bool isPositiveR(Node* root);
	int getEvenElemR(Node* root);
	void getAverageR(Node* root, int& count, int& sum);
	bool deleteAllLeavesR(Node*& root);
	bool findR(Node* root, std::vector<int>& sequence, int value);

	static void outputR(std::ostream &stream, const Node* root);
	friend bool equalsR(const Node* left, const Node* right);

	void clearR(Node*& root);
	Node* copyR(Node* root);
	void stolenR(BinaryTree& tree);
	//sam delal

	bool isBTSR(Node* root, int min, int max);
	void printR(Node* root, int level);
};