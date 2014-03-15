#define _MAIN_
#include "bintree.h"
#include "sequence.cpp"

BinNode::BinNode (const char *str)
{
	value = new char[strlen(str) + 1];
    strcpy(value, str);
    left = right = 0;
}

void
BinNode::FreeSubtree (BinNode *node)
{
	if (node != 0) {
		FreeSubtree(node->left);
		FreeSubtree(node->right);
		delete node;
	}
}

void
BinNode::InsertNode (BinNode *node, BinNode *&subtree)
{
	if (subtree == 0)
    	subtree = node;
	else if (strcmp(node->value, subtree->value) <= 0)
		InsertNode(node, subtree->left);
	else
		InsertNode(node, subtree->right);
}

void
BinNode::DeleteNode (const char *str, BinNode *&subtree)
{
	int cmp;

	if (subtree == 0)
		return;
	if ((cmp = strcmp(str, subtree->value)) < 0)
		DeleteNode(str, subtree->left);
	else if (cmp > 0)
		DeleteNode(str, subtree->right);
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

const BinNode*
BinNode::FindNode (const char *str, const BinNode *subtree)
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

void
BinNode::PrintNode (const BinNode *node)
{
	if (node != 0) {
		PrintNode(node->left);
		cout << node->value << ' ';
		PrintNode(node->right);
	}
}

BinTree::BinTree (Sequence &seq)
{
	root = MakeTree(seq, 0, seq.Size() - 1);
}

void
BinTree::Insert (const char *str)
{
	root->InsertNode(new BinNode(str), root);
}

// global friend:

BinNode*
BinTree::MakeTree (Sequence &seq, int low, int high)
{
	int mid = (low + high) / 2;
	BinNode* node = new BinNode(seq.entries[mid]);

	node->Left() = (mid == low ? 0 : MakeTree(seq, low, mid-1));
	node->Right() = (mid == high ? 0 : MakeTree(seq, mid+1, high));
	return node;
}


int
main (void)
{
	Sequence q(10);
    q.Insert("Sam");
    q.Insert("Neil");
    q.Insert("Adam");
    q.Insert("Jones");
    q.Insert("Alan");
    q.Print();

    BinTree bin(q);
    bin.Print();

    return 0;
}


