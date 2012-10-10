#include "Bst.h"

BNode::BNode(){
  data = 0;
  left = NULL;
  right = NULL;
}

BNode::BNode(int d) {
  data = d;
  left = NULL;
  right = NULL;
}

BNode::BNode(int d,BNode* l, BNode* r){
  data = d;
  left = l;
  right = r;
}

int BNode::GetData() const{
  return data;
}

BST::BST() {
  root = NULL;
  cursor = NULL;
}

BST::~BST() {
  ClearList();
}
BST::BST(const BST& Ftree){
    root = NULL;
    cursor = NULL;
    CopyList(Ftree.root);
}
void BST::ClearList(){
  if (root != NULL) ClearListHelper(root);
  root = NULL;
}

void BST::ClearListHelper(BNode * n){
  // delete down the left branch
  if (n->left != NULL) ClearListHelper(n->left);
  // delete down the right branch
  if (n->right != NULL) ClearListHelper(n->right);
  delete n; // delete this node
}

bool BST::Insert(int e) {
  if (root == NULL){
    BNode * nn = new BNode(e); // BNode is type;	Declaring new value.
    root = nn;
    cursor = nn;
    return true;
  }
  return InsertHelp(e, root);

}

bool BST::InsertHelp(int e, BNode *&n) {
	#ifdef DEBUG
  cout << "InsertHelp got " << e << endl;
#endif
  BNode * next;
  if (e < n->data) {
    next = n->left; // check left side
  }
  else {
    next = n->right; // Check right side
  }

  if (next == NULL) {
    // Creating a New node
    BNode * nn = new BNode(e); // new returns a pointer
	if (e < n->data){ n->left = nn;
	}		
    else n->right = nn;
		cursor = nn;
    return true;
  }
  else {
    return	InsertHelp(e, next);
  }
}

void BST::PrintIn(ostream& oss){
  if(root == NULL) {
    cout << "root is NULL, nothing to print\n";
    return;
  }
  PrintInHelp(oss, root);
}

void BST::PrintInHelp(ostream & oss, BNode * n){
	
  if (n->left != NULL) PrintInHelp(oss, n->left);   // any left legs have been printed
	if(n->data == cursor->data)
  oss << "[" <<  n->data << "]" << " "; // Print itself
	else
		oss << n->data << " ";
#ifdef DEBUG
  cout << "entered printInHelp node value is " << n->data << " left is " << n->left << " right is " << n->right;
#endif
  if (n->right != NULL) PrintInHelp(oss, n->right); // print right legs
}

void BST::PrintPost(ostream& oss){
  if(root == NULL) {
    cout << "root is NULL, nothing to print\n";
    return;
  }
  PrintPostHelp(oss, root);
  cout << endl << "Base List";
}

void BST::PrintPostHelp(ostream & oss, BNode * n){
#ifdef DEBUG
  cout << "entered PrintPostHelp, node holds " << n->data << " left is " << n->left << " right is " << n->right << endl;
#endif
  if (n->left != NULL) PrintPostHelp(oss, n->left); // recursively print left branches
  if (n->right != NULL) PrintPostHelp(oss, n->right); // recursively print right branches
	if(n->data == cursor->data)
  oss << "[" <<  n->data << "]" << " "; // Print itself
	else
		oss << n->data << " ";
}

void BST::PrintPre(ostream& oss){
  if(root == NULL) {
    cout << "root is NULL, nothing to print\n";
    return;
  }
  PrintPreHelp(oss, root);
  cout << endl << "Base List";
}

void BST::PrintPreHelp(ostream & oss, BNode * n){
#ifdef DEBUG
  cout << "entered PrintPreHelp, node holds " << n->data << " left is " << n->left << " right is " << n->right << endl;
#endif
  if(n->data == cursor->data)
  oss << "[" <<  n->data << "]" << " "; // Print itself
	else
		oss << n->data << " ";
  if (n->left != NULL) PrintPreHelp(oss, n->left); // recursively print left branches
  if (n->right != NULL) PrintPreHelp(oss, n->right); // recursively print right branches
}

