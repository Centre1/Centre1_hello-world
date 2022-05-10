#include <string.h>
#include "def.h"

status InitList(SqList& L)
// 1���Ա�L�����ڣ�����һ���յ����Ա�����OK�����򷵻�INFEASIBLE��
{
    if(L.elem){
        return INFEASIBLE;  //L�Ѵ���
    }
    else{   //����
        L.elem = (ElemType*)malloc(sizeof(ElemType)*LIST_INIT_SIZE);
        L.listsize = LIST_INIT_SIZE;
        L.length = 0;
    }

    return OK;
}


status DestroyList(SqList& L)
// 2������Ա�L���ڣ��������Ա�L���ͷ�����Ԫ�صĿռ䣬����OK�����򷵻�INFEASIBLE��
{
	if(L.elem == NULL)	return INFEASIBLE;
	
	memset(L.elem, 0, sizeof(L.elem));
    L.listsize = 0;
    L.length = 0;
    free(L.elem);
    L.elem = NULL;
    return OK;
}


status ClearList(SqList& L)
// 3������Ա�L���ڣ�ɾ�����Ա�L�е�����Ԫ�أ�����OK�����򷵻�INFEASIBLE��
{
    if(L.elem == NULL)
        return INFEASIBLE;
    
    memset(L.elem, 0, sizeof(L.elem));
    L.length = 0;   //��������
    return OK;
}


status ListEmpty(SqList L)
// 4������Ա�L���ڣ��ж����Ա�L�Ƿ�Ϊ�գ��վͷ���TRUE�����򷵻�FALSE��������Ա�L�����ڣ�����INFEASIBLE��
{
    status flag = TRUE; //��ʼ��Ϊ���

    if(L.elem == NULL){
        flag = INFEASIBLE;  //L������
    }
    else if(L.length){   //L��Ϊ��
        flag = FALSE;
    }
    else flag = TRUE; 

    return flag;
}


status ListLength(SqList L)
// 5������Ա�L���ڣ��������Ա�L�ĳ��ȣ����򷵻�INFEASIBLE��
{
    if(L.elem == NULL){
        return INFEASIBLE;  //���Ա�L������
    } 
    else{   //���س���
        return L.length;
    }
}

status GetElem(SqList L,int i,ElemType &e)
// 6������Ա�L���ڣ���ȡ���Ա�L�ĵ�i��Ԫ�أ�������e�У�����OK�����i���Ϸ�������ERROR��������Ա�L�����ڣ�����INFEASIBLE��
{
    status flag = OK;   //��ʼ��Ϊ��ȡ��i��Ԫ�سɹ�

    if(L.elem == NULL){
        flag = INFEASIBLE;
    }
    else{
        if(i<1 || i>L.length){
            flag = ERROR;   //i���Ϸ�
        }
        else{
            e = L.elem[i-1];    //����
        }
    }

    return flag;
}


int LocateElem(SqList L, ElemType e)
// 7������Ա�L���ڣ�����Ԫ��e�����Ա�L�е�λ����Ų����ظ���ţ����e�����ڣ�����0�������Ա�L������ʱ������INFEASIBLE����-1����
{
    int flag = ERROR;   //��ʼ��ΪL���ڵ�δ�ҵ�e

    if(L.elem == NULL) //���Ա�L������
        flag = INFEASIBLE;
    else{
        int i;
        for(i=0; i<L.length && flag==ERROR; i++)
        {   //�ҵ���ͣ
            if(L.elem[i] == e){
                flag = i+1; //λ�����
            }
        }
    }

    return flag;
    /********** End **********/
}

status PriorElem(SqList L,ElemType e,ElemType &pre)
// 8������Ա�L���ڣ���ȡ���Ա�L��Ԫ��e��ǰ����������pre�У�����OK�����û��ǰ��������ERROR��������Ա�L�����ڣ�����INFEASIBLE��
{
    status flag = ERROR;    //��ʼ��ΪL���ڵ�δ�ҵ�e

    if(L.elem == NULL){     //L������
        flag = INFEASIBLE;
    }
    else{
        if(L.elem[0] == e){ //�ж�����ǰ��
            flag = ERROR;
        }
        else{
            for(int i=1; i<L.length && flag==ERROR; i++)
            {   //һ���ҵ�eֹͣ����
                if(L.elem[i] == e){
                    flag = OK;
                    pre = L.elem[i-1];  //ǰ��������pre��
                }
            }
        }
    }

    return flag;
}


status NextElem(SqList L,ElemType e,ElemType &next)
// 9������Ա�L���ڣ���ȡ���Ա�LԪ��e�ĺ�̣�������next�У�����OK�����û�к�̣�����ERROR��������Ա�L�����ڣ�����INFEASIBLE��
{
    status flag = ERROR;    //Ĭ��L����

    if(L.elem == NULL){
        flag = INFEASIBLE;  //L������
    }
    else{
        if(L.elem[L.length-1] == e){    //��̲�����
            flag = ERROR;
        }
        else{
            int i;
            for(i=0; i<L.length-1 && flag==ERROR; i++){   //�ҵ�Ϊֹ
                if(L.elem[i] == e){
                    flag = OK;
                    next = L.elem[i+1];
                }
            }
        }
    }

    return flag;
}


