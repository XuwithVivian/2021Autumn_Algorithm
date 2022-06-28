#include<stdio.h>
#include<time.h>
#include<math.h>
#include<stdlib.h>
#include<windows.h>

typedef struct FibNode
{
    struct FibNode *p;
    struct FibNode *child;
    struct FibNode *left;
    struct FibNode *right;
    int key;
    int degree;
    int mark;
}FibNode;

typedef struct H
{
    int n;
    FibNode *min;
}H;

FibNode *nodes[1001];

H *make_heap()
{
    H *Heap = (H*)malloc(sizeof(H));
    Heap->min = NULL;
    Heap->n = 0;
    return Heap;
}

int insert(H *heap, int x)
{
    FibNode *node;
    node = (FibNode*)malloc(sizeof(FibNode));
    node->p = NULL;
    node->key = x;
    node->child = NULL;
    node->mark = 0;
    node->degree = 0;
    if (heap->min == NULL)
    {
        node->right = node;
        node->left = node;
        heap->min = node;
    }
    else
    {
        node->right = heap->min->right;
        node->left = heap->min;
        heap->min->right->left = node;
        heap->min->right = node;
        if (x < heap->min->key)
            heap->min = node;
    }
    heap->n++;
    nodes[x] = node;
    return heap->n;
}

void cut(H *heap, FibNode *x, FibNode *y)
{
    if (x == y->child)
    {
        if (x->right != x)
            y->child = x->right;
        else
            y->child = NULL;
    }
    x->p = NULL;
    y->degree--;
    x->left->right = x->right;
    x->right->left = x->left;
    x->right = heap->min->right;
    x->left = heap->min;
    heap->min->right->left = x;
    heap->min->right = x;
    x->mark = 0;
}

void cascanding_cut(H *heap, FibNode *y)
{
    FibNode *z;
    z = y->p;
    if (z != NULL)
    {
        if (y->mark == 0)
            y->mark = 1;
        else
        {
            cut(heap, y, z);
            cascanding_cut(heap, z);
        }
    }
}

FibNode *decrease_key(H *heap, FibNode *x, int k)
{
    if (k > x->key)
    {
        printf("new key is greater than current key!\n");
        exit(0);
    }
    nodes[k] = x;
	nodes[x->key] = NULL;
    x->key = k;
    FibNode *y;
    y = x->p;
    if(y != NULL && x->key < y->key)
    {
        cut(heap, x, y);
        cascanding_cut(heap, y);
    }
    if (x->key < heap->min->key)
        heap->min = x;
    return heap->min;
}

void link(H *heap, FibNode *y, FibNode *x){
    FibNode *node;
    y->left->right=y->right;
    y->right->left=y->left;
    if(x->child==NULL){
        x->child=y;
        y->right=y;
        y->left=y;
        y->p=x;
    }
    else{
        node=x->child;
        node->right->left=y;
        y->right=node->right;
        y->left=node;
        node->right=y;
        y->p=x;
    }
    x->degree++;
    y->mark=0;
}


void consolidate(H *heap)
{
    int n = log2(heap->n);
    int d;
    FibNode *A[n+1];
    FibNode *x, *y, *swap;
    for (int i = 0; i <= n; i++)
        A[i] = NULL;
    int root = 1;
    FibNode *w = heap->min->left;
    FibNode *w_bro = heap->min;
    do
    {
        x = w_bro;
        d = x->degree;
        if (w == w_bro)
            root = 0;
        w_bro = w_bro->right;
        while (A[d] != NULL)
        {
            y = A[d];
            if (x->key > y->key)
            {
                swap = x;
                x = y;
                y = swap;
            }
            link(heap, y, x);
            A[d] = NULL;
            d++;
        }
        A[d] = x;
    }while(root);
    heap->min = NULL;
    for (int i = 0; i <= n; i++)
    {
        if(A[i] != NULL)
        {
            if(heap->min == NULL)
            {
                heap->min = A[i];
                heap->min->p = NULL;
                heap->min->left = heap->min;
                heap->min->right = heap->min;
            }
            else
            {
                A[i]->right = heap->min->right;
                heap->min->right->left = A[i];
                A[i]->left = heap->min;
                heap->min->right = A[i];
                if (A[i]->key < heap->min->key)
                    heap->min = A[i];
            }
        }
    }
}

