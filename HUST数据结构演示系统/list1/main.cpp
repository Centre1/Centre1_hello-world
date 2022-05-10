/* Linear Table On Sequence Structure */
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include "def.h"
#include "stu.h"
#include "addition.h"
#define N 255
#define LNE "�����Ա�����!"

//void menu(void);
//void judge(int flag); 

SqList L;
LISTS Lists;
char name[N];	//�����ΪN

int main(void){
	menu();
	L.elem = NULL;
	InitLists(Lists);
	int op=1;		
	while(op){
		status flag = INFEASIBLE;
		ElemType e;		int i=0, t=0;
		memset(name, 0, sizeof(name));
		printf("    ��ѡ����Ĳ���[0~24]: ");
		scanf("%d",&op);
	    switch(op){
			case 1:
				if(InitList(L)==OK)	printf("���Ա����ɹ���\n");
				else printf("���Ա���ʧ�ܣ�(�Ѵ���)\n");
				getchar();
				break;
			case 2:
				if(DestroyList(L)==OK)	printf("���Ա����ٳɹ���\n");
				else printf("���Ա�����ʧ�ܣ�(������)\n");
				getchar();
				break;
			case 3:
				if(ClearList(L)==OK)	printf("���Ա���ճɹ���\n");
				else printf("���Ա����ʧ�ܣ�(������)\n");
				getchar();
				break;
			case 4:
				flag = ListEmpty(L); 
				if(flag==TRUE)		printf("�գ�\n");
				else if(flag==ERROR)printf("��Ϊ�գ�\n");
				else	printf(LNE);
				getchar();
				break;
			case 5:
				t = ListLength(L); 
				if(t==INFEASIBLE)	printf(LNE);
				else printf("��ǰ���Ա���Ϊ %d\n", t);
				getchar();
				break;
			case 6:
				printf("���������Ԫ����ţ� ");
				scanf("%d", &i);
				flag = GetElem(L, i, e);
				if(flag == OK)			printf("��%d��Ԫ��Ϊ %d\n", i, e);
				else if(flag == ERROR)	printf("�Ƿ�����!(�����ڸ����Ԫ��)\n");
				else printf(LNE);
				getchar();
				break;
			case 7:
				printf("����Ŀ��Ԫ�أ� ");
				scanf("%d", &e);
				i = LocateElem(L, e);
				if(i == INFEASIBLE)		printf(LNE);
				else if(i == ERROR)	printf("�����ڸ�Ԫ�أ�\n");
				else printf("Ԫ�� %d �����Ϊ %d\n", e, i);  
				getchar();
				break;
			case 8:
				printf("����Ŀ��Ԫ�أ� ");
				scanf("%d", &e);
				ElemType pre;
				flag = PriorElem(L, e, pre);
				if(flag == INFEASIBLE)	printf(LNE);
				else if(flag == ERROR)	printf("�����ڸ�Ԫ�ػ��Ԫ����ǰ����\n");
				else printf("Ԫ�� %d ��ǰ��Ϊ %d\n", e, pre);  
				getchar();
				break;
			case 9:
				printf("����Ŀ��Ԫ�أ� ");
				scanf("%d", &e);
				ElemType next;
				flag = NextElem(L, e, next);
				if(flag == INFEASIBLE)	printf(LNE);
				else if(flag == ERROR)	printf("�����ڸ�Ԫ�ػ��Ԫ���޺�̣�\n");
				else printf("Ԫ�� %d �ĺ��Ϊ %d\n", e, next);     
				getchar();
				break;
			case 10:
				printf("����λ�ã�0��ʾ���뵽ĩβ���� ");	scanf("%d", &i); 
				printf("����Ԫ�أ� ");	scanf("%d", &e);
				flag = ListInsert(L, i, e);
				if(flag == OK)	printf("����ɹ���\n");
				else if(flag == ERROR) printf("�Ƿ��Ĳ���λ��!\n");
				else printf(LNE);
				getchar();
				break;
			case 11:
				printf("�����ɾ����λ�ã� ");	scanf("%d", &i);
				flag = ListDelete(L, i, e);
				if(flag == OK)	printf("ɾ���ɹ�����ɾ��Ԫ��Ϊ %d\n", e);
				else if(flag == ERROR) printf("��λ����Ԫ�أ�\n");
				else printf(LNE); 
				getchar();
				break;
			case 12:
				flag = ListTraverse(L);
				if(flag == OK)	printf("success!\n");
				else if(flag == ERROR) printf("���Ա��ǿձ�\n");
				else printf(LNE);
				getchar();
				break;
	/*---------------------������------------------------------*/
			case 13:
				if(L.elem == NULL)		printf(LNE);
				else if(L.length == 0)	printf("���Ա��ǿձ�\n");
				else printf("���������������Ϊ %d\n", MaxSubArray(L));
				getchar();
				break; 
			case 14:
				if(L.elem == NULL)		printf(LNE);
				else if(L.length == 0)	printf("���Ա��ǿձ�\n");
				else{
					printf("�����������������k: ");
					scanf("%d", &t);
					printf("��Ϊ %d �������������� %d ��\n", t, SubArrayNum(L,t));
				}
				getchar();
				break; 
			case 15:
				judge(sortList(L));
				getchar();
				break;
			case 16:
				printf("���뱣�浽���ļ����� ");	//��֧�ֿո� 
				scanf("%s", name);
				flag = SaveList(L, name);
				judge(flag);
				getchar();
				break;
			case 17:
				printf("�����ȡ���ļ����� ");	//��֧�ֿո� 
				scanf("%s", name);
				flag = LoadList(L, name);
				if(flag ==INFEASIBLE)	printf("���Ѵ��ڣ��޷���ȡ\n");
				else if (flag==ERROR)	printf("�ļ�������\n");
				else	printf("�ɹ�"); 
				getchar();
				break;
			case 18:
				printf("�����½������Ա����� ");
				scanf("%s", name);
				flag = AddList(Lists, name);
				judge(flag); 
				getchar();
				break;
			case 19:
				printf("�����ɾ�������Ա����� ");
				scanf("%s", name);
				flag = RemoveList(Lists, name);
				judge(flag); 
				getchar();
				break;
			case 20:
				printf("�������Ա����ƣ� ");
				scanf("%s", name); 
				flag = SwitchList(Lists, L, name);
				judge(flag); 
				getchar();
				break;
			case 21:
				printf("�������Ա����ƣ� ");
				scanf("%s", name); 
				flag = LocateList(Lists, name);
				if(flag == INFEASIBLE)	printf("������!\n");
				else	printf("%s ��λ���� %d\n", name, flag);
				getchar();
				break;
			case 22:
				flag = ListsTraverse(Lists);
				judge(flag);
				getchar();
				break;
			case 23:
				flag = GetName(Lists, L);
				judge(flag);
				getchar();
				break;
			case 24:
				printf("�������Ա����ƣ� ");
				scanf("%s", name); 
				flag = UploadList(Lists, L, name);
				if(flag == OK)	printf("��ӳɹ���\n");
				else if(flag == ERROR)	printf("���ʧ�ܣ����Ѵ��ڻ�����ռ䲻�㣩\n");
				else printf(LNE);			
				getchar();
				break;
			case 0:
				break;	
			case 999:
				menu();
				break;	
			default:	//δ����ָ�����ϵͳ 
				system("cls");
				menu();
				break;
		}//end of switch
		printf("\n"); 
	}//end of while
	printf("��ӭ�´���ʹ�ñ�ϵͳ��\n");
}//end of main()