status ListInsert(SqList &L, int i, ElemType e)
// 10������Ա�L���ڣ���Ԫ��e���뵽���Ա�L�ĵ�i��Ԫ��֮ǰ������OK��������λ�ò���ȷʱ������ERROR��������Ա�L�����ڣ�����INFEASIBLE��
{
    status flag;

    if(L.elem == NULL){
        flag = INFEASIBLE;  //L������
    }
    else{
        if(i<0 || i>L.length+1){    //�Ƿ�����
            flag = ERROR;
        }
        else{
            if(L.length >= L.listsize){ //�ռ䲻�㣬����
                L.elem = (ElemType*)realloc(L.elem ,sizeof(ElemType)*(L.listsize + LISTINCREMENT));
                L.listsize += LISTINCREMENT;
            }
			
			if(i == 0)	i = L.length+1; 
            for(int j=L.length; j>i-1; j--){  //��i�����Ԫ�غ���1λ
                L.elem[j] = L.elem[j-1];
            }
            L.elem[i-1] = e;    //����
            L.length++;
            flag = OK;
        }
    }
    return flag;
}



status ListDelete(SqList &L,int i,ElemType &e)
// 11������Ա�L���ڣ�ɾ�����Ա�L�ĵ�i��Ԫ�أ���������e�У�����OK����ɾ��λ�ò���ȷʱ������ERROR��������Ա�L�����ڣ�����INFEASIBLE��
{
    if(L.elem == NULL){
        return INFEASIBLE;  //L������
    }

    status flag;
    if(i<1 || i>L.length){  //�Ƿ�ɾ��
        flag = ERROR;
    }
    else{
        e = L.elem[i-1];
        int j;
        for(j=i-1; j<L.length-1; j++){
            L.elem[j] = L.elem[j+1];
        }
        L.length--;
        flag = OK;
    }

    return flag;
}


status ListTraverse(SqList L)
// 12������Ա�L���ڣ�������ʾ���Ա��е�Ԫ�أ�ÿ��Ԫ�ؼ��һ�񣬷���OK��������Ա�L�����ڣ�����INFEASIBLE��
{
    if(L.elem == NULL)
        return INFEASIBLE;
	if(L.length == 0)
		return ERROR;
		
	printf("\n----------- all elements -----------------------\n");
	for(int i=0; i<L.length; i++)
		printf("%d ",L.elem[i]);
	printf("\n------------------ end ------------------------\n");
    return OK;
}

int MaxSubArray(SqList L)
// 13��ʼ���������Ա�L�Ѵ����ҷǿգ��ҳ�һ���������͵����������飬���ظ����� 
{
	int sum_max = 0;
	int *T = (int*)malloc(sizeof(int)*L.length);
	T[0] = L.elem[0];
	for(int i=1; i<L.length; i++)	//����ǰ׺�� 
		T[i] = T[i-1] + L.elem[i];
			
	for(int i=0; i<L.length; i++)	//������������������ 
	{
		if(T[i] > sum_max)	sum_max = T[i];
		for(int j=i+1; j<L.length; j++)
			if(T[j]-T[i] > sum_max)	
				sum_max = (T[j]-T[i]);
	}
	
	return sum_max; 
}

int SubArrayNum(SqList L, int k)
//14��ʼ���������Ա�L�Ѵ����ҷǿ�, ��������Ǹ������к�Ϊk������������ĸ���
{
	int cnt = 0;
	int *T = (int*)malloc(sizeof(int)*L.length);
	T[0] = L.elem[0];
	for(int i=1; i<L.length; i++)	//����ǰ׺�� 
		T[i] = T[i-1] + L.elem[i];
			
	for(int i=0; i<L.length; i++)	//������������������ 
	{
		if(T[i] == k)	cnt++;
		for(int j=i+1; j<L.length; j++)
			if(T[j]-T[i] == k)	
				cnt++;
	}
		
	return cnt; 
}

status sortList(SqList &L)
//15��ʼ���������Ա�L�Ѵ��ڣ���������ǽ�L��С��������
{
	if(L.elem == NULL) return INFEASIBLE;
	
	int flag = 1;
	for(int i=0; flag && i<L.length-1; i++){
		flag = 0;
		for(int j=0; j+1<(L.length-i); j++)
			if(L.elem[j] > L.elem[j+1]){
				int t = L.elem[j];
				L.elem[j] = L.elem[j+1];
				L.elem[j+1] = t;
				flag = 1;
			}
	}
	return OK;
}

