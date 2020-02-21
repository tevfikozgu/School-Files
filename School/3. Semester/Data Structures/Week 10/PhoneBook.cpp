#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <string>
#include <cstring>
#include <sstream>
#define NAME_LENGTH 30
#define PHONENUM_LENGTH 15

using namespace std;

/* BST CHECKER

bool isBST(node* nptr)
{
    node* t;
    if (nptr==NULL) return true;
    if(isBST(nptr->right)){
        t=nptr->right;
        if(t!=NULL){
            while(t->left){
                t=t->left;
            }
            if(t->data>=nptr->data){
                return false;
            }
        }
    }
    else {
        return false;
    }
    return true;
}

*/

struct Phone_node{
    char name[NAME_LENGTH];
    char phonenum[PHONENUM_LENGTH];
    Phone_node *left;
    Phone_node *right;
};

struct Tree{
    Phone_node *root;
    int nodecount;
    char *filename;
    FILE* phonebook;
    void create();
    void close();
    void emptytree(Phone_node *);
    void add(Phone_node *);
    void remove(char *);
    void remove(Phone_node **);
    void traverse_inorder(Phone_node *);
    int search(char *);
    void read_fromfile();
    void write_inorder(Phone_node *);
    void write_preorder(Phone_node *);
    void write_tofile();
};

typedef Tree Datastructre;

void Tree::create(){
    root =NULL;
    nodecount = 0;
    read_fromfile();
}

//VERILER TREE YE INORDER OLARAK EKLENMELI

void Tree::read_fromfile(){
    struct File_Record{
        char name[NAME_LENGTH];
        char phonenum[PHONENUM_LENGTH];
    };
    File_Record record;
    Phone_node *newnode;
    filename = "phonebook.txt";
    if(!phonebook = fopen(filename,"r+")){
        if(!phonebook = fopen(filename,"w+")){
            cerr << "Could not open file." << endl;
            cerr << "Will work in memory only." << endl;
        }
        return;
    }

    fseek(phonebook,0,SEEK_SET);

    while(!feof(phonebook)){
        newnode = new Phone_node;
        fread(&record,sizeof(File_Record),1,phonebook);
        if(feof(phonebook)){
            break;
        }
        strcpy(newnode->name,record.name);
        strcpy(newnode->phonenum,record.phonenum);
        newnode->left = NULL;
        newnode->right = NULL;
        add(newnode);
        delete newnode;
    }
    fclose(phonebook);
}

void Tree::close(){
    write_tofile();
    emptytree(root);
}

void Tree::write_tofile(){
    if(!(phonebook = fopen(filename,"w+"))){
        cerr << "Could not open File" << endl;
        return;
    }
    write_inorder(root);
    fclose(phonebook);
}

//Writing Inorder!!! BU SEKILDE YAZDIRINCA DOSYAYA ALFABETIK OLARAK YAZICAK. GERI OLUSTURMAYA CALISIRKEN DENGESIZ BIR TREE OLUSCAK HABIRE SAG ALTA EKLICEK!!

void Tree::write_inorder(Phone_node *p){
    struct File_Record{
        char name[NAME_LENGTH];
        char phonenum[PHONENUM_LENGTH];
    };

    File_Record record;
    if(p){
        write_inorder(p->left);
        strcpy(record.name,p->name);
        strcpy(record.phonenum,p->phonenum);
        fwrite(&record,sizeof(File_Record),1,phonebook);
        write_inorder(p->right);
    }
}

//INORDER DEGIL PREORDER OLARAK YAZMALIYIZ!! DOSYAYAAAAA

void Tree::write_preorder(Phone_node *p){
    struct File_Record{
        char name[NAME_LENGTH];
        char phonenum[PHONENUM_LENGTH];
    };

    File_Record record;

    if(p){
        strcpy(record.name,p->name);
        strcpy(record.phonenum,p->phonenum);
        fwrite(&record,sizeof(File_Record),1,phonebook);
        write_preorder(p->left);
        write_preorder(p->right);
    }
}

