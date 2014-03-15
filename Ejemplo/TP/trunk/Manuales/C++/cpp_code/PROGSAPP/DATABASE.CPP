typedef int Key;
typedef double Data;

class Database {
public:
	virtual	void	Insert	(Key&, Data&)	{}
	virtual	void	Delete	(Key&)			{}
	virtual	Data*	Search	(Key&)			{return 0;}
};