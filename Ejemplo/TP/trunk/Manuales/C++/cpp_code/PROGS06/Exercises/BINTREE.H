#ifndef _BINTREE_
#define _BINTREE_

#include <iostream.h>
#include <string.h>

enum Bool {false,true};

class Sequence;

class BinNode {
public:
				BinNode		(const char*);
        		~BinNode	(void)	{delete value;}
	char*&		Value		(void)	{return value;}
    BinNode*&	Left		(void)	{return left;}
    BinNode*&	Right		(void)	{return right;}

    void	 	FreeSubtree	(BinNode *subtree);
	void	 	InsertNode	(BinNode *node, BinNode *&subtree);
	void	 	DeleteNode	(const char*, BinNode *&subtree);
const BinNode* 	FindNode	(const char*, const BinNode *subtree);
	void	 	PrintNode	(const BinNode *node);

private:
	char	*value;		// node value
	BinNode	*left;		// pointer to left child
	BinNode	*right;		// pointer to right child
};

class BinTree {
public:
	     	BinTree	(void)				{root = 0;}
            BinTree	(Sequence &seq);
	    	~BinTree(void)				{root->FreeSubtree(root);}
	void	Insert	(const char *str);
	void 	Delete	(const char *str)	{root->DeleteNode(str, root);}
	Bool	Find	(const char *str)	{return root->FindNode(str, root) != 0;}
	void	Print	(void) 		{root->PrintNode(root);  cout << '\n';}

	BinNode*	MakeTree (Sequence &seq, int low, int high);

protected:
	BinNode* root;			// root node of the tree
};

#endif