/************************************************************************/
/* 图的邻接矩阵存储结构                                                  */
/************************************************************************/
#include <stdio.h>
#define MaxVertexNum 100
#define QueueSize 30
typedef enum{FALSE,TRUE}Boolean;
Boolean visited[MaxVertexNum];
typedef char VertexType;
typedef int EdgeType;
typedef struct  
{
	VertexType vexs[MaxVertexNum];	//顶点表
	EdgeType edges[MaxVertexNum][MaxVertexNum];		//邻接矩阵,可看做边表
	int n,e;	//图中当前的顶点数和边数
}MGraph;
/************************************************************************/
/* 邻接矩阵的建立                                                        */
/************************************************************************/
void CreateMGraph(MGraph *G)
{ 
	int i,j,k;
	char ch1,ch2;
	printf("请输入顶点数和边数(输入格式为:顶点数,边数):\n");
	scanf("%d,%d",&(G->n),&(G->e));
	printf("请输入顶点信息(顶点号<CR>)每个顶点以回车作为结束:\n");
	for(i=0;i<G->n;i++)
	{
		getchar();scanf("%c",&(G->vexs[i]));
	}
	for(i=0;i<G->n;i++)
		for(j=0;j<G->n;j++)
			G->edges[i][j]=0;
		printf("请输入每条边对应的两个顶点的序号(输入格式为:i,j):\n");
		for(k=0;k<G->e;k++)
		{
			getchar();
			printf("请输入第%d条边的顶点序号：",k+1);
			scanf("%c,%c",&ch1,&ch2);
			for(i=0;ch1!=G->vexs[i];i++);
			for(j=0;ch2!=G->vexs[j];j++);
			G->edges[i][j]=1;
		}
}
/************************************************************************/
/* 深度优先遍历（深度优先搜索）                                         */
/************************************************************************/
void DFSM(MGraph *G,int i)
{
	int j;
	printf("深度优先遍历结点: 结点%c\n",G->vexs[i]);	//访问顶点vi
	visited[i]=TRUE;		
	for(j=0;j<G->n;j++)			//依次搜索vi邻接点
		if(G->edges[i][j]==1 && !visited[j])
			DFSM(G,j);
}
void DFSTraverseM(MGraph *G)
{
	int i;
	for(i=0;i<G->n;i++)
		visited[i]=FALSE;	
	for(i=0;i<G->n;i++)
		if(!visited[i]) 
			DFSM(G,i);
}
/************************************************************************/
/* 广度优先遍历（广度优先搜索）                                         */
/************************************************************************/
typedef struct
{
	int front;
	int rear;
	int count;
	int data[QueueSize];
}CirQueue;
void InitQueue(CirQueue *Q)
{
	Q->front=Q->rear=0;
	Q->count=0;
}
int QueueEmpty(CirQueue *Q)
{
	return Q->count=QueueSize;
}
int QueueFull(CirQueue *Q)
{
	return Q->count==QueueSize;
}
void EnQueue(CirQueue *Q,int x)
{ 
	if (QueueFull(Q))
		printf("Queue overflow\n");
	else
	{ 
		Q->count++;
		Q->data[Q->rear]=x;
		Q->rear=(Q->rear+1)%QueueSize;
	}
}
int DeQueue(CirQueue *Q)
{
	int temp;
	if(QueueEmpty(Q))
	{ 
		printf("Queue underflow\n");
		return 0;
	}
	else
	{
		temp=Q->data[Q->front];
		Q->count--;
		Q->front=(Q->front+1)%QueueSize;
		return temp;
	}
}
void BFSM(MGraph *G,int k)
{ 
	int i,j;
	CirQueue Q;
	InitQueue(&Q);
	printf("广度优先遍历结点: 结点%c\n",G->vexs[k]);
	visited[k]=TRUE;
	EnQueue(&Q,k);
	while (!QueueEmpty(&Q))
	{
		i=DeQueue(&Q);
		for (j=0;j<G->n;j++)
			if(G->edges[i][j]==1&&!visited[j])
			{
				printf("广度优先遍历结点:%c\n",G->vexs[j]);
				visited[j]=TRUE;
				EnQueue(&Q,j);
			}
	}
}
void BFSTraverseM(MGraph *G)
{
	int i;
	for (i=0;i<G->n;i++)
		visited[i]=FALSE;
	for (i=0;i<G->n;i++)
		if (!visited[i]) 
			BFSM(G,i);
}
/************************************************************************/
/* 主函数调用                                                           */
/************************************************************************/
int main()
{
	MGraph G;
	CreateMGraph(&G);
	DFSTraverseM(&G);
	BFSTraverseM(&G);
	return 0;
}

