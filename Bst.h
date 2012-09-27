#include <iostream>
using namespace std;

class BNode{
	int data;
	BNode* left;
	BNode* right;
	BNode();
	BNode(int);
	BNode(int, BNode*, BNode*);
	friend class BST;
public:
	int GetData()const;
};

class BST{
	BNode* root;
	BNode* cursor;
	bool InsertHelp(int e, BNode*&);
	void PrintInHelp(ostream& os, BNode* n);
	void PrintPreHelp(ostream& os, BNode* n);
	void PrintPostHelp(ostream& os, BNode* n);
	BNode* FindHelp(int e, BNode*n);
	bool RemoveHelp(int e, BNode*&);
	//Feel free to add Helper routines if you need them here
public:
	BST();
	BST(const BST&); // copy constructor
	~BST(); // destructor
	BST& operator=(const BST&);
	bool Insert(int e);//cursor at insertion point
	bool Remove(int e);//cursor at parent of removed item or at root
	void PrintPre(ostream&);
	void PrintPost(ostream&);
	void PrintIn(ostream&);
	BNode* Find(int e);//cursor at located node or rightmost node
	BNode* AtCursor()const;
	void GoToBeginning();
	void GoToEnd();
	void GoToNext();
	void GoToPrev();
	void ClearList();
	void CopyList();// to be called by copy constructor and assignment
	bool Empty()const;
};
