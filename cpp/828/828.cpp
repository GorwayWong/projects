#include <iostream>
#define MaxSize 50

int swap(int& a, int& b) {
	int temp;
	temp = a;
	a = b;
	b = temp;
}

// 顺序表
typedef struct SqList{
	int data[MaxSize];
	int length;
}SqList;

// 链表
typedef struct LNode {
	int data;
	struct LNode* next;
}LNode, * LinkList;

// 栈
typedef struct SqStack{
	int data[MaxSize];
	int top;
}SqStack;

// 队列
typedef struct SqQueue{
	int data[MaxSize];
	int front, rear;
}SqQueue;

// 链队
typedef struct LinkNode {
	int data;
	struct LinkNode* next;
}LinkNode;

typedef struct LinkQueue{
	LinkNode* front, * rear;
}LinkQueue;

// 二叉树
typedef struct BiTNode {
	int data;
	struct BiTNode* lchild, * rchild;
}BiTNode, * BiTree;

#define MAX_VERTEX_NUM 10
typedef char VertexType;
typedef int EdgeType;
typedef struct {
	VertexType vex[MAX_VERTEX_NUM];//顶点表
	EdgeType edge[MAX_VERTEX_NUM][MAX_VERTEX_NUM];//边表
	int vexnum, arcnum;//图的当前顶点数和边数
}MGraph;

//二分查找
int BinarySearch(SqList L,int key) {
	int low = 0, high = L.length - 1, mid;
	while (low <= high) {
		mid = (low + high) / 2;
		if (L.data[mid] == key) {
			return mid;
		}
		else if (L.data[mid] > key) {
			high = mid - 1;
		}
		else {
			low = mid + 1;
		}
	}
	return -1;
}

// 插入排序
void InsertSort(int A[], int n) {
	int i, j;
	for (i = 2; i <= n; i++)
	{
		if (A[i] < A[i - 1]) {
			A[0] = A[i];//A[0]复制为哨兵 不存储任何元素
			for (j = i - 1; A[0] < A[j]; --j)
				A[j + 1] = A[j];
			A[j + 1] = A[0];
		}
	}
}

//希尔排序
void ShellSort(int A[], int n) {
	int d, i, j;
	for (d = n / 2; d >= 1; d = d / 2) {
		for (i = d + 1; i <= n; i++) {
			if (A[i] < A[i - d]) {
				A[0] = A[i];//A[0]复制为哨兵 不存储任何元素
				for (j = i - d; j > 0 && A[0] < A[j]; j -= d)
					A[j + d] = A[j];
				A[j + d] = A[0];
			}
		}
	}
}

// 冒泡排序
void BubbldSort(int A[], int n) {
	for (int i = 0; i < n-1; i++)
	{
		bool flag = false;
		for (int j = n - 1; j > i; j--)
		{
			if (A[j - 1] > A[j]) {
				swap(A[j - 1], A[j]);
				flag = true;
			}
		}
		if (flag == false)
			return;
	}
}

//快排
int Partition(int A[], int low, int high) {
	int pivot = A[low];
	while (low < high) {
		while (low<high && A[high]>=pivot) --high;//找一个比pivot小的
		A[low] = A[high];
		while (low < high && A[low] <= pivot) ++low;//找一个比pivot大的
		A[high] = A[low];
	}
	A[low] = pivot;
	return low;
}

void QuickSort(int A[], int low, int high) {
	if (low < high) {
		int pivotpos = Partition(A, low, high);
		QuickSort(A, low, pivotpos-1);
		QuickSort(A, pivotpos + 1, high);
	}
}

void SelectSort(int A[], int n) {
	for (int i = 0; i < n-1; i++)
	{
		int min = i;
		for (int j = i+1; j < n-1; j++)
		{
			if (A[j] < A[min]) min = j;
		}
		if (min != i)swap(A[min], A[i]);
	}
}

//结构体输入文件&从文件中读取结构体
typedef struct Inventory {
	int ID;
	char name[50];
	int num;
}Inventory;

//修改对应ID的num，并写回文件
void modifyNumInFile(int targetID, int newNum) {
	FILE* file = fopen("facility.data", "rb+");
	if (file == NULL) {
		return;
	}
	Inventory item;
	while (fread(&item, sizeof(Inventory), 1, file)) {
		if (item.ID == targetID) {
			item.num = newNum;
		}
		fseek(file, 0 - sizeof(Inventory), SEEK_CUR);
		fwrite(&item, sizeof(Inventory), 1, file);
		fclose(file);
		return;
	}
	fclose(file);
}

