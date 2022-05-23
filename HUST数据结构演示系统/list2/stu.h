#include <string.h>
#include "def.h"

status InitList(LinkList &L)
// 1���Ա�L�����ڣ�����һ���յ����Ա�����OK�����򷵻�INFEASIBLE��
{
	status flag = INFEASIBLE;	//Ĭ��ʧ��

	if(L){	//L���� 
		flag = INFEASIBLE;
	}
	else{
		L = (LNode*)malloc(sizeof(LNode));	//������ͷ 
		L->next = NULL;	//��ʼ��
		flag = OK;
	}
	
	return flag;	//��һ����
}

status DestroyList(LinkList &L)
// 2������Ա�L���ڣ��������Ա�L���ͷ�����Ԫ�صĿռ䣬����OK�����򷵻�INFEASIBLE��
{
	if(L == NULL){	//L������ 
		return INFEASIBLE;
	}

	LinkList p = L;
	while(p){	//�ͷſռ� 
		LinkList t = p;
		p = p->next;
		free(t);
	}
	L = NULL;	//��Ϊδ��ʼ�� 
	return OK;
}

status ClearList(LinkList &L)
// 3������Ա�L���ڣ�ɾ�����Ա�L�е�����Ԫ�أ�����OK�����򷵻�INFEASIBLE��
{
	if(L == NULL){	//������
		return INFEASIBLE; 
	}
	
	LinkList p = L->next;	//�ӵ�һ������Ԫ�ؽڵ㿪ʼ 
	while(p){	//�ͷſռ� 
		LinkList t = p;
		p = p->next;
		free(t); 
	}
	L->next = NULL;	//�ָ���ʼ��״̬ 
	return OK;
}

status ListEmpty(LinkList L)
// 4������Ա�L���ڣ��ж����Ա�L�Ƿ�Ϊ�գ��վͷ���TRUE�����򷵻�FALSE��������Ա�L�����ڣ�����INFEASIBLE��
{
	status flag = INFEASIBLE;
	if(L == NULL){	//L������
		flag = INFEASIBLE; 
	} 
    else{
		if(L->next == NULL){    //�п�
			flag = TRUE;
		}
		else{
			flag = FALSE;
		}
	}
	return flag;	//���ٳ���
}

int ListLength(LinkList L)
// 5������Ա�L���ڣ��������Ա�L�ĳ��ȣ����򷵻�INFEASIBLE��
{
	if(L == NULL){	//L������ 
		return INFEASIBLE;
	}
	
	int len = 0;
	LinkList p = L; 
	while(p->next){
		p = p->next;
		len++;
	} 
	return len;
}

status GetElem(LinkList L, int i, ElemType &e)
// 6������Ա�L���ڣ���ȡ���Ա�L�ĵ�i��Ԫ�أ�������e�У�����OK�����i���Ϸ�������ERROR��������Ա�L�����ڣ�����INFEASIBLE��
{
	
	if(L == NULL){	//L������ 
		return INFEASIBLE;
	}
	
	status flag = ERROR;	//Ĭ�Ϸ���ʧ��
	if(i >= 1){
		LinkList p = L->next;
		int cnt = 0;
		while(p && ++cnt < i){	//���ö�·�����пգ����ж���� 
			p = p->next;
		}
		if(cnt == i){	//�Ϸ����� 
			e = p->data; 
			flag = OK; //��ȡ�ɹ� 
		} 
	}
	return flag;
}

status LocateElem(LinkList L,ElemType e)
// 7������Ա�L���ڣ�����Ԫ��e�����Ա�L�е�λ����ţ����e�����ڣ�����ERROR�������Ա�L������ʱ������INFEASIBLE��
{
	if(L == NULL){	//L does not exist
		return INFEASIBLE;
	}
	
	status flag = ERROR;	//Ĭ��δ�ҵ� 
	LinkList p = L->next;
	int cnt = 0;	
	while(flag == ERROR && p){
		cnt++;		//��ǰԪ�����
		if(p->data == e){
			flag = cnt;	//����
		}
		p = p->next;
	}
	return flag;
}


