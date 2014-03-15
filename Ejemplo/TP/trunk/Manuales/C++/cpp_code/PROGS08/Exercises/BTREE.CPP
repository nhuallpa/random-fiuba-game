#include <iostream.h>
#include "database.h"

class BTree : public Database {
public:
	class Page;
	class Item {		// represents each stored item
	public:
    			Item	(void)		{right = 0;}
				Item	(Key, Data);
		Key&	KeyOf	(void)		{return key;}
	    Data&	DataOf	(void)		{return data;}
	    Page*&	Subtree	(void)		{return right;}
    friend	ostream&	operator <<	(ostream&, Item&);
	private:
	    Key		key;	// item's key
	    Data	data;	// item's data
	    Page	*right;	// pointer to right subtree
	};

	class Page {		// represents each tree node
	public:
					Page	(const int size);
	            	~Page	(void)			{delete items;}
		Page*&		Left	(const int ofItem);
	    Page*&		Right	(const int ofItem);
	    const int	Size	(void)			{return size;}
		int&		Used	(void)			{return used;}
        Item&	operator []	(const int n)   {return items[n];}
    	Bool		BinarySearch(Key key, int &idx);
        int 		CopyItems	(Page *dest, const int srcIdx,
								 const int destIdx, const int count);
    	Bool		InsertItem	(Item &item, int atIdx);
        Bool		DeleteItem	(int atIdx);
        void		PrintPage	(ostream& os, const int margin);
	private:
		const int	size;	// max no. of items per page
		int			used;	// no. of items on the page
	    Page		*left;	// pointer to the left-most subtree
	    Item		*items;	// the items on the page
	};

public:
          		BTree		(const int order);
         		~BTree		(void)		{FreePages(root);}
virtual	void	Insert		(Key key, Data data);
virtual	void	Delete		(Key key);
virtual	Bool	Search		(Key key, Data &data);
friend ostream&	operator <<	(ostream&, BTree&);

protected:
    	const int order;	// order of tree
    	Page	*root;		// root of the tree
    	Page	*bufP;	// buffer page for distribution/merging

virtual void	FreePages	(Page *page);
virtual Item*	SearchAux	(Page *tree, Key key);
virtual Item*	InsertAux	(Item *item, Page *page);

virtual void	DeleteAux1	(Key key, Page *page, Bool &underflow);
virtual void	DeleteAux2	(Page *parent,Page *page,
							 const int idx, Bool &underflow);
virtual void	Underflow	(Page *page, Page *child,
							 int idx, Bool &underflow);
};

BTree::Item::Item (Key k, Data d)
{
	key = k;
    data = d;
    right = 0;
}

ostream& operator << (ostream& os, BTree::Item &item)
{
 	os << item.key << ' ' << item.data;
	return os;
}

BTree::Page::Page (const int sz) : size(sz)
{
	used = 0;
    left = 0;
    items = new Item[size];
}

// return the left subtree of an item

BTree::Page*& BTree::Page::Left (const int ofItem)
{
    return ofItem <= 0 ? left: items[ofItem - 1].Subtree();
}

// return the right subtree of an item

BTree::Page*& BTree::Page::Right (const int ofItem)
{
    return ofItem < 0 ? left : items[ofItem].Subtree();
}

// do a binary search on items of a page
// returns true if successful and false otherwise

Bool BTree::Page::BinarySearch (Key key, int &idx)
{
    int	low = 0; 
    int	high = used - 1;
    int	mid;

    do {
        mid = (low + high) / 2;
        if (key <= items[mid].KeyOf())
            high = mid - 1;				// restrict to lower half
        if (key >= items[mid].KeyOf())
            low = mid + 1;              // restrict to upper half
    } while (low <= high);

    Bool found = low - high > 1;

    idx = found ? mid : high;
    return found;
}

// copy a set of items from page to page

int BTree::Page::CopyItems (Page *dest, const int srcIdx,
							const int destIdx, const int count)
{
    for (register i = 0; i < count; ++i)	// straight copy
		dest->items[destIdx + i] = items[srcIdx + i];
    return count;
}

