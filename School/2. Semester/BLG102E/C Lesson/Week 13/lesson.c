#include <stdio.h>
#include <stdlib.h>
#include <myheader.h> // boyle yapacaksan compile ederken -I. koyman lazim ki current directorye baksin.
// #include "myheader.h"   // ya da boyle yapacaksin bu direk current directory bakar

/*
double cube_volume(double side_length);
double cube_surface_area();
--->> Boyle kullanacaksan sorun yok ama bunlari baska dosyadan gostereceksen onu  include etmen lazim.
*/

int main()
{
	double side=0.0;
	printf("Side of Cube: ");
	scanf("%lf",&side);
	
	double vol = cube_volume(side);
	printf("Volume of cube with side %f: %f\n",side,vol);
	
	double area = cube_surface_area(side);
	printf("Area of cube %f\n",area);
	
	return EXIT_SUCCESS;
}


// diger dosyayla birlestirmek icin lesson.c ile cubeops.c ye ayri ayri compile et sonra link ederken soyle yaz gcc -std=c99 -Werror -Wall lesson.o cubeops.o -o cube
