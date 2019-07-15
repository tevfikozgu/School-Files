#include <stdio.h>
#include <stdlib.h>

#define SIZE 100
#define MOVINGA 3


int main()
{
	int my_list[SIZE];
	double my_list1[SIZE];
	double my_list2[SIZE];
	double input;
	double value1,value2,value3;
	double total=0,total1=0,total2=0;
	int answer=1;
	double input1,input2,input3;
	int total_input=0;
	int total_input1=0;
	do{
		printf("Enter input:");
		scanf("%lf",&input);
		my_list[total_input]=input;
		total_input++;
		printf("Type 0 to exit:");
		scanf("%d",&answer);
	}while(answer != 0);
	for (int i=0;i<total_input;i++){
		total+=my_list[i];
		total1=total/(i+1);
		my_list1[i]=total1;
	}
	for (int i=0;i<total_input;i++){
		printf("%.2lf\n",my_list1[i]);
	}
	
	printf("\n");
	
	if (total_input<3){
		printf("0");
	}
		
	else{
		value1=my_list[0];
		value2=my_list[1];
		value3=my_list[2];
		for (int i=0;i<total_input-2;i++){
			total2=(value1+value2+value3)/(MOVINGA);
			my_list2[i]=total2;
			value1=value2;
			value2=value3;
			value3=my_list[i+3];
			total_input1++;
			}
		}
	for (int i=0;i<total_input1;i++){
		printf("%.2lf\n",my_list2[i]);
	}
	return EXIT_SUCCESS;
}
