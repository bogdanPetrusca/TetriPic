//PETRUSCA BOGDAN MIHAI
//313CB
#include "functii.h"
void task4()
{
	int N;
	FILE *in;
	in = fopen("cerinta4.in", "rt");
	if(in == NULL)
	{
		printf("SEGFAULT\n");
		exit(1);
	}
	fscanf (in, "%d", &N);
	printf("%d\n",N );
	//cream tabla
	struct bmp_fileheader *header1=malloc(sizeof(struct bmp_fileheader));
	struct bmp_infoheader *header2=malloc(sizeof(struct bmp_infoheader));

	FILE *file;
	file=fopen("cerinta4.bmp","rb");
	if(file == NULL)
	{
		printf("SEGFAULT\n");
		exit(1);
	}
	fread(header1,sizeof(struct bmp_fileheader),1,file);

	fread(header2,sizeof(struct bmp_infoheader),1,file);

	printf("%d %d\n",header2->height,header2->width );
	
	int val = 3 * header2->width;
	while(1)
	{
		if(val%4==0)
			break;
		else
			val++;
	}
	int padding = val - 3 * header2->width;
	header2->biSizeImage = (3 * header2->width + padding) * header2->height;
	header1->bfSize = header2->biSizeImage + header1->imageDataOffset;
	int i, j;
	struct rgb **a;
	a = malloc(header2->height * sizeof(struct rgb *));
	for(i=0;i<header2->height;i++)
		a[i]=malloc(header2->width * sizeof(struct rgb));
	for(i=0;i<header2->height;i++)
	{
		for(j=0;j<header2->width;j++)
			fread(&a[i][j],3,1,file);
		fseek(file,padding,SEEK_CUR);
	}
	fclose(file);	
	
	struct rgb *white_pixel=malloc(sizeof (struct rgb));
	white_pixel->blue = 255;
	white_pixel->green = 255;
	white_pixel->red = 255;

	struct rgb *black_pixel=malloc(sizeof (struct rgb));
	black_pixel->blue = 0;
	black_pixel->green = 0;
	black_pixel->red = 0;

	struct rgb *red_pixel=malloc(sizeof (struct rgb));
	red_pixel->blue = 0;
	red_pixel->green = 0;
	red_pixel->red = 255;

	struct rgb *blue_pixel=malloc(sizeof (struct rgb));
	blue_pixel->blue = 255;
	blue_pixel->green = 0;
	blue_pixel->red = 0;

	struct rgb *green_pixel=malloc(sizeof (struct rgb));
	green_pixel->blue = 0;
	green_pixel->green = 255;
	green_pixel->red = 0;

	struct rgb *yellow_pixel=malloc(sizeof (struct rgb));
	yellow_pixel->blue = 0;
	yellow_pixel->green = 255;
	yellow_pixel->red = 255;

	struct rgb *orange_pixel=malloc(sizeof (struct rgb));
	orange_pixel->blue = 0;
	orange_pixel->green = 140;
	orange_pixel->red = 255;

	struct rgb *pink_pixel=malloc(sizeof (struct rgb));
	pink_pixel->blue = 255;
	pink_pixel->green = 0;
	pink_pixel->red = 255;

	struct rgb *purple_pixel=malloc(sizeof (struct rgb));
	purple_pixel->blue = 255;
	purple_pixel->green = 0;
	purple_pixel->red = 130;


	struct piesa v[100];
	for (i = 0; i < N; i++) 
	{
		fscanf (in, "%s", &v[i].type);
		fscanf (in, "%d", &v[i].rotation);
		fscanf (in, "%d", &v[i].place);
	}
	fclose(in);
	
	for(i = 0; i < N; i++)
	{
		int X,Y,Z,T;
		int startX,startY= v[i].place*10;
		if(v[i].type == 'L')
		{
			if(v[i].rotation == 0)
			{
				coliziune(a,startY,header2->height-40,&X,&Y,&Z,&T);
				if(X>Y)
					startX=X;
				else
					startX=Y;
				add_color(a,orange_pixel,startX,startX+30,startY,startY+10);
				add_color(a,orange_pixel,startX,startX+10,startY+10,startY+20);
				if(stop(30,header2->height-40,startX) == 1)
					break;
			}
			if(v[i].rotation == 90)
			{
				coliziune(a,startY,header2->height-40,&X,&Y,&Z,&T);
				if(X <= 0 && Y - 10 == 0 && Z-10 <= 0)
					startX=0;
				else
					if(Y-10 > X)
						startX=Y-10;
					else
						if(Z-10 > X)
							startX=Z-10;
						else
							startX = X;
				
				add_color(a,orange_pixel,startX,startX+10,startY,startY+10);
				add_color(a,orange_pixel,startX+10,startX+20,startY,startY+30);
				if(stop(20,header2->height-40,startX) == 1)
					break;
			}
			if(v[i].rotation == 180)
			{
				coliziune(a,startY,header2->height-40,&X,&Y,&Z,&T);
					if(X-20 <= Y)
						startX=Y;
					else
						startX=X-20;
				
				add_color(a,orange_pixel,startX,startX+30,startY+10,startY+20);
				add_color(a,orange_pixel,startX+20,startX+30,startY,startY+10);
				if(stop(30,header2->height-40,startX) == 1)
					break;
			}
			if(v[i].rotation == 270)
			{
				coliziune(a,startY,header2->height-40,&X,&Y,&Z,&T);
				if(X > Y)
					startX = X;
				else
					startX = Y;
				if(startX < Z)
					startX = Z;

				add_color(a,orange_pixel,startX,startX+10,startY,startY+30);
				add_color(a,orange_pixel,startX+10,startX+20,startY+20,startY+30);	
				if(stop(20,header2->height-40,startX) == 1)		
					break;	
			}
		}
		if(v[i].type == 'J')
		{
			if(v[i].rotation == 0)
			{
				coliziune(a,startY,header2->height-40,&X,&Y,&Z,&T);
				if(X>Y)
					startX=X;
				else
					startX=Y;
				add_color(a,pink_pixel,startX,startX+30,startY+10,startY+20);
				add_color(a,pink_pixel,startX,startX+10,startY,startY+10);
				if(stop(30,header2->height-40,startX) == 1)
					break;
			}
			if(v[i].rotation == 90)
			{
				coliziune(a,startY,header2->height-40,&X,&Y,&Z,&T);
				if(X > Y)
					startX = X;
				else
					startX = Y;
				if(startX < Z)
					startX = Z;
				
				add_color(a,pink_pixel,startX,startX+10,startY,startY+30);
				add_color(a,pink_pixel,startX+10,startX+20,startY,startY+10);
				if(stop(20,header2->height-40,startX) == 1)
					break;
			}
			if(v[i].rotation == 180)
			{
				coliziune(a,startY,header2->height-40,&X,&Y,&Z,&T);
					if(Y-20 <= X)
						startX=X;
					else
						startX=Y-20;
				
				add_color(a,pink_pixel,startX,startX+30,startY,startY+10);
				add_color(a,pink_pixel,startX+20,startX+30,startY+10,startY+20);
				if(stop(30,header2->height-40,startX) == 1)
					break;

			}
			if(v[i].rotation == 270)
			{
				
				coliziune(a,startY,header2->height-40,&X,&Y,&Z,&T);
				if(X-10 <= 0 && Y - 10 == 0 && Z <= 0)
					startX=0;
				else
					if(X-10 > Z)
						startX=X-10;
					else
						if(Y-10 > Z)
							startX=Y-10;
						else
							startX = Z;
				printf("%d %d %d\n",X,Y,Z );
				printf("startX: %d\n",startX );
				add_color(a,pink_pixel,startX,startX+10,startY+20,startY+30);
				add_color(a,pink_pixel,startX+10,startX+20,startY,startY+30);
				if(stop(20,header2->height-40,startX) == 1)
					break;			

			}
		}
		if(v[i].type == 'O')
		{
			coliziune(a,startY,header2->height-40,&X,&Y,&Z,&T);
			if(Y>X)
				startX=Y;
			else
				startX=X;
			add_color(a,yellow_pixel,startX,startX+20,startY,startY+20);
			if(stop(20,header2->height-40,startX) == 1)
					break;	
		}
		if(v[i].type == 'I')
		{
			if(v[i].rotation == 0 || v[i].rotation == 180)
			{
				coliziune(a,startY,header2->height-40,&X,&Y,&Z,&T);
				startX = X;
				add_color(a,blue_pixel,startX,startX+40,startY,startY+10);
				if(stop(40,header2->height-40,startX) == 1)
					break;	
			}
			if(v[i].rotation == 90 || v[i].rotation == 270)
			{
				
				coliziune(a,startY,header2->height-40,&X,&Y,&Z,&T);
				

				if(X>=Y)
					startX=X;
				else
					startX=Y;
				if(Z>startX)
					startX=Z;
				if(T>startX)
					startX=T;
				add_color(a,blue_pixel,startX,startX+10,startY,startY+40);
				if(stop(10,header2->height-40,startX) == 1)
					break;	
			}
		}
		if(v[i].type == 'S')
		{
			if(v[i].rotation == 0 || v[i].rotation == 180)
			{
				coliziune(a,startY,header2->height-40,&X,&Y,&Z,&T);
				if(X>=Y)
					startX=X;
				else
					startX=Y;
				if(Z > startX)
				{

					startX = Z-10;
				}
				if(Z<=10)
					startX=X;
				
				add_color(a,red_pixel,startX,startX+10,startY,startY+20);
				add_color(a,red_pixel,startX+10,startX+20,startY+10,startY+30);
				if(stop(20,header2->height-40,startX) == 1)
					break;	
			}
			if(v[i].rotation == 90 || v[i].rotation == 270)
			{
				coliziune(a,startY,header2->height-40,&X,&Y,&Z,&T);
				printf("%d %d\n",X,Y );
				if(Y < X - 10)
						startX=X-10;
					else
						startX=Y;
				printf("startX:%d\n",startX );
				add_color(a,red_pixel,startX+10,startX+30,startY,startY+10);
				add_color(a,red_pixel,startX,startX+20,startY+10,startY+20);
				if(stop(30,header2->height-40,startX) == 1)
					break;	
			}
		}
		if(v[i].type == 'Z')
		{
			if(v[i].rotation == 0 || v[i].rotation == 180)
			{
				coliziune(a,startY,header2->height-40,&X,&Y,&Z,&T);
				if(Y==0 && Z == 0 && X-10 < 10 )
				{
					
					startX=Y;
				}
				if(X-10 > Y)
					startX=X-10;
				else
					startX=Y;
				if(startX<Z)
					startX=Z;
				
				add_color(a,green_pixel,startX,startX+10,startY+10,startY+30);
				add_color(a,green_pixel,startX+10,startX+20,startY,startY+20);
				if(stop(20,header2->height-40,startX) == 1)
					break;	
			}
			if(v[i].rotation == 90 || v[i].rotation == 270)
			{
				coliziune(a,startY,header2->height-40,&X,&Y,&Z,&T);
				if(Y-10 > X)
					startX=Y-10;
				else
					startX = X;
				
				add_color(a,green_pixel,startX,startX+20,startY,startY+10);
				add_color(a,green_pixel,startX+10,startX+30,startY+10,startY+20);
				if(stop(30,header2->height-40,startX) == 1)
					break;	
			}
		}
		if(v[i].type == 'T')
		{

			if(v[i].rotation == 0)
			{
				coliziune(a,startY,header2->height-40,&X,&Y,&Z,&T);
				if(X-10 <= 0 && Y == 0 && Z-10 <= 0)
					startX=0;
				else
					if(X-10 > Y)
						startX=X-10;
					else
						if(Z-10 > Y)
							startX=Z-10;
						else
							startX = Y;
				
				add_color(a,purple_pixel,startX,startX+10,startY+10,startY+20);
				add_color(a,purple_pixel,startX+10,startX+20,startY,startY+30);
				if(stop(20,header2->height-40,startX) == 1)
					break;	
			}
			if(v[i].rotation == 90)
			{
				coliziune(a,startY,header2->height-40,&X,&Y,&Z,&T);
				if(X-10 <=0 && Y == 0)
					startX=0;
				else
					if(X-10>Y)
						startX=X-10;
					else
						startX = Y;
				
				add_color(a,purple_pixel,startX+10,startX+20,startY,startY+10);
				add_color(a,purple_pixel,startX,startX+30,startY+10,startY+20);
				if(stop(30,header2->height-40,startX) == 1)
					break;	
			}
			if(v[i].rotation == 180)
			{
				coliziune(a,startY,header2->height-40,&X,&Y,&Z,&T);
				if(X>Y)
					startX=X;
				else
					startX=Y;
				if(Z>startX)
					startX=Z;
				
				add_color(a,purple_pixel,startX,startX+10,startY,startY+30);
				add_color(a,purple_pixel,startX+10,startX+20,startY+10,startY+20);
				if(stop(20,header2->height-40,startX) == 1)
					break;	
			}
			if(v[i].rotation == 270)
			{
				coliziune(a,startY,header2->height-40,&X,&Y,&Z,&T);
				if(X ==0 && Y-10 <= 0)
					startX=0;
				else
					if(Y-10>X)
						startX=Y-10;
					else
						startX = X;
				
				add_color(a,purple_pixel,startX+10,startX+20,startY+10,startY+20);
				add_color(a,purple_pixel,startX,startX+30,startY,startY+10);
				if(stop(30,header2->height-40,startX) == 1)
					break;	
			}
		}


	}
	//eliminare linii pline
	int row,column;
	int var=0,linii_pline=0,poz;
	for(row=0;row<header2->height-40;row++)
	{
		for(column=0;column<header2->width;column++)
			if(a[row][column].blue!=0 || a[row][column].green!=0 || a[row][column].red!=0)
				var++;
		if(var==header2->width)
		{
			poz=row+1;
			linii_pline++;
		}
		var=0;
	}

	for(row = poz-linii_pline;row<poz;row++)
		for(column=0;column<header2->width;column++)
			a[row][column]=a[row+linii_pline][column];

	for(row=poz;row<poz+linii_pline;row++)
		for(column=0;column<header2->width;column++)
			a[row][column]=*black_pixel;
	
	free(black_pixel);
	free(white_pixel);
	free(blue_pixel);
	free(pink_pixel);
	free(green_pixel);
	free(purple_pixel);
	free(red_pixel);
	free(yellow_pixel);
	free(orange_pixel);
	FILE *piesa;
	int k;
	piesa = fopen("task4.bmp","wb");
	fwrite(header1,sizeof(struct bmp_fileheader),1,piesa);
	fwrite(header2,sizeof(struct bmp_infoheader),1,piesa);
	for(i=0;i<header2->height;i++)
	{
		for(j=0;j<header2->width;j++)
		{
			fwrite(&a[i][j].blue,sizeof(char),1,piesa);
			fwrite(&a[i][j].green,sizeof(char),1,piesa);
			fwrite(&a[i][j].red,sizeof(char),1,piesa);
		}
		int zero=0;
		for(k=0;k<padding;k++)
			fwrite(&zero,sizeof(char),1,piesa);
	}
	fclose(piesa);
	
	for(i=0;i<header2->height;i++)
		free(a[i]);
	free(a);
}
