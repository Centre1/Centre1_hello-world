#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "def.h"
#include "addition.h"
#define maxleng 10005



TElemType *pp = NULL; 
void Create(BiTree &root)
{
	if(pp->key == -1) return;

	if (pp->key == 0){
		pp++;
		root = NULL;
	}
	else{
		
		root = (BiTree)malloc(sizeof(BiTNode));//���ɸ����
		root->data = *pp++;
		Create(root->lchild);//�ݹ鹹��������
		Create(root->rchild); // ;�ݹ鹹�������� �ݹ鹹��������
	}
}

status CreateBiTree(BiTree &T, TElemType definition[])
/*1���ݴ���֦�Ķ������ȸ���������definition����һ�ö������������ڵ�ָ�븳ֵ��T������OK��
�������ͬ�Ĺؼ��֣�����ERROR����������ͨ������������������ʵ�ֱ�������*/
{
    bool bw[10005];
	memset(bw, 0, sizeof(bw)); 
    for(int i=0; definition[i].key!=-1; i++){
    	KeyType key = definition[i].key;
    	if(bw[key] == 0) bw[key]=1;
    	else if(key) return ERROR;	//Key�ظ� 
	}
    
    pp = definition;
	Create(T);
	return OK;
}


status DestroyBiTree(BiTree &T)
//2���ٶ����� 
{
   if (T)
   {
        DestroyBiTree(T->lchild);
        DestroyBiTree(T->rchild);
        free(T);
        T=NULL;
   }
   return OK;
}

status ClearBiTree(BiTree &T)
//3�����������óɿգ���ɾ�����н�㣬�ͷŽ��ռ�
{
	DestroyBiTree(T->lchild);
    DestroyBiTree(T->rchild);
    T->data.key = 0;
    strcpy(T->data.others, "null");
    
	
	free(T); 
	T = NULL;
	return OK;
}

status BiTreeEmpty(BiTree T)
//4��ʼ�����Ƕ�����T���ڣ������������TΪ�ն������򷵻�TRUE�����򷵻�FALSE��
{
	if(T == NULL) return TRUE;
	else if(T->lchild==NULL && T->rchild==NULL && T->data.key==0)
		return TRUE;
	else return FALSE;
}

int BiTreeDepth(BiTree T)
//5�������T�����
{
	int ans = 0;
	if(T && BiTreeEmpty(T)==FALSE)
	{
		int Ldep = BiTreeDepth(T->lchild);
		int Rdep = BiTreeDepth(T->rchild);
		if (Ldep > Rdep) ans = Ldep+1;
		else ans = Rdep+1; 
	}
	return ans;
}


BiTNode* LocateNode(BiTree T,KeyType e)
//6���ҽ��(inorder)
{
	BiTree t = T; 
	BiTree st[maxleng];
	int top = 0;
	do{
		while(t){	//������ڵ� 
			if(top == maxleng) exit(OVERFLOW);
			st[top++] = t;
			t = t->lchild;
		}
		if(top){
			t = st[--top];	//��ջ 
			if(t->data.key == e)
				return t;
			t = t->rchild;
		}
	}while(top || t);
	return NULL;
}

status Assign(BiTree &T, KeyType e, TElemType value)
//7ʵ�ֽ�㸳ֵ����������ͨ������������������ʵ�ֱ�������
{
	BiTree target = LocateNode(T, e);
	if(target){
		BiTree p = LocateNode(T, value.key);
		if(!p || p==target){	//��ֹKey�ظ� 
			target->data = value;
			return OK;
		} 
	}
	return ERROR;
}


BiTNode* GetParent(BiTree T, KeyType e)
//ʵ�ֻ��˫�׽��
{
    if(T->data.key == e) return NULL;	//���ڵ���˫�� 
    
	BiTree t = T; 
	BiTree st[maxleng];
	int top = 0;
	do{		//���� 
		while(t){
			if(top == maxleng) exit(OVERFLOW);
			st[top++] = t;
			t = t->lchild;
		}
		if(top){
			t = st[--top];
			if(t->lchild && t->lchild->data.key==e)	//t��Ŀ��ڵ��˫�� 
				return t;
			else if(t->rchild && t->rchild->data.key==e) 
				return t;
			t = t->rchild;
		}
	}while(top || t);
	
	return NULL;
}


BiTNode* GetSibling(BiTree T, KeyType e)
//8ʵ�ֻ���ֵܽ��
{
    BiTree parent = GetParent(T, e);
	if(parent){
		if(parent->lchild && parent->lchild->data.key==e)	//t��Ŀ��ڵ��˫�� 
			return parent->rchild;
		else if(parent->rchild && parent->rchild->data.key==e) 
			return parent->lchild;
	} 
	return NULL;
}

