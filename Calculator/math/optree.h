// optree.h

#ifndef _OPTREE_h
#define _OPTREE_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif


#define EXECUTE_F execute(double x=nan(nullptr), double Ans=0)

#define FUNCTION_NODE(func)\
class _##func : public opnode\
{\
	double EXECUTE_F {\
		return func(childA->execute(x, Ans));\
	}\
};

#define FUNCTION2_NODE(func)\
class _##func : public opnode\
{\
	double EXECUTE_F {\
		return func(childA->execute(x, Ans), childB->execute(x, Ans));\
	}\
};


class opnode {
	public:
	
	double arg;
	opnode* childA;
	opnode* childB;
	virtual double execute(double x=nan(nullptr), double Ans=0);
};

namespace node {

class cons : public opnode {
	double EXECUTE_F {
		return (arg);
	}
};

class _x : public opnode {
	double EXECUTE_F {
		return (x);
	}
};

class _pi : public opnode {
	double EXECUTE_F {
		return PI;
	}
};

class _e : public opnode {
	double EXECUTE_F {
		return EULER;
	}
};

class _Ans : public opnode {
	double EXECUTE_F {
		return (Ans);
	}
};

class sum : public opnode {
	double EXECUTE_F {
		return childA->execute(x, Ans) + childB->execute(x, Ans);
	}
};

class rest : public opnode {
	double EXECUTE_F {
		return childA->execute(x, Ans) - childB->execute(x, Ans);
	}
};

class mult : public opnode {
	double EXECUTE_F {
		return childA->execute(x, Ans) * childB->execute(x, Ans);
	}
};

class div : public opnode {
	double EXECUTE_F {
		return childA->execute(x, Ans) / childB->execute(x, Ans);
	}
};

class mod : public opnode {
	double EXECUTE_F {
		return remainder(childA->execute(x, Ans), childB->execute(x, Ans));
	}
};

class nroot : public opnode {
	double EXECUTE_F {
		return pow(childB->execute(x, Ans), 1.0 / childA->execute(x, Ans));
	}
};

class sqr : public opnode {
	double EXECUTE_F {
		double a = childA->execute(x, Ans);
		return a * a;
	}
};

class _ln : public opnode {
	double EXECUTE_F {
		return log(childA->execute(x, Ans));
	}
};

class _log : public opnode {
	double EXECUTE_F {
		return log10(childA->execute(x, Ans));
	}
};

FUNCTION_NODE(sqrt);
FUNCTION_NODE(cbrt);
FUNCTION_NODE(sin);
FUNCTION_NODE(cos);
FUNCTION_NODE(tan);
FUNCTION_NODE(asin);
FUNCTION_NODE(acos);
FUNCTION_NODE(atan);
FUNCTION_NODE(sinh);
FUNCTION_NODE(cosh);
FUNCTION_NODE(tanh);
FUNCTION_NODE(asinh);
FUNCTION_NODE(acosh);
FUNCTION_NODE(atanh);
FUNCTION_NODE(log2);
FUNCTION_NODE(exp);
FUNCTION_NODE(abs);
FUNCTION_NODE(floor);
FUNCTION_NODE(ceil);
FUNCTION_NODE(round);

FUNCTION2_NODE(pow);
FUNCTION2_NODE(atan2);
FUNCTION2_NODE(hypot);

}



class optree {
	public:
	optree();
	~optree();

	void makeFromString(String);
	void link(opnode*);

	double execute(double x=nan(nullptr), double Ans=0);
	void wipe();

	private:
	void wipe(opnode* leaf);

	opnode* root;
};


#endif

