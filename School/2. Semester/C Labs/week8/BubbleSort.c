#include <stdio.h>
#include <stdlib.h>

#define SIZE 100

int main() 
{
	int list[SIZE],number_amount;
	printf("Number Amount:");
	scanf("%d",&number_amount);
	for (int i = 0 ; i<number_amount;i++){
		int number;
		printf("%d. number:",i+1);
		scanf("%d",&number);
		list[i]=number;
	}
	for (int i=0;i<number_amount;i++){
		for (int i1=i+1;i1<number_amount;i1++){
			if ( list[i1] < list[i] ){
				int swap = list[i];
				list[i]= list[i1];
				list[i1]=swap;
			}
		}
	}
	for (int i=0;i<number_amount;i++){
		printf("%d\n",list[i]);
	}
	return EXIT_SUCCESS;
}
