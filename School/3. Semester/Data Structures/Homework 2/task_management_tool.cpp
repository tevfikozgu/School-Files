
/*
    Student Name: TEVFIK OZGU
    Student ID: 150180082
    Date: 03/11/2019
*/

#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <iomanip>

#include "task_management_tool.h"

using namespace std; 


void WorkPlan::display(bool verbose,bool testing)
{
	string inone="***";
	if (head!=NULL)
	{
		Task *pivot =new Task;
		Task *compeer =new Task;
			
		pivot=head;
		do
		{
			if(testing)
				inone+=" ";
			else
				cout << pivot->day <<". DAY"<< endl;
			compeer=pivot;
			while(compeer!=NULL)
			{
				string PREV= compeer->previous!=NULL?compeer->previous->name:"NULL";
				string NEXT=compeer->next!=NULL?compeer->next->name:"NULL";
				string CONT=compeer->counterpart!=NULL?compeer->counterpart->name:"NULL";
				if (testing)
					inone+=compeer->name;
				else
					if(verbose)
						cout<<"\t"<<setw(2)<< compeer->time <<":00\t"<< PREV<<"\t<- "<< compeer->name <<"("<< compeer->priority <<")->\t"<<NEXT <<"\t |_"<<CONT<<endl;
					else
						cout<<"\t"<<setw(2)<< compeer->time <<":00\t"<< compeer->name <<"("<< compeer->priority <<")"<<endl;				
				compeer=compeer->counterpart;
			}
			pivot=pivot->next;
		}while(pivot!=head);
		if(testing)
		{
			cout<<inone<<endl;
			cout<<"(checking cycled list:";
			if (checkCycledList())
				cout<<" PASS)"<<endl;
			else
				cout<<" FAIL)"<<endl;
		}
	}
	else
		cout<<"There is no task yet!"<<endl;
}

int WorkPlan::getUsableDay()
{
	return usable_day;
}

int WorkPlan::getUsableTime()
{
	return usable_time;
}


void WorkPlan::create()
{		
	head = NULL;
}

void WorkPlan::close()
{
    //For deleting all tasks
	Task* traverse = head;
    Task* counterpartTracker = NULL;
    Task* countrprt = traverse;

    // if there a is task of days first appoinment
    while (traverse)
    {
        countrprt = traverse;
        while (countrprt) //if there a is task of days counterpart appoinments
        {
            if(countrprt){
                counterpartTracker = countrprt->counterpart;
            }
            delete [] countrprt->name; // can be at remove function but because of app.cpp declaration I have to do it here.
            remove(countrprt);
            countrprt = counterpartTracker;
        }
        traverse = head;
    }
}

