#include "pch.h"
#include "List13.h"

TEST(CreateList, Creation)
{
	list* L = CreateList(1);

	ASSERT_NE(L, nullptr);
	EXPECT_EQ(1, L->Array[0]);
	EXPECT_EQ(1, L->NumOfFilled);
	EXPECT_EQ(nullptr, L->Next);

	free(L);
}

TEST(AddToList, Default_return1)
{
	list* L = (list*)malloc(sizeof(list));
	ASSERT_NE(L, nullptr);

	L->Array[0] = 1;
	L->NumOfFilled = 1;
	L->Next = NULL;

	EXPECT_EQ(AddToList(&L, 2), 1);
	ASSERT_NE(L, nullptr);
	EXPECT_EQ(2, L->Array[1]);
	EXPECT_EQ(2, L->NumOfFilled);
	EXPECT_EQ(nullptr, L->Next);

	free(L);
}
TEST(AddToList, EmptyList_return1)
{
	list* L = NULL;

	ASSERT_EQ(1, AddToList(&L, 1));
	ASSERT_NE(L, nullptr);
	ASSERT_EQ(1, L->Array[0]);
	
	free(L);
}

TEST(AddToList, AddingNewArray_return1)
{
	int num = 4;

	list* L = (list*)malloc(sizeof(list));
	ASSERT_NE(L, nullptr);

	L->Array[0] = 1;
	L->Array[1] = 2;
	L->Array[2] = 3;
	L->NumOfFilled = 3;
	L->Next = NULL;

	EXPECT_EQ(AddToList(&L, 4), 1);
	ASSERT_NE(L->Next, nullptr);
	EXPECT_EQ(4, L->Next->Array[0]);
	EXPECT_EQ(1, L->Next->NumOfFilled);
	EXPECT_EQ(nullptr, L->Next->Next);

	free(L->Next);
	free(L);

}
TEST(Counter, EmptyList_return0)
{
	list* L = NULL;
	ASSERT_EQ(0, Counter(L));
}

TEST(Counter, Default_return4)
{
	list* L = (list*)malloc(sizeof(list));
	ASSERT_NE(L, nullptr);
	L->Next = (list*)malloc(sizeof(list));
	ASSERT_NE(L->Next, nullptr);
	
	L->Array[0] = 1;
	L->Array[1] = 2;
	L->Array[2] = 3;
	L->Next->Array[0] = 4;
	L->NumOfFilled = 3;
	L->Next->NumOfFilled = 1;
	L->Next->Next = NULL;

	ASSERT_EQ(4, Counter(L));

	free(L->Next);
	free(L);
}
TEST(FindKeyByNumber, Default_return1)
{
	int Key;
	list* L = (list*)malloc(sizeof(list));
	ASSERT_NE(L, nullptr);
	L->Next = (list*)malloc(sizeof(list));
	ASSERT_NE(L->Next, nullptr);

	L->Array[0] = 1;
	L->Array[1] = 2;
	L->Array[2] = 3;
	
	L->Next->Array[0] = 4;
	L->Next->Array[1] = 5;
	L->Next->Array[2] = 6;
	L->NumOfFilled = 3;
	L->Next->NumOfFilled = 3;
	L->Next->Next = NULL;

	ASSERT_EQ(1, FindKeyByNumber(L, 5, &Key));
	ASSERT_EQ(Key, 5);

	free(L->Next);
	free(L);
}

TEST(FindKeyByNumber, OutOfRange_return0)
{
	int Key;
	list* L = (list*)malloc(sizeof(list));
	ASSERT_NE(L, nullptr);

	L->Array[0] = 1;
	L->Array[1] = 2;
	L->Array[2] = 3;
	L->NumOfFilled = 3;
	L->Next = NULL;

	ASSERT_EQ(0, FindKeyByNumber(L, 4, &Key));

	free(L);
}