FibNode *extract_min(H *heap)
{
    FibNode *z = heap->min;
    FibNode *x, *y;
    int i;
    nodes[heap->min->key] = NULL;
    if (z != NULL)
    {
        if (z->child != NULL)
        {
            y = z->child;
            for (i = 0; i < z->degree; i++)
            {
                x = y;
                y = y->right;
                x->p = NULL;
                x->left = heap->min;
                x->right = heap->min->right;
                heap->min->right->left = x;
                heap->min->right = x;
            }
        }
        z->child = NULL;
        z->degree = 0;
        z->left->right = z->right;
        z->right->left = z->left;
        heap->n--;
        if (z == z->right)
            heap->min = NULL;
        else
        {
            heap->min = z->right;
            consolidate(heap);
        }
    }
    return z;
}

int delete(H *heap, FibNode *x)
{
    decrease_key(heap, x, 0);
    FibNode *y = extract_min(heap);
    nodes[x->key] = NULL;
    return heap->n;
}

H *Union(H *H1, H *H2)
{
    H *heap;
    heap = make_heap();
    heap->min = H1->min;
    int i, j;
    i = j = 0;
    H1->min->right->left = H2->min->left;
    H2->min->left->right = H1->min->right;
    H1->min->right = H2->min;
    H2->min->left = H1->min;
    if (H1->min == NULL || (H2->min != NULL && H2->min->key < H1->min->key))
        heap->min = H2->min;
    heap->n = H1->n + H2->n;
    return heap;
}

