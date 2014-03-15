typedef int		Key;
typedef	double	Data;
enum Bool { false, true };

class Database {
public:
virtual	void	Insert	(Key key, Data data)	{}
virtual	void	Delete	(Key key)				{}
virtual	Bool	Search	(Key key, Data &data)	{return false;}
};
