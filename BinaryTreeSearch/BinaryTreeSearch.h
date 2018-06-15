#pragma once

class BinaryTreeSearch {
public:
	BinaryTreeSearch();
	BinaryTreeSearch(std::string word);
	BinaryTreeSearch(const BinaryTreeSearch& other);
	BinaryTreeSearch(BinaryTreeSearch&& other);

	BinaryTreeSearch& operator=(const BinaryTreeSearch& other);
	BinaryTreeSearch& operator=(BinaryTreeSearch&& other);

	int find(std::string word);
	void add(std::string word);
	void remove(std::string word);

	int getNumberAllWords();
	friend std::ostream& operator<<(std::ostream &stream, BinaryTreeSearch& tree);
	friend bool operator==(const BinaryTreeSearch& leftTree, const BinaryTreeSearch& rightTree);

	void copy(const BinaryTreeSearch& other);
	void clear();

	~BinaryTreeSearch();
private:
	struct Node {
		std::string word;
		int count;
		Node* left;
		Node* right;
		Node(std::string word, int count = 1, Node* left = nullptr, Node* right = nullptr)
			: word(word), count(count), left(left), right(right) {}
	};
	Node* root;

	//private methods
	Node* copy(const Node* root);
	void stolen(BinaryTreeSearch& tree);
	void clear(Node*& current);

	int find(std::string word, Node* root);
	void add(std::string word, Node*& root);
	void remove(std::string word, Node*& root);

	int getNumberAllWords(Node* root);
	void output(std::ostream &stream, Node* root);
	friend bool equalse(const Node* left, const Node* right);
};