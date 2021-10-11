#pragma once 
#ifdef __cplusplus
extern "C" {
#endif

#define COUNT 3

#include <stdio.h>
#include <stdlib.h>
#include <time.h>


	typedef struct list {
		struct list* Next;
		int NumOfFilled;
		int Array[COUNT];
	}list;

	list* CreateList(int Num);
	int AddToList(list** L, int Key);
	void DestoyList(list* L);
	int FindKeyByNumber(list* L, int Number, int* Key);
	int Counter(list* L);
	int FindNumberByKey(list* L, int Key, int* Number);
	int FindNextByKey(list* L, int Key, int* NextKey);
	int DeleteByNumber(list** L, int Number);

#ifdef __cplusplus
}
#endif