int main()
{
    FILE *fp1, *fp2, *fp3;
    // 打开输入输出文件
    if((fp1 = fopen("../input/2_1_input.txt","r"))==NULL)
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
    H *H1, *H2, *H3, *H4, *H5;
    H1 = make_heap();
    H2 = make_heap();
    H3 = make_heap();
    H4 = make_heap();
    H5 = make_heap();
    int i, val, num;
    LONGLONG begin, over, freq;
    clock_t end, start;
    LARGE_INTEGER number;
    QueryPerformanceFrequency(&number);
    freq = number.QuadPart;
    double time;
    FibNode *node;
    for (i = 0; i < 50; i++)
    {
        fscanf(fp1, "%d", &val);
        num = insert(H1, val);
    }
    for (i = 0; i < 100; i++)
    {
        fscanf(fp1, "%d", &val);
        num = insert(H2, val);
    }
    for (i = 0; i < 150; i++)
    {
        fscanf(fp1, "%d", &val);
        num = insert(H3, val);
    }
    for (i = 0; i < 200; i++)
    {
        fscanf(fp1, "%d", &val);
        num = insert(H4, val);
    }
    // H1
    fprintf(fp2, "H1\n");
    QueryPerformanceFrequency(&number);
    freq = number.QuadPart;
    QueryPerformanceCounter(&number);
    begin = number.QuadPart;
    start = clock();
    num = insert(H1, 249);
    fprintf(fp2, "%d,", num);
    num = insert(H1, 830);
    fprintf(fp2, "%d,", num);
    fprintf(fp2, "%d,", H1->min->key);
    
    num = delete(H1, nodes[127]);
    fprintf(fp2, "%d,", num);
    num = delete(H1, nodes[141]);
    fprintf(fp2, "%d,", num);
    fprintf(fp2, "%d,", H1->min->key);

    node = decrease_key(H1, nodes[75], 61);
    fprintf(fp2, "%d,", node->key);
    node = decrease_key(H1, nodes[198], 169);
    fprintf(fp2, "%d,", node->key);
    
    node = extract_min(H1);
    fprintf(fp2, "%d,", node->key);
    node = extract_min(H1);
    fprintf(fp2, "%d\n", node->key);
    end = clock();
    QueryPerformanceCounter(&number);
    over = number.QuadPart;
    time = (double)(end - start);
    fprintf(fp3, "step2:%lld\n", (over - begin)*10000000/freq);
    // H2
    fprintf(fp2, "H2\n");
    QueryPerformanceFrequency(&number);
    freq = number.QuadPart;
    QueryPerformanceCounter(&number);
    begin = number.QuadPart;
    start = clock();
    num = insert(H2, 816);
    fprintf(fp2, "%d,", num);
    fprintf(fp2, "%d,", H2->min->key);

    num = insert(H2, 345);
    fprintf(fp2, "%d,", num);

    node = extract_min(H2);
    fprintf(fp2, "%d,", node->key);

    num = delete(H2, nodes[504]);
    fprintf(fp2, "%d,", num);
    num = delete(H2, nodes[203]);
    fprintf(fp2, "%d,", num);

    node = decrease_key(H2, nodes[296], 87);
    fprintf(fp2, "%d,", node->key);
    node = decrease_key(H2, nodes[278], 258);
    fprintf(fp2, "%d,", node->key);

    fprintf(fp2, "%d,", H2->min->key);
    node = extract_min(H2);
    fprintf(fp2, "%d\n", node->key);
    end = clock();
    QueryPerformanceCounter(&number);
    over = number.QuadPart;
    time = (double)(end - start);
    fprintf(fp3, "step3:%lld\n", (over - begin)*10000000/freq);
    // H3
    fprintf(fp2, "H3\n");
    QueryPerformanceFrequency(&number);
    freq = number.QuadPart;
    QueryPerformanceCounter(&number);
    begin = number.QuadPart;
    start = clock();
    node = extract_min(H3);
    fprintf(fp2, "%d,", node->key);
    fprintf(fp2, "%d,", H3->min->key);

    num = insert(H3, 262);
    fprintf(fp2, "%d,", num);

    node = extract_min(H3);
    fprintf(fp2, "%d,", node->key);

    num = insert(H3, 832);
    fprintf(fp2, "%d,", num);

    fprintf(fp2, "%d,", H3->min->key);
    num = delete(H3, nodes[134]);
    fprintf(fp2, "%d,", num);
    num = delete(H3, nodes[177]);
    fprintf(fp2, "%d,", num);

    node = decrease_key(H3, nodes[617], 360);
    fprintf(fp2, "%d,", node->key);
    node = decrease_key(H3, nodes[889], 353);
    fprintf(fp2, "%d\n", node->key);
    end = clock();
    QueryPerformanceCounter(&number);
    over = number.QuadPart;
    time = (double)(end - start);
    fprintf(fp3, "step4:%lld\n", (over - begin)*10000000/freq);
    // H4
    fprintf(fp2, "H4\n");
    QueryPerformanceFrequency(&number);
    freq = number.QuadPart;
    QueryPerformanceCounter(&number);
    begin = number.QuadPart;
    start = clock();
    fprintf(fp2, "%d,", H4->min->key);
    num = delete(H4, nodes[708]);
    fprintf(fp2, "%d,", num);

    num = insert(H4, 281);
    fprintf(fp2, "%d,", num);
    num = insert(H4, 347);
    fprintf(fp2, "%d,", num);
    fprintf(fp2, "%d,", H4->min->key);

    num = delete(H4, nodes[415]);
    fprintf(fp2, "%d,", num);

    node = extract_min(H4);
    fprintf(fp2, "%d,", node->key);

    node = decrease_key(H4, nodes[620], 354);
    fprintf(fp2, "%d,", node->key);
    node = decrease_key(H4, nodes[410], 80);
    fprintf(fp2, "%d,", node->key);

    node = extract_min(H4);
    fprintf(fp2, "%d\n", node->key);
    end = clock();
    QueryPerformanceCounter(&number);
    over = number.QuadPart;
    time = (double)(end - start);
    fprintf(fp3, "step5:%lld\n", (over - begin)*10000000/freq);
    // H5
    H5 = Union(H1, Union(H2, Union(H3, H4)));
    fprintf(fp2, "H5\n");
    QueryPerformanceFrequency(&number);
    freq = number.QuadPart;
    QueryPerformanceCounter(&number);
    begin = number.QuadPart;
    start = clock();
    node = extract_min(H5);
    fprintf(fp2, "%d,", node->key);
    fprintf(fp2, "%d,", H5->min->key);

    num = delete(H5, nodes[800]);
    fprintf(fp2, "%d,", num);

    num = insert(H5, 267);
    fprintf(fp2, "%d,", num);
    num = insert(H5, 351);
    fprintf(fp2, "%d,", num);

    node = extract_min(H5);
    fprintf(fp2, "%d,", node->key);

    node = decrease_key(H5, nodes[478], 444);
    fprintf(fp2, "%d,", node->key);
    node = decrease_key(H5, nodes[559], 456);
    fprintf(fp2, "%d,", node->key);
    fprintf(fp2, "%d,", H5->min->key);

    num = delete(H5, nodes[929]);
    fprintf(fp2, "%d\n", num);
    end = clock();
    QueryPerformanceCounter(&number);
    over = number.QuadPart;
    time = (end - start);
    fprintf(fp3, "step7:%lld\n", (over - begin)*10000000/freq);
    //关闭输入输出文件
    fclose(fp1);
    fclose(fp2);
    fclose(fp3);
    return 0;
}
