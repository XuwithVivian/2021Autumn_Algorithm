#include<stdio.h>
#include<time.h>
#include<math.h>
#include<stdlib.h>
#include<windows.h>

int G[730][730];
int V[4] = {27, 81, 243, 729};
int edge[4][2] = {{3, 2}, {3, 3}, {4, 3}, {5, 4}};
int path[730] = {0};

typedef struct Node
{
    struct Node *p;
    int d;
    int front;
}Node;

Node *vertex[730];

void initialize_single_source(int G[730][730], Node *s, int N)
{
    int i;
    for (i = 1; i < N; i++)
    {
        vertex[i]->d = 9999;
        vertex[i]->p = NULL;
        vertex[i]->front = i;
    }
    s->d = 0;
}

void relax(int u, int v, int G[730][730])
{
    if(vertex[v]->d > vertex[u]->d + G[u][v])
    {
        vertex[v]->d = vertex[u]->d + G[u][v];
        vertex[v]->p = vertex[u];
        vertex[v]->front = u;
    }
}

int bellman_ford(int G[730][730], Node *s, int N)
{
    initialize_single_source(G, s, N);
    int i, j, k;
    for (i = 1; i < N; i++)
    {
        for (j = 0; j < N; j++)
        {
            for (k = 0; k < N; k++)
            {
                if(G[j][k] != 0)
                {
                    relax(j, k, G);
                }
            }
        }
    }
    for (j = 0; j < N; j++)
    {
        for (k = 0; k < N; k++)
        {
            if(G[j][k] != 0 && vertex[k]->d > vertex[j]->d + G[j][k])
            {
                return 0;
            }
        }
    }
    return 1; 
}

int main()
{
    FILE *in[4][2], *out[4][2], *fp;
    // FILE *in_11,*in_12,*in_21,*in_22,*in_31,*in_32,*in_41,*in_42;
    // FILE *out_11,*out_12,*out_21,*out_22,*out_31,*out_32,*out_41,*out_42,*fp;
    // 打开输入输出文件
    if((in[0][0] = fopen("../input/input11.txt","r"))==NULL)
    {
        printf("cannot open input11 file\n");
        exit(0);
    }
    if((in[0][1] = fopen("../input/input12.txt","r"))==NULL)
    {
        printf("cannot open input12 file\n");
        exit(0);
    }
    if((in[1][0] = fopen("../input/input21.txt","r"))==NULL)
    {
        printf("cannot open input21 file\n");
        exit(0);
    }
    if((in[1][1] = fopen("../input/input22.txt","r"))==NULL)
    {
        printf("cannot open input22 file\n");
        exit(0);
    }
    if((in[2][0] = fopen("../input/input31.txt","r"))==NULL)
    {
        printf("cannot open input31 file\n");
        exit(0);
    }
    if((in[2][1] = fopen("../input/input32.txt","r"))==NULL)
    {
        printf("cannot open input32 file\n");
        exit(0);
    }
    if((in[3][0] = fopen("../input/input41.txt","r"))==NULL)
    {
        printf("cannot open input41 file\n");
        exit(0);
    }
    if((in[3][1] = fopen("../input/input42.txt","r"))==NULL)
    {
        printf("cannot open input42 file\n");
        exit(0);
    }
    if((out[0][0] = fopen("../output/result11.txt","w"))==NULL)
    {
        printf("cannot open result11 file\n");
        exit(0);
    }
    if((out[0][1] = fopen("../output/result12.txt","w"))==NULL)
    {
        printf("cannot open result12 file\n");
        exit(0);
    }
    if((out[1][0] = fopen("../output/result21.txt","w"))==NULL)
    {
        printf("cannot open result21 file\n");
        exit(0);
    }
    if((out[1][1] = fopen("../output/result22.txt","w"))==NULL)
    {
        printf("cannot open result22 file\n");
        exit(0);
    }
    if((out[2][0] = fopen("../output/result31.txt","w"))==NULL)
    {
        printf("cannot open result31 file\n");
        exit(0);
    }
    if((out[2][1] = fopen("../output/result32.txt","w"))==NULL)
    {
        printf("cannot open result32 file\n");
        exit(0);
    }
    if((out[3][0] = fopen("../output/result41.txt","w"))==NULL)
    {
        printf("cannot open result41 file\n");
        exit(0);
    }
    if((out[3][1] = fopen("../output/result42.txt","w"))==NULL)
    {
        printf("cannot open result42 file\n");
        exit(0);
    }
    if((fp = fopen("../output/time.txt","w"))==NULL)
    {
        printf("cannot open time file\n");
        exit(0);
    }
    int i, j, k, l;
    int N, E;
    clock_t start, end;
    double time;
    for (i = 0; i < 730; i++)
    {
        vertex[i] = (Node *)malloc(sizeof(Node));
    }
    for (i = 0; i < 4; i++)
    {
        for (j = 0; j < 2; j++)
        {
            N = V[i];
            E = edge[i][j];
            for (k = 0; k < N; k++)
            {
                for (l = 0; l < N; l++)
                {
                    fscanf(in[i][j], "%d,", &G[k][l]);
                }
            }
            start = clock();
            int ford = bellman_ford(G, vertex[0], N);
            end = clock();
            time = (double)(end - start) / (CLOCKS_PER_SEC);
            fprintf(fp, "%f\n", time);
            for (k = 1; k < N; k++)
            {
                if (vertex[k]->d != 9999)
                {
                    int length = 0;
                    Node *node = vertex[k];
                    int flag = 0;
                    while (node != vertex[0])
                    {
                        path[length++] = node->front;
                        node = vertex[node->front];
                        if (node->d == 9999)
                        {
                            flag = 1;
                            break;
                        }
                    }
                    if (flag)
                        continue;
                    fprintf(out[i][j], "0,%d,%d;", k, vertex[k]->d);
                    for (l = length - 1; l >= 0; l--)
                    {
                        fprintf(out[i][j], "%d,", path[l]);
                    }
                    fprintf(out[i][j], "%d\n", k); 
                }
            }
        }
    }
    //关闭输入输出文件
    for (i = 0; i < 4; i++)
        for (j = 0; j < 2; j++)
        {
            fclose(in[i][j]);
            fclose(out[i][j]);
        }
    fclose(fp);
    return 0;
}
