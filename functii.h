//PETRUSCA BOGDAN MIHAI
//313CB
#ifndef functii
#define functii
int stop(int height_piesa, int height_table, int startX)
{
	if(startX+height_piesa>height_table)
		return 1;
	else
		return 0;
}
void coliziune( struct rgb **matrice,int Y_start, int max_height, int *X,int *Y, int *Z, int *T )
{
	int i;
	for(i=max_height-1;i>=0;i--)
		if(matrice[i][Y_start+5].blue != 0 || matrice[i][Y_start+5].green != 0 || matrice[i][Y_start+5].red != 0)
		{
			*X = i+1;
			break;
		}
		else
			*X=i;
	for(i=max_height-1;i>=0;i--)
		if(matrice[i][Y_start+15].blue != 0 || matrice[i][Y_start+15].green != 0 || matrice[i][Y_start+15].red != 0)
		{
			*Y = i+1;
			break;
		}
		else
			*Y=i;
	for(i=max_height-1;i>=0;i--)
		if(matrice[i][Y_start+25].blue != 0 || matrice[i][Y_start+25].green != 0 || matrice[i][Y_start+25].red != 0)
		{
			*Z = i+1;
			break;
		}
		else
			*Z=i;
	for(i=max_height-1;i>=0;i--)
		if(matrice[i][Y_start+35].blue != 0 || matrice[i][Y_start+35].green != 0 || matrice[i][Y_start+35].red != 0)
		{
			*T = i+1;
			break;
		}
		else
			*T=i;
}
void add_color(struct rgb **matrice, struct rgb *culoare, int X_start, int X_end, int Y_start, int Y_end)
{
	int row,column;
	for(row = X_start; row < X_end; row++)
		for(column = Y_start; column < Y_end; column++)
			matrice[row][column]=*culoare;
}

#endif