#include <gtest/gtest.h>

extern "C" {
	#include "treap.h"
}

TEST(nodeInsertion, singleNode) {
	srand(1);
	Node* root = NULL;
	insert(&root, 1);

	char testStr[STRING_LENGTH] = "";
	getStrRepr(root, testStr);
	EXPECT_STREQ("(1,67,-,-)", testStr);
}

TEST(nodeInsertion, multipleNodes) {
	srand(1);
	Node* root = NULL;
	insert(&root, 1);
	insert(&root, 2);
	insert(&root, 3);
	insert(&root, 4);
	insert(&root, 5);
	insert(&root, 6);
	insert(&root, 7);
	
	char testStr[STRING_LENGTH] = "";
	getStrRepr(root, testStr);
	EXPECT_STREQ("(3,0,(2,34,(1,67,-,-),-),(5,24,(4,69,-,-),(7,58,(6,78,-,-),-)))", testStr);
}

TEST(treeMerge, generalMerge) {
	srand(1);
	Node* root = NULL, * left = NULL, * right = NULL;
	insert(&left, 1);
	insert(&left, 2);
	insert(&left, 3);
	insert(&left, 4);
	insert(&right, 5);
	insert(&right, 6);
	insert(&right, 7);
	root = merge(left, right);

	char testStr[STRING_LENGTH] = "";
	getStrRepr(root, testStr);
	EXPECT_STREQ("(3,0,(2,34,(1,67,-,-),-),(6,58,(4,69,-,(5,78,-,-)),(7,62,-,-)))", testStr);
}

TEST(treeMerge, mergeSingleNodes) {
	srand(1);
	Node* root = NULL, * left = NULL, * right = NULL;
	insert(&left, 1);
	insert(&right, 2);
	root = merge(left, right);

	char testStr[STRING_LENGTH] = "";
	getStrRepr(root, testStr);
	EXPECT_STREQ("(2,0,(1,67,-,-),-)", testStr);
}

TEST(treeSplit, splitByCenter) {
	srand(1);
	Node* root = NULL, *left = NULL, *right = NULL;
	insert(&root, 1);
	insert(&root, 2);
	insert(&root, 3);
	insert(&root, 4);
	insert(&root, 5);
	insert(&root, 6);
	insert(&root, 7);
	split(root, 4, &left, &right);

	char testStrLeft[STRING_LENGTH] = "", testStrRight[STRING_LENGTH] = "";
	getStrRepr(left, testStrLeft);
	getStrRepr(right, testStrRight);
	EXPECT_STREQ("(3,0,(2,34,(1,67,-,-),-),(4,69,-,-))", testStrLeft);
	EXPECT_STREQ("(5,24,-,(7,58,(6,78,-,-),-))", testStrRight);
}

TEST(treeSplit, splitByBorder) {
	srand(1);
	Node* root = NULL, * left = NULL, * right = NULL;
	insert(&root, 1);
	insert(&root, 2);
	insert(&root, 3);
	insert(&root, 4);
	insert(&root, 5);
	insert(&root, 6);
	insert(&root, 7);
	split(root, 0, &left, &right);

	char testStrLeft[STRING_LENGTH] = "", testStrRight[STRING_LENGTH] = "";
	getStrRepr(left, testStrLeft);
	getStrRepr(right, testStrRight);
	EXPECT_STREQ("-", testStrLeft);
	EXPECT_STREQ("(3,0,(2,34,(1,67,-,-),-),(5,24,(4,69,-,-),(7,58,(6,78,-,-),-)))", testStrRight);
}