status PriorElem(LinkList L,ElemType e,ElemType &pre)
// 8������Ա�L���ڣ���ȡ���Ա�L�е�һ��e��ǰ����������pre�У�����OK�����û��ǰ��������ERROR��������Ա�L�����ڣ�����INFEASIBLE��
{
	if(L == NULL){	//L������ 
		return INFEASIBLE;
	}
	
	status flag = ERROR;	//Ĭ��δ�ҵ� 
	LinkList p = L->next;
	while(flag==ERROR && p && p->next){	//�ҵ�e���������ʱֹͣ 
		if(p->next->data == e){
			pre = p->data;
			flag = OK;
		}
		p = p->next;
	}
	return flag;
}


status NextElem(LinkList L,ElemType e,ElemType &next)
// 9������Ա�L���ڣ���ȡ���Ա�L��һ��e�ĺ�̣�������next�У�����OK�����û�к�̣�����ERROR��������Ա�L�����ڣ�����INFEASIBLE��
{
	if(L == NULL){
		return INFEASIBLE;
	}
	
	status flag = ERROR;	//Ĭ��δ�ҵ� 
	LinkList p = L->next;
	while(p){
		if(p->data==e && p->next){	//�к�� 
			next = p->next->data;
			flag = OK;
		}
		p = p->next; 
	}
	return flag;
}


status ListInsert(LinkList &L,int i,ElemType e)
// 10������Ա�L���ڣ���Ԫ��e���뵽���Ա�L�ĵ�i��Ԫ��֮ǰ������OK��������λ�ò���ȷʱ������ERROR��������Ա�L�����ڣ�����INFEASIBLE��
{
	if(L == NULL){
		return INFEASIBLE;
	} 
	
	status flag = ERROR;	//Ĭ�ϲ���ʧ��
	LinkList p = L;
	int cnt = 0;
	while(flag==ERROR && p){
		cnt++;	//p->next �����, nullҲ��
		if(cnt == i){
			LNode *s;
			s = (LNode*)malloc(sizeof(LNode));
			s->data = e;
			s->next = p->next;
			p->next = s;
            flag = OK;
		}
		p = p->next;
	}
	return flag;
}

status ListDelete(LinkList &L,int i,ElemType &e)
// 11������Ա�L���ڣ�ɾ�����Ա�L�ĵ�i��Ԫ�أ���������e�У�����OK����ɾ��λ�ò���ȷʱ������ERROR��������Ա�L�����ڣ�����INFEASIBLE��
{
    if(L == NULL){  //L������
        return INFEASIBLE;
    }

    status flag = ERROR;
    LinkList p = L;
    int cnt = 0;
    while(flag==ERROR && p && p->next){  //��·��ֹ NULL->next
        cnt++;  //p->next�����
        if(cnt == i){
            LinkList delet = p->next;
            p->next = delet->next;
            e = delet->data;
            free(delet);
            flag = OK;
        }
        p = p->next;
    }
    return flag;
}

status ListTraverse(LinkList L)
// 12������Ա�L���ڣ�������ʾ���Ա��е�Ԫ�أ�ÿ��Ԫ�ؼ��һ�񣬷���OK��������Ա�L�����ڣ�����INFEASIBLE��
{
    if(L == NULL)  //L������
        return INFEASIBLE;
	if(L->next == NULL)	//�ձ� 
		return ERROR;
	
    LinkList p = L->next;   //�ӵ�һ��Ԫ�ؿ�ʼ
    while(p){   //p==NULL ֹͣ
        if(p->next)
            printf("%d ", p->data);
        else
            printf("%d\n", p->data);  //ĩ���
        p = p->next;
    }
    return OK;
}

status reverseList(LinkList &L)
// 13��ʼ���������Ա�L�Ѵ��ڣ���������ǽ�L��ת��
{
	if(L == NULL)	return INFEASIBLE;

	LinkList pre, p;
	pre = NULL;
	p = L->next;
	while(p){
		LinkList t = pre;
		pre = p;
		p = p->next;
		pre->next = t;		
	}
	L->next = pre;
	return OK;
}


