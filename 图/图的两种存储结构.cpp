//1.邻接矩阵存储
#include<iostream>
#include<vector>
using namespace std;

const int MAXV = 100;			//图中最多的顶点数
const int INF = 0x3f3f3f3f;		//用INF表示∞

class MatGraph				    //图邻接矩阵类
{
public:
	int edges[MAXV][MAXV];		//邻接矩阵数组，假设元素为int类型
	int n, e;				    //顶点数，边数
	string vexs[MAXV];			//存放顶点信息
	//图的基本运算算法

	void CreateMatGraph(int a[][MAXV], int n, int e)
		//通过a、n和e来建立图的邻接矩阵
	{
		this->n = n; this->e = e;		//置顶点数和边数
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
				this->edges[i][j] = a[i][j];
	}
	
	void DispMatGraph()		//输出图的邻接矩阵
	{
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n; j++)
				if (edges[i][j] == INF)
					printf("%4s", "∞");
				else
					printf("%4d", edges[i][j]);
			printf("\n");
		}
	}
};

int Degree1(MatGraph& g, int v)  //无向图邻接矩阵g中求顶点v的度
{
	int d = 0;
	for (int j = 0; j < g.n; j++)	   //统计第v行的非0非∞元素个数
		if (g.edges[v][j] != 0 && g.edges[v][j] != INF)
			d++;
	return d;
}

vector<int> Degree2(MatGraph& g, int v)
//有向图邻接矩阵g中求顶点v的出度和入度
{
	vector<int> ans = { 0,0 };		//ans[0]累计出度,ans[1]累计入度
	for (int j = 0; j < g.n; j++)		//统计第v行的非0非∞元素个数为出度
		if (g.edges[v][j] != 0 && g.edges[v][j] != INF)
			ans[0]++;
	for (int i = 0; i < g.n; i++)		//统计第v列的非0非∞元素个数为入度
		if (g.edges[i][v] != 0 && g.edges[i][v] != INF)
			ans[1]++;
	return ans;				//返回出度和入度
}

int main()
{
	MatGraph g1, g2;
	int n = 5, e = 8;
	int a[MAXV][MAXV] = { {0,1,0,1,1},{1,0,1,1,0},{0,1,0,1,1},
			   {1,1,1,0,1},{1,0,1,1,0} };
	g1.CreateMatGraph(a, n, e);
	printf("图G1(无向图)\n"); g1.DispMatGraph();
	printf("求解结果\n");
	for (int i = 0; i < g1.n; i++)
		printf("  顶点%d的度: %d\n", i, Degree1(g1, i));

	n = 5; e = 5;
	int b[MAXV][MAXV] = { {0,8,INF,5,INF},{INF,0,3,INF,INF},
	 {INF,INF,0,INF,6},{INF,INF,9,0,INF},{INF,INF,INF,INF,0} };
	g2.CreateMatGraph(b, n, e);
	printf("图G2(有向图)\n"); g2.DispMatGraph();
	printf("求解结果\n");
	for (int i = 0; i < g2.n; i++)
	{
		vector<int> ans = Degree2(g2, i);
		printf("  顶点%d: 出度=%d 入度=%d 度=%d\n",
			i, ans[0], ans[1], ans[0] + ans[1]);
	}
	return 0;
}


//2.邻接表存储
#include<iostream>
#include<vector>
using namespace std;

const int MAXV = 100;			//图中最多的顶点数
const int INF = 0x3f3f3f3f;		//用INF表示∞

struct ArcNode			//边结点类型
{
	int adjvex;			//邻接点
	int weight;			//权值
	ArcNode* nextarc;		//指向下一条边的边结点
};

struct HNode			//头结点类型
{
	string info;			//顶点信息
	ArcNode* firstarc;		//指向第一条边的边结点
};

class AdjGraph				//图邻接表类
{
public:
	HNode adjlist[MAXV];		//头结点数组
	int n, e;				//顶点数，边数
	AdjGraph()				//构造函数
	{
		for (int i = 0; i < MAXV; i++)	//头结点的firstarc置为空
			adjlist[i].firstarc = NULL;
	}
	~AdjGraph()				//析构函数,释放图的邻接表空间
	{
		ArcNode* pre, * p;
		for (int i = 0; i < n; i++)		//遍历所有的头结点
		{
			pre = adjlist[i].firstarc;
			if (pre != NULL)
			{
				p = pre->nextarc;
				while (p != NULL)		//释放adjlist[i]的所有边结点空间
				{
					delete pre;
					pre = p; p = p->nextarc; 	//pre和p指针同步后移
				}
				delete pre;
			}
		}
	}
	//图的基本运算算法
	void CreateAdjGraph(int a[][MAXV], int n, int e)
		//通过a、n和e来建立图的邻接表
	{
		ArcNode* p;
		this->n = n; this->e = e;			//置顶点数和边数
		for (int i = 0; i < n; i++)			//检查邻接矩阵中每个元素
			for (int j = n - 1; j >= 0; j--)
				if (a[i][j] != 0 && a[i][j] != INF)	//存在一条边
				{
					p = new ArcNode();			//创建一个结点p
					p->adjvex = j;
					p->weight = a[i][j];
					p->nextarc = adjlist[i].firstarc;	//采用头插法插入p
					adjlist[i].firstarc = p;
				}
	}
	
