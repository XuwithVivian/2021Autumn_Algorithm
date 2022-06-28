#include<stdio.h>
#include<time.h>
#include<math.h>
#include<stdlib.h>
#include<windows.h>
#include<string.h>

char P[130], T[4100];
int next[130], pos[4100];

void compute_prefix_function()
{
    int m = strlen(P) - 1;
    int i, q;
    for (i = 0; i < m; i++)
        next[i] = 0;
    int k = 0;
    for (q = 2; q < m + 1; q++)
    {
        while (k > 0 && P[k + 1] != P[q])
        {
            k = next[k];
        }
        if (P[k + 1] == P[q])
        {
            k++;
        }
        next[q] = k;
    }
}

void KMP_matcher(FILE *fp)
{
    int n = strlen(T) - 1;
    int m = strlen(P) - 1;
    compute_prefix_function();
    int q = 0;
    int i, num = 0;
    for (i = 1; i <= n; i++)
    {
        while (q > 0 && P[q + 1] != T[i])
            q = next[q];
        if (P[q + 1] == T[i])
            q++;
        if (q == m)
        {
            pos[num++] = i - m + 1;
            q = next[q];
        }
    }
    fprintf(fp, "%d\n", num);
    for (i = 1; i < m + 1; i++)
        fprintf(fp, "%d ", next[i]);
    fprintf(fp, "\n");
    for (i = 0; i < num; i++)
        fprintf(fp, "%d ", pos[i]);
    fprintf(fp, "\n\n");
}

int main()
{
    FILE *fp1,*fp2,*fp3;
    // 打开输入输出文件
    if((fp1 = fopen("../input/4_1_input.txt","r"))==NULL)
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
    int i, j;
    clock_t start, end;
    double time;
    for (i = 0; i < 5; i++)
    {
        fscanf(fp1, "%s", P);
        fscanf(fp1, "%s", T);
        for (j = strlen(P); j > 0; j--)
        {
            P[j] = P[j - 1];
        }
        for (j = strlen(T); j > 0; j--)
        {
            T[j] = T[j - 1];
        }
        start = clock();
        KMP_matcher(fp2);
        end = clock();
        time = (double)(end - start) / (CLOCKS_PER_SEC);
        fprintf(fp3, "%f\n", time);
    }
    //关闭输入输出文件
    fclose(fp1);
    fclose(fp2);
    fclose(fp3);
    return 0;
}