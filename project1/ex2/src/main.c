#include<stdio.h>
#include<time.h>
#include<stdlib.h>

int n;  // 记录序列长度
int sum;    // 记录LCS个数

// 打印所有LCS
void print_lcs(FILE *fp, char x[n], int i, int j, char z[n],int b[n+1][n+1], int c[n+1][n+1])
{
    if (c[i][j] == 0)
    {
        sum++;
        fprintf(fp, "%s\n", z + 1);
        return;
    }
    int count = c[i][j];
    while (c[i][j] == count && count > 0)
    {
        for (int k = j; c[i][k] == count; k--)
        {
            if(b[i][k] == 1)
            {
                z[count] = x[i - 1];
                print_lcs(fp, x, i-1, k-1, z, b, c);
            }
        }
        i--;
    }
}

int main()
{
    FILE *fp1,*fp2,*fp3,*fp4,*fp5,*fp6,*fp7;
    // 打开输入输出文件
    if((fp1 = fopen("../input/1_2_input.txt","r"))==NULL)
    {
        printf("cannot open input file\n");
        exit(0);
    }
    if((fp2 = fopen("../output/result_10.txt","w"))==NULL)
    {
        printf("cannot open result_10.txt\n");
        exit(0);
    }
    if((fp3 = fopen("../output/result_15.txt","w"))==NULL)
    {
        printf("cannot open result_15.txt\n");
        exit(0);
    }
    if((fp4 = fopen("../output/result_20.txt","w"))==NULL)
    {
        printf("cannot open result_20.txt\n");
        exit(0);
    }
    if((fp5 = fopen("../output/result_25.txt","w"))==NULL)
    {
        printf("cannot open result_25.txt\n");
        exit(0);
    }
    if((fp6 = fopen("../output/result_30.txt","w"))==NULL)
    {
        printf("cannot open result_30.txt\n");
        exit(0);
    }
    if((fp7 = fopen("../output/time.txt","w"))==NULL)
    {
        printf("cannot open time.txt\n");
        exit(0);
    }
    int number;  //用于计数
    int i, j, k, l, h;
    int begin, end;
    for (number = 0; number < 5; number++)
    {
        fscanf(fp1, "%d", &n);  // 读取序列长度
        int c[n+1][n+1], b[n+1][n+1];
        char x[n],y[n],z[n];
        fscanf(fp1, "%s", x);   //读取x序列
        fscanf(fp1, "%s", y);   //读取y序列
        begin = clock();
        // 计算LCS长度
        for (h = 0; h < 1000000; h++)
        {
            for (i = 1; i <= n; i++)
                c[i][0] = 0;
            for (j = 0; j <= n; j++)
                c[0][j] = 0;
            for (i = 1; i <= n; i++)
            {
                for (j = 1; j <= n; j++)
                {
                    if(x[i - 1] == y[j - 1])
                    {
                        c[i][j] = c[i - 1][j - 1] + 1;
                        b[i][j] = 1;
                    }
                    else if (c[i - 1][j] >= c[i][j - 1])
                    {
                        c[i][j] = c[i - 1][j];
                        b[i][j] = 0;
                    }
                    else
                    {
                        c[i][j] = c[i][j - 1];
                        b[i][j] = 0;
                    }
                }
            }
        }
        end = clock();
        fprintf(fp7, "%dns\n", end - begin);
        sum = 0;
        if (n == 10)
        {
            int tell = ftell(fp2);
            fprintf(fp2, "%d\n", 0);
            print_lcs(fp2, x, n, n, z, b, c);
            fseek(fp2, tell, SEEK_SET);
            fprintf(fp2, "%d\n", sum);
            fseek(fp2, 0, SEEK_END);
        }
        else if (n == 15)
        {
            int tell = ftell(fp3);
            fprintf(fp3, "%2d\n", 0);   // 输入一个空行
            print_lcs(fp3, x, n, n, z, b, c);
            fseek(fp3, tell, SEEK_SET);     // 回到文件头部
            fprintf(fp3, "%d\n", sum);      // 输入LCS个数
            fseek(fp3, 0, SEEK_END);    // 回到文件末尾
        }
        else if (n == 20)
        {
            int tell = ftell(fp4);
            fprintf(fp4, "%3d\n", 0);
            print_lcs(fp4, x, n, n, z, b, c);
            fseek(fp4, tell, SEEK_SET);
            fprintf(fp4, "%d\n", sum);
            fseek(fp4, 0, SEEK_END);
        }
        else if (n == 25)
        {
            int tell = ftell(fp5);
            fprintf(fp5, "%4d\n", 0);
            print_lcs(fp5, x, n, n, z, b, c);
            fseek(fp5, tell, SEEK_SET);
            fprintf(fp5, "%d\n", sum);
            fseek(fp5, 0, SEEK_END);
        }
        else if (n == 30)
        {
            int tell = ftell(fp6);
            fprintf(fp6, "%3d\n", 0);
            print_lcs(fp6, x, n, n, z, b, c);
            fseek(fp6, tell, SEEK_SET);
            fprintf(fp6, "%d\n", sum);
            fseek(fp6, 0, SEEK_END);
        }
    }
    //关闭输入输出文件
    fclose(fp1);
    fclose(fp2);
    fclose(fp3);
    fclose(fp4);
    fclose(fp5);
    fclose(fp6);
    fclose(fp7);
    return 0;
}