#include "List13.h"



void PrintArray(int count, int* array)
{
    int i;
    for (i = 0; i < count; i++)
        printf("%i ", array[i]);
}

void PrintList(list* Head)
{
    list* Cur = Head;
    while (Cur != NULL)
    {
        PrintArray(Cur->NumOfFilled, Cur->array);
        printf("\n");
        Cur = Cur->Next;
    }
    return;
}
list* CreateList(int num)
{
    list* res = (list*)malloc(sizeof(list));
    if (res == NULL)
        return NULL;

    res->count = Count;
    res->NumOfFilled = 1;
    res->Next = NULL;
    res->array = (int*)malloc(sizeof(int) * Count);
    res->array[0] = num;

    return res;
}

void DestoyList(list* L)
{
    list* cur;
    while (L != NULL)
    {
        cur = L;
        L = L->Next;
        free(cur->array);
        free(cur);
    }
}
void AddToList(list* L, int key)
{
    list* cur = L;
    list* new;
    while (cur->NumOfFilled == cur->count)
    {
        if (cur->Next == NULL)
            break;
        cur = cur->Next;
    }
    if (cur->NumOfFilled == cur->count && cur->Next == NULL)
        cur->Next = CreateList(key);
    else
    {
        cur->array[cur->NumOfFilled] = key;
        cur->NumOfFilled++;
    }
}

int FindNumberByKey(list* L, int key)
{
    list* cur = L;
    int lilcounter = 0;
    int counter = 1;
    while (cur != NULL)
    {
        while (cur->NumOfFilled > lilcounter)
        {
            if (cur->array[lilcounter] == key)
                return counter;
            lilcounter++;
            counter++;
        }
        cur = cur->Next;
        lilcounter = 0;
    }
    return 0;
}

int FindKeyByNumber(list* L, int number)
{
    list* cur = L;
    int lilcounter = 0;
    int counter = 1;
    while (cur != NULL)
    {
        while (cur->NumOfFilled > lilcounter)
        {
            if (number == counter)
                return cur->array[lilcounter];
            lilcounter++;
            counter++;
        }
        cur = cur->Next;
        lilcounter = 0;
    }
    return 0;
}

int Counter(list* L)
{
    list* cur = L;
    int lilcounter = 0;
    int counter = 0;
    while (cur != NULL)
    {
        while (cur->NumOfFilled > lilcounter)
        {
            lilcounter++;
            counter++;
        }
        cur = cur->Next;
        lilcounter = 0;
    }
    return counter;
}

int FindNextByKey(list* L, int key)
{
    list* cur = L;
    int lilcounter = 0;
    while (cur != NULL)
    {
        while (cur->NumOfFilled > lilcounter)
        {
            if (cur->array[lilcounter] == key)
            {
                if (lilcounter == cur->NumOfFilled - 1)
                    return cur->Next->array[0];
                else
                    return cur->array[lilcounter + 1];
            }
            lilcounter++;
        }
        cur = cur->Next;
        lilcounter = 0;
    }
}



void DeleteByNumber(list* l, int number)
{
    list* cur = l;
    list* tmp = NULL;

    int lilcounter = 0;
    int counter = 1;

    while (1)
    {
        while (cur->NumOfFilled > lilcounter)
        {
            if (counter == number)
                break;
            counter++;
            lilcounter++;
        }
        if (counter == number)
        {
            if (counter % cur->count == 1 && counter != 1)
            {
                if (cur->Next->NumOfFilled == 1)
                {
                    cur->Next = tmp;
                    cur->Next = NULL;
                    free(tmp);
                    return;
                }
                cur = cur->Next;
                lilcounter = 0;
            }
            break;

        }
        cur = cur->Next;
        lilcounter = 0;

    }
    while (1)
    {
        while (cur->NumOfFilled > lilcounter + 1)
        {
            cur->array[lilcounter] = cur->array[lilcounter + 1];
            lilcounter++;
        }
        if (cur->Next == NULL)
            break;
        else
        {
            cur->array[lilcounter] = cur->Next->array[0];
            if (cur->Next->NumOfFilled == 1)
            {
                tmp = cur->Next;
                cur->Next = NULL;
            }
            else
            {
                cur = cur->Next;
                lilcounter = 0;
            }
        }
    }
    if (tmp != NULL)
        free(tmp);
    else
        cur->NumOfFilled--;
}