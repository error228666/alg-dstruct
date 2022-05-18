#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct Tree
{
	int keys[3];
	int size;
	struct Tree* first;
	struct Tree* second;
	struct Tree* third;
	struct Tree* fourth;
	struct Tree* parent; 
}Tree;

Tree* init_tree(int key)
{
	Tree* result = (Tree*)malloc(sizeof(Tree));
	if (result == NULL)
	{
		printf("memory error");
		return NULL;
	}
	
	result->keys[0] = key;
	result->size = 1;
	
	result->first = NULL;
	result->second = NULL;
	result->third = NULL;
	result->fourth = NULL;
	result->parent = NULL;
	
	return result;
}


Tree* node(int key, Tree* first, Tree* second, Tree* third, Tree* fourth, Tree* parent)
{
	Tree* result = (Tree*)malloc(sizeof(Tree));
	if (result == NULL)
	{
		printf("memory error");
		return NULL;
	}
	result->size = 1;
	result->first = first;
	result->second = second; 
	result->third = third;
	result->fourth = fourth;
	result->parent = parent;
	result->keys[0] = key;
	return result;
}


int find(Tree * node,int k) 
{ 
    for (int i = 0; i < node->size; ++i)
        if (node->keys[i] == k) 
			return 1;
    return 0;
}

void swap(int* x, int* y) 
{
    int r = *x;
    *x = *y;
    *y = r;
}

void sort2(int* x, int* y) 
{
	if (*x > *y)
		swap(x, y);
}

void sort3(int* x, int* y, int* z) 
{
	if (*x > *y)
		swap(x, y);
	if (*x > *z)
		swap(x, z);
	if (*y > *z)
		swap(y, z);
}


void sort(Tree* node) 
{
	
	if (node->size == 1)
		return;
	if (node->size == 2)
		sort2(&(node->keys[0]), &(node->keys[1]));
	if (node->size == 3)
		sort3(&(node->keys[0]), &(node->keys[1]), &(node->keys[2]));
}


void insert_to_node(Tree* node, int k) 
{ 
	if (node == NULL)
		return;
	node->keys[node->size] = k;
    node->size++;
    sort(node);
}

void remove_from_node(Tree* node,int k) 
{   
	if (node == NULL)
		return;
	if (node->size >= 1 && node->keys[0] == k)
	{
        node->keys[0] = node->keys[1];
        node->keys[1] = node->keys[2];
		node->size--;
    }
    else if (node->size == 2 && node->keys[1] == k)
	{
        node->keys[1] = node->keys[2];
		node->size--;
	}
}

void become_node2(int k, Tree* node, Tree* first, Tree* second) 
{
	node->keys[0] = k; 
    node->first = first;
    node->second = second;
    node->third = NULL;
    node->fourth = NULL;
    node->parent = NULL;
    node->size = 1;
}

int is_leaf(Tree *node) 
{   
	if (node == NULL)
		return 0;
	if ((node->first == NULL) && (node->second == NULL) && (node->third == NULL))
		return 1;
	else
		return 0;
}

Tree* search(Tree* tree, int k)
{ 
	if (tree == NULL) 
		return NULL;

	if (find(tree, k)) 
		return tree;

	else if (k < tree->keys[0]) 
		return search(tree->first, k);
	
	else if ((tree->size == 2) && (k < tree->keys[1]) || (tree->size == 1)) 
		return search(tree->second, k);
	
	else if (tree->size == 2) 
		return search(tree->third, k);
}

