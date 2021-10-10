#pragma once 
#ifdef __cplusplus
extern "C" {
#endif

#define  _CRTDBG_MAP_ALLOC
#define _CRT_SECURE_NO_WARNINGS


#include <crtdbg.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


	typedef struct list {
		struct list* Next;
		int NumOfFilled;
		int Array[3];
	}list;

	void PrintList(list* Head);
	list* CreateList(int Num);
	int AddToList(list* L, int Key);
	void DestoyList(list* L);
	int FindKeyByNumber(list* L, int Number, int* Key);
	int Counter(list* L);
	int FindNumberByKey(list* L, int Key, int* Number);
	int FindNextByKey(list* L, int Key, int* NextKey);
	int DeleteByNumber(list* L, int Number);

#ifdef __cplusplus
}
#endif