// insert an item into a page

Bool BTree::Page::InsertItem (Item &item, int atIdx)
{
    for (register i = used; i > atIdx; --i)	// shift right
		items[i] = items[i - 1];
    items[atIdx] = item;					// insert
    return ++used >= size;					// overflow?
}

// delete an item from a page

Bool BTree::Page::DeleteItem (int atIdx)
{
    for (register i = atIdx; i < used - 1; ++i)	// shift left
		items[i] = items[i + 1];
    return --used < size/2;					// underflow?
}

// recursively print a page and its subtrees

void BTree::Page::PrintPage (ostream& os, const int margin)
{
	char margBuf[128];

    // build the margin string:
	for (int i = 0; i <= margin; ++i)     
		margBuf[i] = ' ';
	margBuf[i] = '\0';

	// print the left-most child:
    if (Left(0) != 0)
		Left(0)->PrintPage(os, margin + 8);

	// print page and remaining children:        
	for (i = 0; i < used; ++i) {
        os << margBuf;
		os << (*this)[i]  << '\n';
		if (Right(i) != 0)
			Right(i)->PrintPage(os, margin + 8);
	}
}

BTree::BTree (const int ord) : order(ord)
{
    root = 0;
    bufP = new Page(2 * order + 2);
}

void BTree::Insert (Key key, Data data)
{
    Item item(key, data), *receive;

    if (root == 0) {						// empty tree
        root = new Page(2 * order);
        root->InsertItem(item, 0);
    } else if ((receive = InsertAux(&item, root)) != 0) {
        Page *page = new Page(2 * order);	// new root
        page->InsertItem(*receive, 0);
        page->Left(0) = root;
        root = page;
    }
}

void BTree::Delete (Key key)
{
	Bool underflow;

	DeleteAux1(key, root, underflow);
	if (underflow && root->Used() == 0) {	// dispose root
		Page *temp = root;
		root = root->Left(0);
		delete temp;
    }
}

Bool BTree::Search (Key key, Data &data)
{
	Item *item = SearchAux(root, key);

    if (item == 0)
        return false;
    data = item->DataOf();
    return true;
}

ostream& operator << (ostream& os, BTree &tree)
{
	if (tree.root != 0)
    	tree.root->PrintPage(os, 0);
    return os;
}

// recursively free a page and its subtrees

void BTree::FreePages (Page *page)
{
    if (page != 0) {
		FreePages(page->Left(0));
		for (register i = 0; i < page->Used(); ++i)
			FreePages(page->Right(i));
		delete page;
	}
}

// recursively search the tree for an item with matching key
    
BTree::Item* BTree::SearchAux (Page *tree, Key key)
{
    int 	idx;
    Item	*item;

    if (tree == 0)
        return 0;
    if (tree->BinarySearch(key, idx))
		return &((*tree)[idx]);
    return SearchAux(idx < 0 ? tree->Left(0)
							 : tree->Right(idx), key);
}

// insert an item into a page and split the page if it overflows

BTree::Item* BTree::InsertAux (Item *item, Page *page)
{
	Page *child;
	int  idx;

	if (page->BinarySearch(item->KeyOf(), idx))
		return 0;                       	// already in tree

	if ((child = page->Right(idx)) != 0)
		item = InsertAux(item, child);   	// child is not a leaf

	if (item != 0) {                    	// page is a leaf, or passed up
		if (page->Used() < 2 * order) {		// insert in the page
			page->InsertItem(*item, idx + 1);
		} else {                          	// page is full, split
			Page *newP = new Page(2 * order);

			bufP->Used() = page->CopyItems(bufP, 0, 0, page->Used());
			bufP->InsertItem(*item, idx + 1);

            int size = bufP->Used();
            int half = size/2;

			page->Used() = bufP->CopyItems(page, 0, 0, half);
			newP->Used() = bufP->CopyItems(newP, half + 1, 0, size - half - 1);
			newP->Left(0) = bufP->Right(half);

			*item = (*bufP)[half];		// the mid item
			item->Subtree() = newP;
			return item;
		}
	}
	return 0;
}

