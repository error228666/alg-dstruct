#include "pch.h"
#include "F21.h"

TEST(AddingTests, UpdateNumbersTest) 
{
	tree* t = (tree*)malloc(sizeof(tree));
	ASSERT_NE(t, nullptr);
	t->parent = NULL;
	t->key = 1;
	t->count_of_children = 1;
	t->number = 1;
	t->less = NULL;
	t->more = (tree*)malloc(sizeof(tree));
	ASSERT_NE(t->more, nullptr);
	t->more->parent = t;
	t->more->more = NULL;
	t->more->less = NULL;
	t->more->key = 2;
	t->more->number = 2;
	update_numbers(t);
	ASSERT_EQ(t->number, 2);
	ASSERT_EQ(t->more->number, 3);
	free(t->more);
	free(t);
}

TEST(AddingTests, AddingMore)
{
	tree* t = (tree*)malloc(sizeof(tree));
	ASSERT_NE(t, nullptr);
	t->parent = NULL;
	t->key = 2;
	t->count_of_children = 0;
	t->number = 1;
	t->less = NULL;
	t->more = NULL;
	add_to_tree(t, 3);
	ASSERT_EQ(t->more->key, 3);
	ASSERT_EQ(t->more->number, 1);
	ASSERT_EQ(t->more->parent, t);
	ASSERT_EQ(t->more->more, nullptr);
	ASSERT_EQ(t->more->less, nullptr);
	ASSERT_EQ(t->less, nullptr);

	free(t->more);
	free(t);


}

TEST(AddingTests, AddingLess)
{
	tree* t = (tree*)malloc(sizeof(tree));
	ASSERT_NE(t, nullptr);
	t->parent = NULL;
	t->key = 2;
	t->count_of_children = 0;
	t->number = 1;
	t->less = NULL;
	t->more = NULL;
	add_to_tree(t, 1);
	ASSERT_EQ(t->less->key, 1);
	ASSERT_EQ(t->less->number, 1);
	ASSERT_EQ(t->less->parent, t);
	ASSERT_EQ(t->less->more, nullptr);
	ASSERT_EQ(t->less->less, nullptr);
	ASSERT_EQ(t->more, nullptr);

	free(t->less);
	free(t);
}

TEST(AddingTests, AddingSame)
{
	tree* t = (tree*)malloc(sizeof(tree));
	ASSERT_NE(t, nullptr);
	t->parent = NULL;
	t->key = 2;
	t->count_of_children = 0;
	t->number = 1;
	t->less = NULL;
	t->more = NULL;
	add_to_tree(t, 2);
	ASSERT_EQ(t->more->key, 2);
	ASSERT_EQ(t->more->number, 1);
	ASSERT_EQ(t->more->parent, t);
	ASSERT_EQ(t->more->more, nullptr);
	ASSERT_EQ(t->more->less, nullptr);
	ASSERT_EQ(t->less, nullptr);

	free(t->more);
	free(t);
}


TEST(FindOrdinalTest, Root)
{
	tree* t = (tree*)malloc(sizeof(tree));
	ASSERT_NE(t, nullptr);
	t->parent = NULL;
	t->key = 3;
	t->count_of_children = 3;
	t->number = 1;
	t->less = NULL;

	tree* ptr = (tree*)malloc(sizeof(tree));
	t->more = ptr;
	ASSERT_NE(t->more, nullptr);
	t->more->parent = t;
	t->more->more = NULL;
	t->more->less = NULL;
	t->more->key = 4;
	t->more->number = 2;
	t->more->count_of_children = 0;

	t->less = (tree*)malloc(sizeof(tree));
	ASSERT_NE(t->less, nullptr);
	t->less->parent = t;
	t->less->count_of_children = 1;
	t->less->less = NULL;
	t->less->key = 1;
	t->less->number = 3;

	ptr = (tree*)malloc(sizeof(tree));
	t->less->more = ptr;
	ASSERT_NE(t->less->more, nullptr);
	t->less->more->parent = t->less;
	t->less->more->more = NULL;
	t->less->more->less = NULL;
	t->less->more->key = 2;
	t->less->more->number = 4;
	t->less->more->count_of_children = 0;


	ASSERT_EQ(3, find_ordinal(t));

	free(t->less->more);
	free(t->less);
	free(t->more);
	free(t);
}



TEST(FindOrdinalTest, Default)
{
	tree* t = (tree*)malloc(sizeof(tree));
	ASSERT_NE(t, nullptr);
	t->parent = NULL;
	t->key = 3;
	t->count_of_children = 3;
	t->number = 1;
	t->less = NULL;

	tree* ptr = (tree*)malloc(sizeof(tree));
	t->more = ptr;
	ASSERT_NE(t->more, nullptr);
	t->more->parent = t;
	t->more->more = NULL;
	t->more->less = NULL;
	t->more->key = 4;
	t->more->number = 2;
	t->more->count_of_children = 0;

	t->less = (tree*)malloc(sizeof(tree));
	ASSERT_NE(t->less, nullptr);
	t->less->parent = t;
	t->less->count_of_children = 1;
	t->less->less = NULL;
	t->less->key = 1;
	t->less->number = 3;

	ptr = (tree*)malloc(sizeof(tree));
	t->less->more = ptr;
	ASSERT_NE(t->less->more, nullptr);
	t->less->more->parent = t->less;
	t->less->more->more = NULL;
	t->less->more->less = NULL;
	t->less->more->key = 2;
	t->less->more->number = 4;
	t->less->more->count_of_children = 0;

	t->less->more = ptr;

	ASSERT_EQ(2, find_ordinal(t->less->more));

	free(t->less->more);
	free(t->less);
	free(t->more);
	free(t);
}



