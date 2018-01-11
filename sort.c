#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "stdint.h"
#include "stdbool.h"

#include "time.h"


#define LENGTH_OF(x)   (sizeof(x)/sizeof(*x))   //求数组元素个数

#define ARRAY_COUNT    (20480000)  //排序元素个数
//#define __DEBUG   //排序过程输出调试
//#define __INPUT   //输出排序前的数据
//#define __OUTPUT  //输出排序后的数据

/*  
 *排序算法测试，升序
 */

//打印排序中数组内容
void print(int *a, int n, int i)
{
#ifdef __DEBUG
	printf("第%d趟:\t", i + 1);
	for (int j = 0; j < n; j++)
	{
		printf("%d ", a[j]);
	}
	printf("\n");
#endif
}

// 交换两个数
void swap(int *a, int *b)
{
	int temp = 0;

	temp = *a;
	*a = *b;
	*b = temp;
}

/* */


//直接插入排序
void InsertSort(int *a, int n)
{
	int i = 0, j = 0, cur = 0;

	for (i = 1; i < n; i++)  //开始将第一个元素作为有序表，逐步将之后的元素插入到有序表中
	{
		if (a[i] < a[i - 1])  //要排序的元素小于有序表最后一个元素（最大值），将其插入到前面的有序表中
		{
			cur = a[i];  //保存要插入的元素
			j = i - 1;   //从有序表末尾开始比较插入
			do
			{
				a[j + 1] = a[j];  //依次将比要插入的元素大的元素后移
			} while ((--j >= 0) && (cur < a[j]));
			a[j + 1] = cur;  //插入元素到有序表
		}

		print(a, n, i);
	}

}

//希尔排序
/* */
/* 直接插入排序的一般形式，按增量dk进行直接插入排序，当dk=1时即为直接插入排序 */
void ShellInsertSort(int *a, int n, int dk)
{
	int i = 0, j = 0, cur = 0;

	for (i = dk; i < n; i++)   //开始将以dk为间隔的序列中的第一个元素作为有序表，逐步将序列中之后的元素插入到有序表中
	{
		if (a[i] < a[i - dk])  //序列中要排序的元素小于有序表最后一个元素（最大值），将其插入到前面的有序表中
		{
			cur = a[i];  //待插入的元素
			j = i - dk;  //从有序表末尾开始比较并插入
			do
			{
				a[j + dk] = a[j];  //依次将比要插入的元素大的元素后移增量dk
				j -= dk;
			} while ((j >= 0) && (cur < a[j]));
			a[j + dk] = cur;   //将待排序元素插入到有序表中
		}
	}
}

/* 希尔排序，依次取增量dk=n/2,n/4,n/8...1对分割的序列进行一般插入排序 */
void ShellSort(int *a, int n)
{
	int dk = n / 2;   //初始增量取n/2

	while (dk >= 1)
	{
		ShellInsertSort(a, n, dk);
		dk /= 2;  //dk每次缩减一半
	}
}

/* */

//简单选择排序
void SelectSort(int *a, int n)
{
	int i = 0, j = 0, min_index = 0;
	int temp = 0;

	for (i = 0; i < n - 1; i++)
	{
		min_index = i;  //开始将待排序的第一个元素作为最小值
		for (j = i + 1; j < n; j++)  //找出待排序元素中的最小值交换到待排序的第一个位置
		{
			if (a[j] < a[min_index])
			{
				min_index = j;
			}
		}
		if (min_index != i)  //最小值不是待排序的第一个元素，交换
		{
			temp = a[i];
			a[i] = a[min_index];
			a[min_index] = temp;
		}
	}
}

//二元选择排序
void BiSelectSort(int a[], int n)
{
	int i = 0, j = 0, min_index = 0, max_index = 0;
	int temp = 0;

	for (i = 0; i <= n / 2; i++)   //找出待排序元素中的最大值和最小值分别放到待排序的第一个和最后一个位置
	{
		min_index = i;
		max_index = i;// n - i - 1;
		for (j = i; j < n - i; j++)
		{
			if (a[j] < a[min_index])
			{
				min_index = j;
			}
			if (a[j]>a[max_index])
			{
				max_index = j;
			}
		}
		if (min_index != i)  //最小值不是待排序的第一个元素，交换
		{
			//这里交换前要注意，首先交换最小值时，如果当前最大值处于要交换的位置，即待排序元素的第一个位置时，交换后实际最大值位置发生改变，所以需要调整max_index到交换后的位置
			if (max_index == i)
			{
				max_index = min_index;
			}

			temp = a[i];
			a[i] = a[min_index];
			a[min_index] = temp;
		}
		if (max_index != i/*n - i - 1*/)   //最大值不是待排序的最后一个元素，交换
		{
			temp = a[n - i - 1];
			a[n - i - 1] = a[max_index];
			a[max_index] = temp;
		}

		print(a, n, i);
	}
}

