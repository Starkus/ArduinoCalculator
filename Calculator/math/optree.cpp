// 
// 
// 

#include "optree.h"
#include "newparser.h"


optree::optree() {
	root = nullptr;
}

optree::~optree() {
	wipe();
}

void optree::makeFromString(String s) {
	root = parse(s);
}

void optree::link(opnode* otherRoot) {
	/* This links the tree with another. However, since to
	 * modify a tree you should just wipe it clean first,
	 * all the trees linked to the wiped one would be left
	 * with a mere nullptr
	 */

	root = otherRoot;
}

double optree::execute(double x, double Ans) {
	return root->execute(x, Ans);
}

void optree::wipe() {
	wipe(root);
}

void optree::wipe(opnode* leaf) {
	if (leaf != nullptr) {
		wipe(leaf -> childA);
		wipe(leaf -> childB);
		delete leaf;
	}
}