void WorkPlan::add(Task *task)
{

    if (head == NULL){ // First task!

        head = new Task;
        head->name = new char[strlen(task->name)];
        strcpy(head->name,task->name);
        head->day = task->day;
        head->time = task->time;
        head->priority = task->priority;
        head->previous = head;
        head->next = head;
        head->counterpart = NULL;
        return;

    }
    
    //If head task is created before
    Task* new_task = new Task;
    new_task->name = new char[strlen(task->name)];
    strcpy(new_task->name,task->name);
    new_task->day = task->day;
    new_task->time = task->time;
    new_task->priority = task->priority;

    Task* checker = head; //For checking if day struct is created before. Eger o gun varsa o gunun counterpartina eklenecek.
    do
    {
        if (checker->day == new_task->day)
        { //If day is created before
            while ((checker->counterpart != NULL) && (checker->counterpart->time < task->time) && (checker->time < task->time))
            { // For finding task which we want to add after it.
                checker = checker->counterpart;
            }

            //For delaying process of the current task.
            if(checker->time == new_task->time){

                if(checker->priority > new_task->priority){ // if new tasks priority lower than the task which created before.
                    checkAvailableNextTimesFor(new_task);
                    new_task->day = getUsableDay();
                    new_task->time = getUsableTime();
                } else { // if new tasks priority higher than the task which created before.
                    checkAvailableNextTimesFor(checker);
                    delete [] new_task->name;
                    new_task->name = new char[strlen(checker->name)];
                    strcpy(new_task->name,checker->name);
                    new_task->day = getUsableDay();
                    new_task->time = getUsableTime();
                    new_task->priority = checker->priority;
                    delete [] checker->name;
                    checker->name = new char[strlen(task->name)];
                    strcpy(checker->name,task->name);
                    checker->time = task->time;
                    checker->day = task->day;
                    checker->priority = task->priority;
                    while(checker->day != new_task->day){
                        checker = checker->next; //checkeri olmasi gereken gune getiriyorum ki new task i dogru yere eklesin.
                    }
                    while ((checker->counterpart != NULL) && (checker->counterpart->time < new_task->time) && (checker->time < new_task->time))
                    { //checkeri olmasi gereken zamana getiriyorum ki new task i dogru yere eklesin.
                        checker = checker->counterpart;
                    }
                }
            }

            //For delaying process of the task after the current task.
            if(checker->counterpart){ //bi sonraki kendisinden kucuk degilse duruyordu ama esit olma durumu da var.
                if (checker->counterpart->time == new_task->time){
                    checker = checker->counterpart;
                    if(checker->priority > new_task->priority){
                        checkAvailableNextTimesFor(new_task);
                        new_task->day = getUsableDay();
                        new_task->time = getUsableTime();
                    } else{
                        checkAvailableNextTimesFor(checker);
                        delete [] new_task->name;
                        new_task->name = new char[strlen(checker->name)];
                        strcpy(new_task->name,checker->name);
                        new_task->day = getUsableDay();
                        new_task->time = getUsableTime();
                        new_task->priority = checker->priority;
                        delete [] checker->name;
                        checker->name = new char[strlen(task->name)];
                        strcpy(checker->name,task->name);
                        checker->time = task->time;
                        checker->day = task->day;
                        checker->priority = task->priority;
                        while(checker->day != new_task->day){ //yukaridakiyle ayni olay
                            checker = checker->next;
                        }
                        while ((checker->counterpart != NULL) && (checker->counterpart->time < new_task->time) && (checker->time < new_task->time))
                        {
                            checker = checker->counterpart;
                        }
                    }
                }
            }
            
            
            if((checker->day != new_task->day)&&(new_task->day == task->day)){ // if task delayed to another day, checker must show the task day which new_task will be delayed
                checker = head;
                while (checker->day != new_task->day)
                {
                    checker = checker->next;
                }
                while ((checker->counterpart != NULL) && (checker->counterpart->time < task->time) && (checker->time < task->time))
                {
                    checker = checker->counterpart;
                }
            }

            if((checker->next != NULL) && (checker->time > new_task->time)) { // If checker is pointing to the days first appoinment.

                if(checker == head){ // If checker pointing the same task with head.

                    new_task->counterpart = checker;
                    if(head->next == head) { // if there is only head task
                        new_task->next = new_task;
                        new_task->previous = new_task;
                        checker->previous = NULL;
                        checker->next = NULL;
                        head = new_task;
                        return;
                    }
                    new_task->next = checker->next;
                    new_task->previous = checker->previous;
                    checker->previous->next = new_task;
                    checker->next->previous = new_task;
                    checker->previous = NULL;
                    checker->next = NULL;
                    head = new_task;
                    return;
                }

                //adding to the located day.
                new_task->counterpart = checker;
                if(head->next == head) {
                    new_task->next = new_task;
                    new_task->previous = new_task;
                    checker->previous = NULL;
                    checker->next = NULL;
                    head = new_task;
                    return;
                }
                new_task->next = checker->next;
                new_task->previous = checker->previous;
                checker->previous->next = new_task;
                checker->next->previous = new_task;
                checker->previous = NULL;
                checker->next = NULL;
                return;
            }
            new_task->counterpart = checker->counterpart;
            new_task->next = NULL;
            new_task->previous = NULL;
            checker->counterpart = new_task;
            return;
        }
        checker = checker->next;
    } while (checker != head);
    

    //ADD AFTER THE HEAD POINTER
    if (head->day < task->day){
        Task* traverse = head;
        new_task->counterpart = NULL;
        if(traverse->next == traverse){ //IF THERE IS ONLY HEAD TASK
            new_task->next = head;
            new_task->previous = head;
            traverse->next = new_task;
            traverse->previous = new_task;
            return;
        }
        
        while((traverse->day < task->day) && (traverse->next != head) && (traverse->next->day < task->day)){
            traverse = traverse->next; 
        }

        new_task->previous = traverse;
        new_task->next = traverse->next;
        traverse->next->previous = new_task;
        traverse->next = new_task;
        return;
    }

    //IF head day is after task day!
    new_task->counterpart = NULL;
    new_task->next = head;
    new_task->previous = head->previous;
    head->previous->next = new_task;
    head->previous = new_task;
    head = new_task;
    return;
}

Task * WorkPlan::getTask(int day, int time)
{ 	
    //silinmek istenen taskin konumunu alicak
	Task* traverse=head;
	while(traverse->day != day) {
		traverse = traverse->next;
	} 
	while (traverse->time != time){
		traverse = traverse->counterpart;
	}
	return traverse;
}