	void DispAdjGraph()			//输出图的邻接表
	{
		ArcNode* p;
		for (int i = 0; i < n; i++)		//遍历每个头结点
		{
			printf("   [%d]", i);
			p = adjlist[i].firstarc;		//p指向第一个邻接点
			if (p != NULL)  printf("→");
			while (p != NULL)			//遍历第i个单链表
			{
				printf(" (%d,%d)", p->adjvex, p->weight);
				p = p->nextarc;		//p移向下一个邻接点
			}
			printf("\n");
		}
	}

};

int Degree1(AdjGraph& G, int v) 	//无向图邻接表G中求顶点v的度
{
	int d = 0;
	ArcNode* p = G.adjlist[v].firstarc;
	while (p != NULL)			//统计单链表v中边结点个数
	{
		d++;
		p = p->nextarc;
	}
	return d;
}

vector<int> Degree2(AdjGraph& G, int v)
//有向图邻接表G中求顶点v的出度和入度
{
	vector<int> ans = { 0,0 };		//ans[0]累计出度,ans[1]累计入度
	ArcNode* p = G.adjlist[v].firstarc;
	while (p != NULL)   			//统计单链表v中边结点个数
	{
		ans[0]++;
		p = p->nextarc;
	}
	for (int i = 0; i < G.n; i++)		//统计所有为v的边结点个数为v的入度
	{
		p = G.adjlist[i].firstarc;
		while (p != NULL)
		{
			if (p->adjvex == v)
			{
				ans[1]++;
				break;			//一个单链表最多只有一个这样的结点
			}
			p = p->nextarc;
		}
	}
	return ans;				//返回出度和入度
}


int main() {
	// 测试无向图功能
	cout << "========== 测试无向图 ==========" << endl;
	// 无向图的邻接矩阵表示
	// 顶点0与1、2相连
	// 顶点1与0、2、3相连
	// 顶点2与0、1、3相连
	// 顶点3与1、2、4相连
	// 顶点4只与3相连
	int undirectedGraph[MAXV][MAXV] = {
		{0, 1, 1, 0, 0},  // 顶点0的边
		{1, 0, 1, 1, 0},  // 顶点1的边
		{1, 1, 0, 1, 0},  // 顶点2的边
		{0, 1, 1, 0, 1},  // 顶点3的边
		{0, 0, 0, 1, 0}   // 顶点4的边
	};

	AdjGraph G1;
	G1.CreateAdjGraph(undirectedGraph, 5, 6);  // 创建5个顶点6条边的无向图
	cout << "无向图的邻接表表示:" << endl;
	G1.DispAdjGraph();  // 显示邻接表

	// 测试无向图顶点度数计算
	cout << "\n计算无向图各顶点的度数:" << endl;
	for (int v = 0; v < 5; v++) {
		cout << "顶点 " << v << " 的度数为: " << Degree1(G1, v) << endl;
	}
	cout << endl;

	// 测试有向图功能
	cout << "========== 测试有向图 ==========" << endl;
	// 有向图的邻接矩阵表示
	// 顶点0指向1
	// 顶点1指向2和3
	// 顶点2指向3
	// 顶点3指向0和4
	// 顶点4没有出边
	int directedGraph[MAXV][MAXV] = {
		{0, 1, 0, 0, 0},  // 顶点0的出边
		{0, 0, 1, 1, 0},  // 顶点1的出边
		{0, 0, 0, 1, 0},  // 顶点2的出边
		{1, 0, 0, 0, 1},  // 顶点3的出边
		{0, 0, 0, 0, 0}   // 顶点4的出边
	};

	AdjGraph G2;
	G2.CreateAdjGraph(directedGraph, 5, 6);  // 创建5个顶点6条边的有向图
	cout << "有向图的邻接表表示:" << endl;
	G2.DispAdjGraph();  // 显示邻接表

	// 测试有向图顶点出入度计算
	cout << "\n计算有向图各顶点的出度和入度:" << endl;
	for (int v = 0; v < 5; v++) {
		vector<int> degrees = Degree2(G2, v);
		cout << "顶点 " << v << ": 出度=" << degrees[0]
			<< ", 入度=" << degrees[1] << endl;
	}
	cout << endl;

	// 测试析构函数
	cout << "========== 测试析构函数 ==========" << endl;
	{
		cout << "创建临时图对象..." << endl;
		AdjGraph tempGraph;
		int tempMatrix[MAXV][MAXV] = {
			{0, 1, 1},  // 顶点0指向1和2
			{1, 0, 0},  // 顶点1指向0
			{1, 0, 0}   // 顶点2指向0
		};
		tempGraph.CreateAdjGraph(tempMatrix, 3, 4);  // 3个顶点4条边
		cout << "临时图的邻接表:" << endl;
		tempGraph.DispAdjGraph();
		cout << "临时图对象即将离开作用域..." << endl;
	}  // 这里会调用析构函数
	cout << "临时图对象已销毁" << endl;

	return 0;
}
