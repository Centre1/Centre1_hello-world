#include "def.h"
#include "stu.h"
#define N 10005
#define tip "����Ŀ��key��"

//1 a 2 b 0 null  0 null 3 c 4 d  0 null  0 null 5 e  0 null  0 null -1 null

BiTree T = NULL;
TREES Trees;
TElemType definition[N];
char name[N];	//�����ΪN
int now = 0;

int main(void){
	menu();
	InitTrees(Trees);
	int op=1;
	while(op){
		status flag = INFEASIBLE;
		KeyType e = 0;	TElemType value;
		memset(name, 0, sizeof(name));
		printf("    ��ѡ����Ĳ���[0~24]: ");
		scanf("%d", &op);
		
	    switch(op){
			case 1:
				int i; i=0;
				if(T) printf("���Ѵ���");
				else{
					printf("�������������ǰ��������У�\n");
					do{
						scanf("%d%s",&definition[i].key,definition[i].others);
					} while (definition[i++].key!=-1);
					judge( CreateBiTree(T, definition) );
				} 
				break;
			case 2:
				if(T) flag = DestroyBiTree(T);
				judge(flag);
				break;
			case 3:
				if(T) flag = ClearBiTree(T);
				judge(flag);
				break;
			case 4:
				flag = BiTreeEmpty(T);
				if(flag == TRUE)		printf("�գ�");
				else if(flag == FALSE)	printf("�ǿգ�");
				else printf("�������ڣ�"); 
				break;
			case 5:
				int t;
				t = BiTreeDepth(T);
				printf("�������Ϊ %d", t);
				break;
			case 6:
				printf(tip);	scanf("%d", &e);
				BiTNode* obj;
				obj = LocateNode(T, e);
				if(obj){
					printf("ֵ���£�\n");
					print(obj); 
				}
				else	printf("Ŀ�겻���ڣ�"); 
				break;
			case 7:
				printf(tip);	scanf("%d", &e);
				printf("��key��"); scanf("%d", &value.key);
				printf("��others��"); scanf("%s", value.others); 
				judge( Assign(T, e, value) );
				break;
			case 8:
				printf(tip);	scanf("%d", &e);
				BiTNode* brother;
				brother = GetSibling(T, e);
				if(brother == NULL)	printf("��Ԫ�ز����ڻ����ֵܣ�");
				else {
					printf("�ֵ�ֵ���£�\n");
					print(brother);
				}
				break;
			case 9:
				printf(tip);	scanf("%d", &e);
				int LR;
				printf("����λ�ã�0�� 1�� -1������"); 	scanf("%d", &LR); 
				printf("������Ҫ����Ľڵ�ֵ\n");
				printf("key��"); scanf("%d",&value.key);
				printf("others��"); scanf("%s", value.others); 
				flag = InsertNode(T, e, LR, value);
				judge(flag); 
				break;
			case 10:
				if(T){
					printf(tip); scanf("%d", &e); 
					flag = DeleteNode(T,e);
				}
				judge(flag);
				break;
			case 11:
				printf("��������������\n"); 
				flag = PreOrderTraverse(T, visit);
				printf("\n");
				judge(flag);
				break;
			case 12:
				printf("��������������\n"); 
				flag = InOrderTraverse(T, visit);
				printf("\n");
				judge(flag);
				break;
			case 13:
				printf("��������������\n"); 
				flag = PostOrderTraverse(T, visit);
				printf("\n");
				judge(flag);
				break;
			case 14:
				printf("��������������\n"); 
				flag = LevelOrderTraverse(T, visit);
				printf("\n");
				judge(flag);
				break;
				
	/*----------------------------������-----------------------------*/	
			case 15:
				int ans;
				ans = MaxPathSum(T);
				printf("���·���ͣ�%d", MaxPathSum(T));
				break;
			case 16:
				KeyType e1, e2;
				printf("��������Ŀ��key: \n");
				printf("key1��"); scanf("%d", &e1);
				printf("key2��"); scanf("%d", &e2);
				BiTNode* ancestor;
				ancestor = LowestCommonAncestor(T, e1,e2);
				printf("�����������ֵΪ��\n");
				print(ancestor);			 
				break;
			case 17:
				flag = InvertTree(T);
				judge(flag);
				break;
			
			case 18:
				printf("����洢�ļ��� ");
				scanf("%s", name); 
				flag = SaveBiTree(T, name);
				if(flag == OK)	printf("����ɹ���");
				else if(flag == ERROR)	printf("����ʧ�ܣ�");
				else printf("Unknow Error!");
				break;
			case 19:
				printf("�����ȡ�ļ��� ");
				scanf("%s", name);
				flag = LoadBiTree(T, name);
				if(flag == OK)	printf("��ȡ�ɹ���");
				else if(flag == ERROR)	printf("��ȡ���󣡣��ļ������ڣ�");
				else printf("Unknow Error!"); 
				break;
			
			case 20:
				printf("���������ƣ� ");
				scanf("%s", name); 
				flag = SwitchTree(Trees, T, name);
				judge(flag);
				if(flag==OK) now = LocateBiTree(Trees, name);
				break;
			case 21:
				printf("�����½��������� ");
				scanf("%s", name);
				flag = AddBiTree(Trees, name);
				judge(flag); 
				break;
			case 22:
				printf("�����ɾ���������� ");
				scanf("%s", name);
				flag = RemoveBiTree(Trees, name);
				judge(flag); 
				break;
			
			case 23:
				printf("���������ƣ� ");
				scanf("%s", name); 
				flag = LocateBiTree(Trees, name);
				if(flag == INFEASIBLE)	printf("������!\n");
				else	printf("%s ��λ���� %d\n", name, flag);
				break;
			case 24:
				printf("���������ƣ� ");
				scanf("%s", name); 
				flag = Upload(Trees, T, name);
				if(flag == OK) printf("���³ɹ�");
				else if(flag == ERROR) printf("�����ɹ�"); 
				break;
			case 0:
				printf("��ӭ�´���ʹ�ñ�ϵͳ��");
				break;
			case 999:
				menu();
				break;	
			default:	//δ����ָ�����ϵͳ 
				system("cls");
				menu();
				break;
		}//end of switch
		printf("\n\n");
	}//end of while
	
	
}//end of main()


