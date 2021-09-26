
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <typeinfo>
#include <fstream>

#define MAX 100

using namespace std;

struct Node
{
    int data;
    Node* link;
};

struct List
{
    Node* head;
    Node* tail;
};

Node* crenode(int init_data);
void creList(List& l);
void addhead(List& l, Node* node);
int lenList(List l);
void sum2num(List l1,List l2);
void printlist (List l);
void nhapList (string number, List& l);
void nhapmang(string filename, string a[]);
int writefile (char* filename, List l);

int main()
{
    int n=2;
    string a[n];
    nhapmang("twonumbers.dat",a);
    List lst1;
    string number1 = a[0];
    nhapList(number1,lst1);
/*    cout<<"Number 1:\n";
    printlist(lst1);*/
    List lst2;
    string number2 = a[1];
    nhapList(number2,lst2);
/*    cout<<"Number 2:\n";
    printlist(lst2);*/

    sum2num(lst1,lst2);
    return 0;
}

Node* crenode(int init_data){
    Node* node = new Node;
    node->data= init_data;
    node->link= NULL;
    return node;
}

void creList(List& l){
    l.head= NULL;
    l.tail= NULL;
}

void addhead(List& l, Node* node){
    if(l.head==NULL){
        l.head=node;
        l.tail=node;
    }
    else{
        node->link=l.head;
        l.head= node;
    }
}

int lenList(List l){
    int count=0;
    Node* node= l.head;
    while(node!=NULL){
        count++;
        node=node->link;
    }
    return count;
}

void sum2num(List l1,List l2){
    if (l1.head!=NULL && l2.head!=NULL){
        List lsum;
        Node* nodes;
        creList(lsum);

        Node* node;
        Node* node2;

        if (lenList(l1) > lenList(l2)){
            node = l1.head;
            node2 = l2.head;
        }
        else{
            node = l2.head;
            node2 = l1.head;
        }
        while(node!=NULL){

            bool surplus = false;
            Node* temp;

            if (node2!=NULL){
                node->data = node->data + node2->data;
                if (node->data>=10){
                    node->data = node->data-10;
                    if (node->link!=NULL){
                        node->link->data+=1;
                    }
                    else{
                        temp = crenode(1);
                        surplus = true;
                    }
                }
                node2 = node2->link;
            }
            nodes = crenode(node->data);
            addhead(lsum,nodes);
            if (surplus==true){
                addhead(lsum,temp);
            }
            node = node->link;
        }
        /*cout<<"Sum 2 number:\n";
        printlist(lsum);*/
        if (writefile("19469421.txt",lsum)==0){
            cout<<"Khong mo duoc file";
        }
        else{
            cout<<"Ghi file thanh cong";
        }
    }
}

void nhapList (string number, List& l){
    creList(l);
    Node* node;
    for(int i=0;i<number.size();i++){
        int one_num = (int)(number[i])-'0';
        node = crenode(one_num);
        addhead(l,node);
    }
}

void printlist (List l){
    if(l.head!=NULL){
        Node* node= l.head;
        while(node != NULL){
            cout<<node->data<<'\n';
            node=node->link;
        }
        cout<<"\n";
    }
}

void nhapmang(string filename, string a[]){
    fstream file(filename);
    string line;
    getline(file,line);
    a[0] = line;
    getline(file,line);
    a[1] = line;
    file.close();
}

int writefile (char* filename, List l)
{
    FILE* fp = fopen(filename,"r+");

    if (!fp)
        return 0;
    
    string numsum="";
    if(l.head!=NULL){
        Node* node=l.head;
        while(node!=NULL){
            numsum+=to_string(node->data);
            node=node->link;
        }
        fprintf(fp,"%s",numsum.c_str());
    }
    fclose(fp);
    return 1;
}