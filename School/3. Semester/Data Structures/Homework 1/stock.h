#include "node.h"

/*
Student Name: TEVFIK OZGU
Student ID: 150180082
Date: 11/10/2019
*/

struct stock{
    node *head;
    void create();
    void add_stock(int);
    void sell(int);
    void current_stock();
    void clear();
};
