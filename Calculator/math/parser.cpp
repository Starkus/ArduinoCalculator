// 
// 
// 

#include "parser.h"
#include "../io.h"


#define NEGATIVE_SIGN '@'


#define OPERATOR_FROM(str, op, from)																			\
{																												\
	int op_index = str.indexOf(#op, from);																		\
	if (op_index != -1) {																						\
		return parse(str.substring(0, op_index), x) op parse(str.substring(op_index+1), x);						\
	}																											\
}

#define OPERATOR(str, op) OPERATOR_FROM(str, op, 0)

#define OPERATOR_TO_FUNCTION(str, op, func)																		\
{																												\
	int op_index = str.indexOf(op);																				\
																												\
	String pre_function = str.substring(0, op_index);															\
																												\
	if (op_index != -1) {																						\
		if (pre_function.length() != 0)																			\
			return parse(pre_function, x) * func(parse(str.substring(op_index+1), x));							\
																												\
		return func(parse(str.substring(op_index+1), x));														\
	}																											\
}																								

#define OPERATOR_TO_TWOARGFUNCTION(str, op, func)																\
{																												\
	int op_index = str.indexOf(op);																				\
	if (op_index != -1) {																						\
		return func(parse(str.substring(0, op_index), x), parse(str.substring(op_index+1), x));					\
	}																											\
}

#define FUNCTION(func)																							\
{																												\
	if (pre_parenthesis.endsWith(#func)) {																		\
		String pre_function = pre_parenthesis.substring(0, pre_parenthesis.indexOf(#func));						\
																												\
		return parse(pre_function + "(" + String(func(solved_parenthesis), 12) + ")" + post_parenthesis, x);	\
	}																											\
}

#define TWOARG_FUNCTION(func)																					\
{																												\
	if (pre_parenthesis.endsWith(#func)) {																		\
		String pre_function = pre_parenthesis.substring(0, pre_parenthesis.indexOf(#func));						\
																												\
		int comma_index = inside_parenthesis.indexOf(",");														\
		double arg1 = parse(inside_parenthesis.substring(0, comma_index), x);									\
		double arg2 = parse(inside_parenthesis.substring(comma_index+1),  x);									\
																												\
		return parse(pre_function + "(" + String(func(arg1, arg2), 12) + ")" + post_parenthesis, x);			\
	}																											\
}

#define FUNCTION_TO_FUNCTION(writtenfunc, targetfunc)															\
{																												\
	if (pre_parenthesis.endsWith(#writtenfunc)) {																\
		String pre_function = pre_parenthesis.substring(0, pre_parenthesis.indexOf(#writtenfunc));				\
																												\
		String solved_func = String(targetfunc(solved_parenthesis), 12);										\
		return parse(pre_function + "(" + solved_func + ")" + post_parenthesis, x);								\
	}																											\
}



double root(double n, double x) {
	return pow(x, 1.0/n);
}

double square(double x) {
	return x * x;
}



/*
	NOTE: I use 0x15 character to sign negative numbers, so it's different from
	the minus operator.
*/
double parse(String s, double x, double Ans) {

	// Previous answer
	int ans_index = s.indexOf("Ans");
	if (ans_index != -1) {
		String pre  = s.substring(0, ans_index);
		String post = s.substring(ans_index+3);

		s = pre + "(" + String(Ans, 12) + ")" + post;
	}

	// X
	int x_index = s.indexOf((char) CHAR_X);
	if (x_index != -1) {
		String pre  = s.substring(0, x_index);
		String post = s.substring(x_index+1);

		s = pre + "(" + String(x, 12) + ")" + post;
	}

	// PI
	int pi_index = s.indexOf((char) 127);
	if (pi_index != -1) {
		String pre  = s.substring(0, pi_index);
		String post = s.substring(pi_index+1);

		s = pre + "(" + String(PI, 12) + ")" + post;
	}

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
				float solved_parenthesis = parse(inside_parenthesis, x);
				String post_parenthesis = ss.substring(i + 1);

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
				FUNCTION(exp)

				FUNCTION_TO_FUNCTION(ln, log)
				FUNCTION_TO_FUNCTION(log, log10)
				
				TWOARG_FUNCTION(pow)
				TWOARG_FUNCTION(root)
				TWOARG_FUNCTION(atan2)
				TWOARG_FUNCTION(hypot)

				String operators = String("+-*/^%") + (char) CHAR_NROOT + (char) CHAR_SQRT + (char) CHAR_SQR;
				if (operators.indexOf(pre_parenthesis[pre_parenthesis.length()-1]) == -1) {
				pre_parenthesis += '*';
				}
				if (operators.indexOf(post_parenthesis[0]) == -1) {
				post_parenthesis = "*" + post_parenthesis;
				}

				String solved = String(solved_parenthesis, 12);
				if (solved_parenthesis < 0)
					solved.setCharAt(0, NEGATIVE_SIGN);

				return parse(pre_parenthesis + solved + post_parenthesis, x);
			}
		}
	}

	OPERATOR(s, +)
	OPERATOR(s, -)
	OPERATOR(s, *)
	OPERATOR(s, /)

	OPERATOR_TO_TWOARGFUNCTION(s, "^", pow)
	OPERATOR_TO_TWOARGFUNCTION(s, (char) CHAR_NROOT, root)
	OPERATOR_TO_TWOARGFUNCTION(s, "%", remainder)
	
	OPERATOR_TO_FUNCTION(s, (char) CHAR_SQRT, sqrt)

	// Square
	int s_index = s.indexOf((char) CHAR_SQR);
	if (s_index != -1) {
		String pre  = s.substring(0, s_index);
		String post = s.substring(s_index+1);

		if (post.length() == 0) {
			return square(parse(pre, x));
		} else {
			return parse("(" + String(square(parse(pre, x)), 12) + ")" + post, x);
		}
	}

	bool negative = s.startsWith(String(NEGATIVE_SIGN));
	if (negative)
		s = s.substring(1);

	double f = strtod(s.c_str(), NULL);
	if (negative)
		f *= -1;

	return f;
}