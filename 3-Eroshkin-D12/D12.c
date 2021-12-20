#include "D12.h"
void make_file()
{
    
}



int** create_matrix(int n)
{
    int** a = (int**)malloc(sizeof(int) * n);
    if (a == NULL)
    {
        printf("matrix memory error");
        return NULL;
    }
    for (int i = 0; i < n; i++)
    {
        a[i] = (int*)malloc(sizeof(int) * n);
        if (a[i] == NULL)
        {
            printf("matrix2 memory error");
            for (int j = 0; j < i; j++)
                free(a[j]);
            free(a);
            return NULL;
        }
        for (int j = 0; j < n; j++)
            a[i][j] = 0;
    }
    return a;

}

int vertex_comparator1(vertex* val1, vertex* val2)
{
    if (val1->is_colored > val2->is_colored)
        return -1;
    if (val1->is_colored < val2->is_colored)
        return 1;

    if (val1->count_of_colors > val2->count_of_colors)
        return 1;
    if (val1->count_of_colors < val2->count_of_colors)
        return -1;
    if (val1->count_of_colors == val2->count_of_colors)
    {
        if (val1->degree > val2->degree)
            return 1;
        if (val1->degree < val2->degree)
            return -1;
        if (val1->degree == val2->degree)
            return 0;
    }
}

int vertex_comparator(const void* val1, const void* val2)
{
    return vertex_comparator1((vertex*)val1, (vertex*)val2);
}

int color_comparator1(color* val1, color* val2)
{
    return val2->count - val1->count;
}

int color_comparator(const void* val1, const void* val2)
{
    return color_comparator1((color*)val1, (color*)val2);
}

void lab(FILE* input, FILE* output)
{

    int n, k, x, y, flag, finded_color;
    int count_of_colors = 1;
    int count_of_colored = 0;
    int output_type = 1;
    int* value1 = NULL;
    color* value2 = NULL;
    fscanf(input, "%i", &n);
    fscanf(input, "%i", &k);
    

    int* vertex_color = (int*)malloc(sizeof(int) * n);
    if (vertex_color == NULL)
    {
        printf("memory error1");
        return;
    }
    color* colors = (color*)malloc(sizeof(color));
    if (colors == NULL)
    {
        free(vertex_color);
        printf("memory error2");
        return;
    }
    colors[0].count = 0;
    colors[0].num = 1;

    vertex* vec_of_vertex = (vertex*)malloc(sizeof(vertex) * n);
    if (vec_of_vertex == NULL)
    {
        printf("memory error3");
        free(vertex_color);
        free(colors);
        return;
    }
    for (int i = 0; i < n; i++)
    {
        vec_of_vertex[i].count_of_colors = 0;
        vec_of_vertex[i].degree = 0;
        vec_of_vertex[i].colors = NULL;
        vec_of_vertex[i].is_colored = 0;
    }
    int** matrix = create_matrix(n);

    
    while (fscanf(input, "%i %i", &x, &y) != EOF)
    {
        matrix[x - 1][y - 1] = 1;
        matrix[y - 1][x - 1] = 1;
        vec_of_vertex[x - 1].num = x - 1;
        vec_of_vertex[y - 1].num = y - 1;
        vec_of_vertex[x - 1].degree++;
        vec_of_vertex[y - 1].degree++;
    }


    qsort(vec_of_vertex, n, sizeof(vertex), vertex_comparator);

    while (count_of_colored < n)
    {
        finded_color = 0;
        for (int i = 0; i < count_of_colors; i++)
        {
            flag = 0;
            for (int j = 0; j < vec_of_vertex[n - 1].count_of_colors; j++)
                if (colors[i].num == vec_of_vertex[n - 1].colors[j])
                    flag = 1;
            if (flag == 0)
            {
                finded_color = colors[i].num;
                colors[i].count++;
                break;
            }
        }
        if (finded_color == 0)
        {
            if (count_of_colors == k)
            {
                output_type = 0;
                break;
            }
            count_of_colors++;
            value2 = (color*)realloc(colors, sizeof(color) * count_of_colors);
            if (value2 != NULL)
            {
                colors = value2;
                colors[count_of_colors - 1].count = 0;
                colors[count_of_colors - 1].num = count_of_colors;
                finded_color = count_of_colors;
            }
            else
            {
                free(vertex_color);
                free(colors);
                for (int i = 0; i < n; i++)
                {
                    free(vec_of_vertex[i].colors);
                    free(matrix[i]);
                }
                free(matrix);
                free(vec_of_vertex);

                printf("memory error");
                return;
            }
        }
    vertex_color[vec_of_vertex[n - 1].num] = finded_color;

    count_of_colored++;

    for (int i = 0; i < n; i++) // adding finded collor to banned of neigbours
    {
        if (matrix[vec_of_vertex[n - 1].num][i] == 1)
        {
            for (int j = count_of_colored - 1; j < n - 1; j++)
            {
                if (vec_of_vertex[j].num == i)
                {
                    vec_of_vertex[j].count_of_colors++;
                    value1 = (int*)realloc(vec_of_vertex[j].colors, sizeof(int) * vec_of_vertex[j].count_of_colors);
                    if (value1 != NULL)
                    {
                        vec_of_vertex[j].colors = value1;
                        vec_of_vertex[j].colors[vec_of_vertex[j].count_of_colors - 1] = finded_color;
                    }
                    else
                    {
                        free(vertex_color);
                        free(colors);
                        for (int i = 0; i < n; i++)
                        {
                            free(vec_of_vertex[i].colors);
                            free(matrix[i]);
                        }
                        free(matrix);
                        free(vec_of_vertex);
                        printf("memory error4");
                        return;
                    }
                }
            }
        }
    }
    for (int i = 0; i < n; i++)
    {
        matrix[i][vec_of_vertex[n - 1].num] = 0;
        matrix[vec_of_vertex[n - 1].num][i] = 0;
    }
    
    vec_of_vertex[n - 1].is_colored = 1;
    qsort(vec_of_vertex, n, sizeof(vertex), vertex_comparator);
    
    qsort(colors, count_of_colors, sizeof(color), color_comparator);


    }

    if (output_type == 0)
        fprintf(output, "0");
    else
    {
        for (int i = 0; i < n; i++)
            fprintf(output, "%i ", vertex_color[i]);

    }
    free(vertex_color);
    free(colors);
    for (int i = 0; i < n; i++)
    {
        free(vec_of_vertex[i].colors);
        free(matrix[i]);
    }
    free(matrix);
    free(vec_of_vertex);

}
/*
int main()
{
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    _CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_FILE);
    _CrtSetReportFile(_CRT_WARN, _CRTDBG_FILE_STDOUT);
    //int* check = malloc(sizeof(int) * 100);
    FILE* input = fopen("input.txt", "r");
    FILE* output = fopen("output.txt", "w");
    lab(input, output);
    fclose(input);
    fclose(output);

}*/