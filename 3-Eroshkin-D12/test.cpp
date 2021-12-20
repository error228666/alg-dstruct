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
	FILE* input = fopen("input.txt", "r");
	ASSERT_TRUE(input);
	FILE* output = fopen("output.txt", "w");
	ASSERT_TRUE(output);
	lab(input, output);
	fclose(input);
	fclose(output);

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

TEST(VertexComparatorTests, SameVertexes)
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


TEST(LabTests, ImposibleToPaint)
{
	FILE* input = fopen("input.txt", "w");
	
	fprintf(input, "3 2\n1 3\n1 2\n2 3");

	fclose(input);
	input = fopen("input.txt", "r");
	ASSERT_TRUE(input);
	FILE* output = fopen("output.txt", "w");
	ASSERT_TRUE(output);
	lab(input, output);
	fclose(input);
	fclose(output);
	int res;
	output = fopen("output.txt", "r");
	ASSERT_TRUE(output);
	fscanf(output, "%i", &res);
	ASSERT_EQ(0, res);
	fclose(output);
}

TEST(LabTests, PosibleToPaint1)
{
	FILE* input = fopen("input.txt", "w");
	ASSERT_TRUE(input);
	fprintf(input, "3 3\n2 3\n1 3\n1 2");
	fclose(input);
	input = fopen("input.txt", "r");
	ASSERT_TRUE(input);
	FILE* output = fopen("output.txt", "w");
	ASSERT_TRUE(output);
	lab(input, output);
	fclose(input);
	fclose(output);
	int res[3];
	int myres[3] = { 1, 2, 3 };
	output = fopen("output.txt", "r");
	ASSERT_TRUE(output);
	fscanf(output, "%i ", &res[0]);
	fscanf(output, "%i ", &res[1]);
	fscanf(output, "%i ", &res[2]);
	fclose(output);
	ASSERT_EQ(res[0], myres[0]);
	ASSERT_EQ(res[1], myres[1]);
	ASSERT_EQ(res[2], myres[2]);
	
}
