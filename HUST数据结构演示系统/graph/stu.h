#include <string.h>
#include <stdlib.h>
#include "def.h"
#define maxleng 1005
#include <stdio.h> 
#define debug printf("Debug\n");


int LocateVex(ALGraph G,KeyType u)
//3����u��ͼG�в��Ҷ��㣬���ҳɹ�����λ�򣬷��򷵻�-1��
{
    int flag = -1;
	for(int i=0; flag==-1 && i<G.vexnum; i++){
		if(G.vertices[i].data.key == u)
			flag = i;
	}
	return flag;
}


status InsertVex(ALGraph &G,VertexType v)
//7��ͼG�в��붥��v���ɹ�����OK,���򷵻�ERROR
{
    status flag = ERROR; 
	if(LocateVex(G,v.key) == -1){	//��ֹ key �ظ� 
		if(G.vexnum+1 <= MAX_VERTEX_NUM){	//��ֹ��������� 
			int i = G.vexnum;
			G.vertices[i].data = v;
			G.vertices[i].firstarc = NULL;
			G.vexnum++;
			flag = OK; 
		}
	}
	return flag;
}


status InsertArc(ALGraph &G,KeyType v,KeyType w)
//9��ͼG�����ӻ�<v,w>���ɹ�����OK,���򷵻�ERROR
{
	status flag = ERROR;
	
	int iv = LocateVex(G, v);
	int iw = LocateVex(G, w);
	if(iv!=-1 && iw!=-1){
		flag = OK;
		ArcNode* p = G.vertices[iv].firstarc;
		while(flag==OK && p){
			if(p->adjvex == iw)
				flag = ERROR;
			p = p->nextarc;
		} 
		
		if(flag == OK){
			ArcNode* s1 = (ArcNode*)malloc(sizeof(ArcNode));
			s1->adjvex = iv;	s1->nextarc = NULL; 
			ArcNode* s2 = (ArcNode*)malloc(sizeof(ArcNode));
			s2->adjvex = iw;	s1->nextarc = NULL;
			
			if(iw != iv){
				s1->nextarc =  G.vertices[iw].firstarc;
				G.vertices[iw].firstarc = s1;
				s2->nextarc =  G.vertices[iv].firstarc;
				G.vertices[iv].firstarc = s2;
			}
			else{	//loop
				s1->nextarc =  G.vertices[iw].firstarc;
				G.vertices[iw].firstarc = s1;
				free(s2);	//�ͷŶ���ռ� 
			}
			G.arcnum++;	
		}
	}

	return flag;
}	


status CreateCraph(ALGraph &G,VertexType V[],KeyType VR[][2])
/*1����V��VR����ͼT������OK�����V��VR����ȷ������ERROR
�������ͬ�Ĺؼ��֣�����ERROR����������ͨ������������������ʵ�ֱ�������*/
{
    status flag = OK;
	G.kind = UDG;	//��ʼ�� 
	G.vexnum = G.arcnum = 0;
    bool bw[maxleng];
    memset(bw, 0, sizeof(bw));
    
	int i = 0;
    while(flag==OK && V[i].key != -1){	//��ⶥ�� key��Ҫ���ظ��Ҳ������ 
    	if(bw[V[i].key] || i>=MAX_VERTEX_NUM)
			flag = ERROR;
		else bw[V[i].key] = 1;
		i++;
	}
	
	i = 0;
	while(flag==OK && VR[i][0] != -1){	//��⻡ key��Ҫ�󶥵���ڣ� 
		if(!bw[VR[i][0]] || !bw[VR[i][1]])
			flag = ERROR;
		i++;
	}
    
    if(flag == OK){
    	i = 0;
    	while(flag==OK && V[i].key != -1)	//�������� 
			flag = InsertVex(G, V[i++]); 
		if(G.vexnum == 0) flag = ERROR;	//�޶��� 
		
		i = 0;
		while(flag==OK && VR[i][0] != -1){	//������ 
			flag = InsertArc(G, VR[i][0], VR[i][1]); 
			i++;
		}
	}
	return flag;
}

status DestroyGraph(ALGraph &G)
/*2��������ͼG,ɾ��G��ȫ������ͱ�*/
{
	for(int i=0; i<G.vexnum; i++){
		ArcNode* p = G.vertices[i].firstarc;
		G.vertices[i].firstarc = NULL;
		while(p){
			ArcNode* t = p;
			p = p->nextarc;
			free(t);
		}
	}
	
	G.vexnum = 0;
	G.arcnum = 0;
	return OK;
}


