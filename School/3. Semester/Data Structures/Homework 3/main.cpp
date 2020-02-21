/*
Student Name: TEVFIK OZGU
Student ID: 150180082
Date: 11/12/2019
*/

#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <string>
#include <cstring>
#include <sstream>

using namespace std;


struct Node{
    int num;
    int parentNum;
    bool isBS;
    Node *next;
    Node *counterpart;
    Node *phone; 
    Node *parentNode;
};

struct connections{
    Node* root;
    Node* parentP;
    int baseOfMH;
    bool found;
    bool found2;
    void create();
    void search(int,Node*,bool);
    void add(char*,int, int);
    void traverse(string);
    void searchForTraverse(int,Node*);
    void close(Node*);
};

struct NodeForPrinting{
    int data;
    NodeForPrinting* child;
};

struct basicStack{
    NodeForPrinting* head;
};

void connections::create(){

    //creating root node
    root = new Node;
    root->next = NULL;
    root->num = 0;
    root->counterpart = NULL;
    root->phone = NULL;
    root->parentNode = NULL;
};

void connections::searchForTraverse(int phoneNum,Node* currentNode){

    cout << " " << currentNode->num;
    if(currentNode->phone){ //If current base station has mobile hosts
        Node* phoneList = currentNode->phone;
        while(phoneList->num != phoneNum && phoneList->next){
            phoneList = phoneList->next;
        }
        if(phoneList->num == phoneNum){
            found2 = true; // this bool is supplying this function for not searching any more.
            baseOfMH = currentNode->num;
            parentP = currentNode;
            cout << endl;
            return;
        } else{
            if(currentNode->counterpart){
                searchForTraverse(phoneNum,currentNode->counterpart); // Look for the bs of current Node
            }
            if (!found2 && currentNode->next){
                searchForTraverse(phoneNum,currentNode->next); // If mh is not at current node and its bs's then look for the current node's next bs
            }
        }
    }
}

void connections::search(int parentID,Node* parentNode,bool type){

    if(parentNode->num == parentID){ //IF parent Node is found
        if(type){ //If it is BS
            if(parentNode->counterpart != NULL){ // If there are BSs of parent Node then find the last BS
                parentNode = parentNode->counterpart;
                while(parentNode->next){
                    parentNode = parentNode->next;
                }
            } // parent node in en sonuna eklemek icin
            parentP = parentNode;
            found = true;
            return;
        }
        if(parentNode->phone != NULL){ // Find the last MH of MH list
            parentNode = parentNode->phone;
            while(parentNode->next){
                parentNode = parentNode->next;
            }
        } 
        parentP = parentNode;
        found = true;
        return;
    }

    if(parentNode->counterpart){ //For Searching
        search(parentID,parentNode->counterpart,type);
    } 
    if (!found && parentNode->next){ // If parent node is not found on counterpart list then look at the last nodes next.
        search(parentID,parentNode->next,type);
    }
}

void connections::add(char* bs,int id, int parentId){

    Node* newNode = new Node;
    newNode->num = id;
    newNode->parentNum = parentId;
    newNode->next=NULL;
    newNode->counterpart=NULL;
    newNode->phone = NULL;
    newNode->parentNode = NULL;
    found = false; // This is for search function of add. If parent node is found then dont look the currentNodes next!

    if(!strncmp(bs,"BS",2)){
        newNode->isBS = true;
    } else if(!strncmp(bs,"MH",2)){
        newNode->isBS = false;
    } else{
       cout << "ERROR THIS TYPE IS NOT KNOWN. IT MUST BE 'BS' OR 'MH '" << endl;
    }

    if(parentId == 0){ // If parent Node is root
        if(!(root->counterpart)){
            root->counterpart = newNode;
            newNode->parentNode = root;
            return;
        }
        Node *traverse = root->counterpart;
        while(traverse->next){
            traverse = traverse->next;
            
        }
        traverse->next = newNode;

        newNode->parentNode = root;
        return;
    }

    Node *tail = root->counterpart;
    search(parentId,tail,newNode->isBS);

    if(newNode->isBS){ // If newnode is BS
        if(parentP->num == parentId){ // If ParentP doesnt have counterpart
            parentP->counterpart = newNode;
            newNode->parentNode = parentP;
            return;
        }else if(parentP->parentNum == parentId){ // If ParentP has counterpart
            parentP->next = newNode;
            newNode->parentNode = parentP->parentNode;
        }
    } else if (!(newNode->isBS)){ // If new node is MH
        if((parentP->num == parentId) && (parentP->isBS)){ // If ParentP doesnt have counterpart
            parentP->phone = newNode;
        } else if(parentP->parentNum == parentId){ // If ParentP has counterpart
            parentP->next = newNode;
        }
    }
}

void connections::traverse(string line){

    found2 = false; // If found dont look at the parent Nodes next
    istringstream iss(line);
    string messages[2];
    string token;
    
    int i = 0;
    while (getline(iss, token, '>')){
        messages[i] = token;
        i++;
     }

    stringstream geek(messages[1]);
    int phoneNum = 0;
    geek >> phoneNum; // String to Int Converter

    cout << "Traversing:0";
    searchForTraverse(phoneNum,root->counterpart);
    if (found2){
        cout << "Message:" << messages[0] << " To:0 ";
        
        basicStack Stack; //I created temporary stack for printing the stack datas. Also this stack supplies First In Last Out, so I can print from root to parentBS
        Stack.head = NULL;
        while(parentP->parentNode){
            if (Stack.head == NULL){
                Stack.head = new NodeForPrinting;
                Stack.head->data = parentP->num;
                Stack.head->child = NULL;
            } else {
                NodeForPrinting* traverse = new NodeForPrinting;
                traverse->child = Stack.head;
                traverse->data = parentP->num;
                Stack.head = traverse;
            }
            parentP = parentP->parentNode;
        }
        NodeForPrinting* traverse = Stack.head;
        while(traverse){
            cout << traverse->data << " ";
            traverse = traverse->child;
            delete Stack.head;
            Stack.head = traverse;
        }
        
        cout << "mh_" << phoneNum <<endl;
        
    } else{
        cout << endl << "Can not be reached the mobile host mh_" << phoneNum << " at the moment"<<endl;
    }
}

void connections::close(Node* parent){

    if (parent->counterpart){ //Go to counterpart while there is counterpart
        close(parent->counterpart);
    }

    while(parent->phone){ //If there is a phone pointer of current node
        Node* traverse = parent->phone;
        if(traverse->next){
            parent->phone = traverse->next;
            delete traverse;
        } else {
            parent->phone = NULL;
            delete traverse;
        }
    }
    if(parent->next){
        Node* nextBS = parent->next;
        delete parent;
        close(nextBS);
    } else {
        delete parent;
    }
}

int main(int argc, char *argv[]){
    ifstream infile1(argv[1]);
    ifstream infile2(argv[2]);
    if(!infile1.is_open()){
        cout<<"ERROR WHILE OPENING NETWORK FILE"<<endl;
        if(!infile2.is_open()){
            cout<<"ERROR WHILE OPENING MESSAGES FILE"<<endl;
        }
    } else {
        connections network;
        network.create();
        string line;
        int ID;
        int parentID;
        char type[2];
        while (infile1 >> type >> ID >> parentID){
            network.add(type,ID,parentID);
        }
        while(getline(infile2,line)){
            network.traverse(line);
        }
        network.close(network.root->counterpart);
        delete network.root;
        network.root = NULL;
    }
    infile1.close();
    return 0;
}