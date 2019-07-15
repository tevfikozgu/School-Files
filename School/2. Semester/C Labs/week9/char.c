#include <stdio.h>
#include <stdlib.h>

int len(char* wbc)
{
    int len = 0;
    while (*(wbc + len) != '\0'){
        len++;
    }
    return (len);    
}

void copy(char* wbc,char* other,int length)
{
    for (int i = 0; i<length;i++){
        *(other + i) = *(wbc + i);
    }
    *(other + length) = '\0';
}

void concatt(char* wbc,char* other,int length,int length2)
{
	int i2 = 0;
	for (int i=length;i<length+length2;i++){
		*(wbc + i) = *(other + i2);
		i2++;
	}
}

char* substring(char* wbc, int start, int length)
{
	char* subs;
	subs = (char*) malloc(20 * sizeof(char));
	int i2=0;
	for (int i=start;i<length;i++){
		*(subs + i2) = *(wbc + i);
		i2++;
	}
	*(subs+(length-start)) = '\0';
	return subs;
}

char* inttostring(int year)
{
	char* string= NULL;
	int year2=year;
	int basamak=0;
	string = (char*) malloc(20 * sizeof(char));
	while (year2 != 0){
		year2 = year2 / 10;
		basamak++;
	}
	int basamak2 = basamak-1;
	for (int i = 0;i<basamak;i++){
		int bolum = year % 10;
		year = year / 10;
		*(string + basamak2) = bolum + '0';
		basamak2--;
	}
	*(string + basamak) = '\0';
	return string;
}

int main()
{
    char wbc[20] = "tevfik";
    char* catf = "ozgu";
    int year = 1999;
    int start=2;
    char other[20];
    int length = len(wbc);
    int length2 = len(catf);
    int length3 = length+length2;
    //copy(wbc,other,length);
    //printf("%s\n",other);
    concatt(wbc,catf,length,length2);
    //printf("%s\n",wbc);
    char* a = substring(wbc,start,length3);
    //printf("%s\n",a);
    char* years = inttostring(year);
    printf("%s\n",years);
    return EXIT_SUCCESS;
}