// delete an item from a page and deal with underflows

void BTree::DeleteAux1 (Key key, Page *page, Bool &underflow)
{
	int  	idx;
    Page	*child;

	underflow = false;
	if (page == 0)
		return;

	if (page->BinarySearch(key, idx)) {
		if ((child = page->Left(idx)) == 0) {	// page is a leaf                                                    
			underflow = page->DeleteItem(idx);
		} else {								// page is a subtree
			// delete from subtree:
			DeleteAux2(page, child, idx, underflow);
			if (underflow)
				Underflow(page, child, idx - 1, underflow);
		}
	} else {									// is not on this page
		child = page->Right(idx);
		DeleteAux1(key, child, underflow);		// should be in child
		if (underflow)
			Underflow(page, child, idx, underflow);
	}
}

// delete an item and deal with underflows by borrowing
// items from neighboring pages or merging two pages

void BTree::DeleteAux2 (Page *parent,Page *page,
						const int idx, Bool &underflow)
{
	Page *child = page->Right(page->Used() - 1);

	if (child != 0) {							// page is not a leaf
		DeleteAux2(parent, child, idx, underflow); // go another level down
		if (underflow)
			Underflow(page, child, page->Used() - 1, underflow);
	} else {                                    // page is a leaf
    	// save right:
		Page *right = parent->Right(idx);
		// borrow an item from page for parent:
        page->CopyItems(parent, page->Used() - 1, idx, 1);
        // restore right:
		parent->Right(idx) = right;
		underflow = page->DeleteItem(page->Used() - 1);
	}
}

// handle underflows

void BTree::Underflow (Page *page, Page *child,
						int idx, Bool &underflow)
{
	Page *left = idx < page->Used() - 1 ? child : page->Left(idx);
	Page *right = left == child ? page->Right(++idx) : child;

	// copy contents of left, parent item, and right onto bufP:
	int size = left->CopyItems(bufP, 0, 0, left->Used());
	(*bufP)[size] = (*page)[idx];
	bufP->Right(size++) = right->Left(0);
	size += right->CopyItems(bufP, 0, size, right->Used());
   
	if (size > 2 * order) {
    	// distribute bufP items between left and right:
		int half = size/2;
		left->Used() = bufP->CopyItems(left, 0, 0, half);
		right->Used() = bufP->CopyItems(right, half + 1, 0, size - half - 1);
		right->Left(0) = bufP->Right(half);
		(*page)[idx] = (*bufP)[half];
		page->Right(idx) = right;
		underflow = false;
	} else {
		// merge, and free the right page:
		left->Used() = bufP->CopyItems(left, 0, 0, size);
		underflow = page->DeleteItem(idx);
		delete right;
	}
}

//-------------------------------------------------------------

class BStar : public BTree {
public:
				BStar		(const int order) : BTree(order) {}
virtual	void	Insert		(Key key, Data data);

protected:
virtual Item*	InsertAux	(Item *item, Page *page);
virtual Item*	Overflow	(Item *item, Page *page,
							 Page *child, int idx);
};

// insert with overflow/underflow handling

void BStar::Insert (Key key, Data data)
{
	Item item(key, data);
	Item *overflow;
	Page *left, *right;
	Bool dummy;

	if (root == 0) {			// empty tree
		root = new Page(2 * order);
		root->InsertItem(item, 0);
	} else if ((overflow = InsertAux(&item, root)) != 0) {
		left = root;			// root becomes a left child
		root = new Page(2 * order);
		right = new Page (2 * order);
		root->InsertItem(*overflow, 0);
		root->Left(0) = left;	// the left-most child of root 
		root->Right(0) = right;	// the right child of root
		right->Left(0) = overflow->Subtree();
		// right is underflown (size == 0):
		Underflow(root, right, 0, dummy);
	}
}

// inserts and deals with overflows