status PutVex(ALGraph &G,KeyType u,VertexType value)
//4����u��ͼG�в��Ҷ��㣬���ҳɹ����ö���ֵ�޸ĳ�value������OK��
//�������ʧ�ܻ�ؼ��ֲ�Ψһ������ERROR
{
	status flag = ERROR;
	if(LocateVex(G,value.key)==-1 || u==value.key){
		int i = LocateVex(G, u); 
		if(i != -1){
			G.vertices[i].data = value;
			flag = OK;			
		}
	}
	return flag;
}


int FirstAdjVex(ALGraph G,KeyType u)
//5����u��ͼG�в��Ҷ��㣬���ҳɹ����ض���u�ĵ�һ�ڽӶ���λ�򣬷��򷵻�-1��
{
	int i = LocateVex(G, u);
	if(i != -1)
		return G.vertices[i].firstarc->adjvex;
	else
		return -1;
}



int NextAdjVex(ALGraph G,KeyType v,KeyType w)
//6����u��ͼG�в��Ҷ��㣬���ҳɹ����ض���v���ڽӶ��������w����һ�ڽӶ����λ�򣬲���ʧ�ܷ���-1��
{
	int ans = -1;	bool flag = 0;	 
	int i = LocateVex(G, v);
	if(i != -1){
		ArcNode* p = G.vertices[i].firstarc;
		while(!flag && p){	//���� w 
			if(G.vertices[p->adjvex].data.key == w){
				flag = 1;
				if(p = p->nextarc)
					ans = p->adjvex;
			}
			else p = p->nextarc;
		}
	}
	
	return ans;
}


status Delete(ALGraph &G, int iu,int iv){	//ɾ�� iu �е� iv 
	status flag = ERROR;
	ArcNode* p = G.vertices[iu].firstarc;
	if(p && p->adjvex==iv){
		G.vertices[iu].firstarc = p->nextarc;
		free(p);
		flag = OK;
	}
	else if(p){
		while(flag==ERROR && p->nextarc){
			if(p->nextarc->adjvex == iv){
				ArcNode* t = p->nextarc;
				p->nextarc = p->nextarc->nextarc;
				free(t);
				flag = OK;
			}
			else p = p->nextarc;
		}		
	}
	return flag;
} 

status DeleteVex(ALGraph &G,KeyType v)
//8��ͼG��ɾ���ؼ���v��Ӧ�Ķ����Լ���صĻ����ɹ�����OK,���򷵻�ERROR
{
	status flag = ERROR;
	
	int iv = LocateVex(G, v);
	if(iv != -1 && G.vexnum>1){
		ArcNode* p = G.vertices[iv].firstarc;
		while(p){
			Delete(G, p->adjvex, iv);	//ɾ��һ�������ϵĻ� 
			
			ArcNode* t = p;		//ɾ�� 
			p = p->nextarc;
			free(t); 
			G.arcnum--;
		}
		
		for(int i=iv; i<G.vexnum-1; i++)	//ɾ���� 
			G.vertices[i] = G.vertices[i+1];
		G.vexnum--;
		
		for(int i=0; i<G.vexnum; i++){	//�ع��±� 
			p = G.vertices[i].firstarc;
			while(p){
				if(p->adjvex > iv)
					p->adjvex--;
				p = p->nextarc;
			}
		}
		flag = OK;
	}
	
	return flag;
}




status DeleteArc(ALGraph &G,KeyType v,KeyType w)
//10��ͼG��ɾ����<v,w>���ɹ�����OK,���򷵻�ERROR
{
    status flag = ERROR;
    
    int iv = LocateVex(G, v);
    int iw = LocateVex(G, w);
	if(iv!=-1 && iw!=-1){
		ArcNode* p = G.vertices[iv].firstarc;
		int flag1 = Delete(G, iv, iw);
		int flag2 = Delete(G, iw, iv);
		if(flag1 && flag2){
			G.arcnum--;
			flag = OK;	
		} 
	
	} 
	return flag;
}



bool visited[maxleng];
void visit(VertexType v)
{
    printf(" %d %s\n",v.key,v.others);
}

void DFS(ALGraph G, void (*visit)(VertexType), int i)
{
	visit(G.vertices[i].data); 
	visited[i] = 1;
	ArcNode* p = G.vertices[i].firstarc;
	while(p){
		if(!visited[p->adjvex])
			DFS(G,visit,p->adjvex);
		p = p->nextarc;
	}
}
status DFSTraverse(ALGraph &G,void (*visit)(VertexType))
//11��ͼG������������������������ζ�ͼ�е�ÿһ������ʹ�ú���visit����һ�Σ��ҽ�����һ��
{
	if(G.vexnum == 0) return ERROR;
	
	printf("-------------------------------------\n");
	memset(visited, 0, sizeof(visited));
	for(int i=0; i<G.vexnum; i++){
		if(!visited[i]) DFS(G,visit,i);
	}
	printf("-------------------------------------\n");
	return OK;
}


