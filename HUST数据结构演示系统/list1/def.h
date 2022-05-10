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
#endif

#ifndef _ELEM_
#define _ELEM_ 
typedef int status;  
typedef int ElemType; //����Ԫ�����Ͷ���
#endif


#ifndef _LIST_
#define _LIST_
#define LIST_INIT_SIZE 100
#define LISTINCREMENT  10  
typedef int ElemType;
typedef struct{  //˳���˳��ṹ���Ķ���  
	ElemType *elem;  
	int length;
	int listsize;  
}SqList;  
#endif

#ifndef _LISTS_
#define _LISTS_
#define LISTS_INIT_SIZE 100
typedef struct LsNode{  //���Ա�Ĺ�����壨˳��� 
	struct{
		char name[30];
		SqList L;	
	}elem[LISTS_INIT_SIZE];
	int length;
	int listsize;
}LISTS;
#endif 


#endif