Tree* split(Tree* item)
{
	if (item->size < 3) 
		return item;

	Tree* x = node(item->keys[0], item->first, item->second, NULL, NULL, item->parent); // —оздаем две новые вершины,
	if (x == NULL)
	{
		printf("memory error");
		return NULL;
	}
	Tree* y = node(item->keys[2], item->third, item->fourth, NULL, NULL, item->parent);  // которые имеют такого же родител€, как и раздел€ющийс€ элемент.
	if (y == NULL)
	{
		printf("memory error");
		free(x);
		return NULL;
	}

	if (x->first != NULL)  
		x->first->parent = x; 
	
	if (x->second != NULL)
		x->second->parent = x;
	
	if (y->first != NULL)
		y->first->parent = y;    
	
	if (y->second != NULL)
		y->second->parent = y;

	if (item->parent != NULL)
	{
		insert_to_node(item->parent,item->keys[1]);

		if (item->parent->first == item) 
			item->parent->first = NULL;
		else if (item->parent->second == item) 
			item->parent->second = NULL;
		else if (item->parent->third == item) 
			item->parent->third = NULL;

		
		if (item->parent->first == NULL) 
		{
			item->parent->fourth = item->parent->third;
			item->parent->third = item->parent->second;
			item->parent->second = y;
			item->parent->first = x;
		}
		else if (item->parent->second == NULL) 
		{
			item->parent->fourth = item->parent->third;
			item->parent->third = y;
			item->parent->second = x;
		}
		else 
		{
			item->parent->fourth = y;
			item->parent->third = x;
		}

		Tree* tmp = item->parent;
		free(item);
		return tmp;
	}
	else 
	{
		x->parent = item;   
		y->parent = item;   
		become_node2(item->keys[1],item, x, y);
		return item;
	}
}


Tree* insert_into_tree(Tree* tree, int k) 
{ 
	if (tree == NULL) 
		return init_tree(k); 
	
	if (search(tree, k))
		return tree;
	
	if (is_leaf(tree) != NULL)
		insert_to_node(tree, k);
	else if (k < tree->keys[0]) 
		insert_into_tree(tree->first, k);
	else if ((tree->size == 1) || ((tree->size == 2) && k <= tree->keys[1])) 
		insert_into_tree(tree->second, k);
	else 
		insert_into_tree(tree->third, k);

	return split(tree);
}

Tree* search_min(Tree* p) 
{ 
	if (p == NULL) 
		return p;
	if (p->first == NULL) 
		return p;
	else 
		return search_min(p->first);
}

