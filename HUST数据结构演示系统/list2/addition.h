#include <string.h>
#include "def.h"
//#include "list.h"
void menu(void)
{
	printf("\n\n");
	printf("      Menu for Linear Table On Sequence Structure \n");
	printf("-------------------------------------------------\n");
	printf("	1.  InitList	\t13. reverseList\n");
	printf("	2.  DestroyList \t14. RemoveNthFromEnd\n");
	printf("	3.  ClearList	\t15. sortList \n");
	printf("	4.  ListEmpty	\t16. SaveList\n");
	printf("	5.  ListLength	\t17. LoadList\n");
	printf("	6.  GetElem	    \t18. AddList\n");
	printf("	7.  LocateElem	\t19. RemoveList\n");
	printf("	8.  PriorElem	\t20. LocateList\n");
	printf("	9.  NextElem	\t21. SwitchList\n");
	printf("	10. ListInsert	\t22. ListsTraverse\n");
	printf("	11. ListDelete	\t23. GetName\n");
	printf("	12. ListTrabverse\t24. UploadList\n");
	printf("	0.  Exit	    \t999. menu\n");
	printf("-------------------------------------------------\n");
}


void judge(int flag)
{
	switch(flag)
	{
		case OK:
			printf("�����ɹ���");
			break;
		case ERROR:
			printf("����ʧ�ܣ����Ƿ�������Ŀ�겻���ڵȣ�");
			break; 
		case INFEASIBLE:
			printf("�����ڣ�");
			break;
		default:
			printf("δ֪����");
			break;
	}
}

void INIT(LISTS &Lists, LinkList &L)
{
	Lists = (LsNode*)malloc(sizeof(LsNode));
	Lists->L = NULL;
	strcpy(Lists->name, "LISTS_HEAD");
	Lists->next = NULL;
}

status SwitchList(LISTS Lists, LinkList &L, char ListName[])
// 21�л���ǰ���Ա�ΪListName 
{
	status flag = ERROR;
	LISTS p = Lists;
    while(flag==ERROR && p->next){
    	p = p->next;
    	if(strcmp(p->name, ListName) == 0){
    		L = p->L;
    		flag = OK;
		}
	}
	return flag;
}

status ListsTraverse(LISTS Lists)
// 22�����������Ա����� 
{
	if(Lists->next == NULL)
		return ERROR;
	
	LISTS p = Lists->next;
	int i = 1;
	printf("\n----------------- all lists -------------------\n");
	printf("%d\t%s", i, p->name);
    while(p->next){
    	p = p->next;
    	i++;
    	printf("\n%d\t%s", i, p->name);
	}
	printf("\n-------------------- end -----------------------\n");
	return OK;
}


status GetName(LISTS Lists, LinkList L, char *ListName)//
// 23�鿴��ǰ���Ա�����
{
	if(L == NULL)	return INFEASIBLE;
	
	status flag = ERROR;
	LISTS p = Lists;
    while(flag==ERROR && p->next){
    	p = p->next;
    	if(p->L == L){
			strcpy(ListName, p->name);
    		flag = OK;
		}
	}
	return flag;
}

status UploadList(LISTS &Lists, LinkList L, char ListName[])
// 24����ǰ����ӵ������
{
	if(L == NULL)	return INFEASIBLE;
	status flag = OK;
	LISTS p = Lists;
	while(p->next){	//�ұ�β�����������ر� 
		p = p->next;
		if(p->L==L || strcmp(p->name, ListName)==0)
			flag = ERROR; 
	}
	
	if(flag == OK){
		LISTS s = (LsNode*)malloc(sizeof(LsNode));
		if(s == NULL)
			flag = ERROR;
		else{
			strcpy(s->name, ListName);
			s->L = L;
			s->next = NULL; 
			
			if(flag == OK)
				p->next = s;
		}
	}
	
	return flag;
}
 