bool BST::Empty()const {
  if (root != NULL) return false;
  return true;
}

void BST::GoToBeginning() {
  if(root == NULL) return;
  else{
  BNode * n = root;
  while (n->left != NULL) {
    n = n->left;
  }
  cursor = n;
  }
}

void BST::GoToEnd() {
  BNode * n = root;
  if (n == NULL) return; // uh, no?
  while (n->right != NULL) {
    n = n->right;
  }
  cursor = n;
}

BNode * BST::Find(int e) {
  FindHelper(e, root);
  return cursor;
}

void BST::FindHelper(int e, BNode * current){
  if (current == NULL) {
    GoToEnd(); // catches the null case;
	cursor = NULL;
    return;
  }
  if (e == current->data) cursor = current;
  if (e < current->data) FindHelper(e, current->left);
  if (e > current->data) FindHelper(e, current->right);
}

BNode * BST::AtCursor()const {
  return cursor;
}

bool BST::Remove(int e){
  BNode * d = Find(e); // get a pointer to the node
  if(d==NULL) return false; // well DUH 
  // BNode * parent = getParent(d);
  cout << "removing " << e << " node has value " << d->data << "branches are " << d->left << " " << d->right << endl;
  cout << "Does NULL == 0? " << (NULL == 0) << endl;
  // node has no children, remove from tree
  if ((d->left == NULL) && (d->right == NULL)) {
    cout << "inside zero children remove\n";
    if (d == root) {
      cout << "inside root removal\n";
      delete d;
      root = NULL;
      return true; // ARGH
    } else {
      cout << "removing non-root zero-child node\n";
      BNode * parent = getParent(d);
      // check parent, set matching branch pointer to NULL
      if (parent->left == d) {
        parent->left = NULL;
        delete d;
        return true;
      } else {
        parent->right = NULL;
        delete d;
        return true;
      }
    }
  } else {
    cout << "skipped out of zero children\n";
  }

  int children = 0; // this is ugly
  BNode * child;
  if(d->left != NULL) {
    children++;
    child = d->left;
  }
  if(d->right != NULL) {
    children++;
    child = d->right;
  }
  if(children == 1) {   // has only one child
    // delete node, replace with its one child
    BNode * parent = getParent(d);
    if(parent->left == d) parent->left = child;
    if(parent->right == d) parent->right = child;
    delete d;
  }
  /* node to delete has two children
     swap value with left-most child of right subtree (in-order successor)
     in-order successor node will have zero or one children,
     delete swapped value according to simpler cases above
  */
  BNode * succ = d->right; // follow branch to the right once
  cout << "succ after one step right has value " << d->data << endl;
  // a segfault here can only mean I'm not setting the branch pointers to NULL!
  while(succ->left != NULL) { // follow branches all the way to the left
    succ = succ->left;
  }
#ifdef DEBUG
  cout << "delete node with two children should now have traversed to in-order successor\n";
  cout << "traversed from" << d->data << " to " << succ->data << endl;
#endif
  // swap the two integer values
  int tmp = d->data;
  d->data = succ->data;
  succ->data = tmp;
  // delete the node that has one or two children
  return Remove(succ->data);
}


BNode * BST::getParent(BNode * child){
  if (child == root) return NULL;
  return getParentHelp(child, root);
}

/*
  got handed node, if this node has pointer to the object of search, return THIS node.
  if not, call ourself with the children
  if no children, return NULL pointer.
 */
BNode* BST::getParentHelp(BNode * child,BNode * current){
#ifdef DEBUG
  cout << "entered getParentHelp, node holds " << current->data << " left is " << current->left << " right is " << current->right;
#endif
  if(current == NULL) return NULL;
  if(current->left == child) return current; // check this node
  if(current->right == child) return current; // check this node
  BNode * found;
  if ( (found = getParentHelp(child, current->left)) ) return found; // recursively search left branches
  if ( (found = getParentHelp(child, current->right)) ) return found; // recursively search right branches
  return NULL;
}

