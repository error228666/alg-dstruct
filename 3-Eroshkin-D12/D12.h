#pragma once 
#ifdef __cplusplus
extern "C" {
#endif


#define _CRTDBG_MAP_ALLOC
#define _CRT_SECURE_NO_WARNINGS
#include <crtdbg.h>
#include <stdio.h>
#include <stdlib.h>

	typedef struct vertex
	{
		int num;
		int degree;
		int count_of_colors;
		int* colors;
		int is_colored;
	}vertex;

	typedef struct color
	{
		int num;
		int count;
	}color;
	void lab(char* input_name, char* output_name);
	int color_comparator(const void* val1, const void* val2);
	int color_comparator1(color* val1, color* val2);
	int vertex_comparator(const void* val1, const void* val2);
	int vertex_comparator1(vertex* val1, vertex* val2);
#ifdef __cplusplus
}
#endif