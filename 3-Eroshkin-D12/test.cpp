#include "pch.h"
#include "D12.h"
/*

Proceesor	AMD Ryzen 5 3500U with Radeon Vega Mobile Gfx, 2100 MHertz, cores: 4, logical processors: 8
RAM	8,00 

Test results:
	Time 70 s 
	Memory ~ 400 mb at peak

*/


TEST(StressTest, MakeFile)
{
	int x, y;
	int count_of_vertex = 10000;
	int count_of_colors = 10000;
	int iters = 1000;
	FILE* input = fopen("input.txt", "w");
	ASSERT_TRUE(input);
	fprintf(input, "%d %d\n", count_of_vertex, count_of_colors);
	for (int j = 1; j <= count_of_vertex; j += 2)
	{

		for (int i = 1; i <= iters; i += 2)
		{
			if (j + i > count_of_vertex)
				y = j - i;
			else
				y = j + i;

			fprintf(input, "%d %d\n", j, y);
		}
	}
	fclose(input);
}



TEST(StressTest, Testing)
{
	lab("input.txt", "output.txt");

}

TEST(ColorComparatorTests, TestingCompare)
{
	color color_a, color_b, color_c;
	color_a.count = 10;
	color_b.count = 0;
	color_c.count = 10;
	ASSERT_GT(0, color_comparator(&color_a, &color_b));
	ASSERT_LT(0, color_comparator(&color_b, &color_a));
	ASSERT_EQ(0, color_comparator(&color_a, &color_c));
}

TEST(VertexComparatorTests, TestingCompareByIsColored)
{
	vertex a, b;
	a.is_colored = 1;
	b.is_colored = 0;
	ASSERT_GT(0, vertex_comparator(&a, &b));
	ASSERT_LT(0, vertex_comparator(&b, &a));
}

TEST(VertexComparatorTest, TestingCompareByCountOfColors)
{
	vertex a, b;
	a.is_colored = 0;
	b.is_colored = 0;
	a.count_of_colors = 1;
	b.count_of_colors = 0;
	ASSERT_LT(0, vertex_comparator(&a, &b));
	ASSERT_GT(0, vertex_comparator(&b, &a));
}

TEST(VertexComparatorTests, TestingCompareByDegree)
{
	vertex a, b;
	a.is_colored = 0;
	b.is_colored = 0;
	a.count_of_colors = 0;
	b.count_of_colors = 0;
	a.degree = 1;
	b.degree = 0;
	ASSERT_LT(0, vertex_comparator(&a, &b));
	ASSERT_GT(0, vertex_comparator(&b, &a));
}

TEST(VertexComparatorTests, Same)
{
	vertex a, b;
	a.is_colored = 0;
	b.is_colored = 0;
	a.count_of_colors = 0;
	b.count_of_colors = 0;
	a.degree = 0;
	b.degree = 0;
	ASSERT_EQ(0, vertex_comparator(&a, &b));
}


TEST(LabTests, ImpossibleToPaint)
{
	FILE* input = fopen("input.txt", "w");
	
	fprintf(input, "3 2\n1 3\n1 2\n2 3");

	fclose(input);
	
	lab("input.txt", "output.txt");
	int res;
	FILE *output = fopen("output.txt", "r");
	ASSERT_TRUE(output);
	fscanf(output, "%i", &res);
	ASSERT_EQ(0, res);
	fclose(output);
}

TEST(LabTests, PossibleToPaint1)
{
	FILE* input = fopen("input.txt", "w");
	ASSERT_TRUE(input);
	fprintf(input, "3 3\n2 3\n1 3\n1 2");
	fclose(input);
	lab("input.txt", "output.txt");
	int res[3];
	int myres[3] = { 1, 2, 3 };
	FILE *output = fopen("output.txt", "r");
	ASSERT_TRUE(output);
	fscanf(output, "%i ", &res[0]);
	fscanf(output, "%i ", &res[1]);
	fscanf(output, "%i ", &res[2]);
	fclose(output);
	ASSERT_EQ(res[0], myres[0]);
	ASSERT_EQ(res[1], myres[1]);
	ASSERT_EQ(res[2], myres[2]);
	
}

TEST(LabTests, PossibleToPaint2)
{
	FILE* input = fopen("input.txt", "w");
	ASSERT_TRUE(input);
	fprintf(input, "8 3\n1 2\n1 4\n2 3\n2 5\n3 4\n4 5\n4 6\n4 7\n7 8\n6 8\n6 3");
	fclose(input);
	lab("input.txt", "output.txt");
	int res[8];
	int myres[8] = { 2, 1, 3, 1, 2, 2, 2, 1 };
	FILE* output = fopen("output.txt", "r");
	ASSERT_TRUE(output);
	for (int i = 0; i < 8; i++)
	{
		fscanf(output, "%i ", &res[i]);
		ASSERT_EQ(res[i], myres[i]);
	}
	fclose(output);

}


TEST(LabTests, PossibleToPaint3)
{
	FILE* input = fopen("input.txt", "w");
	ASSERT_TRUE(input);
	fprintf(input, "7 3\n1 2\n1 6\n1 4\n2 4\n4 3\n2 3\n3 5\n6 7\n3 6\n");
	fclose(input);
	lab("input.txt", "output.txt");
	int res[7];
	int myres[7] = { 1, 3, 1, 2, 2, 2, 1 };
	FILE* output = fopen("output.txt", "r");
	ASSERT_TRUE(output);
	for (int i = 0; i < 7; i++)
	{
		fscanf(output, "%i ", &res[i]);
		ASSERT_EQ(res[i], myres[i]);
	}
	fclose(output);

}
