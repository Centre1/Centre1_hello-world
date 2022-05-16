#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "def.h"
#include "stu.h"
#define N 10005
#define tip "������Ŀ��key��"
#define g(t) (G.vertices[t].data) 


void menu(void)
{
	printf("\n\n");
	printf("      Menu for Linear Table On Sequence Structure \n");
	printf("-----------------------------------------------------\n");
	printf("	1. CreateCraph \t\t13. VerticesSetLessThanK\n");
	printf("	2. DestroyGraph\t\t14. ShortestPathLength\n");
	printf("	3. LocateVex	\t15. ConnectedComponentsNums \n");
	printf("	4. PutVex 	\t16. SaveGraph\n");
	printf("	5. FirstAdjVex	\t17. LoadGraph\n");
	printf("	6. NextAdjVex   \t18. AddGraph\n");
	printf("	7. InsertVex	\t19. RemoveGraph\n");
	printf("	8. DeleteVex	\t20. SwitchGraph\n");
	printf("	9. InsertArc	\t21. LocateGraph\n");
	printf("	10.DeleteArc	\t22. Upload\n");
	printf("	11.DFSTraverse\t\n");
	printf("	12.BFSTraverse\t\n");
	printf("	0.  Exit	    \t999. menu\n");
	printf("-----------------------------------------------------\n");
}


void judge(int flag)
{
	switch(flag)
	{
		case OK:
			printf("�����ɹ���");
			break;
		case ERROR:
			printf("����ʧ�ܣ���key�ظ���Ŀ�겻���ڵȣ�");
			break; 
		case INFEASIBLE:
			printf("ͼ�����ڣ�");
			break;
		default:
			printf("δ֪����");
			break;
	}
}
//
//void INIT(ALGraphs &Gs){
//	
//	
//	Gs.elem[0].G = (ALGraph*)malloc(sizeof(ALGraph));
//	strcpy(Gs.elem[0].name, "origin");
//	Gs.length++; 
//}


void print(VertexType data)
{
	printf("key = %d    others = %s\n", data.key, data.others);
}

