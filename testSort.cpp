#include <iostream>
#include <time.h>
#include <random>

using namespace std;
const int MAX = 10;

void print(int *a, int sz) {
	for (int i = 0; i < sz; i++)
		cout << a[i] << " ";
	cout << endl;
}
//基数排序
//msd testing not implementing


//lsd testing
void RadixSortLSD(int *a, int arraySize)
{
	int i, bucket[MAX], maxVal = 0, digitPosition = 1;
	for (i = 0; i < arraySize; i++) {
		if (a[i] > maxVal) maxVal = a[i];
	}

	int pass = 1;  // used to show the progress
	/* maxVal: this variable decide the while-loop count
	if maxVal is 3 digits, then we loop through 3 times */
	while (maxVal / digitPosition > 0) {
		/* reset counter */
		int digitCount[10] = { 0 };

		/* count pos-th digits (keys) */
		for (i = 0; i < arraySize; i++)
			digitCount[a[i] / digitPosition % 10]++;

		/* accumulated count */
		for (i = 1; i < 10; i++)
			digitCount[i] += digitCount[i - 1];

		/* To keep the order, start from back side */
		for (i = arraySize - 1; i >= 0; i--)
			bucket[--digitCount[a[i] / digitPosition % 10]] = a[i];

		/* rearrange the original array using elements in the bucket */
		for (i = 0; i < arraySize; i++)
			a[i] = bucket[i];

		/* at this point, a array is sorted by digitPosition-th digit */
		cout << "pass #" << pass++ << ": ";
		print(a, arraySize);

		/* move up the digit position */
		digitPosition *= 10;
	}
}

//桶排序
#include <iostream>
#include <iomanip>
using namespace std;

#define NARRAY 8  /* array size */
#define NBUCKET 5 /* bucket size */
#define INTERVAL 10 /* bucket range */

struct Node
{
	int data;
	struct Node *next;
};

void BucketSort(int arr[]);
struct Node *InsertionSort(struct Node *list);
void print(int arr[]);
void printBuckets(struct Node *list);
int getBucketIndex(int value);

void BucketSort(int arr[])
{
	int i, j;
	struct Node **buckets;

	/* allocate memory for array of pointers to the buckets */
	buckets = (struct Node **)malloc(sizeof(struct Node*) * NBUCKET);

	/* initialize pointers to the buckets */
	for (i = 0; i < NBUCKET; ++i) {
		buckets[i] = NULL;
	}

	/* put items into the buckets */
	for (i = 0; i < NARRAY; ++i) {
		struct Node *current;
		int pos = getBucketIndex(arr[i]);
		current = (struct Node *) malloc(sizeof(struct Node));
		current->data = arr[i];
		current->next = buckets[pos];
		buckets[pos] = current;
	}

	/* check what's in each bucket */
	for (i = 0; i < NBUCKET; i++) {
		cout << "Bucket[" << i << "] : ";
		printBuckets(buckets[i]);
		cout << endl;
	}

	/* sorting bucket using Insertion Sort */
	for (i = 0; i < NBUCKET; ++i) {
		buckets[i] = InsertionSort(buckets[i]);
	}

	/* check what's in each bucket */
	cout << "-------------" << endl;
	cout << "Bucktets after sorted" << endl;
	for (i = 0; i < NBUCKET; i++) {
		cout << "Bucket[" << i << "] : ";
		printBuckets(buckets[i]);
		cout << endl;
	}

	/* put items back to original array */
	for (j = 0, i = 0; i < NBUCKET; ++i) {
		struct Node *node;
		node = buckets[i];
		while (node) {
			arr[j++] = node->data;
			node = node->next;
		}
	}

	/* free memory */
	for (i = 0; i < NBUCKET; ++i) {
		struct Node *node;
		node = buckets[i];
		while (node) {
			struct Node *tmp;
			tmp = node;
			node = node->next;
			free(tmp);
		}
	}
	free(buckets);
	return;
}

/* Insertion Sort */
struct Node *InsertionSort(struct Node *list)
{
	struct Node *k, *nodeList;
	/* need at least two items to sort */
	if (list == 0 || list->next == 0) {
		return list;
	}

