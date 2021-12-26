#include "F21.h"


tree *create_tree(int key)
{
	tree* res = (tree*)malloc(sizeof(tree));
	if (res == NULL)
	{
		printf("memory error");
		return NULL;
	}
	res->key = key;
	res->less = NULL;
	res->more = NULL;
	res->parent = NULL;
	res->count_of_children = 0;
	return res;
}



void add_to_tree(tree* t, int key)
{
	if (t == NULL)
	{
		printf("null tree");
		return;
	}
	tree* new = (tree*)malloc(sizeof(tree));
	if (new == NULL)
	{ 
		printf("memory error");
		return;
	}
	new->key = key;
	new->count_of_children = 0;
	new->less = NULL;
	new->more = NULL;
	
	tree* ptr = t;
	tree* parent = NULL;
	while (ptr != NULL)
	{
		parent = ptr;
		ptr->count_of_children++;
		if (key < ptr->key)
			ptr = ptr->less;
		else
			ptr = ptr->more;
	}

	new->parent = parent;
	if (key < parent->key)
		parent->less = new;
	else
		parent->more = new;

}
void print_tree(tree* t, int n)
{
	int i;
	if (t != NULL)
	{
		print_tree(t->more, n + 1);
		for (i = 0; i < n; i++) putchar('  ');
		printf("%i\n", t->key);
		print_tree(t->less, n + 1);
	}
}

void destroy_tree(tree* t)
{
	
	if (t->less != NULL)
		destroy_tree(t->less);
	if (t->more != NULL)
		destroy_tree(t->more);
	if (t->less == NULL && t->more == NULL)
	{
		if (t->parent != NULL)
		{
			if (t->parent->less == t)
				t->parent->less = NULL;
			else
				t->parent->more = NULL;
		}
		free(t);

	}
}



int find_ordinal(tree* t)
{
	int result = 1;
	while (t != NULL)
	{
		if (t->less != NULL)
			result += 1 + t->less->count_of_children;
		if (t->parent == NULL)
			break;
		if (t->parent->more == t)
		{
			t = t->parent;
			result++;
		}
		else
			break;
	}
	return result;
}


tree* find_k_min(tree* t, int k)
{
	
	int r;
	if (t->less)
		r = t->less->count_of_children + 2;
	else
		r = 1;
	if (r != k)
	{
		if (k < r)
			t = find_k_min(t->less, k);
		else
			t = find_k_min(t->more, k - r);

	}
	return t;

}

tree *find_k_less(tree *t, int k, int *err)
{
	*err = 0;
	if (k == 0)
		return t;
	int ordinal = find_ordinal(t);
	int needfull_ordinal = ordinal - k;
	if (needfull_ordinal <= 0)
	{
		*err = 1;
		return NULL;
	}
	while (t->parent != NULL)
		t = t->parent;
	return find_k_min(t, needfull_ordinal);
}
/*
void main(void)
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	_CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_FILE);
	_CrtSetReportFile(_CRT_WARN, _CRTDBG_FILE_STDOUT);
	tree* t = create_tree(10);
	int err = 0;
	add_to_tree(t, 5);
	add_to_tree(t, 15);
	add_to_tree(t, 3);
	add_to_tree(t, 6);
	add_to_tree(t, 7);
	add_to_tree(t, 4);
	add_to_tree(t, 11);
	add_to_tree(t, 16);
	

	print_tree(t, 1);
	destroy_tree(t);
}
*/