status BFSTraverse(ALGraph &G,void (*visit)(VertexType))
//12��ͼG���й�������������������ζ�ͼ�е�ÿһ������ʹ�ú���visit����һ�Σ��ҽ�����һ��
{
	if(G.vexnum == 0) return ERROR;
	
	printf("-------------------------------------\n");
	memset(visited, 0, sizeof(visited));
	for(int i=0; i<G.vexnum; i++){
		int Q[maxleng];
		memset(Q, -1, sizeof(Q));
		int head=0, tail=0;
		if(!visited[i]){
			visit(G.vertices[i].data);
			visited[i] = 1;
			Q[tail++] = i;
			
			while(head < tail){
				int t = Q[head++];
				ArcNode* p = G.vertices[t].firstarc;
				while(p){	//�������ڵ� 
					if(!visited[p->adjvex]){
						int iv = p->adjvex;
						visit(G.vertices[iv].data);
						visited[iv] = 1;
						Q[tail++] = iv;
						
					}
					p = p->nextarc; 
				}//�������ڵ���� 
			}	
		}//end of bfs
	}
	printf("-------------------------------------\n");
	return OK;
}

int* VerticesSetLessThanK(ALGraph G, KeyType v, int k)
//13��ʼ������ͼG���ڣ���������Ƿ����붥��v����С��k�Ķ��㼯�ϣ�
{
	int i = LocateVex(G, v);
	if(i == -1){	//Ŀ�겻���� 
		return NULL; 
	}
	
	memset(visited, 0, sizeof(visited));
	int* Q = (int*)malloc(sizeof(int)*maxleng); //�ö�̬����洢
	memset(Q, -1, sizeof(Q));
	int head=0, tail=0;
	
//	visit(G.vertices[i].data);
	visited[i] = 1;
	Q[tail++] = i;
	
	int dis = 0;
	while(++dis<k && head<tail){
		int t = Q[head++];
		ArcNode* p = G.vertices[t].firstarc;
		while(p){	//�������ڵ� 
			if(!visited[p->adjvex]){
				int iv = p->adjvex;
//				visit(G.vertices[iv].data);
				visited[iv] = 1;
				Q[tail++] = iv;
			}
			p = p->nextarc; 
		}//�������ڵ���� 
	}
	Q[tail] = -1;	
	return Q;	//���ؼ��ϰ������� 
}


int ShortestPathLength(ALGraph G, KeyType v, KeyType w)
//14��ʼ������ͼG���ڣ���������Ƿ��ض���v�붥��w�����·���ĳ��ȣ�
{
	int ans = -1;
	
	int iv = LocateVex(G,v);
	int iw = LocateVex(G,w);
	
	if(iv!=-1 && iw!=-1){
		if(iv == iw) ans = 0;
		else{
			memset(visited, 0, sizeof(visited));
			int* Q = (int*)malloc(sizeof(int)*maxleng);
			memset(Q, -1, sizeof(Q));
			int head=0, tail=0;
			
			visited[iv] = 1;
			Q[tail++] = iv;
					
			int dis = 0;
			while(ans==-1 && head<tail){
				++dis;
				int t = Q[head++];
				ArcNode* p = G.vertices[t].firstarc;
				while(p){	//�������ڵ� 
					if(p->adjvex == iw){
						ans = dis;
						break;
					}
					if(!visited[p->adjvex]){
						int iv = p->adjvex;
						visited[iv] = 1;
						Q[tail++] = iv;
					}
					p = p->nextarc; 
				}//�������ڵ���� 
			}
			free(Q);
		}
	}
	return ans;
}


int ConnectedComponentsNums(ALGraph G)
//15��ʼ������ͼG���ڣ���������Ƿ���ͼG��������ͨ�����ĸ����� 
{
	int ans = 0;
	
	memset(visited, 0, sizeof(visited));
	for(int i=0; i<G.vexnum; i++){
		int Q[maxleng];
		memset(Q, -1, sizeof(Q));
		int head=0, tail=0;
		if(!visited[i]){
			visited[i] = 1;
			Q[tail++] = i;
			
			while(head < tail){
				int t = Q[head++];
				ArcNode* p = G.vertices[t].firstarc;
				while(p){	//�������ڵ� 
					if(!visited[p->adjvex]){
						int iv = p->adjvex;
						visited[iv] = 1;
						Q[tail++] = iv;
						
					}
					p = p->nextarc; 
				}//�������ڵ���� 
			}	
			ans++; 
		}//end of bfs
	}
	
	return ans;
}


