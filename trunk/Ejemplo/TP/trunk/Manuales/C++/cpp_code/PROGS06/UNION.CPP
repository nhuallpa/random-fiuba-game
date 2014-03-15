union Value;

class Pair {
public:
	//...
private:
	Value	*head;
	Value	*tail;
};

union Value {
	long	integer;
	double	real;
	char	*string;
	Pair	list;
	//...
};

class Object {
public:
	//...
private:
	enum ObjType {intObj, realObj, strObj, listObj};
	ObjType type;
	Value	val;
};
