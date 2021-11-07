#include "graph.h"

/*
Процессор	AMD Ryzen 5 3500U with Radeon Vega Mobile Gfx, 2100 МГц, ядер: 4, логических процессоров: 8
Установленная оперативная память (RAM)	8,00 ГБ

Результаты стресс теста:
Время - 50.4 с
Память ~ 122 Мб
*/

void making_files()
{
	int count_of_vertex = 1000000;
	FILE* input = fopen("input.txt", "w");
	fprintf(input, "%d\n", count_of_vertex);
	fprintf(input, "%d %d\n", 0, rand() % count_of_vertex);
	for (int i = 0; i < 10000000; i++)
	{
		fprintf(input, "%d %d\n", rand() % count_of_vertex, rand() % count_of_vertex);
	}
	fclose(input);
	FILE *output = fopen("output.txt", "w");
	fclose(output);
}

void my_stress_test()
{
	int i, count_of_vertex, error;
	unsigned long my_time;
	list_of_adjacency* l;
	FILE* input, * output;

	making_files();
	input = fopen("input.txt", "r");
	output = fopen("output.txt", "w");

	my_time = clock();
	l = making_list(input, &count_of_vertex, &error);
	if (error != 0)
	{
		errors_consider(error);
		fclose(output);
		fclose(input);
		return;
	}
	bfs(l, count_of_vertex, output, &error);
	if (error != 0)
	{
		destroy_list_of_adjacency(l, count_of_vertex);
		errors_consider(error);
		fclose(output);
		fclose(input);
		return;
	}
	printf("time - %f\n", ((double)(clock() - my_time) / CLOCKS_PER_SEC));
	fclose(output);
	fclose(input);
}


int main()
{
	my_stress_test();
	lab();

}
