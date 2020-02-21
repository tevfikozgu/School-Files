/*
PLEASE DO NOT CHANGE THIS FILE 
*/

/*
    Student Name: TEVFIK OZGU
    Student ID: 150180082
    Date: 03/11/2019
*/

#define NAME_LENGTH 2

struct Task{
	char *name;
	int day;
	int time;
	int priority;

	Task *previous;
	Task *next;
	Task *counterpart;
};
