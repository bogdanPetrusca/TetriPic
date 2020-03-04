#include <stdlib.h>
#include <stdio.h>
#include "bmp_header.h"
#include "functii.h"

pozitii verificare(struct rgb **a,int pozX,int pozY)
{
	int i,j;
	pozitii x,str;
	x.a = malloc(sizeof(struct rgb));
	x.b = malloc(sizeof(struct rgb));
	x.c = malloc(sizeof(struct rgb));
	x.d = malloc(sizeof(struct rgb));
	x.e = malloc(sizeof(struct rgb));

	x.a = &a[pozX+10][pozY];
	x.b = &a[pozX+10][pozY+10];
	x.c = &a[pozX][pozY+10];
	x.d = &a[pozX-10][pozY+10];
	x.e = &a[pozX-10][pozY];
	str = x;
	return str;
	free(x.a); free(x.b); free(x.c); free(x.d); free(x.e); 

}

int main()
{
	struct bmp_fileheader *header1=malloc(sizeof(struct bmp_fileheader));
	struct bmp_infoheader *header2=malloc(sizeof(struct bmp_infoheader));
	FILE *file;
	file=fopen("bonus.bmp","rb");
	if(file == NULL)
	{
		printf("SEGFAULT\n");
		exit(1);
	}
	fread(header1,sizeof(struct bmp_fileheader),1,file);
	fread(header2,sizeof(struct bmp_infoheader),1,file);
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

	FILE *out;
	out = fopen("bonus.out","wt");
	int nr=0;
	for(i=0;i<header2->height-40;i=i+10)
		for(j=0;j<header2->width;j=j+10)
			if(a[i][j].blue != 0 || a[i][j].green != 0 || a[i][j].red != 0)
				nr++;
	fprintf(out, "%d\n",nr/4);
	pozitii vecini;
	
	for(i=0;i<header2->height-40;i=i+10)
		for(j=0;j<header2->width;j=j+10)
		{
			//pentru I
			vecini = verificare(a,i,j);
			if((a[i][j].blue == 255 && a[i][j].green == 0 && a[i][j].red == 0) && 
				(vecini.a->blue == 255 && vecini.a->green == 0 && vecini.a->red == 0))
			{	
				fprintf(out,"I %d %d\n",0,j/10 );
				add_color(a,black_pixel,i,i+40,j,j+10);
				
			}
			if((a[i][j].blue == 255 && a[i][j].green == 0 && a[i][j].red == 0) && 
				(vecini.c->blue == 255 && vecini.c->green == 0 && vecini.c->red == 0))
			{	
				fprintf(out,"I %d %d\n",90,j/10 );
				add_color(a,black_pixel,i,i+10,j,j+40);
			}
			//pentru O
			if((a[i][j].blue == 0 && a[i][j].green == 255 && a[i][j].red == 255) && 
				(vecini.c->blue == 0 && vecini.c->green == 255 && vecini.c->red == 255))
			{	
				fprintf(out,"O %d %d\n",0,j/10 );
				add_color(a,black_pixel,i,i+20,j,j+20);
			}
			//pentru L
			if((a[i][j].blue == 0 && a[i][j].green == 140 && a[i][j].red == 255) && 
				(vecini.a->blue == 0 && vecini.a->green == 140 && vecini.a->red == 255) &&
				(vecini.c->blue == 0 && vecini.c->green == 140 && vecini.c->red == 255))
			{	
				fprintf(out,"L %d %d\n",0,j/10 );
				add_color(a,black_pixel,i,i+30,j,j+10);
				add_color(a,black_pixel,i,i+10,j+10,j+20);

			}
			if((a[i][j].blue == 0 && a[i][j].green == 140 && a[i][j].red == 255) && 
				(vecini.a->blue == 0 && vecini.a->green == 140 && vecini.a->red == 255) &&
				(vecini.b->blue == 0 && vecini.b->green == 140 && vecini.b->red == 255))
			{	
				fprintf(out,"L %d %d\n",90,j/10 );
				add_color(a,black_pixel,i+10,i+20,j,j+30);
				add_color(a,black_pixel,i,i+10,j,j+10);

			}
			if((a[i][j].blue == 0 && a[i][j].green == 140 && a[i][j].red == 255) && 
				(vecini.c->blue == 0 && vecini.c->green == 140 && vecini.c->red == 255) &&
				(vecini.d->blue == 0 && vecini.d->green == 140 && vecini.d->red == 255))
			{	
				fprintf(out,"L %d %d\n",180,j/10 );
				add_color(a,black_pixel,i,i+10,j,j+10);
				add_color(a,black_pixel,i,i-20,j+10,j+20);

			}
			if((a[i][j].blue == 0 && a[i][j].green == 140 && a[i][j].red == 255) && 
				(vecini.c->blue == 0 && vecini.c->green == 140 && vecini.c->red == 255) &&
				(a[i][j+20].blue == 0 && a[i][j+20].green == 140 && a[i][j+20].red == 255))
			{	
				fprintf(out,"L %d %d\n",270,j/10 );
				add_color(a,black_pixel,i,i+10,j,j+30);
				add_color(a,black_pixel,i+10,i+20,j+20,j+30);

			}
			//pentru J
			if((a[i][j].blue == 255 && a[i][j].green == 0 && a[i][j].red == 255) && 
				(vecini.a->blue != 255 && vecini.a->green != 0 && vecini.a->red != 255) &&
				(vecini.c->blue == 255 && vecini.c->green == 0 && vecini.c->red == 255))
			{	
				fprintf(out,"J %d %d\n",0,j/10 );
				add_color(a,black_pixel,i,i+10,j,j+10);
				add_color(a,black_pixel,i,i+30,j+10,j+20);

			}
			if((a[i][j].blue == 255 && a[i][j].green == 0 && a[i][j].red == 255) && 
				(vecini.a->blue == 255 && vecini.a->green == 0 && vecini.a->red == 255) &&
				(vecini.c->blue == 255 && vecini.c->green == 0 && vecini.c->red == 255))
			{	
				fprintf(out,"J %d %d\n",90,j/10 );
				add_color(a,black_pixel,i,i+10,j,j+30);
				add_color(a,black_pixel,i+10,i+20,j,j+10);

			}
			if((a[i][j].blue == 255 && a[i][j].green == 0 && a[i][j].red == 255) && 
				(vecini.a->blue == 255 && vecini.a->green == 0 && vecini.a->red == 255) &&
				(a[i+20][j].blue == 255 && a[i+20][j].green == 0 && a[i+20][j].red == 255))
			{	
				fprintf(out,"J %d %d\n",180,j/10 );
				add_color(a,black_pixel,i,i+30,j,j+10);
				add_color(a,black_pixel,i+20,i+30,j+10,j+20);

			}
			if((a[i][j].blue == 255 && a[i][j].green == 0 && a[i][j].red == 255) && 
				(vecini.c->blue == 255 && vecini.c->green == 0 && vecini.c->red == 255) &&
				(a[i][j+20].blue == 255 && a[i][j+20].green == 0 && a[i][j+20].red == 255))
			{	
				fprintf(out,"J %d %d\n",270,j/10 );
				add_color(a,black_pixel,i,i+10,j,j+30);
				add_color(a,black_pixel,i-10,i,j+20,j+30);

			}
			//pentru S
			if((a[i][j].blue == 0 && a[i][j].green == 0 && a[i][j].red == 255) && 
				(vecini.b->blue == 0 && vecini.b->green == 0 && vecini.b->red == 255) &&
				(vecini.c->blue == 0 && vecini.c->green == 0 && vecini.c->red == 255))
			{	
				fprintf(out,"S %d %d\n",0,j/10 );
				add_color(a,black_pixel,i,i+10,j,j+20);
				add_color(a,black_pixel,i+10,i+20,j+10,j+30);

			}
			if((a[i][j].blue == 0 && a[i][j].green == 0 && a[i][j].red == 255) && 
				(vecini.a->blue == 0 && vecini.a->green == 0 && vecini.a->red == 255) &&
				(vecini.c->blue == 0 && vecini.c->green == 0 && vecini.c->red == 255))
			{	
				fprintf(out,"S %d %d\n",90,j/10 );
				add_color(a,black_pixel,i,i+20,j,j+10);
				add_color(a,black_pixel,i-10,i+10,j+10,j+20);

			}
			//pentru Z
			if(i>=10)
			{
				if((a[i][j].blue == 0 && a[i][j].green == 255 && a[i][j].red == 0) && 
					(a[i][j+10].blue == 0 && a[i][j+10].green == 255 && a[i][j+10].red == 0) &&
					(a[i-10][j+10].blue == 0 && a[i-10][j+10].green == 255 && a[i-10][j+10].red == 0))
				{	

					fprintf(out,"Z %d %d\n",0,j/10 );
					add_color(a,black_pixel,i,i+10,j,j+20);
					add_color(a,black_pixel,i-10,i,j+10,j+30);

				}
			}
			if((a[i][j].blue == 0 && a[i][j].green == 255 && a[i][j].red == 0) &&
				(vecini.a->blue == 0 && vecini.a->green == 255 && vecini.a->red == 0) &&
				(vecini.b->blue == 0 && vecini.b->green == 255 && vecini.b->red == 0))
			{	
				
				fprintf(out,"Z %d %d\n",90,j/10 );
				add_color(a,black_pixel,i,i+20,j,j+10);
				add_color(a,black_pixel,i+10,i+30,j+10,j+20);

			}
			//pentru T
			if((a[i][j].blue == 255 && a[i][j].green == 0 && a[i][j].red == 130) && 
				(vecini.c->blue == 255 && vecini.c->green == 0 && vecini.c->red == 130) &&
				(vecini.d->blue == 255 && vecini.d->green == 0 && vecini.d->red == 130) &&
				(a[i+20][j].blue == 255 && a[i+20][j].green == 0 && a[i+20][j].red == 130))
			{	
				fprintf(out,"T %d %d\n",0,j/10 );
				add_color(a,black_pixel,i,i+10,j,j+30);
				add_color(a,black_pixel,i-10,i,j+20,j+30);

			}
			if((a[i][j].blue == 255 && a[i][j].green == 0 && a[i][j].red == 130) && 
				(vecini.c->blue == 255 && vecini.c->green == 0 && vecini.c->red == 130) &&
				(a[i+10][j+10].blue == 255 && a[i+10][j+10].green == 0 && a[i+10][j+10].red == 130))
			{	
				fprintf(out,"T %d %d\n",90,j/10 );
				add_color(a,black_pixel,i,i+10,j,j+10);
				add_color(a,black_pixel,i-10,i+20,j+10,j+20);

			}
			if((a[i][j].blue == 255 && a[i][j].green == 0 && a[i][j].red == 130) && 
				(vecini.c->blue == 255 && vecini.c->green == 0 && vecini.c->red == 130) &&
				(vecini.b->blue == 255 && vecini.b->green == 0 && vecini.b->red == 130) &&
				(a[i+20][j].blue == 255 && a[i+20][j].green == 0 && a[i+20][j].red == 130))
			{	
				fprintf(out,"T %d %d\n",180,j/10 );
				add_color(a,black_pixel,i,i+10,j,j+30);
				add_color(a,black_pixel,i+10,i+20,j+10,j+20);

			}
			if((a[i][j].blue == 255 && a[i][j].green == 0 && a[i][j].red == 130) && 
				(vecini.a->blue == 255 && vecini.a->green == 0 && vecini.a->red == 130) &&
				(vecini.b->blue == 255 && vecini.b->green == 0 && vecini.b->red == 130))
			{	
				fprintf(out,"T %d %d\n",270,j/10 );
				add_color(a,black_pixel,i,i+30,j,j+10);
				add_color(a,black_pixel,i+10,i+20,j+10,j+20);

			}
		}



	FILE *f;
	int k;
	f = fopen("test.bmp","wb");
	fwrite(header1,sizeof(struct bmp_fileheader),1,f);
	fwrite(header2,sizeof(struct bmp_infoheader),1,f);
	for(i=0;i<header2->height;i++)
	{
		for(j=0;j<header2->width;j++)
		{
			fwrite(&a[i][j].blue,sizeof(char),1,f);
			fwrite(&a[i][j].green,sizeof(char),1,f);
			fwrite(&a[i][j].red,sizeof(char),1,f);
		}
		int zero=0;
		for(k=0;k<padding;k++)
			fwrite(&zero,sizeof(char),1,f);
	}
	fclose(f);
	free(header1);
	free(header2);
	for(i=0;i<header2->height;i++)
		free(a[i]);
	free(a);
}