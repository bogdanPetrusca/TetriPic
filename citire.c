#include <stdio.h>
#include <stdlib.h>
struct piesa
{
	char tip;
	int rotatie;
	int start_Y;

};
int main()
{
	int N,H,L,i;
	char a;
	int b,c;
	FILE *in;
	in=fopen("cerinta3.in","rt");
	fscanf(in,"%d",&N);
	fscanf(in,"%d",&H);
	fscanf(in,"%d",&L);
	struct piesa v[100];
	printf("%d %d %d\n",N,H,L );
	for(i=0;i<N;i++)
	{
		fscanf(in,"%s",&a);
		fscanf(in,"%d",&b);
		fscanf(in,"%d",&c);
		printf("%c %d %d\n",a,b,c );
	}
	fclose(in);
}