void WorkPlan::checkAvailableNextTimesFor(Task *delayed)	
{	
    Task* temp = head;
    int usableHour = delayed->time; //usable_hour initially equal to delayed task's time.
    while(temp->day != delayed->day){
        temp = temp->next;
    }
    
    Task* timeChecker = temp;
    while(timeChecker->time != delayed->time){
        timeChecker = timeChecker->counterpart;
    } // time checker is showing the same time with delayed task
    Task* traverse = timeChecker;
    do
    {
        Task* lastHour = temp;
        while (lastHour->counterpart)
        {
            lastHour = lastHour->counterpart;
        }
        int lastTime = lastHour->time; //last hour of the delayed task's day
        if(temp->time > usableHour){ // If time is found!!
            WorkPlan::usable_time = usableHour;
            WorkPlan::usable_day = traverse->day;
            return; 
        }
        
        if(usableHour<lastTime){ //If it can be delayed to the current day!
            while((traverse->counterpart)&&(usableHour==traverse->time)){
                usableHour++;
                traverse = traverse->counterpart;
                //This loop finds the first available time at the same day of traverse.
            }
            if(usableHour<lastTime){ //To be sure it is lower than last appoinment of the day.
                WorkPlan::usable_time = usableHour;
                WorkPlan::usable_day = traverse->day;
                return;
            }
        }
        
        if(temp->next == head){ // if temp is pointing the last day of the appoinments
           
            if(usableHour < 16){ // if there is allocation for the delayed task at same day
                WorkPlan::usable_time = usableHour+1;
                WorkPlan::usable_day = temp->day;
                return;
            }
             
            WorkPlan::usable_time = 8;
            WorkPlan::usable_day = temp->day + 1;
            return;
        }
        temp=temp->next;
        usableHour = 8; //sonraki gune alip uygun saati 8 yaptim saat 8 den itibaren arayacak
        traverse=temp;
    }while(temp != head);
}

void WorkPlan::delayAllTasksOfDay(int day)
{
	Task* temp = head;
    while(temp->day != day){
        temp = temp->next;
    }
    Task* counterprt = temp;
    Task* counterTracker = temp;
    while(counterTracker != NULL){
        Task* new_task_delay = new Task;
        new_task_delay->name = new char[strlen(counterTracker->name)];
        strcpy(new_task_delay->name,counterTracker->name);
        new_task_delay->priority = counterTracker->priority;
        new_task_delay->counterpart = NULL;
        while(counterTracker->day == day){
            checkAvailableNextTimesFor(counterTracker);
            counterTracker->time = getUsableTime();
            counterTracker->day = getUsableDay();
        }
        new_task_delay->day = counterTracker->day;
        new_task_delay->time = counterTracker->time;
        counterTracker = counterTracker->counterpart;
        delete [] counterprt->name;
        remove(counterprt);
        add(new_task_delay);
        counterprt = counterTracker;
    }
}

void WorkPlan::remove(Task *target)
{
	Task* traverse = head;
    while(traverse->day != target->day){
        traverse = traverse->next;
    }
    while(traverse->time != target->time){
        traverse = traverse->counterpart;
    }

    if(traverse->next){
        if(traverse->counterpart == NULL){
            Task* temp = traverse;
            if(traverse == head){
                if(traverse->next == head){
                    delete traverse;
                    head=NULL;
                    return;
                }
                traverse->next->previous = temp->previous;
                traverse->previous->next = temp->next;
                head = traverse->next;
                //delete [] traverse->name;
                delete traverse;
                traverse = NULL;
                return;
            }
            traverse->next->previous = temp->previous;
            traverse->previous->next = temp->next;
            //delete [] traverse->name;
            delete traverse;
            traverse = NULL;
            return;
        }
        Task* temp = traverse->counterpart;
        if(traverse == head){
            if(traverse->next == head){

                temp->next = temp;
                temp->previous = temp;
                head = temp;
                //delete [] traverse->name; app.cpp HATASINDAN DOLAYI SILEMIYORUM!
                delete traverse;
                traverse = NULL;
                return;


            }
            traverse->next->previous = temp;
            traverse->previous->next = temp;
            temp->next = traverse->next;
            temp->previous = traverse->previous;
            head = temp;
            //delete [] traverse->name;
            delete traverse;
            traverse = NULL;
            return;
            
        }
        traverse->next->previous = temp;
        traverse->previous->next = temp;
        temp->next = traverse->next;
        temp->previous = traverse->previous;
        //delete [] traverse->name;
        delete traverse;
        traverse = NULL;
        return;
    }
    Task* temp = head;
    while(temp->day != target->day){
        temp = temp->next;
    }
    while(temp->counterpart != traverse){
        temp = temp->counterpart;
    }
    temp->counterpart = traverse->counterpart;
    //delete [] traverse->name;
    delete traverse;
    traverse = NULL;
    target = NULL;
    return;

}

bool WorkPlan::checkCycledList()
{
	Task *pivot=new Task();
	pivot=head;
	int patient=100;
	bool r=false;
	while (pivot!=NULL&&patient>0)
	{		
		patient--;
		pivot=pivot->previous;
		if(pivot==head)
		{
			r=true;
			break;
		}
	}
	cout<<"("<<100-patient<<")";
	patient=100;
	bool l=false;
	while (pivot!=NULL&&patient>0)
	{		
		patient--;
		pivot=pivot->next;
		if(pivot==head)
		{
			l=true;
			break;
		}
	}
	return r&l;
}