TEST(FindKMin, Default)
{
	tree* t = (tree*)malloc(sizeof(tree));
	ASSERT_NE(t, nullptr);
	t->parent = NULL;
	t->key = 3;
	t->count_of_children = 3;
	t->number = 1;
	t->less = NULL;

	tree* ptr = (tree*)malloc(sizeof(tree));
	t->more = ptr;
	ASSERT_NE(t->more, nullptr);
	t->more->parent = t;
	t->more->more = NULL;
	t->more->less = NULL;
	t->more->key = 4;
	t->more->number = 2;
	t->more->count_of_children = 0;

	t->less = (tree*)malloc(sizeof(tree));
	ASSERT_NE(t->less, nullptr);
	t->less->parent = t;
	t->less->count_of_children = 1;
	t->less->less = NULL;
	t->less->key = 1;
	t->less->number = 3;

	ptr = (tree*)malloc(sizeof(tree));
	t->less->more = ptr;
	ASSERT_NE(t->less->more, nullptr);
	t->less->more->parent = t->less;
	t->less->more->more = NULL;
	t->less->more->less = NULL;
	t->less->more->key = 2;
	t->less->more->number = 4;
	t->less->more->count_of_children = 0;

	ASSERT_EQ(t->less->more, find_k_min(t, 2));

	free(t->less->more);
	free(t->less);
	free(t->more);
	free(t);
}


TEST(FindKLessTests, ZeroK)
{
	tree* t = (tree*)malloc(sizeof(tree));
	ASSERT_NE(t, nullptr);
	t->parent = NULL;
	t->key = 3;
	t->count_of_children = 3;
	t->number = 1;
	t->less = NULL;

	tree* ptr = (tree*)malloc(sizeof(tree));
	t->more = ptr;
	ASSERT_NE(t->more, nullptr);
	t->more->parent = t;
	t->more->more = NULL;
	t->more->less = NULL;
	t->more->key = 4;
	t->more->number = 2;
	t->more->count_of_children = 0;

	t->less = (tree*)malloc(sizeof(tree));
	ASSERT_NE(t->less, nullptr);
	t->less->parent = t;
	t->less->count_of_children = 1;
	t->less->less = NULL;
	t->less->key = 1;
	t->less->number = 3;

	t->less->more = (tree*)malloc(sizeof(tree));
	ASSERT_NE(t->less->more, nullptr);
	t->less->more->parent = t->less;
	t->less->more->more = NULL;
	t->less->more->less = NULL;
	t->less->more->key = 2;
	t->less->more->number = 4;
	t->less->more->count_of_children = 0;

	int err;

	ASSERT_EQ(t, find_k_less(t, 0, &err));
	ASSERT_EQ(err, 0);

	free(t->less->more);
	free(t->less);
	free(t->more);
	free(t);
}

TEST(FindKLessTests, TooBigK)
{
	tree* t = (tree*)malloc(sizeof(tree));
	ASSERT_NE(t, nullptr);
	t->parent = NULL;
	t->key = 3;
	t->count_of_children = 3;
	t->number = 1;
	t->less = NULL;

	tree* ptr = (tree*)malloc(sizeof(tree));
	t->more = ptr;
	ASSERT_NE(t->more, nullptr);
	t->more->parent = t;
	t->more->more = NULL;
	t->more->less = NULL;
	t->more->key = 4;
	t->more->number = 2;
	t->more->count_of_children = 0;
	t->less = (tree*)malloc(sizeof(tree));

	ASSERT_NE(t->less, nullptr);
	t->less->parent = t;
	t->less->count_of_children = 1;
	t->less->less = NULL;
	t->less->key = 1;
	t->less->number = 3;

	ptr = (tree*)malloc(sizeof(tree));
	t->less->more = ptr;
	ASSERT_NE(t->less->more, nullptr);
	t->less->more->parent = t->less;
	t->less->more->more = NULL;
	t->less->more->less = NULL;
	t->less->more->key = 2;
	t->less->more->number = 4;
	t->less->more->count_of_children = 0;

	int err;

	ASSERT_EQ(nullptr, find_k_less(t, 10, &err));
	ASSERT_EQ(err, 1);


	free(t->less->more);
	free(t->less);
	free(t->more);
	free(t);
}

TEST(FindKLessTests, Default)
{
	tree* t = (tree*)malloc(sizeof(tree));
	ASSERT_NE(t, nullptr);
	t->parent = NULL;
	t->key = 3;
	t->count_of_children = 3;
	t->number = 1;
	t->less = NULL;
	tree* ptr = (tree*)malloc(sizeof(tree));
	t->more = ptr;
	ASSERT_NE(t->more, nullptr);
	t->more->parent = t;
	t->more->more = NULL;
	t->more->less = NULL;
	t->more->key = 4;
	t->more->number = 2;
	t->more->count_of_children = 0;
	t->less = (tree*)malloc(sizeof(tree));
	ASSERT_NE(t->less, nullptr);
	t->less->parent = t;
	t->less->count_of_children = 1;
	t->less->less = NULL;
	t->less->key = 1;
	t->less->number = 3;

	ptr = (tree*)malloc(sizeof(tree));
	t->less->more = ptr;
	ASSERT_NE(t->less->more, nullptr);
	t->less->more->parent = t->less;
	t->less->more->more = NULL;
	t->less->more->less = NULL;
	t->less->more->key = 2;
	t->less->more->number = 4;
	t->less->more->count_of_children = 0;

	t->less->more = ptr;
	int err;

	ASSERT_EQ(t->less->more, find_k_less(t, 1, &err));
	ASSERT_EQ(err, 0);


	free(t->less->more);
	free(t->less);
	free(t->more);
	free(t);
}





