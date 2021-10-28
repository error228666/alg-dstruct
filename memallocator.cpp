#include <stdio.h>
#include "memallocator.h"

void* head = NULL;
void* memory = NULL;
int avaible_size = 0;

int myabs(int a)
{
	if (a >= 0)
		return a;
	else
		return a * (-1);
}

int memgetminimumsize()
{
	return 2 * sizeof(int) + 2 * sizeof(void*);
}

int memgetblocksize()
{
	return 2 * sizeof(int) + 2 * sizeof(void*);
}



int* leftsizegetting(void* d)
{
	return (int*)d;
}

void** nextblockgetting(void* d)
{
	return (void**)((char*)d + sizeof(int));
}

void** prevblockgetting(void* d)
{
	return (void**)((char*)d + sizeof(int) + sizeof(void*));
}

int* rightsizegetting(void* d)
{
	return (int*)((char*)d + myabs(*leftsizegetting(d)) - sizeof(int));
}





int meminit(void* pMemory, int size)
{
	if (size <= memgetminimumsize())
		return 0;
	void* d = pMemory;
	*leftsizegetting(d) = size;
	*nextblockgetting(d) = NULL;
	*prevblockgetting(d) = NULL;
	*rightsizegetting(d) = size;
	head = d;
	memory = pMemory;
	avaible_size = size;
	return size;
}

void* memalloc(int size)
{
	if (size < 1 || size > avaible_size - memgetblocksize())
		return NULL;
	int bestsize = avaible_size + 1;
	void* block = head;
	int isfounded = 0;
	void* bestblock = block;
	void* newblock = NULL;
	while (block != NULL)
	{
		if (*leftsizegetting(block) < bestsize && *leftsizegetting(block) >= memgetblocksize() + size)
		{
			isfounded = 1;
			bestblock = block;
			bestsize = *leftsizegetting(block);
		}
		block = *nextblockgetting(block);
	}
	if (isfounded == 0)
		return NULL;
	if (*leftsizegetting(bestblock) - size - 2 * memgetblocksize() > 0) // if we can make a new block
	{
		newblock = (void*)((char*)bestblock + size + memgetblocksize());
		*leftsizegetting(newblock) = *leftsizegetting(bestblock) - memgetblocksize() - size;
		*rightsizegetting(newblock) = *leftsizegetting(newblock);
		*nextblockgetting(newblock) = *nextblockgetting(bestblock);
		*prevblockgetting(newblock) = *prevblockgetting(bestblock);
		
		if (*prevblockgetting(bestblock) == NULL) // first block
		{
			if (*nextblockgetting(bestblock) != NULL) // not single block
				*prevblockgetting(*nextblockgetting(bestblock)) = newblock;
			head = newblock;
		}
		else
		{
			if (*nextblockgetting(bestblock) != NULL) // not last
				*prevblockgetting(*nextblockgetting(bestblock)) = newblock;
			*nextblockgetting(*prevblockgetting(bestblock)) = newblock;
		}
		

		*leftsizegetting(bestblock) = size + memgetblocksize();
	}
	else
	{
		if (*prevblockgetting(bestblock) != NULL) // not first
		{
			if (*nextblockgetting(bestblock) != NULL) // not last
			{
				*prevblockgetting(*nextblockgetting(bestblock)) = *prevblockgetting(bestblock);
				*nextblockgetting(*prevblockgetting(bestblock)) = *nextblockgetting(bestblock);
			}
			else //last block
				*nextblockgetting(*prevblockgetting(bestblock)) = NULL;
			
		}
		else // first block
		{
			if (*nextblockgetting(bestblock) != NULL) // not single
			{
				*prevblockgetting(*nextblockgetting(bestblock)) = NULL;
				head = *nextblockgetting(bestblock);
			}
			else // single block
				head = NULL;		
		}		
	}
	*leftsizegetting(bestblock) *= -1;
	*rightsizegetting(bestblock) = *leftsizegetting(bestblock);
	*prevblockgetting(bestblock) = NULL;
	*nextblockgetting(bestblock) = NULL;
	return (void*)((char*)bestblock + sizeof(int) + 2 * sizeof(void*));
}


void memfree(void* p)
{
	if (p == NULL)
		return;
	void* newblock = (void*)((char*)p - sizeof(int) - 2 * sizeof(void*));
	void* leftblock = NULL;
	void* rightblock = NULL;
	int ismergedl = 0, ismergedr = 0;

	if ((char*)newblock - 1 > (char*)memory)
		leftblock = (void*)((char*)newblock - myabs(*((int*)newblock - 1)));
	if((char*)newblock + myabs(*leftsizegetting(newblock)) < (char*)memory + avaible_size)
		rightblock = (void*)(rightsizegetting(newblock) + 1);
	
	if (leftblock != NULL)
	{											/*u did this check above*/
		if (*leftsizegetting(leftblock) <= 0 && leftblock >= (char*)memory)
			leftblock = NULL;
	}
	
	if (rightblock != NULL)
	{
		if (*leftsizegetting(rightblock) <= 0 && (char*)rightblock < (char*)memory + avaible_size)
			rightblock = NULL;
	}
	
	*leftsizegetting(newblock) *= -1;
	*rightsizegetting(newblock) *= -1;
	
	if (leftblock != NULL)
	{
		ismergedl = 1;
		*leftsizegetting(leftblock) += *leftsizegetting(newblock);
		*rightsizegetting(leftblock) = *leftsizegetting(leftblock);
		newblock = leftblock;
	}

	if (rightblock != NULL)
	{
		ismergedr = 1;
		if (ismergedl == 0) // adding newblock in start of list
		{
			*nextblockgetting(newblock) = head;
			if (head != NULL)
				*prevblockgetting(head) = newblock;
			*prevblockgetting(newblock) = NULL;
			head = newblock;
		}
		//deleting rightblock from list
		if (*prevblockgetting(rightblock) != NULL) // not first
		{
			if (*nextblockgetting(rightblock) != NULL) // not last
			{
				*prevblockgetting(*nextblockgetting(rightblock)) = *prevblockgetting(rightblock);
				*nextblockgetting(*prevblockgetting(rightblock)) = *nextblockgetting(rightblock);
			}
			else // last
				*nextblockgetting(*prevblockgetting(rightblock)) = NULL;
		}
		else // first
		{
			if (*nextblockgetting(rightblock) != NULL) // not single
			{
				head = *nextblockgetting(rightblock);
				*prevblockgetting(head) = NULL;
			}
			else // single
				head = *nextblockgetting(rightblock);

		}
		*leftsizegetting(newblock) += *leftsizegetting(rightblock);
		*rightsizegetting(newblock) = *leftsizegetting(newblock);
	}
	if (ismergedl == 0 && ismergedr == 0)
	{
		*nextblockgetting(newblock) = head;
		if (head != NULL)
			*prevblockgetting(head) = newblock;
		*prevblockgetting(newblock) = NULL;
		head = newblock;
	}
	

}

void memdone() 
{
	void* block = memory;
	while ((char*)block < (char*)memory + avaible_size) {
		if (*leftsizegetting(block) < 0)
			fprintf(stderr, " Memory leak at 0x%p\n", (char*)block + sizeof(int) + sizeof(void*));
		block = (void*)((char*)block + myabs(*leftsizegetting(block)));
	}
}