status  SaveList(SqList L, char FileName[])
// 16������Ա�L���ڣ������Ա�L�ĵ�Ԫ��д��FileName�ļ��У�����OK�����򷵻�INFEASIBLE��
{
    if(L.elem == NULL)	return INFEASIBLE;
    FILE *fp;
    if((fp=fopen(FileName, "wb")) == NULL)
    	return ERROR;

	fwrite(&L.listsize, sizeof(int), 1, fp);	//д�������С 
	fwrite(&L.length, sizeof(int), 1, fp);	//д�볤�� 
    for(int i=0; i<L.length; i++)
        fwrite(L.elem+i, sizeof(ElemType), 1, fp);
    fclose(fp);
    return OK;
}

status  LoadList(SqList &L,char FileName[])
// 17������Ա�L�����ڣ���FileName�ļ��е����ݶ��뵽���Ա�L�У�����OK�����򷵻�INFEASIBLE��
{
	if(L.length > 0)
        return INFEASIBLE;
        
    FILE *fp;
    if((fp=fopen(FileName, "rb")) == NULL)
    	return ERROR;

	fread(&L.listsize, sizeof(int), 1, fp);	//���������С 
	fread(&L.length, sizeof(int), 1, fp);	//���볤�� 
    if(L.elem == NULL)
		L.elem = (ElemType*)malloc(sizeof(ElemType)*L.listsize);
    for(int i=0; i<L.length; i++)
        fread(L.elem+i, sizeof(ElemType), 1, fp);
    fclose(fp);
    return OK;
}

status AddList(LISTS &Lists,char ListName[])
// 18ֻ��Ҫ��Lists������һ������ΪListName�Ŀ����Ա����Ա������ֺ�̨���Գ�����롣
{
    status flag = OK;
    int i = Lists.length;
    const int cntup = 10;
    int cnt = 0;
    while(((flag = InitList(Lists.elem[i].L)) != OK ) && cnt<cntup){
        Lists.elem[i].L.elem = NULL;
        cnt++;
    }
    if(flag == OK){
    	strcpy(Lists.elem[i].name, ListName);
   		Lists.length++;
	}
    return flag;
}

status RemoveList(LISTS &Lists,char ListName[])
// 19Lists��ɾ��һ������ΪListName�����Ա�
{
    status flag = ERROR;

    for(int i=0; flag==ERROR && i<Lists.length; i++)
    {
        if(strcmp(Lists.elem[i].name,ListName) == 0)
        {
            for(; i<Lists.length-1; i++)
                Lists.elem[i] = Lists.elem[i+1];
            // flag = DestroyList(Lists.elem[i].L);
            flag = OK;
            Lists.length--;
        }
    }
    return flag;
}

status SwitchList(LISTS Lists, SqList &L, char ListName[])
// 20����ǰ���Ա��л���ListName 
{
	status flag = ERROR;
	for(int i=0; flag==ERROR && i<Lists.length; i++){
		if(strcmp(Lists.elem[i].name, ListName) == 0){
			flag = OK;
			L = Lists.elem[i].L;
		}
	}
	return flag;
}

status LocateList(LISTS Lists, char ListName[])
// 21����ListName���λ�� 
{
	status flag = INFEASIBLE;
	for(int i=0; flag==INFEASIBLE && i<Lists.length; i++){
		if(strcmp(Lists.elem[i].name, ListName) == 0){
			flag = i+1;
			break;
		}
	}
	return flag;
}

status ListsTraverse(LISTS Lists)
// 22����Lists, bw=1ʱ����������� 
{
	if(Lists.length == 0)
		return ERROR;
	
	for(int i=0; i<Lists.length; i++){
		printf("%d\t%s", i+1, Lists.elem[i].name);
		printf("\n");
	}
	return OK;
}

status GetName(LISTS Lists, SqList L)
// 23��ǰ������� 
{
	status flag = ERROR;
	for(int i=0; flag==ERROR && i<Lists.length; i++){
		if(Lists.elem[i].L.elem == L.elem){
			flag = OK;
			printf("%s\n", Lists.elem[i].name);
		}
	}
	return flag;
}

status UploadList(LISTS &Lists, SqList L, char ListName[])
// 24�ѵ�ǰ����ӵ������
{
//	if(L.elem == NULL)
//		return INFEASIBLE; 
//	if(Lists.length+1 > Lists.listsize)
//		return ERROR;
//		
//	status flag = ERROR;
//	for(int i=0; flag==ERROR && i<Lists.length; i++){
//		if(Lists.elem[i].L.elem == L.elem){
//			return ERROR;
//		}
//	}
//	Lists.elem[Lists.length].L = L;
//	strcpy(Lists.elem[Lists.length].name, ListName);
//	Lists.length++;
//	return OK; 

	status flag = ERROR;
	for(int i=0; flag==ERROR && i<Lists.length; i++){
		if(Lists.elem[i].L.elem == L.elem){
			Lists.elem[i].L = L;
			flag = OK;
		}
	}
	
	if(flag == ERROR){
		Lists.elem[Lists.length].L = L;
		strcpy(Lists.elem[Lists.length].name, ListName);
		Lists.length++;
		flag = OK;
	}
	
	return flag; 
}