status SaveGraph(ALGraph G, char FileName[])
//16��ͼ������д�뵽�ļ�FileName��
{
	FILE* fp;
	fp = fopen(FileName, "wb");
	if(fp == NULL){
		printf("file not found\n");
		return ERROR;
	}
	
	fwrite(&G.vexnum, sizeof(int), 1, fp);
	fwrite(&G.arcnum, sizeof(int), 1, fp);
	fwrite(&G.kind, sizeof(int), 1, fp);
	
	int end = -1;
	for(int i=0; i<G.vexnum; i++){
		fwrite(&G.vertices[i].data, sizeof(VertexType), 1, fp);
		
		ArcNode* p = G.vertices[i].firstarc;
		while(p){
			fwrite(&p->adjvex, sizeof(int), 1, fp);
			p = p->nextarc;
		}
		fwrite(&end, sizeof(int), 1, fp);		
	}
	
	fclose(fp);
	return OK;
}
status LoadGraph(ALGraph &G, char FileName[])
//17�����ļ�FileName��ͼ���ݣ�����ͼ���ڽӱ�
{
	FILE* fp;
	fp = fopen(FileName, "rb");
	if(fp == NULL){
		printf("file not found\n");
		return ERROR;
	}

	fread(&G.vexnum, sizeof(int), 1, fp);
	fread(&G.arcnum, sizeof(int), 1, fp);
	fread(&G.kind, sizeof(int), 1, fp);
	
	int t = 0;
	for(int i=0; i<G.vexnum; i++){
		ArcNode* tail = (ArcNode*)malloc(sizeof(ArcNode));	//��ʱ�����յ�ͷ��㣬����β�� 
		tail->nextarc = NULL; 
		fread(&G.vertices[i].data, sizeof(VertexType), 1, fp);
		G.vertices[i].firstarc = tail;
		
		do{
			fread(&t, sizeof(int), 1, fp);
			if(t != -1){
				ArcNode* p = (ArcNode*)malloc(sizeof(ArcNode));
				p->adjvex = t;
				p->nextarc = NULL;				
				
				tail->nextarc = p;
				tail = p;
			}
		}while(t != -1);
		
		tail = G.vertices[i].firstarc;
		G.vertices[i].firstarc = tail->nextarc;
		free(tail);	//�ͷ�ͷ��� 
	}
	fclose(fp);
	return OK;
}


status AddGraph(ALGraphs &Gs, char name[])
//18ͼ�����
{
	ALGraph *pG = (ALGraph*)malloc(sizeof(ALGraph));
	pG->vexnum = 0;
	pG->arcnum = 0;
	pG->kind = UDG;
	
	Gs.elem[Gs.length].G.vexnum = 0;
	Gs.elem[Gs.length].G.arcnum = 0;
	Gs.elem[Gs.length].G.kind = UDG;
	
	strcpy(Gs.elem[Gs.length].name, name);
	Gs.length++;
	
	return OK;
}

status RemoveGraph(ALGraphs &Gs, char name[])
//19ͼ���Ƴ� 
{
	status flag = ERROR;
	
	for(int i=0; flag==ERROR && i<Gs.length; i++)
	{
		if(strcmp(Gs.elem[i].name,name)==0){
			DestroyGraph(Gs.elem[i].G);
			for(int j=i; j<Gs.length-1; j++)
				Gs.elem[j] = Gs.elem[j+1];
			Gs.length--;
			flag = OK; 
		}	
	}
	
	return flag;
}

status SwitchGraph(ALGraphs Gs, char name[], ALGraph &G)
//20 ͼ���л� 
{
	status flag = ERROR;
	
	for(int i=0; flag==ERROR && i<Gs.length; i++)
	{
		if(strcmp(Gs.elem[i].name,name)==0){
			G = Gs.elem[i].G;
			flag = OK; 
		}	
	}
	
	return flag;
}

int LocateGraph(ALGraphs Gs, char name[])
//21ͼ�Ĳ��� 
{
	int ans = -1;
	for(int i=0; ans==-1 && i<Gs.length; i++)
		if(strcmp(Gs.elem[i].name,name)==0)
			ans = i;
	return ans;
	
}

status Upload(ALGraphs &Gs, char name[], ALGraph &G)
{
	int i = LocateGraph(Gs, name);
	if(i != -1){
		printf("���¡���"); 
		Gs.elem[i].G = G;
	}
	else{
		printf("��ӡ���"); 
		AddGraph(Gs, name);
		Gs.elem[Gs.length-1].G = G;
	}
	return OK;
}
