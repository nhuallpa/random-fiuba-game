#include "sequence.h"

Sequence::Sequence (const int size) : slots(size)
{
	entries = new String[size];
    used = 0;
}

void
Sequence::Insert (const char *str)
{
	if (used >= slots)
    	return;
    for (register i = 0; i < used; ++i) {
    	if (strcmp(str,entries[i]) < 0)
        	break;
    }
    for (register j = used; j > i; --j)
    	entries[j] = entries[j-1];
    entries[i] = new char[strlen(str) + 1];
    strcpy(entries[i], str);
    ++used;
}

void
Sequence::Delete (const char *str)
{
    for (register i = 0; i < used; ++i) {
    	if (strcmp(str,entries[i]) == 0) {
        	delete entries[i];
    		for (register j = i; j < used-1; ++j)
    			entries[j] = entries[j+1];
            --used;
        	break;
        }
    }
}

Bool
Sequence::Find (const char *str)
{
    for (register i = 0; i < used; ++i)
    	if (strcmp(str,entries[i]) == 0)
        	return true;
    return false;
}

void
Sequence::Print (void)
{
	cout << '[';
    for (register i = 0; i < used; ++i) {
    	cout << entries[i];
        if (i < used-1)
        	cout << ',';
    }
    cout << "]\n";
}

#ifndef _MAIN_

int
main (void)
{
	Sequence q(10);
    q.Insert("Sam");
    q.Insert("Neil");
    q.Insert("Adam");
    q.Insert("Jones");
    q.Insert("Alan");
    if (q.Find("Sam"))
    	cout << "contains Sam\n";
    q.Delete("Alan");
    q.Print();
    return 0;
}

#endif