void option_Graph(ALGraphs &Gs)
{
	menu();
	char name[N];	//�����ΪN
	Gs.listsize = GRAPHS_INIT_SIZE;
	Gs.length = 0;
	AddGraph(Gs, "origin");
	ALGraph G = Gs.elem[0].G;
	
	int op=1;
	while(op){
		status flag = INFEASIBLE;
		memset(name, 0, sizeof(name));
		KeyType e = -1;
		int t = -1;
		
		printf("    ��ѡ����Ĳ���[0~24]: ");
		scanf("%d", &op);
	    switch(op){
			case 1:{
				printf("�����붥�㡢�������ݣ�\n") ;
				VertexType V[30];
				KeyType VR[100][2];
				int i = 0;
				do {
				    scanf("%d%s",&V[i].key,V[i].others);
				} while(V[i++].key!=-1);
				i = 0;
				do {
				    scanf("%d%d",&VR[i][0],&VR[i][1]);
				} while(VR[i++][0]!=-1);
				flag = CreateCraph(G, V, VR);
				judge(flag);
				break;
			}
			
			case 2:
				flag = DestroyGraph(G);
				judge(flag);
				break;
			
			case 3:
				printf(tip);	scanf("%d", &e);
				t = LocateVex(G, e);
				if(t != -1){
					printf("λ��Ϊ��%d\n", t);
					print(g(t)); 
				}
				else printf("Ŀ�겻���ڣ�"); 
				break;
			
			
			case 4:{
				VertexType value; 
				printf(tip);	scanf("%d", &e);
				printf("��key��"); scanf("%d", &value.key);
				printf("��others��"); scanf("%s", value.others); 
				flag = PutVex(G, e, value);
				judge(flag);
				break;
			}
			
			case 5:
				printf(tip);	scanf("%d", &e);
				t = FirstAdjVex(G, e);
				if(t == -1)	printf("Ŀ�궥�㲻���ڻ��޵�һ�ڽӵ㣡");
				else {
					printf("��һ�ڽӵ�λ��%d\n", t);
					print(g(t));
				}
				break;
			

			case 6:{
				printf(tip);	scanf("%d", &e);
				KeyType w;
				printf("������Զ��㣺"); scanf("%d", &w); 
				t = NextAdjVex(G, e, w);
				if(t == -1)	printf("Ŀ�궥�㲻���ڻ�����һ�ڽӵ㣡");
				else {
					printf("��һ�ڽӵ�λ��%d\n", t);
					print(g(t));
				}
				break;
			}
				
			case 7:{
				VertexType v;
				printf(tip); scanf("%d", &v.key);
				printf("����others��"); scanf("%s", v.others); 
				flag = InsertVex(G,v);
				judge(flag);
				break;
			}
				
			case 8:
				printf(tip); scanf("%d", &e);
				flag = DeleteVex(G,e);
				judge(flag);
				break;
			
			
			case 9:{
				KeyType v,w;
				printf("���뻡��һ�ˣ�"); scanf("%d", &v);
				printf("���뻡��һ�ˣ�"); scanf("%d", &w); 
				flag = InsertArc(G,v, w);
				judge(flag);
				break;
			}
			
			case 10:{
				KeyType v,w;
				printf("���뻡��һ�ˣ�"); scanf("%d", &v);
				printf("���뻡��һ�ˣ�"); scanf("%d", &w); 
				flag = DeleteArc(G,v, w);
				judge(flag);
				break;
			}
			
			case 11:
				printf("���������������������£�\n"); 
				flag = DFSTraverse(G, visit);
				judge(flag);
				break;
			case 12:
				printf("���������������������£�\n"); 
				flag = BFSTraverse(G, visit);
				judge(flag);
				break;
				
	/*----------------------------������-----------------------------*/	
			
			case 13:{
				printf(tip); scanf("%d", &e);
				printf("����������ޣ�"); scanf("%d", &t);
				int *ans = VerticesSetLessThanK(G, e, t);
				if(ans == NULL) printf("Ŀ�겻����");
				else if(ans[1] == -1) printf("�޾���С��k�ĵ�");
				else{
					int i;
					for(i=1; ans[i]!=-1; i++)
						print(g(ans[i]));
					printf("һ���� %d ����", i-1);
					free(ans);
				}
				break;
			}
		
			case 14:{
				KeyType v, w;
				printf("key1��"); scanf("%d", &v); 
				printf("key2��"); scanf("%d", &w);
				int dis = ShortestPathLength(G, v, w);
				if(dis == -1)
					printf("v��w�����ڣ�����·����"); 
				else
					printf("���·���ĳ����� %d", dis);
				break;
			}
			
			
			case 15:
				t = ConnectedComponentsNums(G);
				printf("��ͨ�����ĸ����� %d", t); 
				break;
			
			case 16:
				printf("����洢�ļ��� ");
				scanf("%s", name); 
				flag = SaveGraph(G, name);
				if(flag == OK)	printf("����ɹ���");
				else if(flag == ERROR)	printf("����ʧ�ܣ�");
				else printf("UNKNOWN ERROR!");
				break;
			case 17:
				printf("�����ȡ�ļ��� ");
				scanf("%s", name);
				flag = LoadGraph(G, name);
				if(flag == OK)	printf("��ȡ�ɹ���");
				else if(flag == ERROR)	printf("��ȡ���󣡣��ļ������ڵȣ�");
				else printf("UNKNOWN ERROR!"); 
				break;
			
			
			case 18:{
				printf("�����½�ͼ����");
				scanf("%s", name);
				flag = AddGraph(Gs, name);
				judge(flag);
				break;
			}
			
			case 19:{
				printf("����ɾ��ͼ����");
				scanf("%s", name);
				flag = RemoveGraph(Gs, name);
				judge(flag);
				break;
			}
			
			case 20:{
				printf("�����л�ͼ����");
				scanf("%s", name);
				flag = SwitchGraph(Gs, name, G);
				judge(flag);
				break;
			}
			
			case 21:{
				printf("�������ͼ����");
				scanf("%s", name);
				t = LocateGraph(Gs, name);
				if(t == -1) printf("δ�ҵ�");
				else printf("ͼ %s �����Ϊ %d", name, t+1); //��1��ʼ 
				break;
			}
			
			case 22:{
				printf("�����ϴ�ͼ����");
				scanf("%s", name);
				flag = Upload(Gs, name, G);
				judge(flag);
				break;
			} 


			case 0:
				printf("��ӭ�´���ʹ�ñ�ϵͳ��");
				break;
			case 999:
				menu();
				break;	
			default:	//δ����ָ�ˢ��ϵͳ���� 
				system("cls");
				menu();
				break;
		}//end of switch
		printf("\n\n");
	}//end of while
}

