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
      cursor = n->left;
  }
  else {
    next = n->right; // Check right side
  }

  if (next == NULL) {
    // Creating a New node
    BNode * nn = new BNode(e); // new returns a pointer
    if (e < n->data) n->left = nn;
    else n->right = nn;
      cursor = n->right;
    return true;
  }
  else {
    return	InsertHelp(e, next);
  }
}

void BST::PrintIn(ostream& oss){
  PrintInHelp(oss, root);
}

void BST::PrintInHelp(ostream & oss, BNode * n){
#ifdef DEBUG
  cout << "entered PrintInHelp, node holds " << n->data << " left is " << n->left << " right is " << n->right << endl;
#endif
  if (n->left != NULL) PrintInHelp(oss, n->left);   // any left legs have been printed
  oss << n->data << endl; // Print itself
  if (n->right != NULL) PrintInHelp(oss, n->right); // print right legs
}

void BST::PrintPost(ostream& oss){
  PrintPostHelp(oss, root);
}

void BST::PrintPostHelp(ostream & oss, BNode * n){
#ifdef DEBUG
  cout << "entered PrintInHelp, node holds " << n->data << " left is " << n->left << " right is " << n->right << endl;
#endif
  if (n->left != NULL) PrintPostHelp(oss, n->left); // recursively print left branches
  if (n->right != NULL) PrintPostHelp(oss, n->right); // recursively print right branches
  oss << n->data << endl; // Print itself
}

void BST::PrintPre(ostream& oss){
  PrintPreHelp(oss, root);
}

void BST::PrintPreHelp(ostream & oss, BNode * n){
#ifdef DEBUG
  cout << "entered PrintPreHelp, node holds " << n->data << " left is " << n->left << " right is " << n->right << endl;
#endif
  oss << n->data << endl; // Print itself
  if (n->left != NULL) PrintPreHelp(oss, n->left); // recursively print left branches
  if (n->right != NULL) PrintPreHelp(oss, n->right); // recursively print right branches
}

bool BST::Empty()const {
  if (root != NULL) return false;
  return true;
}

void BST::GoToBeginning() {
  BNode * n = root;
  while (n->left != NULL) {
    n = n->left;
  }
  cursor = n;
}

void BST::GoToEnd() {
  BNode * n = root;
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
    GoToEnd(); // catches the null case
	cout << "Did not find. Returning end node" << endl;
    return;
  }
  if (e == current->data) cursor = current;
  if (e < current->data) FindHelper(e, current->left);
  if (e > current->data) FindHelper(e, current->right);
}

BNode * BST::AtCursor()const {
  return cursor;
}
/*
int BST::Remove(int e){
  BNode * d = Find(e); // get a pointer to the node
  // node has no children, remove from tree

}
*/
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
  cout << "entered getParentHelp, node holds " << n->data << " left is " << n->left << " right is " << n->right << endl;
#endif
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