//冒泡排序
void BubbleSort(int *a, int n)
{
	int i = 0, j = 0;
	int temp = 0;

	for (i = 0; i < n - 1; i++)
	{
		for (j = 1; j < n - i; j++)   //每次冒泡将本次的最大值放到数组最后，这些元素不再参与冒泡比较，这里注意内循环次数
		{
			if (a[j] < a[j - 1])   //相邻元素比较，将较小的元素交换到前面，较大值放到后面
			{
				temp = a[j - 1];
				a[j - 1] = a[j];
				a[j] = temp;
			}
		}

		print(a, n, i);
	}
}

//快速排序
/*  */
/* 进行一次数据分割，将一个基准元素放到排好序的正确位置，被基准元素分割的两部分一部分元素都比它小，另一部分比它大,返回基准元素最终位置 */
int partition(int *a, int low, int high)
{
	//随机选择一个枢轴值并交换到a[low]处
	//int r = rand() % (high - low);
	//swap(&a[low], &a[low + r]);

	int pivotKey = a[low];   //选择第一个元素作为基准元素

	while (low < high)    //从表的两端交替向中间扫描
	{
		while ((low < high) && (a[high] >= pivotKey))  high--;   //从high位置开始向前搜索到low+1的位置，遇到比基准元素小的元素时跳出循环并将其交换到低端
		//swap(&a[low], &a[high]);
		a[low] = a[high];

		while ((low < high) && (a[low] <= pivotKey))  low++;     //从low位置开始向后搜索到high-1的位置，遇到比基准元素大的元素时跳出循环并将其交换到高端
		//swap(&a[low], &a[high]);
		a[high] = a[low];

	}
	a[low] = pivotKey;

	return low;   //返回基准元素的最终位置
}

/* 快速排序，递归实现，对一组数进行分割，再对分割后的子序列进行分割直到全部完成排序 */
void _QuickSort(int *a, int low, int high)
{
	int pivotKey = 0;

	if (low < high)
	{
		pivotKey = partition(a, low, high);   //先进行一次分割将表一分为二
		_QuickSort(a, low, pivotKey - 1);     //递归对低子表递归排序
		_QuickSort(a,pivotKey + 1, high);     //递归对高子表递归排序
	}

	return;
}

/* 快速排序外部封装，保持和其它排序一样的接口 */
void QuickSort(int *a, int n)
{
	_QuickSort(a, 0, n - 1);
}


//堆排序
/* 将一个元素向下调整，注意堆为从0 ～ (n-1)编号,结点i的左右孩子分别为2(i+1)-1和2(i+1) */
void AdjustDown(int *a, int k, int n)
{
	int tmp = a[k];     //暂存待调整元素
	int i = 0;

	for (i = 2 * (k + 1) - 1; i < n; i = (i + 1) * 2 - 1)  //沿key较大子结点向下筛选
	{
		if ((i < n - 1) && (a[i] < a[i + 1])) i++;         //取key较大的子节点的下标用以对比筛选

		if (tmp>a[i]) break;    //双亲结点key已经比孩子中较大的大，符合大根堆定义，筛选结束
		else
		{
			a[k] = a[i];        //将子女中key较大的a[i]调整到双亲结点上
			k = i;              //修改k为刚调整过的子女结点的下标，继续对其子树进行筛选
		}
	}
	a[k] = tmp;                 //被筛选结点的值放入最终位置
}
/* 建立大根堆，注意堆为从0 ～ (n-1)编号,结点i的左右孩子分别为2(i+1)-1和2(i+1) */
void BuildMaxHeap(int *a, int n)
{
	int i = 0;
	for (i = n / 2 - 1; i >= 0; i--)  //从(⌊n/2⌋-1) ～ 0，反复调整堆
	{
		AdjustDown(a, i, n);
	}
}

/* 堆排序，注意堆为从0 ～ (n-1)编号,结点i的左右孩子分别为2(i+1)-1和2(i+1) */
void HeapSort(int *a, int n)
{
	int i = 0;

	BuildMaxHeap(a, n);            //建立初始堆（大根堆）
	for (i = n - 1; i > 0; i--)    //n-1趟交换和再建堆过程，从(n-1) ～ 1
	{
		swap(&a[i], &a[0]);        //将堆顶元素（大根堆中为最大值）和堆底元素（最后一个元素）交换，确定此次的最大值位置
		AdjustDown(a, 0, i);       //调整刚交换上来的堆顶元素，将剩余i个元素再整理成大根堆
		
		print(a, n, i);
	}
}


//归并排序
/* 将一个数组中相邻的两段有序表合并为一个有序表，即a[low...mid]和a[mid+1...high] */
static int b[ARRAY_COUNT+1] = { 0 }; //需要一个辅助数组
void Merge(int *a, int low, int mid, int high)
{
	int i = 0, j = 0, k = 0;

	memcpy(b + low, a + low, sizeof(int)*(high - low + 1));  //将此次合并的两个表中数据复制到辅助数组

	for (i = low, j = mid + 1, k = i; (i <= mid) && (j <= high); k++)
	{
		if (b[i] <= b[j])   //比较两个有序表数据，将较小值复制回a中
		{
			a[k] = b[i++];
		}
		else
		{
			a[k] = b[j++];
		}
	}
	while (i <= mid)  a[k++] = b[i++];   //若第一个表有剩余元素，复制
	while (j <= high) a[k++] = b[j++];   //若第二个表有剩余元素，复制
}

