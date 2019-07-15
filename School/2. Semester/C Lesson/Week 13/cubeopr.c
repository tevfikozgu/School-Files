#include <math.h> // bunu kullanabilmek icin -lm koyman lazim linkingde

double cube_volume(double side_length)
{
	double volume = side_length*side_length*side_length;
	return volume;
}

double cube_surface_area()
{
	return sqrt(9);
}
