//PETRUSCA BOGDAN MIHAI
//313CB
void piesa_I()
{
	//dau valori celor 2 structuri
	struct bmp_fileheader *header1=malloc(sizeof(struct bmp_fileheader));
	struct bmp_infoheader *header2=malloc(sizeof(struct bmp_infoheader));

	header1->fileMarker1 = 'B';
	header1->fileMarker2 = 'M';
	header1->unused1 = 0;
	header1->unused2 = 0;
	header1->imageDataOffset = 54;

	header2->biSize = 40;
	header2->width = 30;
	header2->height = 60;
	header2->planes = 1;
	header2->bitPix = 24;
	header2->biCompression = 0;
	header2->biXPelsPerMeter = 0;
	header2->biYPelsPerMeter = 0;
	header2->biClrUsed = 0;
	header2->biClrImportant = 0;

	//calculez paddingul
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

	//dau valori celor  pixeli de care am nevoie
	struct rgb *white_pixel=malloc(sizeof (struct rgb));
	white_pixel->blue = 255;
	white_pixel->green = 255;
	white_pixel->red = 255;

	struct rgb *blue_pixel=malloc(sizeof (struct rgb));
	blue_pixel->blue = 255;
	blue_pixel->green = 0;
	blue_pixel->red = 0;

	//formez matricea de pixeli
	int i,j;
	struct rgb **a;
	a=malloc(header2->height * sizeof(struct rgb *));
	for(i=0;i<header2->height;i++)
		a[i]=malloc(header2->width * sizeof(struct rgb));

	for(i=0;i<header2->height;i++)
		for(j=0;j<header2->width;j++)
			a[i][j]=*white_pixel;
	for(i=10;i<50;i++)
		for(j=10;j<20;j++)
			a[i][j]=*blue_pixel;
	//adaug totul in fisier
	FILE *piesa;
	int k;
	piesa = fopen("piesa_I.bmp","wb");
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


	//rotatie 90 de grade
	struct rotatie grade_90;
	grade_90.a = 0;
	grade_90.b = 1;
	grade_90.c = -1;
	grade_90.d =0;
	//a_90 este matricea de pixeli rotita
	struct rgb **a_90;
	a_90 = malloc(30 * sizeof(struct rgb *));
	for(i=0;i<30;i++)
		a_90[i] = malloc(60 * sizeof(struct rgb ));
	//pe fiecare element al matricei matrice_90 se vor afla
	//noile coordonate obtinute prin inmultirea lui i si j
	//cu matricea de rotatie
	struct coordonate matrice_90[100][100];

	for(i=0;i<header2->height;i++)
		for(j=0;j<header2->width;j++)
		{
			int val1,val2;
			val1 = grade_90.a * i + grade_90.b * j;
			val2 = grade_90.c * i + grade_90.d * j;
			matrice_90[i][j].x = val1;
			matrice_90[i][j].y = val2; 
		}

	for(i=0;i<header2->height;i++)
		for(j=0;j<header2->width;j++)
			a_90[ matrice_90[i][j].x ][ matrice_90[i][j].y + 59] = a[i][j];
	//schimbam width-ul si height-ul
	header2->width = 60;
	header2->height = 30;
	val = 3 * header2->width;
	//calculam noul padding
	while(1)
	{
		if(val%4==0)
			break;
		else
			val++;
	}
	padding = val - 3 * header2->width;
	header2->biSizeImage = (3 * header2->width + padding) * header2->height;
	header1->bfSize = header2->biSizeImage + header1->imageDataOffset;
	//adaugam totul in fisier
	FILE *piesa_rotita_90;
	piesa_rotita_90 = fopen("piesa_I_90.bmp","wb");
	fwrite(header1,sizeof(struct bmp_fileheader),1,piesa_rotita_90);
	fwrite(header2,sizeof(struct bmp_infoheader),1,piesa_rotita_90);
	for(i=header2->height-1;i>=0;i--)
	{
		for(j=header2->width-1;j>=0;j--)
		{
			fwrite(&a_90[i][j].blue,sizeof(char),1,piesa_rotita_90);
			fwrite(&a_90[i][j].green,sizeof(char),1,piesa_rotita_90);
			fwrite(&a_90[i][j].red,sizeof(char),1,piesa_rotita_90);
		}
		int zero=0;
		for(k=0;k<padding;k++)
			fwrite(&zero,sizeof(char),1,piesa_rotita_90);
	}
	fclose(piesa_rotita_90);
	for(i=0;i<30;i++)
		free(a_90[i]);
	free(a_90);

	//rotatie 180 de grade
	header2->width = 30;
	header2->height = 60;
	struct rotatie grade_180;
	grade_180.a = 1;
	grade_180.b = 0;
	grade_180.c = 0;
	grade_180.d = 1;

	struct rgb **a_180;
	a_180 = malloc(header2->height * sizeof(struct rgb *));
	for(i=0;i<header2->height;i++)
		a_180[i] = malloc(header2->width * sizeof(struct rgb));


	struct coordonate matrice_180[100][100];

	for(i=0;i<header2->height;i++)
		for(j=0;j<header2->width;j++)
		{
			int val1,val2;
			val1 = grade_180.a * i + grade_180.b * j;
			val2 = grade_180.c * i + grade_180.d * j;
			matrice_180[i][j].x = val1;
			matrice_180[i][j].y = val2; 
		}
	for(i=0;i<header2->height;i++)
		for(j=0;j<header2->width;j++)
			a_180[ matrice_180[i][j].x ][ matrice_180[i][j].y ] = a[i][j];
	
	val = 3 * header2->width;
	while(1)
	{
		if(val%4==0)
			break;
		else
			val++;
	}
	padding = val - 3 * header2->width;
	header2->biSizeImage = (3 * header2->width + padding) * header2->height;
	header1->bfSize = header2->biSizeImage + header1->imageDataOffset;
	
	FILE *piesa_rotita_180;
	piesa_rotita_180 = fopen("piesa_I_180.bmp","wb");
	fwrite(header1,sizeof(struct bmp_fileheader),1,piesa_rotita_180);
	fwrite(header2,sizeof(struct bmp_infoheader),1,piesa_rotita_180);
	for(i=header2->height-1;i>=0;i--)
	{
		for(j=header2->width-1;j>=0;j--)
		{
			fwrite(&a_180[i][j].blue,sizeof(char),1,piesa_rotita_180);
			fwrite(&a_180[i][j].green,sizeof(char),1,piesa_rotita_180);
			fwrite(&a_180[i][j].red,sizeof(char),1,piesa_rotita_180);
		}
		int zero=0;
		for(k=0;k<padding;k++)
			fwrite(&zero,sizeof(char),1,piesa_rotita_180);
	}

	fclose(piesa_rotita_180);
	for(i=0;i<60;i++)
		free(a_180[i]);
	free(a_180);

	//rotatie 270 de grade
	struct rotatie grade_270;
	grade_270.a = 0;
	grade_270.b = -1;
	grade_270.c = 1;
	grade_270.d = 0;

	struct rgb **a_270;
	a_270 = malloc(30 * sizeof(struct rgb *));
	for(i=0;i<30;i++)
		a_270[i] = malloc(60 * sizeof(struct rgb));

	struct coordonate matrice_270[100][100];

	for(i=0;i<header2->height;i++)
		for(j=0;j<header2->width;j++)
		{
			int val1,val2;
			val1 = grade_270.a * i + grade_270.b * j;
			val2 = grade_270.c * i + grade_270.d * j;
			matrice_270[i][j].x = val1;
			matrice_270[i][j].y = val2; 
		}
	for(i=0;i<header2->height;i++)
		for(j=0;j<header2->width;j++)
			a_270[ matrice_270[i][j].x + 29][ matrice_270[i][j].y] = a[i][j];

	header2->width = 60;
	header2->height = 30;
	val = 3 * header2->width;
	while(1)
	{
		if(val%4==0)
			break;
		else
			val++;
	}
	padding = val - 3 * header2->width;
	header2->biSizeImage = (3 * header2->width + padding) * header2->height;
	header1->bfSize = header2->biSizeImage + header1->imageDataOffset;
	
	FILE *piesa_rotita_270;
	piesa_rotita_270 = fopen("piesa_I_270.bmp","wb");
	fwrite(header1,sizeof(struct bmp_fileheader),1,piesa_rotita_270);
	fwrite(header2,sizeof(struct bmp_infoheader),1,piesa_rotita_270);
	for(i=header2->height-1;i>=0;i--)
	{
		for(j=header2->width-1;j>=0;j--)
		{
			fwrite(&a_270[i][j].blue,sizeof(char),1,piesa_rotita_270);
			fwrite(&a_270[i][j].green,sizeof(char),1,piesa_rotita_270);
			fwrite(&a_270[i][j].red,sizeof(char),1,piesa_rotita_270);
		}
		int zero=0;
		for(k=0;k<padding;k++)
			fwrite(&zero,sizeof(char),1,piesa_rotita_270);
	}

	fclose(piesa_rotita_270);
	for(i=0;i<30;i++)
		free(a_270[i]);
	free(a_270);

	for(i=0;i<header2->height;i++)
		free(a[i]);
	free(a);

	free(header1);
	free(header2);
	free(white_pixel);
	free(blue_pixel);
}