Item* BStar::InsertAux (Item *item, Page *page)
{
	Page *child;
	int  idx;

	if (page->BinarySearch(item->KeyOf(), idx))
		return 0;							// already in tree
	if ((child = page->Right(idx)) != 0) {
		// child not a leaf:
		if ((item = InsertAux(item, child)) != 0)    
			return Overflow(item, page, child, idx);
	} else if (page->Used() < 2 * order) {	// item fits in node
		page->InsertItem(*item, idx + 1);
	} else {								// node is full
		int size = page->Used(); 
		bufP->Used() = page->CopyItems(bufP, 0, 0, size);
		bufP->InsertItem(*item, idx + 1);
		bufP->CopyItems(page, 0, 0, size);
		*item = (*bufP)[size];
		return item;
	}
	return 0;
}

// handles underflows

Item* BStar::Overflow (Item *item, Page *page,
						Page *child, int idx)
{
    Page *left = idx < page->Used() - 1 ? child : page->Left(idx);
    Page *right = left == child ? page->Right(++idx) : child;

	// copy left, overflown and parent items, and right into buf: 
	bufP->Used() = left->CopyItems(bufP, 0, 0, left->Used());
	if (child == left ) {
    	bufP->InsertItem(*item, bufP->Used());
		bufP->InsertItem((*page)[idx], bufP->Used());
		bufP->Right(bufP->Used() - 1) = right->Left(0);
		bufP->Used() +=
				right->CopyItems(bufP, 0, bufP->Used(), right->Used());
	} else {
        bufP->InsertItem((*page)[idx], bufP->Used());
		bufP->Right(bufP->Used() - 1) = right->Left(0);
		bufP->Used() +=
				right->CopyItems(bufP, 0, bufP->Used(), right->Used());
        bufP->InsertItem(*item, bufP->Used());
	}
	if (bufP->Used() < 4 * order + 2) {
		// distribute buf between left and right:
        int size = bufP->Used(), half;

		left->Used() = bufP->CopyItems(left, 0, 0, half = size/2);
		right->Used() = bufP->CopyItems(right, half + 1, 0, size - half - 1);
		right->Left(0) = bufP->Right(half);
		(*page)[idx] = (*bufP)[half];
		page->Right(idx) = right;
		return 0;
	} else {
		// split int 3 pages:
		Page *newP = new Page(2 * order);
	    int  mid1, mid2;

		mid1 = left->Used() = bufP->CopyItems(left, 0, 0, (4 * order + 1) / 3);
		mid2 = right->Used() = bufP->CopyItems(right, mid1 + 1, 0, 4 * order / 3);
		mid2 += mid1 + 1;
		newP->Used() = bufP->CopyItems(newP, mid2 + 1, 0, (4 * order + 2) / 3);
		right->Left(0) = bufP->Right(mid1);
		bufP->Right(mid1) = right;
		newP->Left(0) = bufP->Right(mid2);
		bufP->Right(mid2) = newP;
		(*page)[idx] = (*bufP)[mid2];
		if (page->Used() < 2 * order) {
			page->InsertItem((*bufP)[mid1], idx);
			return 0;
		} else {
			*item = (*page)[page->Used() - 1];
            (*page)[page->Used() - 1] = (*bufP)[mid1];
			return item;
		}
	}
}

#include <stdlib.h>
#include <ctype.h>

int main (void)
{
    Key  	key, key1, key2;
    Data	data;
    char 	option[20];
    BStar 	tree(2);			// B-tree of order 2

    for (;;) {
        cout << "S)earch, I)nsert, D)elete, P)rint, Q)uit ? ";
        cin >> option;
        if (isupper(*option)) *option = tolower(*option);
        switch (*option) {
            case 's':   cout << "key? ";   cin >> key;
		               if (tree.Search(key, data))
		                  cout << "data = " << data << '\n';
                        else
                           cout << "no such item.\n";
                        break;
            case 'i':   cout << "key = from, to? ";
						cin >> key1 >> key2;
                        for (key = key1; key <= key2; ++key)
		                   tree.Insert(key, key+0.5);
                        break;
            case 'd':   cout << "key? ";
						cin >> key;
                        tree.Delete(key);
						break;
            case 'p':   cout << tree;
						break;
            case 'q':   exit(0);
         }
    }
}