Tree* redistribute(Tree* leaf)
{
	if (leaf == NULL)
		return NULL;

	Tree* parent = leaf->parent;
	Tree* first = parent->first;
	Tree* second = parent->second;
	Tree* third = parent->third;

	if ((parent->size == 2) && (first->size < 2) && (second->size < 2) && (third->size < 2))
	{
		if (first == leaf) 
		{
			parent->first = parent->second;
			parent->second = parent->third;
			parent->third = NULL;
			insert_to_node(parent->first,parent->keys[0]);
			parent->first->third = parent->first->second;
			parent->first->second = parent->first->first;

			if (leaf->first != NULL) 
				parent->first->first = leaf->first;
			else if (leaf->second != NULL) 
				parent->first->first = leaf->second;

			if (parent->first->first != NULL) 
				parent->first->first->parent = parent->first;

			remove_from_node(parent, parent->keys[0]);
			free(first);
		}
		else if (second == leaf)
		{
			insert_to_node(first, parent->keys[0]);
			remove_from_node(parent, parent->keys[0]);
			if (leaf->first != NULL) 
				first->third = leaf->first;
			else if (leaf->second != NULL) 
				first->third = leaf->second;

			if (first->third != NULL) 
				first->third->parent = first;

			parent->second = parent->third;
			parent->third = NULL;

			free(second);
		}
		else if (third == leaf) 
		{
			insert_to_node(second, parent->keys[1]);
			parent->third = NULL;
			remove_from_node(parent, parent->keys[1]);
			if (leaf->first != NULL) 
				second->third = leaf->first;
			else if 
				(leaf->second != NULL) second->third = leaf->second;

			if (second->third != NULL)  
				second->third->parent = second;

			free(third);
		}
	}
	else if ((parent->size == 2) && ((first->size == 2) || (second->size == 2) || (third->size == 2))) 
	{
		if (third == leaf)
		{
			if (leaf->first != NULL)
			{
				leaf->second = leaf->first;
				leaf->first = NULL;
			}

			insert_to_node(leaf, parent->keys[1]);
			if (second->size == 2) 
			{
				parent->keys[1] = second->keys[1];
				remove_from_node(second, second->keys[1]);
				leaf->first = second->third;
				second->third = NULL;
				if (leaf->first != NULL) 
					leaf->first->parent = leaf;
			}
			else if (first->size == 2) 
			{
				parent->keys[1] = second->keys[0];
				leaf->first = second->second;
				second->second = second->first;
				if (leaf->first != NULL) 
					leaf->first->parent = leaf;

				second->keys[0] = parent->keys[0];
				parent->keys[0] = first->keys[1];
				remove_from_node(first, first->keys[1]);
				second->first = first->third;
				if (second->first != NULL) 
					second->first->parent = second;
				first->third = NULL;
			}
		}
		else if (second == leaf)
		{
			if (third->size == 2) 
			{
				if (leaf->first == NULL) 
				{
					leaf->first = leaf->second;
					leaf->second = NULL;
				}
				insert_to_node(second,parent->keys[1]);
				parent->keys[1] = third->keys[0];
				remove_from_node(third, third->keys[0]);
				second->second = third->first;
				if (second->second != NULL)
					second->second->parent = second;
				third->first = third->second;
				third->second = third->third;
				third->third = NULL;
			}
			else if (first->size == 2) 
			{
				if (leaf->second == NULL) 
				{
					leaf->second = leaf->first;
					leaf->first = NULL;
				}
				insert_to_node(second, parent->keys[0]);
				parent->keys[0] = first->keys[1];
				remove_from_node(first, first->keys[1]);
				second->first = first->third;
				if (second->first != NULL) 
					second->first->parent = second;
				first->third = NULL;
			}
		}
		else if (first == leaf) 
		{
			if (leaf->first == NULL) 
			{
				leaf->first = leaf->second;
				leaf->second = NULL;
			}
			insert_to_node(first, parent->keys[0]);
			if (second->size == 2)
			{
				parent->keys[0] = second->keys[0];
				remove_from_node(second, second->keys[0]);
				first->second = second->first;
				if (first->second != NULL) 
					first->second->parent = first;
				second->first = second->second;
				second->second = second->third;
				second->third = NULL;
			}
			else if (third->size == 2)
			{
				parent->keys[0] = second->keys[0];
				second->keys[0] = parent->keys[1];
				parent->keys[1] = third->keys[0];
				remove_from_node(third, third->keys[0]);
				first->second = second->first;
				if (first->second != NULL) 
					first->second->parent = first;
				second->first = second->second;
				second->second = third->first;
				if (second->second != NULL) 
					second->second->parent = second;
				third->first = third->second;
				third->second = third->third;
				third->third = NULL;
			}
		}
	}
	else if (parent->size == 1)
 {
		insert_to_node(leaf, parent->keys[0]);

		if (first == leaf && second->size == 2) 
		{
			parent->keys[0] = second->keys[0];
			remove_from_node(second, second->keys[0]);

			if (leaf->first == NULL) 
				leaf->first = leaf->second;

			leaf->second = second->first;
			second->first = second->second;
			second->second = second->third;
			second->third = NULL;
			if (leaf->second != NULL) leaf->second->parent = leaf;
		}
		else if (second == leaf && first->size == 2) 
		{
			parent->keys[0] = first->keys[1];
			remove_from_node(first, first->keys[1]);

			if (leaf->second == NULL) leaf->second = leaf->first;

			leaf->first = first->third;
			first->third = NULL;
			if (leaf->first != NULL) leaf->first->parent = leaf;
		}
	}
	return parent;
}

