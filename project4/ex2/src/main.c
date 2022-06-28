#include<stdio.h>
#include<time.h>
#include<math.h>
#include<stdlib.h>
#include<windows.h>
#include<string.h>

char P[130], T[4100];
int pos[4100], t[4100];
int d[4] = {2, 2, 10, 10};
int q[4] = {13, 1009, 13, 1009};
double timer[4][5];
int num_r, num_f;

void rabin_karp_matcher(int d, int q)
{
    int n = strlen(T) - 1;
    int m = strlen(P) - 1;
    int i, j;
    int h = 1;
    num_r = num_f = 0;
    for (i = 0; i < m - 1; i++)
    {
        h = (h * d) % q;
    }
    int p = 0;
    for (i = 0; i < 4100; i++)
        t[i] = 0;
    for (i = 1; i <= m; i++)
    {
        p = ((d * p + P[i]) % q + q) % q;
        t[0] = ((d * t[0] + T[i]) % q + q) % q;
    }
    for (i = 0; i <= n - m; i++)
    {
        if ((p - t[i]) % q == 0)
        {
            for (j = 1; j <= m; j++)
            {
                if (P[j] != T[i + j])
                    break;
            }
            if (j == m + 1)
            {
                pos[num_r++] = i + 1;
            }
            else
            {
                num_f++;
            }
        }
        if (i < n - m)
        {
            t[i + 1] = (((d * (t[i] - T[i + 1] * h) + T[i + m + 1]) % q) + q) % q;
        }
    }
}

int main()
{
    FILE *fp1,*fp2,*fp3;
    // 打开输入输出文件
    if((fp1 = fopen("../input/4_2_input.txt","r"))==NULL)
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
        for (j = 0; j < 4; j++)
        {
            start = clock();
            rabin_karp_matcher(d[j], q[j]);
            end = clock();
            timer[j][i] = (double)(end - start) / (CLOCKS_PER_SEC);
            if (j == 0)
                fprintf(fp2, "%d\n", num_r);
            fprintf(fp2, "%d ", num_f);
        }
        fprintf(fp2, "\n");
        for (j = 0; j < num_r; j++)
            fprintf(fp2, "%d ", pos[j]);
        fprintf(fp2, "\n\n");
    }
    fprintf(fp3, "(%d,%d)\n", d[0], q[0]);
    for (i = 0; i < 5; i++)
        fprintf(fp3, "%f ", timer[0][i]);
    fprintf(fp3, "\n");

    fprintf(fp3, "(%d,%d)\n", d[1], q[1]);
    for (i = 0; i < 5; i++)
        fprintf(fp3, "%f ", timer[1][i]);
    fprintf(fp3, "\n");

    fprintf(fp3, "(%d,%d)\n", d[2], q[2]);
    for (i = 0; i < 5; i++)
        fprintf(fp3, "%f ", timer[2][i]);
    fprintf(fp3, "\n");

    fprintf(fp3, "(%d,%d)\n", d[3], q[3]);
    for (i = 0; i < 5; i++)
        fprintf(fp3, "%f ", timer[3][i]);
    fprintf(fp3, "\n");
    //关闭输入输出文件
    fclose(fp1);
    fclose(fp2);
    fclose(fp3);
    return 0;
}