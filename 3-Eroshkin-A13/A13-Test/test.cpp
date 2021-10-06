#include "pch.h"
#include "List13.h"

TEST(CreateList, Creation) 
{
	list* L = CreateList(1);
	ASSERT_NE(L, nullptr);
	EXPECT_EQ(1, L->array[0]);
	EXPECT_EQ(1, L->NumOfFilled);
	EXPECT_EQ(Count, L->count);	
	EXPECT_EQ(nullptr, L->Next);
	DestoyList(L); 
}

TEST(AddToList, Default)
{
	list* L = (list*)malloc(sizeof(list));
	L->array = (int*)malloc(sizeof(int) * Count);
	L->array[0] = 1;
	L->NumOfFilled = 1;
	L->count = Count;
	L->Next = NULL;
	AddToList(L, 2);
	ASSERT_NE(L, nullptr);
	EXPECT_EQ(2, L->array[1]);
	EXPECT_EQ(2, L->NumOfFilled);
	EXPECT_EQ(Count, L->count);
	EXPECT_EQ(nullptr, L->Next);
	DestoyList(L);
}
TEST(AddToList, AddingNewArray)
{
	int num = Count + 1;
	int i;
	list* L = (list*)malloc(sizeof(list));
	L->array = (int*)malloc(sizeof(int) * Count);
	for (i = 0; i < Count; i++)
	{
		L->array[i] = i + 1;
	}
	L->NumOfFilled = Count;
	L->count = Count;
	L->Next = NULL;
	AddToList(L, num);
	ASSERT_NE(L->Next, nullptr);
	EXPECT_EQ(num, L->Next->array[0]);
	EXPECT_EQ(1, L->Next->NumOfFilled);
	EXPECT_EQ(Count, L->count);
	EXPECT_EQ(nullptr, L->Next->Next);
	DestoyList(L);

}
TEST(Counter, EmptyList)
{
	list* L = NULL;
	ASSERT_EQ(0, Counter(L));
}

TEST(Counter, Counting)
{
	int i;
	list* L = (list*)malloc(sizeof(list));
	L->array = (int*)malloc(sizeof(int) * Count);
	for (i = 0; i < Count; i++)
	{
		L->array[i] = i + 1;
	}
	L->Next = (list*)malloc(sizeof(list));
	L->Next->array = (int*)malloc(sizeof(int) * Count);
	L->Next->array[0] = i + 2;
	L->NumOfFilled = Count;
	L->Next->NumOfFilled = 1;
	L->count = Count;
	L->Next->count = Count;
	L->Next->Next = NULL;
	ASSERT_EQ(i + 1, Counter(L));
	DestoyList(L);
}
TEST(FindKeyByNumber, Default)
{
	list* L = (list*)malloc(sizeof(list));
	L->array = (int*)malloc(sizeof(int) * Count);
	L->array[0] = 1;
	L->array[1] = 2; 
	L->array[2] = 3;
	L->Next = (list*)malloc(sizeof(list));
	L->Next->array = (int*)malloc(sizeof(int) * Count);
	L->Next->array[0] = 4;
	L->Next->array[1] = 5;
	L->Next->array[2] = 6;
	L->NumOfFilled = Count;
	L->Next->NumOfFilled = Count;
	L->count = Count;
	L->Next->count = Count;
	L->Next->Next = NULL;
	ASSERT_EQ(5, FindKeyByNumber(L, 5));
	DestoyList(L);
}

TEST(FindKeyByNumber, OutOfRange_expect0)
{
	list* L = (list*)malloc(sizeof(list));
	L->array = (int*)malloc(sizeof(int) * Count);
	L->array[0] = 1;
	L->array[1] = 2;
	L->array[2] = 3;
	L->NumOfFilled = Count;
	L->count = Count;
	L->Next = NULL;
	ASSERT_EQ(0, FindKeyByNumber(L, 4));
}

TEST(FindNumberByKey, Default)
{
	list* L = (list*)malloc(sizeof(list));
	L->array = (int*)malloc(sizeof(int) * Count);
	L->array[0] = 1;
	L->array[1] = 2;
	L->array[2] = 3;
	L->Next = (list*)malloc(sizeof(list));
	L->Next->array = (int*)malloc(sizeof(int) * Count);
	L->Next->array[0] = 4;
	L->Next->array[1] = 5;
	L->Next->array[2] = 6;
	L->NumOfFilled = Count;
	L->Next->NumOfFilled = Count;
	L->count = Count;
	L->Next->count = Count;
	L->Next->Next = NULL;
	ASSERT_EQ(5, FindNumberByKey(L, 5));
	DestoyList(L);
}

