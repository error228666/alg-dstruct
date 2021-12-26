#pragma once 
#ifdef __cplusplus
extern "C" {
#endif

#define _CRTDBG_MAP_ALLOC
#define _CRT_SECURE_NO_WARNINGS
#include <crtdbg.h>
#include <stdio.h>

	typedef struct tree {
		int key;
		int count_of_children;
		struct tree* less;
		struct tree* more;
		struct tree* parent;
	}tree;

	tree* create_tree(int key);
	void add_to_tree(tree* t, int key);
	void print_tree(tree* t, int n);
	void destroy_tree(tree* t);
	int find_ordinal(tree* t);
	tree* find_k_min(tree* t, int k);
	tree* find_k_less(tree* t, int k, int* err);

#ifdef __cplusplus
}
#endif
