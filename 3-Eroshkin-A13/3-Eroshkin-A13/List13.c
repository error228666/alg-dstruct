#include "List13.h"

list* CreateList(int Num)
{
    list* Res = (list*)malloc(sizeof(list));
    if (Res == NULL)
        return NULL;
    Res->NumOfFilled = 1;
    Res->Next = NULL;
    Res->Array[0] = Num;

    return Res;
}

void DestoyList(list* L)
{
    list* Cur;
    while (L != NULL)
    {
        Cur = L;
        L = L->Next;
        free(Cur);
    }
}
int AddToList(list* L, int Key)
{
    list* Cur = L;
    list* New;
    while (Cur->NumOfFilled == 3)
    {
        if (Cur->Next == NULL)
            break;
        Cur = Cur->Next;
    }
    if (Cur->NumOfFilled == 3 && Cur->Next == NULL)
    {
        Cur->Next = CreateList(Key);
        if (Cur->Next == NULL)
            return 0;
    }
    else
    {
        Cur->Array[Cur->NumOfFilled] = Key;
        Cur->NumOfFilled++;
    }
    return 1;
}

int FindNumberByKey(list* L, int Key, int* Number)
{
    list* Cur = L;
    int LilCounter = 0;
    int Counter = 1;
    while (Cur != NULL)
    {
        while (Cur->NumOfFilled > LilCounter)
        {
            if (Cur->Array[LilCounter] == Key)
            {
                *Number = Counter;
                return 1;
            }
            LilCounter++;
            Counter++;
        }
        Cur = Cur->Next;
        LilCounter = 0;
    }
    return 0;
}

int FindKeyByNumber(list* L, int Number, int* Key)
{
    list* Cur = L;
    int LilCounter = 0;
    int Counter = 1;
    while (Cur != NULL)
    {
        while (Cur->NumOfFilled > LilCounter)
        {
            if (Number == Counter)
            {
                *Key = Cur->Array[LilCounter];
                return 1;
            }
            LilCounter++;
            Counter++;
        }
        Cur = Cur->Next;
        LilCounter = 0;
    }
    return 0;
}

int Counter(list* L)
{
    list* Cur = L;
    if (L == NULL)
        return 0;
    int Counter = Cur->NumOfFilled;
    while (Cur->Next != NULL)
    {
        Cur = Cur->Next;
        Counter += Cur->NumOfFilled;
    }
    return Counter;
}

int FindNextByKey(list* L, int Key, int* NextKey)
{
    list* Cur = L;
    int LilCounter = 0;
    while (Cur != NULL)
    {
        while (Cur->NumOfFilled > LilCounter)
        {
            if (Cur->Array[LilCounter] == Key)
            {
                if (LilCounter == Cur->NumOfFilled - 1)
                {
                    if (Cur->Next == 0)
                        return 0;
                    else
                    {
                        *NextKey = Cur->Next->Array[0];
                        return 1;
                    }
                }
                else
                {
                    *NextKey = Cur->Array[LilCounter + 1];
                    return 1;
                }
            }
            LilCounter++;
        }
        Cur = Cur->Next;
        LilCounter = 0;
    }
    return 0;
}



int DeleteByNumber(list* L, int Number)
{
    list* Cur = L;
    list* Prev = NULL;
    list* Tmp = NULL;
    int LilCounter = 0;
    int BigCounter, i;
    for (BigCounter = 1; BigCounter < Number; BigCounter++)
    {
        if (LilCounter == Cur->NumOfFilled - 1)
        {
            if (Cur->Next == NULL)
                return 0;
            else
            {
                LilCounter = 0;
                Prev = Cur;
                Cur = Cur->Next;
            }
        }
        else
            LilCounter++;
    }
    for (i = LilCounter; i < Cur->NumOfFilled - 1; i++)
        Cur->Array[i] = Cur->Array[i + 1];
    Cur->NumOfFilled--;
    if (Cur->NumOfFilled == 0)
    {
        if (Prev == NULL)
        {
            if (Cur->Next == NULL)
                free(Cur);
            else
            {
                for (i = 0; i < Cur->Next->NumOfFilled; i++)
                    Cur->Array[i] = Cur->Next->Array[i];
                Cur->NumOfFilled = Cur->Next->NumOfFilled;
                Tmp = Cur->Next;
                Cur->Next = Cur->Next->Next;
                free(Tmp);
            }
        }
        else
        {
            Prev->Next = Cur->Next;
            free(Cur);
        }
    }
    return 1;
}