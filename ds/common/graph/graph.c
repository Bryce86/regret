/************************************************************************/
/* ͼ���ڽӾ���洢�ṹ                                                  */
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
	VertexType vexs[MaxVertexNum];	//�����
	EdgeType edges[MaxVertexNum][MaxVertexNum];		//�ڽӾ���,�ɿ����߱�
	int n,e;	//ͼ�е�ǰ�Ķ������ͱ���
}MGraph;
/************************************************************************/
/* �ڽӾ���Ľ���                                                        */
/************************************************************************/
void CreateMGraph(MGraph *G)
{ 
	int i,j,k;
	char ch1,ch2;
	printf("�����붥�����ͱ���(�����ʽΪ:������,����):\n");
	scanf("%d,%d",&(G->n),&(G->e));
	printf("�����붥����Ϣ(�����<CR>)ÿ�������Իس���Ϊ����:\n");
	for(i=0;i<G->n;i++)
	{
		getchar();scanf("%c",&(G->vexs[i]));
	}
	for(i=0;i<G->n;i++)
		for(j=0;j<G->n;j++)
			G->edges[i][j]=0;
		printf("������ÿ���߶�Ӧ��������������(�����ʽΪ:i,j):\n");
		for(k=0;k<G->e;k++)
		{
			getchar();
			printf("�������%d���ߵĶ�����ţ�",k+1);
			scanf("%c,%c",&ch1,&ch2);
			for(i=0;ch1!=G->vexs[i];i++);
			for(j=0;ch2!=G->vexs[j];j++);
			G->edges[i][j]=1;
		}
}
/************************************************************************/
/* ������ȱ������������������                                         */
/************************************************************************/
void DFSM(MGraph *G,int i)
{
	int j;
	printf("������ȱ������: ���%c\n",G->vexs[i]);	//���ʶ���vi
	visited[i]=TRUE;		
	for(j=0;j<G->n;j++)			//��������vi�ڽӵ�
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
/* ������ȱ������������������                                         */
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
	printf("������ȱ������: ���%c\n",G->vexs[k]);
	visited[k]=TRUE;
	EnQueue(&Q,k);
	while (!QueueEmpty(&Q))
	{
		i=DeQueue(&Q);
		for (j=0;j<G->n;j++)
			if(G->edges[i][j]==1&&!visited[j])
			{
				printf("������ȱ������:%c\n",G->vexs[j]);
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
/* ����������                                                           */
/************************************************************************/
int main()
{
	MGraph G;
	CreateMGraph(&G);
	DFSTraverseM(&G);
	BFSTraverseM(&G);
	return 0;
}

