#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_SIZE 50
#define MAX_LINE 50

int main()
{
	
	FILE* fp = NULL;
	char name[MAX_SIZE + 1];
	int height  = 0;
	
	fp = fopen("people.txt","r+");
	if (fp == NULL) {
		fprintf(stderr,"File not found \n");
		exit(EXIT_FAILURE);
	}
	
	char line[MAX_LINE + 1];

	while(true){
		fgets(line, MAX_LINE , fp);
		sscanf(line, "%s %d",name,&height);
		if (feof(fp)){
			break;
		}
		printf("Name: %s, Height: %d\n",name,height);
	}
	/*
	while(!feof(fp)){
		fgets(line, MAX_LINE , fp);
		sscanf(line, "%s %d",name,&height);
		printf("Name: %s, Height: %d\n",name,height);
	}
	* 2 KERE BASIYOR!!
	*/
	
	fclose(fp);
	
	printf("What is Your Name: ");
	scanf("%s" , name);
	
	printf("Height: ");
	scanf("%d" , &height);
	fp = fopen("people.txt","a");
	fprintf(fp,"%s %d\n",name,height);
	fclose(fp);
	
	return EXIT_SUCCESS;
}
