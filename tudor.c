#include <stdio.h>
int sum(int a[10][10][10],int end_x,int end_y,int end_z)
{
	int i,j,k,s=0;
	for(i=0;i<end_x;i++)
		for(j=0;j<end_y;j++)
			for(k=0;k<end_z;k++)
				s+=a[i][j][k];
	return s;
}
int main()
{
	int dim_x,dim_y,dim_z;
	int i,j,k;
	scanf("%d %d %d",&dim_x,&dim_y,&dim_z);
	int cub[10][10][10];
	for(i=0;i<dim_x;i++)
		for(j=0;j<dim_y;j++)
			for(k=0;k<dim_z;k++)
				scanf("%d",&cub[i][j][k]);
	printf("%d\n",sum(cub,dim_x,dim_y,dim_z) );
}