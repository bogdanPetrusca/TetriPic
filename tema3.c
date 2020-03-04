//PETRUSCA BOGDAN MIHAI
//313CB
#include <stdio.h>
#include <stdlib.h>
#include "bmp_header.h"
#include "piesa_S.h"
#include "piesa_I.h"
#include "piesa_J.h"
#include "piesa_L.h"
#include "piesa_O.h"
#include "piesa_T.h"
#include "piesa_Z.h"
#include "task3.h"
#include "task4.h"
#include "functii.h"
#include "bonus.h"
#include <string.h>

int main(int argc, char *argv[])
{
	
	if(argv[1][0] == '1' || argv[1][0] == '2')
	{
		piesa_S();
		piesa_I();
		piesa_J();
		piesa_L();
		piesa_O();
		piesa_T();	
		piesa_Z();
		return 0;
	}
	if (argv[1][0] == '3')
	{
			task3();
			return 0;
	}
	if (argv[1][0] == '4')	
	{
			task4();
			return 0;
	}
	if (strcmp(argv[1],"bonus") == 0)
	{
		bonus();
		return 0;
	}
	return 0;
}