status RemoveNthFromEnd(LinkList &L, int n)
// 14��ʼ���������Ա�L�Ѵ����ҷǿ�, ��������Ǹ������е�����n���ڵ㣻
{
	if(L == NULL)	return INFEASIBLE;
	int len = ListLength(L); 
	if(len < n)	return ERROR;	//�Ƿ�λ�� 
	
	int id = len + 1 - n;	//��ɾ���ڵ����� 
//	LinkList p = L;
//	int cnt = 0;	//��ǰ������ 
//	while(cnt < id-1 && p->next){
//		p = p->next;
//		cnt++;
//	}
//	LinkList t = p->next; 
//	p->next = p->next->next;
//	free(t);
//	return OK;
	ElemType e;
	return ListDelete(L, id, e);
}


status sortList(LinkList L)
// 15��ʼ���������Ա�L�Ѵ��ڣ���������ǽ�L��С�������� 
{
	if(L == NULL)
		return INFEASIBLE;
	
	LinkList done = NULL;	//���ź���Ĳ��� 
	while(done != L->next){
		LinkList pre = L;
		LinkList p = L->next;
		for(; p->next!=done; pre=p,p=p->next)
			if(p->data > p->next->data){
				pre->next = p->next;
				p->next = p->next->next;
				pre->next->next = p;
				p = pre->next;	//��������� 
			}
		done = p;
	}
	return OK;
}


status SaveList(LinkList L,char FileName[])
// 16������Ա�L���ڣ������Ա�L�ĵ�Ԫ��д��FileName�ļ��У�����OK�����򷵻�INFEASIBLE��
{
    if(L == NULL){	//L���� 
        return INFEASIBLE;
    }

    FILE *fout;
    fout = fopen(FileName, "wb");
    if(fout==NULL || L->next==NULL)	return ERROR;
    
    LinkList p = L->next;
    while(p){   //����
    	fwrite(&(p->data), sizeof(ElemType), 1, fout);
        p = p->next;
    }
    fclose(fout);
    return OK;
}

status LoadList(LinkList &L,char FileName[])
// 17������Ա�L�����ڻ�գ���FileName�ļ��е����ݶ��뵽���Ա�L�У�����OK�����򷵻�INFEASIBLE��
{
    if(L!=NULL && L->next!=NULL){	//L���� 
        return INFEASIBLE;
    }

    FILE *fin;
    fin = fopen(FileName, "rb");
    if(fin == NULL)	return ERROR;
	 
    if(L == NULL)
		L = (LNode*)malloc(sizeof(LNode));  //������ͷ
    LinkList tail = L;  //βָ��
    int e;
    while(fread(&e, sizeof(ElemType), 1, fin)){ //e�洢�����data
        LNode *s;
        s = (LNode*)malloc(sizeof(LNode));
        s->data = e;
        tail->next = s;
        tail = s;
    }
    tail->next = NULL;
    fclose(fin);
    return OK;
}


status AddList(LISTS &Lists,char ListName[])
// 18ֻ��Ҫ��Lists������һ������ΪListName�Ŀ����Ա�
{
	status flag = OK;
	LISTS p = Lists;
	while(flag==OK && p->next){	//�ұ�β�������� 
		p = p->next;
		if(strcmp(p->name, ListName) == 0)
			flag = ERROR; 
	}
	
	if(flag == OK){
		LISTS s = (LsNode*)malloc(sizeof(LsNode));
		if(s == NULL)
			flag = ERROR;
		else{
			strcpy(s->name, ListName);
			s->L = NULL;
			flag = InitList(s->L);
			s->next = NULL; 
			
			if(flag == OK)
				p->next = s;
		}
	}
	
	return flag;
}

status RemoveList(LISTS &Lists,char ListName[])
// 19��Lists��ɾ��һ������ΪListName�����Ա�
{
    status flag = ERROR;
    
    LISTS p = Lists;
    while(flag==ERROR && p->next){
    	if(strcmp(p->next->name, ListName) == 0){
    		LISTS t = p->next;
			p->next = p->next->next;
    		free(t);
    		flag = OK;
		}
		else
    		p = p->next;
	}
	return flag;
}

int LocateList(LISTS Lists,char ListName[])
// 20��Lists�в���һ������ΪListName�����Ա��ɹ������߼���ţ����򷵻�0
{
    LISTS p = Lists;
    int i = 0;
    while(p->next){
    	p = p->next;
		i++;
    	if(strcmp(p->name, ListName) == 0)
    		return i;
	}
	return 0;
}


/*   21~24�ź����� addition.h��   */ 