/*
int BST::RemoveHelp(int e)
{
    BNode *back;
    BNode *temp;
    BNode *delParent;    // Parent of node to delete
    BNode *delNode;      // Node to delete

    temp = root;
    back = NULL;

    // Find the node to delete
    while((temp != NULL) && (e != temp->e))
    {
        back = temp;
        if(Key < temp->e)
            temp = temp->left;
        else
            temp = temp->right;
    }

    if(temp == NULL) // Didn't find the one to delete
    {
        cout << "Key not found. Nothing deleted.\n";
        return false;
    }
    else
    {
        if(temp == root) // Deleting the root
        {
            delNode = root;
            delParent = NULL;
        }
        else
        {
            delNode = temp;
            delParent = back;
        }
    }

    // Case 1: Deleting node with no children or one child
    if(delNode->right == NULL)
    {
        if(delParent == NULL)    // If deleting the root
        {
            root = delNode->left;
            delete delNode;
            return true;
        }
        else
        {
            if(delParent->left == delNode)
                delParent->left = delNode->left;
            else
                delParent->right = delNode->left;
            delete delNode;
            return true;
        }
    }
    else // There is at least one child
    {
        if(delNode->left == NULL)    // Only 1 child and it is on the right
        {
            if(delParent == NULL)    // If deleting the root
            {
                root = delNode->right;
                delete delNode;
                return true;
            }
            else
            {
                if(delParent->left == delNode)
                    delParent->left = delNode->right;
                else
                    delParent->right = delNode->right;
                delete delNode;
                return true;
            }
        }
        else // Case 2: Deleting node with two children
        {
            // Find the replacement value.  Locate the node
            // containing the largest value smaller than the
            // key of the node being deleted.
            temp = delNode->left;
            back = delNode;
            while(temp->right != NULL)
            {
                back = temp;
                temp = temp->right;
            }
            // Copy the replacement values into the node to be deleted
            delNode->Key = temp->Key;
            delNode->fValue = temp->fValue;
            delNode->iValue = temp->iValue;
            strcpy(delNode->cArray, temp->cArray);

            // Remove the replacement node from the tree
            if(back == delNode)
                back->left = temp->left;
            else
                back->right = temp->left;
            delete temp;
            return true;
        }
    }
}
*/

 /*

void BST::GoToNext(){
	GoToNextHelper(root);

}

void BST::GoToNextHelper(current){
	if(cursor < current){
		if(cursor->right !=NULL)
			cursor = cursor->right;
		else if(cursor->right == NULL){
			if(current->left > cursor)
				cursor = cuurent->left;
			else if(root->left < cursor)
				cursor = current;
		}
	}
	else if(cursor > current)

}
 */
void BST::CopyList(BNode* previousNode) {
    
	Insert(previousNode->data);
    
	if (previousNode->left != NULL)
		CopyList(previousNode->left);
    
	if (previousNode->right != NULL)
		CopyList(previousNode->right);
}
BST& BST::operator=(const BST& Ftree){
    
    ClearList();
    
    CopyList(Ftree.root); // Ftree = First Tree
    
    return *this;
    
}
/*
BNode * BST::getParent(BNode * child){
    
BNode * temp; // Create temp Node
temp = root; // Set temp = root for start
 
if (child == temp || child == temp->left || child == temp->right)
return temp;

do { if (child == temp->left || child == temp->right) // If child the number is left or right
        return temp;
    
    if (child->data < temp->data && temp->right != child) // If the child number less than temp and to the right is not the child
        temp = temp->left;      
        
        if (child->data > temp->data && temp->right != child) // If it is greater than return right
            temp = temp->right;
            } while (temp->left != child || temp->right != child);
return temp;
}
*/
