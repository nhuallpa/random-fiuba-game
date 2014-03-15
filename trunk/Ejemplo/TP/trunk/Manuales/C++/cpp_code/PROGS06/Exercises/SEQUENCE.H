#ifndef _SEQUENCE_
#define _SEQUENCE_

#include <iostream.h>
#include <string.h>

// enum Bool {false, true};
typedef char *String;

class BinNode;
class BinTree;

class Sequence {
public:
				Sequence	(const int size);
                ~Sequence	(void)		{delete entries;}
	void		Insert		(const char*);
	void		Delete		(const char*);
	Bool		Find		(const char*);
	void		Print		(void);
    int			Size		(void)	{return used;}
friend	BinNode* BinTree::MakeTree (Sequence &seq, int low, int high);

protected:
	char		**entries;		// sorted array of string entries
    const int	slots;			// number of sequence slots
	int			used;			// number of slots used so far			
};

#endif