void Tree::emptytree(Phone_node *p){
    if(p){
        if(p->left != NULL){
            emptytree(p->left);
            p->left = NULL;
        }
        if(p->right != NULL){
            emptytree(p->right);
            p->right = NULL;
        }
        delete p;
    }
}

void search_record(){
    char name[NAME_LENGTH];
    cout << "Please enter the name of person you want to search for (Press '*' for complete list):" << endl;
    cin.ignore(1000,'\n');
    cin.getline(name,NAME_LENGTH);
    if(book.search(name) == 0) {
        cout << "Could not find record matching search criteria" << endl; 
    }
    getchar();
}

int Tree::search(char *search_name){
    Phone_node *traverse;
    traverse = root;
    int countfound = 0;
    bool all = false;
    if(search_name[0] == '*')
        all = true;
    if(all){
        traverse_inorder(root);
        countfound++;
    }

    else{
        while(traverse && !countfound){
            int comparison = strcmp(search_name,traverse->name);
            if(comparison<0){
                traverse = traverse->left;
            }
            else if(comparison > 0){
                traverse = traverse->right;
            }
            else {
                cout << traverse->name << " " << traverse->phonenum << endl;
            }
        }
    }
    return countfound;
}

void Tree::traverse_inorder(Phone_node *p){
    if(p){
        traverse_inorder(p->left);
        cout << p->name << " " << p->phonenum << endl;
        traverse_inorder(p->right);
    }
}

void add_record() {
    Phone_node newrecord;
    cout << "Please enter the information for the person you want to record" << endl;
    cout << "Name : ";
    cin.ignore(1000, '\n'); 
    cin.getline(newrecord.name, NAME_LENGTH); 
    cout << "Phone number :";
    cin >> setw(PHONENUM_LENGTH) >> newrecord.phonenum;
    book.add(&newrecord);
    cout << "Record added" << endl;
    getchar();
    book.add(&newrecord);
    cout << "Record added" << endl;
    getchar();
}

void Tree::add(Phone_node *toadd){
    Phone_node *traverse, *newnode;
    traverse = root;
    int comparison;
    bool added = false;
    newnode = new Phone_node;
    strcpy(newnode->name,toadd->name);
    strcpy(newnode->phonenum,toadd->phonenum);
    newnode->left = NULL;
    newnode->right = NULL;
    if(root == NULL){
        root = newnode;
        nodecount++;
        return;
    }
    while((traverse != NULL) && (!added)){
        comparison = strcmp(newnode->name,traverse->name);
        if(comparison<0){
            if(traverse->left != NULL){
                traverse = traverse->left;
            } else {
                traverse->left = newnode;
                added = true;
            }
        }
        else if (comparison > 0) {
            if (traverse->right != NULL)
                traverse = traverse->right; 
            else {
                traverse->right = newnode;
                added = true; 
            }
        }
        else {
            cout <<"Data cannot repeat. \n";
        }
    }
    if(added) nodecount++;
}

void upadete_record(){
    struct Phone_Record{
        char name[NAME_LENGTH];
        char phonenum[PHONENUM_LENGTH];
    };
    char name[NAME_LENGTH];
    char choice;
    cout << "Please enter the name" << " of the person you want" <<  " to update:" << endl;
    cin.ignore(1000, '\n');
    cin.getline(name,NAME_LENGTH);

    int personcount = book.search(name);
    if (personcount == 0) {
        cout << "NOT FOUND" << endl;
    }
    else {
        cout << "Record Found" << endl;
        cout << "Do you want to update?"<< "(y/n) "; 
        do {
            cin >> choice;
        } while (choice != ‘y' && choice != ‘n');
        if (choice == '\n') return;
        Phone_Record newrecord;
        cout << "Please enter current info" << endl;
        cout << "Name : ";
        cin.ignore(1000, '\n');
        cin.getline(newrecord.name, NAME_LENGTH); cout << "Phone number :";
        cin >> setw(PHONENUM_LENGTH)>> newrecord.phonenum;
        book.remove(name);
        book.add(&newrecord);
        cout << "Record successfully updated" << endl;
    }
    getchar();
}