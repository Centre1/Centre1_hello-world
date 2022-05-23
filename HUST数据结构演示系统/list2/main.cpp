/* Linear Table On Sequence Structure */
#include <stdio.h>
#include <stdlib.h>
#include "def.h"
#include "stu.h"
#include "addition.h"
#define N 255
#define LNE "�����Ա����ڣ�"

//void menu(void);
//void judge(int flag); 

LinkList L = NULL;
LISTS Lists = NULL;
char name[N];	//�����ΪN

int main(void){
	INIT(Lists, L);
	menu();
	int op=1;
	
			
	while(op){
		status flag = INFEASIBLE;
		ElemType e;		int t=0;
		memset(name, 0, sizeof(name));
		printf("    ��ѡ����Ĳ���[0~24]: ");
		scanf("%d", &op);
		
	    switch(op){
			case 1:
				flag = InitList(L);
				if(flag == OK)	printf("��ʼ���ɹ���");
				else	printf("��ʼ��ʧ�ܣ������Ѵ��ڣ�");
				break;
			case 2:
				flag = DestroyList(L);
				judge(flag);
				break;
			case 3:
				flag = ClearList(L);
				judge(flag);
				break;
			case 4:
				flag = ListEmpty(L);
				if(flag == TRUE)	printf("�գ�");
				else if(flag == FALSE)	printf("�ǿգ�");
				else printf(LNE);
				break;
			case 5:
				t = ListLength(L);
				if(t == INFEASIBLE)	printf(LNE);
				else	printf("���Ա���Ϊ %d", t);
				break;
			case 6:
				printf("����Ԫ����ţ� ");
				scanf("%d", &t);
				flag = 	GetElem(L, t, e);
				if(flag == OK)	printf("��%d��Ԫ���� %d", t, e);
				else if(flag == ERROR)	printf("����Ų����ڣ�");
				else printf(LNE); 
				break;
			case 7:
				printf("����Ŀ��Ԫ�أ� ");
				scanf("%d", &e);
				flag = LocateElem(L, e);
				if(flag == INFEASIBLE)	printf(LNE);
				else if(flag == ERROR)	printf("��Ԫ�ز����ڣ�");
				else printf("Ԫ��%d������� %d", e, flag);
				break;
			case 8:
				printf("����Ŀ��Ԫ�أ� ");
				scanf("%d", &e);
				ElemType pre;
				flag = PriorElem(L, e, pre);
				if(flag == OK)	printf("Ԫ��%d��ǰ���� %d", e, pre);
				else if(flag == ERROR)	printf("��Ԫ�ز����ڻ���ǰ����");
				else printf(LNE);
				break;
			case 9:
				printf("����Ŀ��Ԫ�أ� ");
				scanf("%d", &e);
				ElemType next;
				flag = NextElem(L, e, next);
				if(flag == OK)	printf("Ԫ��%d�ĺ���� %d", e, next);
				else if(flag == ERROR)	printf("��Ԫ�ز����ڻ��޺�̣�");
				else printf(LNE);
				break;
			case 10:
				printf("����λ�ã� ");	scanf("%d", &t); 
				printf("����Ԫ�أ� ");	scanf("%d", &e);
				flag = ListInsert(L, t, e);
				judge(flag);
				break;
			case 11:
				printf("����λ�ã� ");	scanf("%d", &t); 
				flag = ListDelete(L, t, e);
				if(flag == OK)	printf("ɾ�� %d �ɹ�", e);
				else if(flag == ERROR)	printf("����Ų����ڣ�");
				else printf(LNE);
				break;
			case 12:
				flag = ListTraverse(L);
				if(flag == OK)	printf("������ϣ�");
				else if(flag == ERROR) printf("�ձ�");
				else printf(LNE); 
				break; 
				
	/*----------------------------������-----------------------------*/	
			case 13:
				flag = reverseList(L);
				judge(flag);
				break;
			case 14:
				printf("���뵹����ţ� ");
				scanf("%d", &t);
				flag = RemoveNthFromEnd(L, t);
				judge(flag);
				break;
			case 15:
				flag = sortList(L);
				judge(flag);
				break;
			case 16:
				printf("����洢�ļ��� ");
				scanf("%s", name); 
				flag = SaveList(L, name);
				if(flag == OK)	printf("����ɹ���");
				else if(flag == ERROR)	printf("��Ϊ�գ�");
				else printf(LNE); 
				break;
			case 17:
				printf("�����ȡ�ļ��� ");
				scanf("%s", name);
				flag = LoadList(L, name);
				if(flag == OK)	printf("��ȡ�ɹ���");
				else if(flag == ERROR)	printf("��ȡ���󣡣��ļ������ڣ�");
				else printf("���Ա��Ѵ����Ҳ�Ϊ�գ�"); 
				break;
			case 18:
				printf("�����½����Ա����ƣ� ");
				scanf("%s", name);
				flag = AddList(Lists, name);
				if(flag == OK)	printf("�½��ɹ���");
				else	printf("�½�ʧ�ܣ����������ռ䲻��ȣ�");
				break;
			case 19:
				printf("����ɾ�����Ա����ƣ� ");
				scanf("%s", name);
				flag = RemoveList(Lists, name);
				judge(flag);
				break;
			case 20:
				printf("����������Ա����ƣ� ");
				scanf("%s", name);
				t = LocateList(Lists, name);
				if(t == 0)	printf("δ�ҵ���");
				else	printf("���Ա� %s ������� %d", name, t); 
				break;
			case 21:
				printf("����Ŀ�����Ա�����ƣ� ");
				scanf("%s", name);
				flag = SwitchList(Lists, L, name);
				judge(flag);
				break;
			case 22:
				flag = ListsTraverse(Lists);
				if(flag == ERROR)	printf("�����Ա�"); 
				break;
			case 23:
				flag = GetName(Lists, L, name);
				if(flag == OK)	printf("��ǰ���Ա�Ϊ %s", name); 
				else if(flag == ERROR)	printf("���ڹ�����У�");
				else printf(LNE);
				break;
			case 24:
				printf("�������Ա����ƣ� ");
				scanf("%s", name);
				flag = UploadList(Lists, L, name);
				if(flag == OK)	printf("��ӳɹ���");
				else if(flag == ERROR)printf("���ʧ�ܣ������ڹ�����л�������");
				else printf(LNE);
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
		printf("\n\n"); 
	}//end of while
	
	
	printf("��ӭ�´���ʹ�ñ�ϵͳ��\n");
}//end of main()


