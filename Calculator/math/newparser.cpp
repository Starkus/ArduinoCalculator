/*
 * newparser.cpp
 *
 * Created: 14/5/2017 20:04:48
 *  Author: emili
 */ 

#include "newparser.h"
#include "../io.h"


String operators = String("+-*/^%") + CHAR_NROOT + CHAR_SQRT;


opnode* newNodeFromOperator(char op) {
	switch (op)
	{
	case '+':
		return new node::sum();
	case '-':
		return new node::rest();
	case '*':
		return new node::mult();
	case '/':
		return new node::div();
	case '^':
		return new node::_pow();
	case '%':
		return new node::mod();
	case CHAR_NROOT:
		return new node::nroot();
	case CHAR_SQRT:
		return new node::_sqrt();
	case CHAR_SQR:
		return new node::sqr();
	}
}

#define OPERATOR(op)\
{\
	int op_index = s.indexOf(op);\
	if (op_index != -1) {\
		opnode* node = newNodeFromOperator(op);\
		node->childA = parse(s.substring(0, op_index));\
		node->childB = parse(s.substring(op_index+1));\
		return node;\
	}\
}

#define FUNCTION(func)\
{\
	if (pre_parenthesis.endsWith(#func)) {\
		pre_parenthesis = pre_parenthesis.substring(0, pre_parenthesis.indexOf(#func));\
		\
		solved_par = new node::_##func();\
		solved_par->childA = parse(inside_parenthesis);\
	}\
}

#define FUNCTION2(func)\
{\
	if (pre_parenthesis.endsWith(#func)) {\
		pre_parenthesis = pre_parenthesis.substring(0, pre_parenthesis.indexOf(#func));\
		\
		int comma_index = inside_parenthesis.indexOf(",");\
		\
		solved_par = new node::_##func();\
		solved_par->childA = parse(inside_parenthesis.substring(0, comma_index));\
		solved_par->childB = parse(inside_parenthesis.substring(comma_index + 1));\
	}\
}

#define VARIABLE(var, _node)\
{\
	int var_len = String(var).length();\
	int var_index = s.indexOf(var);\
	\
	if (var_index != -1) {\
		String prevar = s.substring(0, var_index);\
		String postvar = s.substring(var_index + var_len);\
		\
		bool pre  =  prevar.length() > 0;\
		bool post = postvar.length() > 0;\
		\
		if (pre && post) {\
			opnode* a = new node::mult();\
			opnode* b = new node::mult();\
			\
			a->childA = parse(prevar);\
			a->childB = new node::_node();\
			\
			b->childA = a;\
			b->childB = parse(postvar);\
			\
			return b;\
		}\
		else if (pre) {\
			opnode* r = new node::mult();\
			r->childA = parse(prevar);\
			r->childB = new node::_node();\
			\
			return r;\
		}\
		else if (post) {\
			opnode* r = new node::mult();\
			r->childA = new node::_node();\
			r->childB = parse(postvar);\
			\
			return r;\
		}\
		return new node::_node();\
	}\
}


opnode* parse(String s) {

	// Parenthesis
	int begin_index = s.indexOf('(');
	if (begin_index != -1) {
		
		String pre_parenthesis = s.substring(0, begin_index);
		String ss = s.substring(begin_index + 1);

		int levels = 0;

		for (int i=0; i < ss.length(); ++i) {
			
			if (ss[i] == '(')
				++levels;
			else if (ss[i] == ')')
				--levels;

			if (levels == -1) {
				
				String inside_parenthesis = ss.substring(0, i);
				String post_parenthesis = ss.substring(i + 1);

				opnode* solved_par = nullptr;

				char pre_op, post_op;

				
				FUNCTION(abs)
				FUNCTION(floor)
				FUNCTION(ceil)
				FUNCTION(round)
				FUNCTION(sqrt)
				FUNCTION(cbrt)
				FUNCTION(sinh)
				FUNCTION(cosh)
				FUNCTION(tanh)
				FUNCTION(asin)
				FUNCTION(acos)
				FUNCTION(atan)
				FUNCTION(asinh)
				FUNCTION(acosh)
				FUNCTION(atanh)
				FUNCTION(sin)
				FUNCTION(cos)
				FUNCTION(tan)
				FUNCTION(log2)
				FUNCTION(log)
				FUNCTION(ln)
				FUNCTION(exp)
				
				FUNCTION2(pow)
				FUNCTION2(atan2)
				FUNCTION2(hypot)


				if (solved_par == nullptr) {
					solved_par = parse(inside_parenthesis);
				}


				pre_op = pre_parenthesis[pre_parenthesis.length()-1];
				if (operators.indexOf(pre_op) == -1) {
					pre_op = '*';
				} else {
					pre_parenthesis = pre_parenthesis.substring(0, pre_parenthesis.length()-1);
				}

				post_op = post_parenthesis[0];
				if (operators.indexOf(post_op) == -1) {
					post_op = '*';
				} else {
					post_parenthesis = post_parenthesis.substring(1);
				}

				opnode *a, *b;

				bool pre  =  pre_parenthesis.length() > 0;
				bool post = post_parenthesis.length() > 0;

				// If we only got what's inside the parenthesis, just
				// parse that.
				if (!pre && !post) {
					return solved_par;
				}

				if (pre)
					a = newNodeFromOperator(pre_op);
				if (post)
					b = newNodeFromOperator(post_op);

				// If there's something before the parenthesis, fill
				// node A with (Pre, Inside).
				if (pre) {
					a->childA = parse(pre_parenthesis);
					a->childB = solved_par;
					// And if that's it, return A.
					if (!post)
						return a;

					// Else, we put A in a branch of B.
					b->childA = a;
				} else {
					// Or if only post-par, just the inside.
					b->childA = solved_par;
				}
				// Then the post-par in the other branch of B.
				b->childB = parse(post_parenthesis);

				// And return B which contains A (if it exists).
				return b;
			}
		}
	}
	
	OPERATOR('+')
	OPERATOR('-')
	OPERATOR('*')
	OPERATOR('/')
	OPERATOR('^')
	OPERATOR('%')

	OPERATOR(CHAR_NROOT)
	OPERATOR(CHAR_SQRT)
	OPERATOR(CHAR_SQR)

	// Variables
	
	VARIABLE(CHAR_X, _x);
	VARIABLE("Ans", _Ans);
	VARIABLE(CHAR_PI, _pi);
	VARIABLE("e", _e);

	// Literal
	opnode* node = new node::cons();
	node->arg = strtod(s.c_str(), NULL);
	return node;
}

double parseOnce(String s) {
	optree* tree = new optree;

	tree->makeFromString(s);
	double result = tree->execute();

	delete tree;

	return result;
}