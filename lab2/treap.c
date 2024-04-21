#include "treap.h"

Node* createNode(int val, int priority) {
	Node* newNode = malloc(sizeof(Node));
	newNode->left = NULL;
	newNode->right = NULL;
	newNode->val = val;
	newNode->priority = priority;
	newNode->parent = NULL;
	return newNode;
}

void getStrRepr(Node* root, char* buffer) { // For testing -> (val,priority,leftNode,rightNode), '-' for NULL
	/* Represents nodes A(val = 2, priority = 1), B(1, 2), C(3, 3) as string
		A
	   / \    -> (2,1,(1,2,-,-),(3,3,-,-))
	  B   C
	*/

	char str[BUFFER_SIZE];

	if (!root) {
		strcat(buffer, "-");
		return;
	}
	sprintf(str, "(%d,%d,", root->val, root->priority);
	strcat(buffer, str);
	getStrRepr(root->left, buffer);
	strcat(buffer, ",");
	getStrRepr(root->right, buffer);
	strcat(buffer, ")");
}

void insert(Node** root, int val) {
	Node* cursor = *root;
	Node* lastNode = NULL;
	Node* x = NULL, * tmp = NULL;
	Node* lastCursorParent, * insertedNode = createNode(val, rand() % 100);

	int leftOrRight;

	if (!cursor) {
		(*root) = createNode(val, rand() % 100);
		return;
	}

	while (cursor) {
		lastNode = cursor;
		if (val <= cursor->val) {
			cursor = cursor->left;
			leftOrRight = 0;
		}
		else {
			cursor = cursor->right;
			leftOrRight = 1;
		}
	}

	cursor = insertedNode;
	insertedNode->parent = lastNode;
	if (leftOrRight) {
		lastNode->right = cursor;
	}
	else {
		lastNode->left = cursor;
	}

	while (insertedNode->parent) {
		cursor = insertedNode->parent;

		if (val <= cursor->val) {
			if (cursor->left->priority < cursor->priority) {
				// Right rotation
				x = cursor->left;
				tmp = x->right;

				if (cursor->parent) {
					leftOrRight = (cursor->parent->right == cursor);
				}

				x->right = cursor;
				cursor->left = tmp;
				if (tmp) {
					tmp->parent = cursor;
				}

				if (cursor->parent) {
					if (leftOrRight) {
						cursor->parent->right = x;
					}
					else {
						cursor->parent->left = x;
					}
				}

				x->parent = cursor->parent;
				cursor->parent = x;
			}
			else {
				return;
			}
		}
		else {
			if (cursor->right->priority < cursor->priority) {
				// Left rotation
				x = cursor->right;
				tmp = x->left;

				if (cursor->parent) {
					leftOrRight = (cursor->parent->right == cursor);
				}

				x->left = cursor;
				cursor->right = tmp;
				if (tmp) {
					tmp->parent = cursor;
				}

				if (cursor->parent) {
					if (leftOrRight) {
						cursor->parent->right = x;
					}
					else {
						cursor->parent->left = x;
					}
				}

				x->parent = cursor->parent;
				cursor->parent = x;
			}
			else {
				return;
			}
		}
	}
	(*root) = insertedNode;
}

Node* merge(Node* left, Node* right) {
	Node** lastFreeSpace = NULL, * lastFreeSpaceParent = NULL, * root = NULL;
	Node* cursor_left = left, * cursor_right = right;

	while (cursor_left && cursor_right) {
		if (cursor_left->priority < cursor_right->priority) {
			if (!root) {
				root = cursor_left;
				lastFreeSpace = &root->right;

				lastFreeSpaceParent = root;
			}
			else {
				cursor_left->parent = lastFreeSpaceParent;
				(*lastFreeSpace) = cursor_left;
				lastFreeSpace = &(*lastFreeSpace)->right;

				lastFreeSpaceParent = cursor_left;
			}
			cursor_left = cursor_left->right;
		}
		else {
			if (!root) {
				root = cursor_right;
				lastFreeSpace = &root->left;

				lastFreeSpaceParent = root;
			}
			else {
				cursor_right->parent = lastFreeSpaceParent;
				(*lastFreeSpace) = cursor_right;
				lastFreeSpace = &(*lastFreeSpace)->left;

				lastFreeSpaceParent = cursor_left;
			}
			cursor_right = cursor_right->left;
		}
	}
	if (!cursor_left) {
		cursor_right->parent = lastFreeSpaceParent;
		lastFreeSpaceParent->right = cursor_right;

		lastFreeSpace = cursor_right;
	}
	else {
		cursor_left->parent = lastFreeSpaceParent;
		lastFreeSpaceParent->left = cursor_left;

		lastFreeSpace = cursor_left;
	}
	return root;
}

void split(Node* root, int x, Node** leftSubTree, Node** rightSubTree) {
	Node* cursor = root;
	(*leftSubTree) = NULL;
	(*rightSubTree) = NULL;
	Node* lastLeft = NULL, * lastRight = NULL;

	while (cursor) {
		if (cursor->val <= x) {
			if (lastLeft != NULL) {				
				if (cursor->parent) {
					if (cursor->parent->left == cursor) {
						cursor->parent->left = NULL;
					}
					else {
						cursor->parent->right = NULL;
					}
				}
				lastLeft->right = cursor;
				cursor->parent = lastLeft;
			}
			else {
				(*leftSubTree) = cursor;
				if ((*leftSubTree)->parent) {
					(*leftSubTree)->parent->left = NULL;
					(*leftSubTree)->parent = NULL;
				}
			}
			lastLeft = cursor;
			cursor = cursor->right;
		}
		else {
			if (lastRight != NULL) {
				if (cursor->parent) {
					if (cursor->parent->left == cursor) {
						cursor->parent->left = NULL;
					}
					else {
						cursor->parent->right = NULL;
					}
				}
				lastRight->left = cursor;
				cursor->parent = lastRight;
			}
			else {
				(*rightSubTree) = cursor;
				if ((*rightSubTree)->parent) {
					(*rightSubTree)->parent->right = NULL;
					(*rightSubTree)->parent = NULL;
				}
			}
			lastRight = cursor;
			cursor = cursor->left;
		}
	}
}