	nodeList = list;
	k = list->next;
	nodeList->next = 0; /* 1st node is new list */
	while (k != 0) {
		struct Node *ptr;
		/* check if insert before first */
		if (nodeList->data > k->data)  {
			struct Node *tmp;
			tmp = k;
			k = k->next;
			tmp->next = nodeList;
			nodeList = tmp;
			continue;
		}

		for (ptr = nodeList; ptr->next != 0; ptr = ptr->next) {
			if (ptr->next->data > k->data) break;
		}

		if (ptr->next != 0){
			struct Node *tmp;
			tmp = k;
			k = k->next;
			tmp->next = ptr->next;
			ptr->next = tmp;
			continue;
		}
		else{
			ptr->next = k;
			k = k->next;
			ptr->next->next = 0;
			continue;
		}
	}
	return nodeList;
}

int getBucketIndex(int value)
{
	return value / INTERVAL;
}

void print(int ar[])
{
	int i;
	for (i = 0; i < NARRAY; ++i) {
		cout << setw(3) << ar[i];
	}
	cout << endl;
}

void printBuckets(struct Node *list)
{
	struct Node *cur = list;
	while (cur) {
		cout << setw(3) << cur->data;
		cur = cur->next;
	}
}

int tongsort(void)
{
	//int array[NARRAY] = { 29, 25, 3, 49, 9, 37, 21, 43 };
	int array[NARRAY] = { 9, 2, 8, 49, 6, 7, 1, 3 };
	cout << "Initial array" << endl;
	print(array);
	cout << "-------------" << endl;

	BucketSort(array);
	cout << "-------------" << endl;
	cout << "Sorted array" << endl;
	print(array);
	return 0;
}

#include <assert.h>
//计数排序
void CountSort(int* array, int size)
{
	assert(array);
	int max = array[0];//序列中的最大值
	int min = array[0];//序列中的最小值
	for (int i = 0; i < size; ++i)
	{
		if (array[i] >= max)
		{
			max = array[i];
		}
		if (array[i] < min)
		{
			min = array[i];
		}
	}
	int range = max - min + 1;//需要开辟的空间大小
	int* count = new int[range];
	memset(count, 0, sizeof(int)*range);//辅助空间初始化为0,0代表没有那个数

	for (int i = 0; i < size; ++i)
	{
		count[array[i] - min]++;//array[i]-min是将该数对应到辅助空间的下标
	}
	int index = 0;
	for (int i = 0; i < range; ++i)//遍历辅助空间
	{
		while (count[i]--)//下标处的数值是几，说明该数出现了几次
		{
			array[index++] = i + min;//将下标处的数对应回原数组
		}
	}
	delete[] count;
	for (int i = 0; i < size; i++)
	{
		cout << array[i] << ",";
	}
}

#define SWAP(type, a , b) {\
	type tmp; \
	tmp = a; \
	a = b; \
	b = tmp; }

#define SIZE 1028

void quickSort(int *arr, int left, int right)
{
	int pivot = arr[left];
	int p = left;
	int q = right;
	static int cnt = 0;
	p++;
	if (left >= right)
	{
		return;
	}
	while (p < q)
	{
		while (p < q && pivot >= arr[p])
		{
			p++;
		}
		while (p < q && pivot <= arr[q])
		{
			q--;
		}
		if (p < q)
		{
			SWAP(int, arr[p], arr[q]);
		}
	}
	if (pivot < arr[p])
	{
		p--;
	}
	SWAP(int, arr[left], arr[p]);
	cnt++;
	cout << "count : " << cnt << endl;
	for (int i = 0; i < SIZE; i++)
	{
		cout << arr[i] << ",";
	}
	cout << endl;
	quickSort(arr, left, p - 1);
	quickSort(arr, p + 1, right);
}

