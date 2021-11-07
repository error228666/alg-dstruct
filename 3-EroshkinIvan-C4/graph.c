#include "graph.h"


void errors_consider(int error)
{
	switch (error)
	{
	case 1:
	{
		printf("memory error\n");
		break;
	}
	case 2:
	{
		printf("trying to work with null queue\n");
		break;
	}
	case 3:
	{
		printf("trying to pop empty queue\n");
		break;
	}
	default:
		break;
	}
}

int comparator(const void* val1, const void* val2)
{
	if (*(int *)val1 == *(int*)val2)
		return 0;
	if (*(int*)val1 > *(int*)val2)
		return 1;
	else
		return -1;
}

int push(queue* q, int data)
{
	if (q == NULL)
		return 2;
	list* new = (list*)malloc(sizeof(list));
	if (new == NULL)
		return 1;
	
	new->data = data;
	new->prev = NULL;
	new->next = q->head;
	if (q->head != NULL)
		q->head->prev = new;
	q->head = new;
	if (q->tail == NULL)
		q->tail = new;
	return 0;
}

int pop(queue* q, int* data)
{
	list* tmp;
	if (q == NULL)
		return 2;	

	if (q->tail == NULL) // no elements in queue
		return 3;
	
	*data = q->tail->data;
	if (q->head == q->tail) // single element
	{
		tmp = q->head;
		q->head = NULL;
		q->tail = NULL;
		free(tmp);
		return 0;
	}
	else
	{
		tmp = q->tail;
		q->tail = q->tail->prev;
		q->tail->next = NULL;
		free(tmp);
		return 0;
	}

}


void destroy_queue(queue* q)
{
	list* cur = q->head;
	list* tmp;
	while (cur != NULL)
	{
		tmp = cur;
		cur = cur->next;
		free(tmp);
	}
	free(q);
}


void destroy_list_of_adjacency(list_of_adjacency* l, int count_of_vertex)
{
	int i;
	for (i = 0; i < count_of_vertex; i++)
		free(l[i].neighbors);
		
	free(l);
}

list_of_adjacency* making_list(FILE *stream, int *count_of_vertex, int *error)
{ 
	int i = 0;
	int first_vertex, second_vertex;
	list_of_adjacency* l;

	fscanf(stream, "%d", count_of_vertex);
	
	l = (list_of_adjacency*)malloc(*count_of_vertex * sizeof(list_of_adjacency));
	if (l == NULL)
	{
		*error = 1;
		return NULL;
	}

	for (i = 0; i < *count_of_vertex; i++)
	{
		l[i].count = 0;
		l[i].neighbors = NULL;
	}
	while (fscanf(stream, "%d %d", &first_vertex, &second_vertex) != EOF)
	{
		
		l[first_vertex].count++;
		l[first_vertex].neighbors = (int *)realloc(l[first_vertex].neighbors, l[first_vertex].count * sizeof(int));
		if (l[first_vertex].neighbors == NULL)
		{
			for (i = 0; i < *count_of_vertex; i++)
			{
				if (l[i].neighbors != NULL)
					free(l[i].neighbors);
			}
			destroy_list_of_adjacency(l, *count_of_vertex);
			*error = 1;
			return NULL;
		}
		l[first_vertex].neighbors[l[first_vertex].count - 1] = second_vertex;

		
		l[second_vertex].count++;
		l[second_vertex].neighbors = (int *)realloc(l[second_vertex].neighbors, l[second_vertex].count * sizeof(int));
		if (l[second_vertex].neighbors == NULL)
		{
			for (i = 0; i < *count_of_vertex; i++)
			{
				if (l[i].neighbors != NULL)
					free(l[i].neighbors);
			}
			destroy_list_of_adjacency(l, *count_of_vertex);
			*error = 1;
			return NULL;
		}
		l[second_vertex].neighbors[l[second_vertex].count - 1] = first_vertex;
	}
	for (i = 0; i < *count_of_vertex; i++)
		qsort(l[i].neighbors, l[i].count, sizeof(int), comparator);
	*error = 0;
	return l;
}



void bfs(list_of_adjacency* l, int count_of_vertex, FILE *output_stream, int *error)
{
	int i, flag;
	int current;
	int* visited = (int *)malloc(sizeof(int) * count_of_vertex);
	if (visited == NULL)
	{
		destroy_list_of_adjacency(l, count_of_vertex);
		int* error = 1;
		return;
	}
	queue* q = (queue*)malloc(sizeof(queue));
	if (q == NULL)
	{
		destroy_list_of_adjacency(l, count_of_vertex);
		free(visited);
		*error = 1;
		return;
	}
	q->tail = NULL;
	q->head = NULL;
	for (i = 0; i < count_of_vertex; i++)
		visited[i] = 0;
	flag = push(q, 0);
	if (flag != 0)
	{
		free(q);
		free(visited);
		*error = flag;
		return;
	}
	visited[0] = 1;
	while (q->head != NULL)
	{
		flag = pop(q, &current);
		if (flag != 0)
		{
			destroy_queue(q);
			free(visited);
			*error = flag;
			return;
		}
		fprintf(output_stream, "%d ", current);

		for (i = 0; i < l[current].count; i++)
		{
			if (visited[l[current].neighbors[i]] == 0)
			{
				flag = push(q, l[current].neighbors[i]);
				if (flag != 0)
				{
					destroy_queue(q);
					free(visited);
					*error = flag;
					return;
				}
				visited[l[current].neighbors[i]] = 1;
			}
		}
	}
	*error = 0;
	destroy_queue(q);
	free(visited);
}



void lab()
{
	int count_of_vertex, error;
	list_of_adjacency* l = making_list(stdin, &count_of_vertex, &error);
	if (error != 0)
	{
		errors_consider(error);
		return;
	}
	bfs(l, count_of_vertex, stdout, &error);
	if (error != 0)
	{
		destroy_list_of_adjacency(l, count_of_vertex);
		errors_consider(error);
		return;
	}

}