Tree* merge(Tree* leaf) 
{
	if (leaf == NULL)
		return NULL;
	Tree* parent = leaf->parent;

	if (parent->first == leaf) 
	{
		insert_to_node(parent->second, parent->keys[0]);
		parent->second->third = parent->second->second;
		parent->second->second = parent->second->first;

		if (leaf->first != NULL)
			parent->second->first = leaf->first;
		else if (leaf->second != NULL)
			parent->second->first = leaf->second;

		if (parent->second->first != NULL) 
			parent->second->first->parent = parent->second;

		remove_from_node(parent, parent->keys[0]);
		free(parent->first);
		parent->first = NULL;
	}
	else if (parent->second == leaf)
	{
		insert_to_node(parent->first, parent->keys[0]);

		if (leaf->first != NULL) 
			parent->first->third = leaf->first;
		else if (leaf->second != NULL) 
			parent->first->third = leaf->second;

		if (parent->first->third != NULL) 
			parent->first->third->parent = parent->first;

		remove_from_node(parent, parent->keys[0]);
		free(parent->second);
		parent->second = NULL;
	}

	if (parent->parent == NULL) 
	{
		Tree* tmp = NULL;
		if (parent->first != NULL) tmp = parent->first;
		else tmp = parent->second;
		tmp->parent = NULL;
		free(parent);
		return tmp;
	}
	return parent;
}

Tree* fix(Tree* leaf)
{
	if (leaf == NULL)
		return NULL;
	if (leaf->size == 0 && leaf->parent == NULL) 
	{
		free(leaf);
		return NULL;
	}
	if (leaf->size != 0) 
	{
		if (leaf->parent != NULL) 
			return fix(leaf->parent);
		else return leaf;
	}

	Tree* parent = leaf->parent;
	if (parent->first->size == 2 || parent->second->size == 2 || parent->size == 2)
		leaf = redistribute(leaf); 
	else if (parent->size == 2 && parent->third->size == 2) 
		leaf = redistribute(leaf); 
	else 
		leaf = merge(leaf);
	return fix(leaf);
}

Tree* remove_from_tree(Tree* root, int k)
{
	if (root == NULL)
		return NULL;
	Tree* item = search(root, k); 

	if (!item)
		return root;

	Tree* min = NULL;
	if (item->keys[0] == k)
		min = search_min(item->second);
	else
		min = search_min(item->third);

	if (min)
	{ 
		int* z = (k == item->keys[0] ? &(item->keys[0]) : &(item->keys[1]));
		swap(z, &(min->keys[0]));
		item = min;
	}

	remove_from_node(item, k);
	return fix(item);
}


void destroy_tree(Tree* tree)
{
	if (!tree)
		return;
	destroy_tree(tree->first);
	destroy_tree(tree->second);
	destroy_tree(tree->third);
	free(tree);
}

void print_tree(Tree* tree, int n)
{
	int i;
	if (tree == NULL) 
		return;

	print_tree(tree->first, n + 2);
	for (i = 0; i < n; i++)
		printf("  ");

	printf("%d", tree->keys[0]);
	printf("\n");
	print_tree(tree->second, n + 2);
	
	for (int i = 0; i < n; i++)
		printf("  ");
	if (tree->size == 2) 
		printf("%d", tree->keys[1]);
	printf("\n");
	print_tree(tree->third, n + 2);
}


void lab()
{
	Tree* t = NULL;
	char command[16] = " ", ch;
	int key;
	while (fgets(command, 16, stdin)) 
	{
		sscanf(command, "%c%i", &ch, &key);
		switch (ch) 
		{
		case 'a':
			t = insert_into_tree(t, key);
			break;
		case 'r':
			t = remove_from_tree(t, key);
			break;
		case 'f':
			if (search(t, key))
				fprintf(stdout, "yes\n");
			else
				fprintf(stdout, "no\n");
			break;
		case 'p':
			print_tree(t, 1);
			fprintf(stdout, "\n");
			break;
		default:
			destroy_tree(t);
			return 0;
		}
	}
	destroy_tree(t);
	return 0;
}



int main()
{

	lab();


}