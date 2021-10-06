#pragma once 
#ifdef __cplusplus
extern "C" {
#endif

#define  _CRTDBG_MAP_ALLOC
#define _CRT_SECURE_NO_WARNINGS
#define Count 3
#include <crtdbg.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


	typedef struct list {
		struct list* Next;
		int count;
		int NumOfFilled;
		int* array;
	}list;

	void PrintList(list* Head);
	list* CreateList(int num);
	void AddToList(list* L, int key);
	void DestoyList(list* L);
	int FindKeyByNumber(list* L, int number);
	int Counter(list* L);
	int FindNumberByKey(list* L, int key);
	int FindNextByKey(list* L, int key);
	void DeleteByNumber(list* l, int number);

#ifdef __cplusplus
}
#endif