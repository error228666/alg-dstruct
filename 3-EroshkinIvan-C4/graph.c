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



int push(queue* q, int data)
{
	if (q == NULL)
		return 2;
	list* new = (list*)malloc(sizeof(list));
	if (new == NULL)
		return 1;

	new->data = data;
	new->next = NULL;

	
	if (q->head == NULL)
	{
		q->head = new;
		q->tail = new;
	}
	else
	{
		q->tail->next = new;
		q->tail = q->tail->next;
	}
	return 0;
}

int pop(queue* q, int* data)
{
	list* tmp, *current;
	if (q == NULL)
		return 2;	

	if (q->tail == NULL) // no elements in queue
		return 3;
	
	*data = q->head->data;
	tmp = q->head;
	q->head = q->head->next;
	free(tmp);

	if (q->head == NULL)
		q->tail = NULL;

	return 0;



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
	{
		if (l[i].neighbors != NULL)
			free(l[i].neighbors);
	}
	free(l);
}

list_of_adjacency* making_list(FILE *stream, int *count_of_vertex, int *error)
{ 
	int i = 0;
	int* pointer;
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
		pointer = (int*)realloc(l[first_vertex].neighbors, l[first_vertex].count * sizeof(int));
		if (pointer != NULL)
			l[first_vertex].neighbors = pointer;
		else 
		{
			destroy_list_of_adjacency(l, *count_of_vertex);
			*error = 1;
			return NULL;
		}
		l[first_vertex].neighbors[l[first_vertex].count - 1] = second_vertex;


		l[second_vertex].count++;
		pointer = (int *)realloc(l[second_vertex].neighbors, l[second_vertex].count * sizeof(int));
		if (pointer != NULL)
			l[second_vertex].neighbors = pointer;
		else
		{
			destroy_list_of_adjacency(l, *count_of_vertex);
			*error = 1;
			return NULL;
		}
		l[second_vertex].neighbors[l[second_vertex].count - 1] = first_vertex;
	}
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
		*error = 1;
		return;
	}
	queue* q = (queue*)malloc(sizeof(queue));
	if (q == NULL)
	{
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
	destroy_list_of_adjacency(l);

}

