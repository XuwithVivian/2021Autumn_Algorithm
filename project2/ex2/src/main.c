#include<stdio.h>
#include<time.h>
#include<math.h>
#include<stdlib.h>
#include<windows.h>

typedef struct Node
{
    struct Node *p;
    int rank;
}Node;

Node *find_set(Node *x)
{
    if (x != x->p)
        x->p = find_set(x->p);
    return x->p;
}

void link(Node *x, Node *y)
{
    if (x->rank > y->rank)
    {
        y->p = x;
    }
    else
    {
        x->p = y;
        if (x->rank == y->rank)
            y->rank = y->rank + 1;
    }
}

void Union(Node *x, Node *y)
{
    link(find_set(x), find_set(y));
}

int main()
{
    FILE *fp1, *fp2, *fp3;
    // 打开输入输出文件
    if((fp1 = fopen("../input/2_2_input.txt","r"))==NULL)
    {
        printf("cannot open input file\n");
        exit(0);
    }
    if((fp2 = fopen("../output/result.txt","w"))==NULL)
    {
        printf("cannot open result.txt\n");
        exit(0);
    }
    if((fp3 = fopen("../output/time.txt","w"))==NULL)
    {
        printf("cannot open time.txt\n");
        exit(0);
    }
    int i, j, k;
    LONGLONG begin, over, freq;
    LARGE_INTEGER number;
    QueryPerformanceFrequency(&number);
    freq = number.QuadPart;
    for (i = 0; i < 5; i++)
    {
        int num = 0;
        int N = (i + 1) * 5 + 5;
        int family[N][N];
        for (j = 0; j < N; j++)
        {
            for (k = 0; k < N; k++)
            {
                fscanf(fp1, "%d", &family[j][k]);
            }
        }
        Node *node[N];
        QueryPerformanceCounter(&number);
        begin = number.QuadPart;
        for (j = 0; j < N; j++)
        {
            node[j] = (Node *)malloc(sizeof(Node));
            node[j]->p = node[j];
            node[j]->rank = 0;
        }
        for (j = 0; j < N; j++)
        {
            for (k = j; k < N; k++)
            {
                if (k != j)
                {
                    if ((family[j][k] == 1 || family[k][j] == 1 ) && find_set(node[j]) != find_set(node[k]))
                    {
                        Union(node[j], node[k]);
                    }
                }
            }
        }
        for (j = 0; j < N; j++)
        {
            int flag = 1;
            for (k = 0; k < j; k++)
            {
                if (find_set(node[j]) == find_set(node[k]))
                    flag = 0;
            }
            if (flag == 1)
                num++;
        }
        QueryPerformanceCounter(&number);
        over = number.QuadPart;
        fprintf(fp2, "n=%d 家族数:%d\n", N, num);
        fprintf(fp3, "n=%d 时间:%lld\n", N, (over - begin)*10000000/freq);
    }
    //关闭输入输出文件
    fclose(fp1);
    fclose(fp2);
    fclose(fp3);
    return 0;
}