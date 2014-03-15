#include <iostream.h>
#include <string.h>

enum Bool {false,true};

typedef char *Str;

template <class Type>
class BinNode {
public:
				BinNode		(const Type&);
        		~BinNode	(void)	{}
	Type&		Value		(void)	{return value;}
    BinNode*&	Left		(void)	{return left;}
    BinNode*&	Right		(void)	{return right;}

    void	 	FreeSubtree	(BinNode *subtree);
	void	 	InsertNode	(BinNode *node, BinNode *&subtree);
	void	 	DeleteNode	(const Type&, BinNode *&subtree);
const BinNode* 	FindNode	(const Type&, const BinNode *subtree);
	void	 	PrintNode	(const BinNode *node);

private:
	Type	value;		// node value
	BinNode	*left;		// pointer to left child
	BinNode	*right;		// pointer to right child
};

template <class Type>
class BinTree {
public:
	     	BinTree	(void);
	    	~BinTree(void);
	void	Insert	(const Type &val);
	void 	Delete	(const Type &val);
	Bool	Find	(const Type &val);
	void	Print	(void);

protected:
	BinNode<Type> *root;	// root node of the tree
};

template <class Type>
BinNode<Type>::BinNode (const Type &val)
{
	value = val;
    left = right = 0;
}

// specialization:

BinNode<Str>::BinNode (const Str &str)
{
	value = new char[strlen(str) + 1];
    strcpy(value, str);
    left = right = 0;
}

template <class Type>
void BinNode<Type>::FreeSubtree (BinNode<Type> *node)
{
	if (node != 0) {
		FreeSubtree(node->left);
		FreeSubtree(node->right);
		delete node;
	}
}

template <class Type>
void BinNode<Type>::InsertNode (BinNode<Type> *node, BinNode<Type> *&subtree)
{
	if (subtree == 0)
    	subtree = node;
	else if (node->value <= subtree->value)
		InsertNode(node, subtree->left);
	else
		InsertNode(node, subtree->right);
}

// specialization:

void BinNode<Str>::InsertNode (BinNode<Str> *node, BinNode<Str> *&subtree)
{
	if (subtree == 0)
    	subtree = node;
	else if (strcmp(node->value, subtree->value) <= 0)
		InsertNode(node, subtree->left);
	else
		InsertNode(node, subtree->right);
}

template <class Type>
void BinNode<Type>::DeleteNode (const Type &val, BinNode<Type> *&subtree)
{
	int cmp;

	if (subtree == 0)
		return;
	if (val < subtree->value)
		DeleteNode(val, subtree->left);
	else if (val > subtree->value)
		DeleteNode(val, subtree->right);
	else {
		BinNode* handy = subtree;
		if (subtree->left == 0) 		// no left subtree
			subtree = subtree->right;
		else if (subtree->right == 0)	// no right subtree
			subtree = subtree->left;
		else { 							// left and right subtree
        	subtree = subtree->right;
            // insert left subtree into right subtree:
			InsertNode(subtree->left, subtree->right);
        }
		delete handy;
	}
}

// specialization:

void BinNode<Str>::DeleteNode (const Str &str, BinNode<Str> *&subtree)
{
	int cmp;

	if (subtree == 0)
		return;
	if ((cmp = strcmp(str, subtree->value)) < 0)
		DeleteNode(str, subtree->left);
	else if (cmp > 0)
		DeleteNode(str, subtree->right);
	else {
		BinNode<Str>* handy = subtree;
		if (subtree->left == 0) 		// no left subtree
			subtree = subtree->right;
		else if (subtree->right == 0)	// no right subtree
			subtree = subtree->left;
		else { 							// left and right subtree
        	subtree = subtree->right;
            // insert left subtree into right subtree:
			InsertNode(subtree->left, subtree->right);
        }
		delete handy;
	}
}

template <class Type>
const BinNode<Type>*
BinNode<Type>::FindNode (const Type &val, const BinNode<Type> *subtree)
{
	if (subtree == 0)
		return 0;
    if (val < subtree->value)
        return FindNode(val, subtree->left);
	if (val > subtree->value)
		return FindNode(val, subtree->right);
	return subtree;
}

// specialization:

const BinNode<Str>*
BinNode<Str>::FindNode (const Str &str, const BinNode<Str> *subtree)
{
	int cmp;

	return (subtree == 0)
			? 0
            : ((cmp = strcmp(str, subtree->value)) < 0
            	? FindNode(str, subtree->left)
                : (cmp > 0
					? FindNode(str, subtree->right)
					: subtree));

}

template <class Type>
void BinNode<Type>::PrintNode (const BinNode<Type> *node)
{
	if (node != 0) {
		PrintNode(node->left);
		cout << node->value << ' ';
		PrintNode(node->right);
	}
}

template <class Type>
void BinTree<Type>::Insert (const Type &val)
{
	root->InsertNode(new BinNode<Type>(val), root);
}

template <class Type>
BinTree<Type>::BinTree (void)
{
	root = 0;
}

template <class Type>
BinTree<Type>::~BinTree(void)
{
	root->FreeSubtree(root);
}

template <class Type>
void BinTree<Type>::Delete (const Type &val)
{
	root->DeleteNode(val, root);
}

template <class Type>
Bool BinTree<Type>::Find (const Type &val)
{
	return root->FindNode(val, root) != 0;
}

template <class Type>
void BinTree<Type>::Print (void)
{
	root->PrintNode(root);  cout << '\n';
}

int main (void)
{
	BinTree<int> nums;

    nums.Insert(10);
    nums.Insert(5);
    nums.Insert(100);
    nums.Insert(25);
    nums.Delete(5);
    cout << nums.Find(100) << '\n';
    nums.Print();

	BinTree<Str> tree;

    tree.Insert("Sam");
    tree.Insert("Neil");
    tree.Insert("Adam");
    tree.Insert("Jones");
    tree.Insert("Alan");
    tree.Delete("Adam");
    cout << tree.Find("Jones") << '\n';
    tree.Print();

    return 0;
}


