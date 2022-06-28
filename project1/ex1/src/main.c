#include<stdio.h>
#include<time.h>
#include<stdlib.h>
int n;

// 输出最优括号化方案
void print_parens(FILE *fp,int s[][n], int i, int j)
{
	if(i == j)
	{
		fprintf(fp, "A%d", i+1);
	}
	else
	{
		fprintf(fp, "(");
		print_parens(fp,s,i,s[i][j]);
		print_parens(fp,s,s[i][j]+1,j);
		fprintf(fp, ")");
	}
}

int main()
{
	FILE *fp1,*fp2,*fp3;
    // 打开输入输出文件
    if((fp1 = fopen("../input/1_1_input.txt","r"))==NULL)
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
    int number;  //用于计数
    int i, j, k, l, h;
    int begin, end;
    for (number = 0; number < 5; number++)
    {
        fscanf(fp1, "%d", &n);  // 读取矩阵个数
        long long p[n+1];
        long long m[n][n];
        int s[n][n];
        for (i = 0; i <= n; i++)
        {
            fscanf(fp1, "%lld", &p[i]);     // 读取矩阵大小向量
        } 
        begin = clock();
        for (h = 0; h < 1000000; h++)
        {
            for ( i = 0; i < n; i++)
            {
                m[i][i] = 0;
            }
            for (l = 2; l <= n; l++)
            {
                for (i = 0; i < n - l + 1; i++)
                {
                    j = i + l - 1;
                    m[i][j] = 9223372036854775807;
                    for (k = i ; k < j ; k++)
                    {
                        long long q = m[i][k] + m[k + 1][j] + p[i]*p[k + 1]*p[j + 1];
                        if (q < m[i][j])
                        {
                            m[i][j] = q;
                            s[i][j] = k;
                        }
                    }
                }
            }
        }    
        end = clock();
        if (n==5)
        {
            //打印计算表项m
            printf("m:\n");
            printf("\t4\t3\t2\t1\t0\n");
            for ( i = 0; i < n; i++)
            {
                printf("%d\t",i);
                for (j = n - 1; j >= i; j--)
                    printf("%lld\t", m[i][j]);
                printf("\n");
            }
            //打印计算表项s
            printf("s:\n");
            printf("\t3\t2\t1\t0\n");
            for ( i = 0; i < n - 1; i++)
            {
                printf("%d\t",i);
                for (j = n - 1; j >= i + 1; j--)
                    printf("%lld\t", s[i][j]);
                printf("\n");
            }
		}
        fprintf(fp2, "%lld\n", m[0][n-1]);  // 写入最少乘法运算次数
        print_parens(fp2,s,0,n-1);
        fprintf(fp2, "\n");
        fprintf(fp3, "%dns\n", end - begin);    // 写入运行时间
    }
    //关闭输入输出文件
    fclose(fp1);
    fclose(fp2);
    fclose(fp3);
    return 0;
}
