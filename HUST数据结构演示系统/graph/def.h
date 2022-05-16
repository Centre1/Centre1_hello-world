#ifndef _STU_384_
#define _STU_384_



#ifndef _VALUE_
#define _VALUE_
#define TRUE 1  
#define FALSE 0  
#define OK 1  
#define ERROR 0  
#define INFEASIBLE -1  
#define OVERFLOW -2
#define MAX_VERTEX_NUM 20  
#endif


#ifndef _ELEM_
#define _ELEM_ 
typedef int status;  
typedef int KeyType;   
typedef enum {DG,DN,UDG,UDN} GraphKind;  
typedef struct {  
	KeyType  key;  
	char others[20];  
} VertexType; //�������Ͷ���
#endif


#ifndef _GRAPH_
#define _GRAPH_
typedef struct ArcNode {         //�������Ͷ���  
    int adjvex;              //����λ�ñ��   
    struct ArcNode  *nextarc;       //��һ������ָ��  
} ArcNode;  

typedef struct VNode{                //ͷ��㼰���������Ͷ���  
    VertexType data;           //������Ϣ  
    ArcNode *firstarc;           //ָ���һ����  
} VNode,AdjList[MAX_VERTEX_NUM];  

typedef  struct ALGraph{  //�ڽӱ�����Ͷ���  
    AdjList vertices;          //ͷ�������  
    int vexnum,arcnum;         //������������  
    GraphKind  kind;        //ͼ������  
} ALGraph;
#endif


#ifndef _GRAPHS_
#define _GRAPHS_
#define GRAPHS_INIT_SIZE 20
typedef struct GsNode{
	struct{
		char name[30];
		ALGraph G;	
	}elem[GRAPHS_INIT_SIZE];
	int length;
	int listsize;
}ALGraphs; 
#endif



#endif