TEST(FindNumberByKey, Default_return1)
{
	int Number;
	list* L = (list*)malloc(sizeof(list));
	ASSERT_NE(L, nullptr);
	L->Next = (list*)malloc(sizeof(list));
	ASSERT_NE(L->Next, nullptr);

	L->Array[0] = 1;
	L->Array[1] = 2;
	L->Array[2] = 3;
	L->Next->Array[0] = 4;
	L->Next->Array[1] = 5;
	L->Next->Array[2] = 6;
	L->NumOfFilled = 3;
	L->Next->NumOfFilled = 3;
	L->Next->Next = NULL;

	ASSERT_EQ(1, FindNumberByKey(L, 5, &Number));
	ASSERT_EQ(5, Number);

	free(L->Next);
	free(L);
}

TEST(FindNumberByKey, OutOfRange_expect0)
{
	int Number;
	list* L = (list*)malloc(sizeof(list));
	ASSERT_NE(L, nullptr);

	L->Array[0] = 1;
	L->Array[1] = 2;
	L->Array[2] = 3;
	L->NumOfFilled = 3;
	L->Next = NULL;

	ASSERT_EQ(0, FindNumberByKey(L, 4, &Number));

	free(L);
}

TEST(FindNextByKey, Default_return1)
{
	int NextKey;
	list* L = (list*)malloc(sizeof(list));
	ASSERT_NE(L, nullptr);
	L->Next = (list*)malloc(sizeof(list));
	ASSERT_NE(L->Next, nullptr);

	L->Array[0] = 1;
	L->Array[1] = 2;
	L->Array[2] = 3;
	L->Next->Array[0] = 4;
	L->Next->Array[1] = 5;
	L->Next->Array[2] = 6;
	L->NumOfFilled = 3;
	L->Next->NumOfFilled = 3;
	L->Next->Next = NULL;

	ASSERT_EQ(1, FindNextByKey(L, 5, &NextKey));
	ASSERT_EQ(6, NextKey);

	free(L->Next);
	free(L);
}

TEST(FindNextByKey, ResaultInNextNode_return1)
{
	int NextKey;
	list* L = (list*)malloc(sizeof(list));
	ASSERT_NE(L, nullptr);
	L->Next = (list*)malloc(sizeof(list));
	ASSERT_NE(L->Next, nullptr);

	L->Array[0] = 1;
	L->Array[1] = 2;
	L->Array[2] = 3;
	L->Next->Array[0] = 4;
	L->Next->NumOfFilled = 1;
	L->NumOfFilled = 3;
	L->Next->Next = NULL;

	ASSERT_EQ(1, FindNextByKey(L, 3, &NextKey));
	ASSERT_EQ(4, NextKey);

	free(L->Next);
	free(L);

}

TEST(FindNextByKey, OutOfRange_return0)
{
	int NextKey;
	list* L = (list*)malloc(sizeof(list));
	ASSERT_NE(L, nullptr);
	

	L->Array[0] = 1;
	L->Array[1] = 2;
	L->Array[2] = 3;
	L->NumOfFilled = 3;
	L->Next = NULL;

	ASSERT_EQ(0, FindNextByKey(L, 4, &NextKey));

	free(L);

}


TEST(DeleteByNumber, Default_return1)
{
	list* L = (list*)malloc(sizeof(list));
	ASSERT_NE(L, nullptr);
	L->Next = (list*)malloc(sizeof(list));
	ASSERT_NE(L->Next, nullptr);

	L->Array[0] = 1;
	L->Array[1] = 2;
	L->Array[2] = 3;
	L->Next->Array[0] = 4;
	L->Next->Array[1] = 5;
	L->Next->NumOfFilled = 2;
	L->NumOfFilled = 3;
	L->Next->Next = NULL;

	ASSERT_EQ(1, DeleteByNumber(&L, 2));
	ASSERT_EQ(L->Array[0], 1);
	ASSERT_EQ(L->Array[1], 3);
	ASSERT_EQ(L->NumOfFilled, 2);
	ASSERT_EQ(L->Next->Array[0], 4);
	ASSERT_EQ(L->Next->NumOfFilled, 2);
	ASSERT_EQ(L->Next->Next, nullptr);

	free(L->Next);
	free(L);
}


