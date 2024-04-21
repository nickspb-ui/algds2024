#include "treap.h"

int main() {
	srand(1);
	char strToPrint[STRING_LENGTH] = "";
	Node* root = NULL;
	Node* left = NULL, * right = NULL;
	insert(&left, 1);
	insert(&right, 2);

	strcpy(strToPrint, "");
	getStrRepr(left, strToPrint);
	printf(strToPrint);
	printf("\n");

	strcpy(strToPrint, "");
	getStrRepr(right, strToPrint);
	printf(strToPrint);
	printf("\n");

	root = merge(left, right);
	
	strcpy(strToPrint, "");
	getStrRepr(root, strToPrint);
	printf(strToPrint);
	printf("\n");

	return 0;
}