TEST(FindNumberByKey, OutOfRange_expect0)
{
	list* L = (list*)malloc(sizeof(list));
	L->array = (int*)malloc(sizeof(int) * Count);
	L->array[0] = 1;
	L->array[1] = 2;
	L->array[2] = 3;
	L->NumOfFilled = Count;
	L->count = Count;
	L->Next = NULL;
	ASSERT_EQ(0, FindNumberByKey(L, 4));
}

TEST(FindNextByKey, Default)
{
	list* L = (list*)malloc(sizeof(list));
	L->array = (int*)malloc(sizeof(int) * Count);
	L->array[0] = 1;
	L->array[1] = 2;
	L->array[2] = 3;
	L->Next = (list*)malloc(sizeof(list));
	L->Next->array = (int*)malloc(sizeof(int) * Count);
	L->Next->array[0] = 4;
	L->Next->array[1] = 5;
	L->Next->array[2] = 6;
	L->NumOfFilled = Count;
	L->Next->NumOfFilled = Count;
	L->count = Count;
	L->Next->count = Count;
	L->Next->Next = NULL;
	ASSERT_EQ(6, FindNextByKey(L, 5));
	DestoyList(L);
}

TEST(FindNextByKey, ResaultInNextNode)
{
	list* L = (list*)malloc(sizeof(list));
	L->array = (int*)malloc(sizeof(int) * Count);
	L->array[0] = 1;
	L->array[1] = 2;
	L->array[2] = 3;
	L->Next = (list*)malloc(sizeof(list));
	L->Next->array = (int*)malloc(sizeof(int) * Count);
	L->Next->array[0] = 4;
	L->Next->NumOfFilled = 1;
	L->NumOfFilled = Count;
	L->count = Count;
	L->Next->count = Count;
	L->Next->Next = NULL;
	ASSERT_EQ(4, FindNextByKey(L, 3));
	DestoyList(L);

}

TEST(DeleteByNumber, Default)
{
	list* L = (list*)malloc(sizeof(list));
	L->array = (int*)malloc(sizeof(int) * Count);
	L->Next = (list*)malloc(sizeof(list));
	L->Next->array = (int*)malloc(sizeof(int) * Count);
	L->array[0] = 1;
	L->array[1] = 2;
	L->array[2] = 3;
	L->Next->array[0] = 4;
	L->Next->array[1] = 5;
	L->Next->NumOfFilled = 2;
	L->Next->count = Count;
	L->count = Count;
	L->NumOfFilled = 3;
	L->Next->Next = NULL;
	DeleteByNumber(L, 2);
	ASSERT_EQ(L->array[0], 1);
	ASSERT_EQ(L->array[1], 3);
	ASSERT_EQ(L->array[2], 4);
	ASSERT_EQ(L->Next->array[0], 5);
	ASSERT_EQ(L->Next->NumOfFilled, 1);
	ASSERT_EQ(L->Next->Next, nullptr);
	DestoyList(L);
}

TEST(DeleteByNumber, DeletingLastKeyInNode)	
{
	list* L = (list*)malloc(sizeof(list));
	L->array = (int*)malloc(sizeof(int) * Count);
	L->array[0] = 1;
	L->array[1] = 2;
	L->array[2] = 3;
	L->Next = (list*)malloc(sizeof(list));
	L->Next->array = (int*)malloc(sizeof(int) * Count);
	L->Next->array[0] = 4;
	L->count = Count;
	L->NumOfFilled = 3;
	L->Next->NumOfFilled = 1;
	L->Next->Next = NULL;
	DeleteByNumber(L, 3);
	ASSERT_EQ(L->array[0], 1);
	ASSERT_EQ(L->array[1], 2);
	ASSERT_EQ(L->array[2], 4);
	ASSERT_EQ(L->Next, nullptr);
	ASSERT_EQ(L->NumOfFilled, 3);
	DestoyList(L);
}
TEST(DeleteByNumber, DeletingSingleKeyInLastNode)
{
	list* L = (list*)malloc(sizeof(list));
	L->array = (int*)malloc(sizeof(int) * Count);
	L->array[0] = 1;
	L->array[1] = 2;
	L->array[2] = 3;
	L->Next = (list*)malloc(sizeof(list));
	L->Next->array = (int*)malloc(sizeof(int) * Count);
	L->Next->array[0] = 4;
	L->count = Count;
	L->NumOfFilled = 3;
	L->Next->NumOfFilled = 1;
	L->Next->Next = NULL;
	DeleteByNumber(L, 4);
	ASSERT_EQ(L->array[0], 1);
	ASSERT_EQ(L->array[1], 2);
	ASSERT_EQ(L->array[2], 3);
	ASSERT_EQ(L->Next, nullptr);
	ASSERT_EQ(L->NumOfFilled, 3);
	DestoyList(L);
}


