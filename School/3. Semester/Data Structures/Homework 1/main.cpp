#include <iostream>
#include <stdlib.h>
#include <ctype.h>
#include <fstream>
#include "stock.h"


/*
Student Name: TEVFIK OZGU
Student ID: 150180082
Date: 11/10/2019
*/


using namespace std;


void stock::create() { //For creating a stock.
    head = NULL;
}

void stock::add_stock(int stockNum) {  //adding stock function
    
    //IF it is the first stock
    if (head == NULL){
        head=new node;
        head->size = stockNum;
        head->quant=1;
        head->next = NULL;
        return;
    }
    
    
    //For Protecting head pointer
    node *buffer = head;
    
    //If stockNum size is created before increase its quant by 1
    while(buffer){
        if (buffer->size == stockNum) {
            buffer->quant += 1;
            return;
        }
        buffer = buffer->next;
    }
    
    //Add to the front of the head pointer since its size is lower then head->size
    if(stockNum < head->size) {
        node* temp = new node;
        temp->next = NULL;
        temp->size = stockNum;
        temp->quant = 1;
        temp->next = head;
        head = temp;
        return;
    }
    
    
    buffer = head;
    
    //Add after the head pointer since its size is higher then head->size
    if(buffer->size < stockNum){
        
        // ADD TO THE MIDDLE
        while(buffer->next) {
            if(buffer->next->size > stockNum) {
                node* tempp = new node;
                tempp->size = stockNum;
                tempp->quant = 1;
                tempp->next = buffer->next;
                buffer->next = tempp;
                return;
            }
            buffer = buffer->next;
        }
        
        //ADD TO THE END
        node* temp = new node;
        temp->next = NULL;
        temp->size = stockNum;
        temp->quant = 1;
        buffer->next = temp;
        return;
    }
}

void stock::sell(int stockNum) { //selling function
    
    node *buffer = head;
    
    while(buffer){
        
        if (buffer->size == stockNum) { // When stockNum node is found
            if(buffer == head){ //If head node is sold
                if(buffer->quant > 1){ //If there is more than 1 stock that node wont be deleted
                    buffer->quant -= 1;
                    return;
                } else if(buffer->quant == 1) { //Node will be deleted if there is only 1 stock
                    head = head->next;
                    delete buffer;
                    return;
                }
                
            } else{ //If another node is sold
                if(buffer->quant > 1){ //If quant > 1 it wont be deleted
                    buffer->quant -= 1;
                    return;
                }
                
                //If quant==1 that node will be deleted:
                node* prev = head; // prev is for getting the previous node of buffer for not losing its next pointer
                while(prev->next != NULL && prev->next != buffer){
                    prev = prev->next;
                }
                prev->next = prev->next->next;
                delete buffer;
                return;
            }
        }
        buffer = buffer->next;
    }
    
    //If there is no stock
    cout << "NO_STOCK" << endl;
    
}


void stock::current_stock() { //prints current stock
    
    node* temp = head; //temp is for protecting head pointer.
    while (temp) {
        cout << temp->size << ":" << temp->quant << endl;
        temp = temp->next;
    }
}

void stock::clear() { //clear all stock
    node* buff = head; //buff is for protecting head pointer.
    while (buff) {
        head = buff->next;
        delete buff;
        buff = head;
    }
}


int main(int argc, char *argv[]) {
    FILE* fp;
    if(!(fp = fopen (argv[1], "r"))){ //If file could not be opened.
        cout<<"ERROR WHILE OPENING FILE"<<endl;
    } else {
        int stockNum = 0;
        stock myStock; // creating stock struct
        myStock.create();

        while (!feof (fp)) {
            //gets value from the file
            fscanf (fp, "%d", &stockNum);
            if(stockNum > 0) {
                myStock.add_stock(stockNum);
            } else if (stockNum == 0){
                myStock.current_stock();
            } else {
                myStock.sell(abs(stockNum));
            }
        }
        
        myStock.clear(); //clear everything from Memory
        fclose (fp);
        
    }
    return EXIT_SUCCESS;
}
