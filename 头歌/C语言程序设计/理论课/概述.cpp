//��1�� �ۼ����
#include<stdio.h>
int main()
{
	/**********  Begin  **********/
    int n,a,ans=0;
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		ans+=i;
	}
	printf("%d\n",ans);
    
	/**********  Begin  **********/
    return 0;
}


//��2�� ��������ƽ��ֵ
#include<stdio.h>
int main()
{
	/**********  Begin  **********/
    int n=0,a,sum=0;
	double ave=0.0;
	for(int i=1;i<=10;i++){
		scanf("%d",&a);
		if(a>0){
			sum+=a;
			n++;
		}	
	}
	ave+=sum;
	if(n!=0)	ave=ave/n;
	printf("�ۼӺ�:%d\n",sum);
	printf("ƽ��ֵ:%.1lf\n",ave);
	/**********  End  **********/
    return 0;
} 
