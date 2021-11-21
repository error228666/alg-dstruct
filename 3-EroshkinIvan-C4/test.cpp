#include "pch.h"
#include "graph.h"
/*
Proceesor	AMD Ryzen 5 3500U with Radeon Vega Mobile Gfx, 2100 MHertz, cores: 4, logical processors: 8
RAM	8,00 ца

Test results:
Time 100 s
Memory ~ 256 mb at peak
*/
TEST(StressTest, MakingFiles) 
{
	int x, y;
	int count_of_vertex = 1000000;
	int iters = 100;
	FILE* input = fopen("input.txt", "w");
	if (input == NULL)
	{
		printf("file error");
		ASSERT_TRUE(input);
	
	}
	fprintf(input, "%d\n", count_of_vertex);
	fprintf(input, "0 1\n");
	for (int j = 0; j < count_of_vertex; j += 2)
	{

		for (int i = 1; i < iters; i += 2)
		{
			if (j + i > count_of_vertex)
				y = j - i;
			else
				y = j + i;
			
			fprintf(input, "%d %d\n", j, y);
		}
	}
	fclose(input);
	FILE* output = fopen("output.txt", "w");
	fclose(output);
}

TEST(StressTest, Testing)
{
	int i, count_of_vertex, error;
	list_of_adjacency* l;
	FILE* input, * output;

	input = fopen("input.txt", "r");
	output = fopen("output.txt", "w");
	if (input == NULL)
	{
		printf("file error");
		ASSERT_TRUE(input);
	}

	if (output == NULL)
	{
		printf("file error");
		ASSERT_TRUE(output);
	}
	
	l = making_list(input, &count_of_vertex, &error);
	
	if (error != 0)
	{
		errors_consider(error);
		fclose(output);
		fclose(input);
		ASSERT_FALSE(error);
	}
	bfs(l, count_of_vertex, output, &error);

	if (error != 0)
	{
		destroy_list_of_adjacency(l, count_of_vertex);
		errors_consider(error);
		fclose(output);
		fclose(input);
		ASSERT_FALSE(error);
	}
	destroy_list_of_adjacency(l, count_of_vertex);
	fclose(output);
	fclose(input);
}