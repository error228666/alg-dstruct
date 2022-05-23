#define _CRT_SECURE_NO_WARNINGS



#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int table_size = 100000;

typedef struct Node 
{
	char *str;
	struct Node* next;

}Node;

void Destroy_List(Node* head)
{
	Node* next = NULL;
	Node* cur = head;
	while (cur != NULL)
	{
		next = cur->next;
		free(cur->str);
		free(cur);
		cur = next;
	}

}

int Add_To_List(Node** head, char* str)
{
	Node* new = (Node*)malloc(sizeof(Node));
	if (new == NULL)
	{
		printf("memory error");
		return 1;
	}
	new->str = (char*)malloc(sizeof(char) * (strlen(str) + 1));
	if (new->str == NULL)
	{
		printf("memory error");
		free(new);
		return 1;
	}
	strcpy(new->str, str);
	new->next = *head;
	*head = new;
	

}

int Find_In_List(Node* head, char *str)
{
	Node* cur = head;
	while (cur != NULL)
	{
		if (strcmp(cur->str, str) == 0)
			return 1;
		cur = cur->next;
	}
	return 0;
}


void Delete_From_List(Node** head, char* str)
{
	Node* del = *head;
	Node* prev = NULL;
	Node* next = NULL;
	int is_in_list = 0;
	while (del != NULL)
	{
		if (strcmp(del->str, str) == 0)
		{
			is_in_list = 1;
			break;
		}
		prev = del;
		del = del->next;
	}
	if (is_in_list == 1)
	{
		
		next = del->next; 
		
		if (prev == NULL && next == NULL)
		{
			free(del->str);
			free(del);
			(*head) = NULL;
			return;
		}
		if (prev != NULL)
		{
			prev->next = next;
		}
		else
			*head= next;
		free(del->str);
		free(del);
	}	
}





int Hash_Func(char* str)
{
	int res = 0;
	for (int i = 0; str[i] != '\0'; i++) 
		res = res * 16 + str[i];
	return res % table_size;
}


Node** Init_Table()
{
	Node** result = (Node**)malloc(sizeof(Node*) * table_size);
	if (result == NULL)
	{
		printf("memory error");
		return NULL;
	}
	for (int i = 0; i < table_size; i++)
		result[i] = NULL;
	return result;
}

void Destroy_Table(Node** Table)
{
	for (int i = 0; i < table_size; i++)
		Destroy_List(Table[i]);
	free(Table);
}



int Add_To_Table(Node** Table, char* str)
{
	if (Find_In_Table(Table, str) == 1)
		return 0;
	
	int hash = Hash_Func(str);
	return Add_To_List(&Table[hash], str);
}

int Find_In_Table(Node** Table, char* str)
{
	int hash = Hash_Func(str);
	return Find_In_List(Table[hash], str);
}

void Delete_From_Table(Node** Table, char* str)
{
	int hash = Hash_Func(str);
	Delete_From_List(&Table[hash], str);
}

void Print_List(Node* head)
{
	Node* cur = head;
	while (cur != NULL)
	{
		printf("%s -> ", cur->str);
		cur = cur->next;
	}
	printf("NULL\n");

}

void Print_Table(Node** table)
{
	for (int i = 0; i < table_size; i++)
	{
		printf("%i ", i);
		Print_List(table[i]);
	}


}


int main()
{
	Node** table = Init_Table();
	char buf[16] = { 0 };
	char c = 0;
	char str[10000] = { 0 };
	while (fgets(buf, 16, stdin)) 
	{
		sscanf(buf, "%c %s", &c, &str);
		switch (c) {
		case 'a':
			Add_To_Table(table, str);
			break;
		case 'r':
			Delete_From_Table(table, str);
			break;
		case 'f':
			printf("%s\n", Find_In_Table(table, str) ? "yes" : "no");
			break;
		default:
			Destroy_Table(table);
			return 0;
		}
	}
	Destroy_Table(table);
	return 0;

}