/* 2路归并排序 */
void _MergeSort(int *a, int low, int high)
{
	int mid = 0;
	if (low < high)
	{
		mid = (low + high) / 2;          //从中间分为两个子序列
		_MergeSort(a, low, mid);         //对左侧序列递归归并排序
		_MergeSort(a, mid + 1, high);    //对右侧序列递归归并排序
		Merge(a, low, mid, high);        //归并
	}
}
/* 2路归并排序，封装使接口一样 */
void MergeSort(int *a, int n)
{
	_MergeSort(a, 0, n - 1);
}


/* */





int main(int argc, char *argv[])
{
	char input_buf[1024] = { 0 };    //输入缓存

	//待排序数组原始值备份
	//int array[] = { 20, 19, 18, 17, 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0, -1, -2, -3 };
	//int array[] = { -12, 2, 19, 8, 17, 6, 1, 101, 13, 13, 12, 51, 70, 9, 7, 10, 21, 15, 14, 23, 22, 21, 30, -1, -2, -3, 14, 12, 13, 91 };
	static int array_back[ARRAY_COUNT] = { 0 };
	static int array[ARRAY_COUNT] = { 0 };

	//利用随机数生成待排序数初值
	for (int i = 0; i < LENGTH_OF(array_back); i++)
	{
		int num = rand();
		if (ARRAY_COUNT < RAND_MAX)
		{
			array_back[i] = num%ARRAY_COUNT;
		}
		else
		{
			array_back[i] = num;
		}
	}

	while (1)
	{
		char *str = input_buf;  //指向输入缓存
		size_t len = 0;  //输入字符串长度

		printf("please input command:\n");
		fgets(input_buf, sizeof(input_buf), stdin);  //从stdin得到输入，以'\n'结尾
		len = strlen(str);
		//去除末尾的'\n'
		*(str + len - 1) = '\0';
		len -= 1;
		printf("len=%lld,input string:%s\n", len, str);


		if (strncmp(str, "sort",4) == 0)  //排序
		{
			memcpy(array, array_back, sizeof(array));  //每次重新填充为原始值

			printf("original:\t");
#ifdef __INPUT
			for (int i = 0; i < LENGTH_OF(array); i++)
			{
				printf("%d ", array[i]);
			}
#endif
			printf("\n");

			clock_t start = 0, end = 0;

			start = clock();  //得到起始CPU时间

			if (strcmp(str + 4, "insert") == 0)
			{
				//直接插入排序
				InsertSort(array, LENGTH_OF(array));
				printf("InsertSort:\t");
			}
			else if (strcmp(str + 4, "shell") == 0)
			{
				//希尔排序
				ShellSort(array, LENGTH_OF(array));
				printf("ShellSort:\t");
			}
			else if (strcmp(str + 4, "select") == 0)
			{
				//简单选择排序
				SelectSort(array, LENGTH_OF(array));
				printf("SelectSort:\t");
			}
			else if (strcmp(str + 4, "biselect") == 0)
			{
				//二元选择排序
				BiSelectSort(array, LENGTH_OF(array));
				printf("BiSelectSort:\t");
			}
			else if (strcmp(str + 4, "bubble") == 0)
			{
				//冒泡排序
				BubbleSort(array, LENGTH_OF(array));
				printf("BubbleSort:\t");
			}
			else if (strcmp(str + 4, "quick") == 0)
			{
				//快速排序
				QuickSort(array, LENGTH_OF(array));
				printf("QuickSort:\t");
			}
			else if (strcmp(str + 4, "heap") == 0)
			{
				//堆排序
				HeapSort(array, LENGTH_OF(array));
				printf("HeapSort:\t");
			}
			else if (strcmp(str + 4, "merge") == 0)
			{
				//归并排序
				MergeSort(array, LENGTH_OF(array));
				printf("MergeSort:\t");
			}


			else
			{
				printf("not sort:\t");
			}

			end = clock();   //得到结束CPU时间

			//排序后的数据
			for (int i = 0; i < LENGTH_OF(array); i++)
			{
				//检查升序排序是否正确
				if ((i<LENGTH_OF(array) - 1) && (array[i]>array[i + 1]))
				{
					printf("ERROR:%d,%d\n", array[i], array[i + 1]);
				}
#ifdef __OUTPUT
				printf("%d ", array[i]);
#endif
			}
			printf("\n");

			printf("start=%ld,end=%ld,time=%ld\n", start, end, end - start);
		}
		else if (strcmp(str, "heap") == 0)
		{
			uint8_t *p = NULL;
			uint64_t size = 8 * 1024 * 1024 * 1024ull;

			p = (uint8_t *)malloc(size);
			if (p == NULL)
			{
				printf("malloc failed!\n");
				perror("malloc");
			}
			else
			{
				memset(p, 'c', size);

				system("pause");
				free(p);
			}
		}

		else
		{
			/* */
		}

		memset(input_buf, 0, sizeof(input_buf));  //清空输入缓存
		
	}
}