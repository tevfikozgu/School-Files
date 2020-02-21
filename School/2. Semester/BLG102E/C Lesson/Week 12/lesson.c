#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME 50


struct person_s {
	char name[MAX_NAME + 1];
	int height;
};

int main()
{
	/*
	char name[MAX_NAME + 1];
	printf("What is Your Name: ");
	scanf("%s" , name);
	
	int height;
	printf("Height: ");
	scanf("%d" , &height);
	

	struct person_s person;
	strncpy(person.name, name, MAX_NAME);
	person.height = height;
	*/
	
	struct person_s *person = (struct person_s*) malloc(sizeof(struct person_s));
	printf("What is Your Name: ");
	scanf("%s" , person->name);
	
	printf("Height: ");
	scanf("%d" , &(person->height));
	
	
	FILE* fp = fopen("people.dat" , "wb");
	fwrite(person , sizeof(struct person_s),1, fp);
	fclose(fp);
	free(person);

	//

	struct person_s person2;
	FILE* fp2 = fopen("people.dat" , "rb");
	fread(&person2 , sizeof(struct person_s),1, fp2);
	printf("Name: %s, Height: %d\n",person2.name, person2.height);
	fclose(fp2);
	
	
	return EXIT_SUCCESS;
}
