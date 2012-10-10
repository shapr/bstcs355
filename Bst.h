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
	bool InsertHelp(int e, BNode*&); // - done ********
	void PrintInHelp(ostream& os, BNode* n); // - done ********
	void PrintPreHelp(ostream& os, BNode* n); // - done ********
	void PrintPostHelp(ostream& os, BNode* n); // - done ********
    void ClearListHelper(BNode* n); // - done ********
	BNode* FindHelp(int e, BNode*n); // - done ********
    void FindHelper(int e, BNode * current); // - done ********
    BNode * getParentHelp(BNode * child,BNode * current); // - done ********
    
    bool RemoveHelp(int e, BNode*&);
    
	//Feel free to add Helper routines if you need them here
public:
	BST(); // - done ********
	//BST(const BST&); // copy constructor
	~BST(); // destructor // - done ********
    
	bool Insert(int e);//cursor at insertion point // - done ********
    bool Remove(int e);//cursor at parent of removed item or at root // - done ********
	void PrintPre(ostream&); // - done ********
	void PrintPost(ostream&);// - done ********
	void PrintIn(ostream&); // - done ********
	BNode* Find(int e);//cursor at located node or rightmost node // - done ********
	BNode* AtCursor()const; // - done ********
	void GoToBeginning(); // - done ********
	void GoToEnd(); // - done ********
    
    void GoToNext();
	void GoToNextHelper(BNode * current);
    void GoToPrev();
    BNode * getParent(BNode * child); // CHECK_______________ I just toyed with it and left it commented out
   // BST& operator=(const BST&); // CHECK____________________
    void CopyList(BNode*);// to be called by copy constructor and assignment CHECK_________________________

    
	void ClearList(); // - done ********
	bool Empty()const; // - done ********
    
    

};
