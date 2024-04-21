#pragma once
#define BUFFER_SIZE 32
#define STRING_LENGTH 128
#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>

 typedef struct Node {
	int val;
	int priority;
	struct Node* left;
	struct Node* right;
	struct Node* parent;
} Node;

Node* createNode(int, int);

void getStrRepr(Node*, char*);
void split(Node*, int, Node**, Node**);
Node* merge(Node*, Node*);
void insert(Node**, int);