struct Range {
	int start, end;
	Range(int s = 0, int e = 0) {
		start = s, end = e;
	}
};
template <typename T> // 整數或浮點數皆可使用,若要使用物件(class)時必須設定"小於"(<)、"大於"(>)、"不小於"(>=)的運算子功能
void quick_sort(T arr[], const int len) {
	if (len <= 0)
		return; // 避免len等於負值時宣告堆疊陣列當機
	// r[]模擬堆疊,p為數量,r[p++]為push,r[--p]為pop且取得元素
	Range r[len];
	int p = 0;
	r[p++] = Range(0, len - 1);
	while (p) {
		Range range = r[--p];
		if (range.start >= range.end)
			continue;
		T mid = arr[range.end];
		int left = range.start, right = range.end - 1;
		while (left < right) {
			while (arr[left] < mid && left < right) left++;
			while (arr[right] >= mid && left < right) right--;
			std::swap(arr[left], arr[right]);
		}
		if (arr[left] >= arr[range.end])
			std::swap(arr[left], arr[range.end]);
		else
			left++;
		r[p++] = Range(range.start, left - 1);
		r[p++] = Range(left + 1, range.end);
	}
}

#include <stack>

void NewQuickSort(int *tlist, int size)
{
	stack<int> pos;
	stack<pair<int, int>> ps;
	pair<int, int> pr;
	ps.push(make_pair(0, size - 1));
	//ps.push(pair<int, int>(0, size - 1));
	//pos.push(0);
	//pos.push(size - 1);
	while (!ps.empty())
	{
		//int right = pos.top();
		//pos.pop();
		//int left = pos.top();
		//pos.pop();
		pr = ps.top();
		ps.pop();
		int left = pr.first;
		int right = pr.second;

		int i = left, j = right;
		int pivot = tlist[i];
		i++;
		if (left >= right)
		{
			continue;
		}
		while (i < j)
		{
			while (i < j && pivot >= tlist[i])
			{
				i++;
			}
			while (i < j && pivot <= tlist[j])
			{
				j--;
			}
			if (i < j)
			{
				SWAP(int, tlist[i], tlist[j]);
			}
		}
		if (pivot < tlist[i])
		{
			i--;
		}
		SWAP(int, tlist[left], tlist[i]);
		//for (int ii = 0; ii < SIZE; ii++)
		//{
		//	cout << tlist[ii] << ",";
		//}
		//cout << endl;
		//pos.push(left);
		//pos.push(i - 1);
		//pos.push(i + 1);
		//pos.push(right);
		ps.push(make_pair(left, i - 1));
		ps.push(make_pair(i + 1, right));
	}
}

void testQS()
{
	int nlist[SIZE];
	srand(time(NULL));
	for (int i = 0; i < SIZE; i++)
	{
		nlist[i] = rand() % SIZE;
		cout << "," << nlist[i];
	}
	cout << endl;
	//quickSort(nlist, 0, SIZE - 1);
	NewQuickSort(nlist, SIZE);
	cout << "Sort After" << endl;
	for (int i = 0; i < SIZE; i++)
	{
		cout << nlist[i] << ",";
	}
	cout << endl;
}

void quickSort2(int a[], int left, int right)
{
	int i = left;
	int j = right;
	int temp = a[left];
	if (left >= right)
		return;
	while (i != j)
	{
		while (i<j&&a[j] >= temp)
			j--;
		if (j>i)
			a[i] = a[j];//a[i]已经赋值给temp,所以直接将a[j]赋值给a[i],赋值完之后a[j],有空位
		while (i<j&&a[i] <= temp)
			i++;
		if (i<j)
			a[j] = a[i];
	}
	a[i] = temp;//把基准插入,此时i与j已经相等R[low..pivotpos-1].keys≤R[pivotpos].key≤R[pivotpos+1..high].keys
	quickSort2(a, left, i - 1);/*递归左边*/
	quickSort2(a, i + 1, right);/*递归右边*/
}


int main111()
{
	int a[] = { 17, 45, 75, 90, 2, 24, 80, 66, 100, 120, 99, 10, 12,13 };
	const size_t sz = sizeof(a) / sizeof(a[0]);

	//cout << "Count Sort " << endl;
	//CountSort(a, sz);
	//cout << endl;
	//cout << "pass #0: ";
	//print(a, sz);
	//RadixSortLSD(&a[0], sz);
	//cout << endl;
	testQS();
	//tongsort();
	return 0;
}