status InsertNode(BiTree &T,KeyType e,int LR,TElemType c)
//9�����㡣��������ͨ������������������ʵ�ֱ�������
{
	int flag = ERROR;
	BiTree p = (BiTNode *)malloc(sizeof(BiTNode));	//����������ڵ� 
	p->data = c;
	p->lchild = p->rchild = NULL;
	
	if(LR == -1){	//��Ϊ���ڵ���� 
		p->rchild = T;
		T = p;
		flag = OK; 
	}
	else{
		if(LocateNode(T, c.key) == NULL){	//��ֹKey�ظ� 
			BiTree target = LocateNode(T, e);
			if(target){	//���Բ��� 
				if(LR == 0){
					p->rchild = target->lchild;
					target->lchild = p;
				}
				else if(LR == 1){
					p->rchild = target->rchild; 
					target->rchild = p;
				}
				flag = OK;
			}
		}
	}
	if(flag == ERROR) free(p);	//����ʧ��,�ͷſռ� 
	return flag;
}


BiTree NewChild(BiTree target)
//�������������ɾ���Ľڵ�ĺ��ӽڵ� 
{
	if(target->lchild){
		if(target->rchild){
			BiTree t = target->lchild;
			while(t->rchild){	//�����ҽڵ� 
				t = t->rchild;
			}
			t->rchild = target->rchild;
		}
		return target->lchild;
	} 
	else return target->rchild;
}

status DeleteNode(BiTree &T,KeyType e)
//10ɾ����㡣��������ͨ������������������ʵ�ֱ�������(�ǵݹ�)
{
	status flag = ERROR;
	BiTree target=NULL, parent=NULL; 
	if(T->data.key == e){	//ɾ�����ڵ� 
		target = T;
		T = NewChild(target);
		free(target);
		flag = OK;
	}
	else if(parent = GetParent(T,e)){
		if(parent->lchild && parent->lchild->data.key==e){	//ɾ������ 
			target = parent->lchild; 
			parent->lchild = NewChild(target);
		}
		else if(parent->rchild && parent->rchild->data.key==e){	//ɾ���Һ��� 
			target = parent->rchild;
			parent->rchild = NewChild(target);			
		}
		free(target); 
		flag = OK;
	}
	return flag;
}


void visit(BiTree T)
{
    printf(" %d,%s",T->data.key,T->data.others);
}

status PreOrderTraverse(BiTree T,void (*visit)(BiTree))
//11�������������T
{
    // �������ﲹ����룬��ɱ�������
    /********** Begin *********/
    if(T){
		visit(T);
   		PreOrderTraverse(T->lchild, visit);
		PreOrderTraverse(T->rchild, visit);
	}
    return OK;
    /********** End **********/
}

status InOrderTraverse(BiTree T,void (*visit)(BiTree))
//12�������������T
{
	BiTree t = T; 
	BiTree st[maxleng];
	int top = 0;
	do{
		while(t){	//������ڵ� 
			if(top == maxleng) exit(OVERFLOW);
			st[top++] = t;
			t = t->lchild;
		}
		if(top){
			t = st[--top];	//��ջ 
			visit(t);
			t = t->rchild;
		}
	}while(top || t);
	return OK;
}

status PostOrderTraverse(BiTree T,void (*visit)(BiTree))
//13�������������T
{
    // �������ﲹ����룬��ɱ�������
    /********** Begin *********/
    if(T){
    	PostOrderTraverse(T->lchild, visit); 
		PostOrderTraverse(T->rchild, visit); 
		visit(T);
	}
	return OK;
    /********** End **********/
}


status LevelOrderTraverse(BiTree T,void (*visit)(BiTree))
//14�������������T
{
	BiTree Array[maxleng];
	int head=0, tail=0;
	
	Array[tail++] = T;
	while(tail > head){
		BiTree t = NULL; 
		if(t = Array[head]){
			visit(t);
			Array[tail++] = t->lchild;
			Array[tail++] = t->rchild;
		}
		head++;
	}
	return OK;
}

int MaxPathSum(BiTree T)
//15���·����, ��ʼ�����Ƕ�����T���ڣ���������Ƿ��ظ��ڵ㵽Ҷ�ӽ������·���ͣ�
{
	int ans = 0;
	if(T){
		ans = T->data.key;
		int L = MaxPathSum(T->lchild);
		int R = MaxPathSum(T->rchild);
		
		if(L>R) ans += L;
		else ans += R;
	}
	return ans;
}


void GetWay(BiTree t, KeyType e, BiTree st[])
//�������Ѱ��·����·������st������ 
{
	BiTree pre = NULL;
	int top = 0; 
	bool flag = 1;
	
	do{
		while(t){
			st[top++] = t;
			if(t->data.key == e){
				st[top] = NULL;
				return ;
			} 
			t = t->lchild;
		}
		pre = NULL;	flag = 1;
		while(flag && top){
			t = st[top-1];
			if(t->rchild == pre){
				//print
				top--;
				pre = t;
			}
			else{
				t = t->rchild;
				flag = 0;
			}
		}
	}while(top);
	
}

