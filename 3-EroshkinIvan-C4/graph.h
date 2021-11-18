#pragma once
#ifdef __cplusplus
extern "C" {
#endif

#define _CRT_SECURE_NO_WARNINGS
#include <time.h>
#include <stdio.h>
#include <stdlib.h>


typedef struct
{
	int count;
	int* neighbors;
}list_of_adjacency;

typedef struct list
{
	int data;
	struct list* next;

}list;

typedef struct 
{
	list *head;
	list* tail;
}queue;

void errors_consider(int error);

int push(queue* q, int data);
int pop(queue* q, int* data);
void destroy_queue(queue* q);

list_of_adjacency* making_list(FILE* stream, int* count_of_vertex, int* error);
void destroy_list_of_adjacency(list_of_adjacency* l, int count_of_vertex);


void bfs(list_of_adjacency* l, int count_of_vertex, FILE* output_stream, int* error);

void lab();

#ifdef __cplusplus
}
#endif 