//求无向图连通分量个数
bool visited[100];
void DFS(MGraph G,int v) {
	visited[v] = true;
	for (int i = 0; i < G.vexnum; i++) {
		if (visited[i] == false && G.edge[v][i] == 1) {
			DFS(G, i);
		}
	}
}

// 树的孩子兄弟链表结构下，求树的叶子结点个数
// 注意到一个结点如果只有右兄弟结点，也是孩子结点
int countLeafNodes(BiTree root) {
	if (root == NULL) {
		return 0;
	}
	if (root->lchild == NULL) {//如果当前结点只有兄弟没有孩子
		return 1 + countLeafNodes(root->rchild);
	}
	else {
		return countLeafNodes(root->lchild) + countLeafNodes(root->rchild);
	}
}

// 从命令行读入两个文件名data1和data2，将data1中的内容每一行加上行号存入data2
int main1(int argc,char *argv[]) {
	if (argc != 3) {
		return 1;
	}
	FILE* data1 = fopen(argv[1], "r");
	if (data1 == NULL) {
		perror("无法打开data1文件");
		return 1;
	}
	FILE* data2 = fopen(argv[2], "w");
	if (data2 == NULL) {
		perror("无法创建或打开data2文件");
		return 1;
	}
	char line[1000];//假设每行不超过1000个字符
	int lineNumber = 1;
	while (fgets(line, sizeof(line), data1) != NULL) {
		fprintf(data2, "%d:%s", lineNumber++, line);//如果用fputs，就不能方便在前面加个行号了
	}
	fclose(data1);
	fclose(data2);
	return 0;
}

//递归求最大公约数（辗转相除法）
int gcd(int m, int n) {
	if (n == 0) {
		return n;
	}
	else {
		return gcd(n, m % n);
	}
}
//求最小公倍数
int lcm(int m, int n) {
	return m * n / gcd(m, n);
}

//判断链表中是否有环（快慢指针）
int hasCycle(LinkList L) {
	if (L == NULL || L->next == NULL) {
		return 0;
	}
	LNode* fast, * slow;
	fast = L->next->next;
	slow = L->next;
	while (fast->next != NULL && fast->next->next != NULL) {
		if (fast == slow) {
			return 1;
		}
		slow = slow->next;
		fast = fast->next->next;
	}
	return 0;
}

//在有环的链表中，找到环的入口
LNode* entryNodeOfLoop(LinkList L) {
	LNode* fast, * slow;
	fast = L;
	slow = L;
	while (fast) {
		if (fast->next == NULL) {
			return NULL;
		}
		slow = slow->next;
		fast = fast->next->next;
		if (slow == fast) {//快慢指针相遇之后
			fast = L;
			while (fast != slow) {//快指针回到头指针位置，然后快慢指针同时移动，再次相遇就是入口
				fast = fast->next;
				slow = slow->next;
			}
			return fast;
		}
	}
	return NULL;
}

//求二叉树最大深度
int maxDepth(BiTree root) {
	int res, resLeft, resRight;
	if (root == NULL) return 0;
	resLeft = maxDepth(root->lchild);
	resRight = maxDepth(root->rchild);
	return 1 + (resLeft > resRight ? resLeft : resRight);
}

//判断是否平衡二叉树
bool isBalanced(BiTree root) {
	if (root == NULL) {
		return true;
	}
	int leftDepth = maxDepth(root->lchild);
	int rightDepth = maxDepth(root->rchild);
	int diff = leftDepth - rightDepth;
	if (abs(diff) > 1) {
		return 0;
	}
	return isBalanced(root->lchild) && isBalanced(root->rchild);
}

//判断是否二叉搜索树
//如果用简单的递归，只判断了当前结点和左右子结点的大小关系，如果有更深层次结点不满足的情况则无法正确判断
bool isValidBST(BiTree root,long min,long max) {
	if (root == NULL) {
		return true;
	}
	if (root->data <= min || root->data >= max) {
		return false;
	}
	return isValidBST(root->lchild, min, root->data) && isValidBST(root->rchild, root->data, max);
}

int main()
{ 
	std::cout << "Hello World!\n";
}