BiTNode* LowestCommonAncestor(BiTree T, KeyType e1, KeyType e2)
//16�����������, ��ʼ�����Ƕ�����T���ڣ���������Ǹö�������e1�ڵ��e2�ڵ������������ȣ�
{
	BiTree st1[maxleng], st2[maxleng];
	GetWay(T, e1, st1);
	GetWay(T, e2, st2);
	
	int i = 0, j = 0;
	while(st1[i] && st2[j] && st1[i]==st2[j]){
		i++;
		j++;
	}
	
	return st1[i-1];
}


status InvertTree(BiTree &T)
//17��ת������, ��ʼ���������Ա�L�Ѵ��ڣ���������ǽ�T��ת��ʹ�����нڵ�����ҽڵ㻥����
{
	if(T){
		BiTree tmp = T->lchild;
		T->lchild = T->rchild;
		T->rchild = tmp;
		InvertTree(T->lchild);
		InvertTree(T->rchild);
	}
	return OK;
}

status SaveBiTree(BiTree T, char FileName[])
//18���������Ľ������д�뵽�ļ�FileName��
{
    FILE* fp;
	if ((fp=fopen(FileName,"wb"))==NULL){
		printf("File open error!\n ");
		return ERROR;
	}
	
	BiTree st[maxleng];
	int top = 0;
	TElemType null0 = {0, "null"};
	st[top++] = T;
	while(top){
		BiTree p = st[--top];
		if(p) {
			fwrite(&p->data, sizeof(TElemType), 1, fp);
			st[top++] = p->rchild;
			st[top++] = p->lchild; 
		}
		else fwrite(&null0, sizeof(TElemType), 1, fp);	
	}
	TElemType end = {-1, "null"};
	fwrite(&end, sizeof(TElemType), 1, fp);
	fclose(fp);
	return OK;
}
status LoadBiTree(BiTree &T,  char FileName[])
//19�����ļ�FileName�Ľ�����ݣ�����������
{
	TElemType definition[maxleng];
	FILE* fp;
	if ((fp=fopen(FileName,"rb"))==NULL){
		printf("File open error!\n ");
		return ERROR;
	}
	TElemType t;
	int cnt = 0;
	do{
		fread(&t, sizeof(TElemType), 1, fp);
		definition[cnt++] = t; 
	}while(t.key != -1);
	
	fclose(fp);
	return CreateBiTree(T, definition);
}



status SwitchTree(TREES Trees, BiTree &T, char TreeName[])
// 20����ǰ���л���name 
{
	status flag = ERROR;
	for(int i=0; flag==ERROR && i<Trees.length; i++){
		if(strcmp(Trees.elem[i].name, TreeName) == 0){
			flag = OK;
			T = Trees.elem[i].T;
		}
	}
	return flag;
}


status AddBiTree(TREES &Trees,char TreeName[])
// 21ֻ��Ҫ��Trees������һ������ΪTreeName����
{
    status flag = ERROR;
    int i = Trees.length;
    
    BiTree t = (BiTree)malloc(sizeof(BiTNode));
	if(t){
		t->lchild = t->rchild = NULL;
		t->data.key = 0;
		flag = OK; 
	}
	
    if(flag == OK){
    	Trees.elem[i].T = t;
    	strcpy(Trees.elem[i].name, TreeName);
   		Trees.length++;
	}
    return flag;
}

status RemoveBiTree(TREES &Trees,char TreeName[])
// 22Lists��ɾ��һ������ΪTreeName�����Ա�
{
    status flag = ERROR;

    for(int i=0; flag==ERROR && i<Trees.length; i++)
    {
        if(strcmp(Trees.elem[i].name,TreeName) == 0)
        {
            for(; i<Trees.length-1; i++)
                Trees.elem[i] = Trees.elem[i+1];
            // flag = DestroyList(Trees.elem[i].L);
            flag = OK;
            Trees.length--;
        }
    }
    return flag;
}


status LocateBiTree(TREES Trees, char TreeName[])
// 23����TreeName���λ�� 
{
	status flag = INFEASIBLE;
	for(int i=0; flag==INFEASIBLE && i<Trees.length; i++){
		if(strcmp(Trees.elem[i].name, TreeName) == 0){
			flag = i+1;
			break;
		}
	}
	return flag;
}


status Upload(TREES &Trees, BiTree T, char TreeName[])
// 24�л���ǰ��ΪTreeName 
{
	status flag = ERROR;
    int i = LocateBiTree(Trees, TreeName)-1;
    if(i == INFEASIBLE-1){
    	i = Trees.length++;
    	strcpy(Trees.elem[i].name, TreeName);
		flag = ERROR; 
	}
	else flag = OK; 
    
	Trees.elem[i].T = T;
//	strcpy(Trees.elem[i].name, TreeName);
//	Trees.length++;
    return flag;
}

	