TEST(DeleteByNumber, DeletingSingleKeyInLastNode_return1)
{
	list* L = (list*)malloc(sizeof(list));
	ASSERT_NE(L, nullptr);
	L->Next = (list*)malloc(sizeof(list));
	ASSERT_NE(L->Next, nullptr);

	L->Array[0] = 1;
	L->Array[1] = 2;
	L->Array[2] = 3;
	L->Next->Array[0] = 4;
	L->NumOfFilled = 3;
	L->Next->NumOfFilled = 1;
	L->Next->Next = NULL;

	ASSERT_EQ(1, DeleteByNumber(&L, 4));
	ASSERT_EQ(L->Array[0], 1);
	ASSERT_EQ(L->Array[1], 2);
	ASSERT_EQ(L->Array[2], 3);
	ASSERT_EQ(L->Next, nullptr);
	ASSERT_EQ(L->NumOfFilled, 3);

	free(L->Next);
	free(L);
}

TEST(DeleteByNumber, DeletingSingleElementInHead_return1)
{
	list* L = (list*)malloc(sizeof(list));
	ASSERT_NE(L, nullptr);
	L->Next = (list*)malloc(sizeof(list));
	ASSERT_NE(L->Next, nullptr);

	L->Array[0] = 1;
	L->Next->Array[0] = 2;
	L->NumOfFilled = 1;
	L->Next->NumOfFilled = 1;
	L->Next->Next = NULL;

	ASSERT_EQ(1, DeleteByNumber(&L, 1));
	ASSERT_EQ(L->Array[0], 2);
	ASSERT_EQ(L->Next, nullptr);
	ASSERT_EQ(L->NumOfFilled, 1);
	free(L->Next);
	free(L);
}

TEST(DeleteByNumber, DeletingSingleElementNotInHead_return1)
{
	list* L = (list*)malloc(sizeof(list));
	ASSERT_NE(L, nullptr);
	L->Next = (list*)malloc(sizeof(list));
	ASSERT_NE(L->Next, nullptr);
	L->Next->Next = (list*)malloc(sizeof(list));
	ASSERT_NE(L->Next->Next, nullptr);

	L->Array[0] = 1;
	L->Next->Array[0] = 2;
	L->Next->Next->Array[0] = 3;
	L->NumOfFilled = 1;
	L->Next->NumOfFilled = 1;
	L->Next->Next->NumOfFilled = 1;
	L->Next->Next->Next = NULL;

	ASSERT_EQ(1, DeleteByNumber(&L, 2));
	ASSERT_EQ(L->Array[0], 1);
	ASSERT_EQ(L->Next->Array[0], 3);
	ASSERT_EQ(L->Next->Next, nullptr);
	ASSERT_EQ(L->NumOfFilled, 1);
	ASSERT_EQ(L->Next->NumOfFilled, 1);

	free(L->Next);
	free(L);
}

TEST(DeleteByNumber, OutOfRange_return0)
{
	list* L = (list*)malloc(sizeof(list));
	ASSERT_NE(L, nullptr);
	L->Next = (list*)malloc(sizeof(list));
	ASSERT_NE(L->Next, nullptr);

	L->Array[0] = 1;
	L->Next->Array[0] = 2;
	L->NumOfFilled = 1;
	L->Next->NumOfFilled = 1;
	L->Next->Next = NULL;

	ASSERT_EQ(0, DeleteByNumber(&L, 3));

	free(L->Next);
	free(L);
}

TEST(DeleteByNumber, DeletingList_return1)
{
	list* L = (list*)malloc(sizeof(list));
	ASSERT_NE(L, nullptr);

	L->Array[0] = 1;
	L->NumOfFilled = 1;
	L->Next = NULL;

	ASSERT_EQ(1, DeleteByNumber(&L, 1));
	ASSERT_EQ(nullptr, L);
}