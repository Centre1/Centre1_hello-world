#include <stdio.h>
#include "def.h"


void menu(void)
{
	printf("\n\n");
	printf("      Menu for Linear Table On Sequence Structure \n");
	printf("-------------------------------------------------\n");
	printf("	1. CreateBiTree \t13. PostOrderTraverse\n");
	printf("	2. DestroyBiTree\t14. LevelOrderTraverse\n");
	printf("	3. ClearBiTree	\t15. MaxPathSum \n");
	printf("	4. BiTreeEmpty	\t16. LowestCommonAncestor\n");
	printf("	5. BiTreeDepth	\t17. InvertTree\n");
	printf("	6. LocateNode   \t18. SaveBiTree\n");
	printf("	7. Assign	\t19. LoadBiTree\n");
	printf("	8. GetSibling	\t20. SwitchTree\n");
	printf("	9. InsertNode	\t21. AddBiTree\n");
	printf("	10.DeleteNode	\t22. RemoveBiTree\n");
	printf("	11.PreOrderTraverse\t23. LocateBiTree\n");
	printf("	12.InOrderTraverse\t24. Upload\n");
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
			printf("����ʧ�ܣ���key�ظ���Ŀ�겻���ڵȣ�");
			break; 
		case INFEASIBLE:
			printf("�������ڣ�");
			break;
		default:
			printf("δ֪����");
			break;
	}
}

void print(BiTNode *tmp){
	printf("key = %d    others = %s", tmp->data.key, tmp->data.others);
}


void InitTrees(TREES &Trees)
{
	Trees.length = 0;
	Trees.treesize = TREES_INIT_SIZE;
	
}

