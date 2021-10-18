#include <iostream>
#include <stdio.h>
#include <cstring>
#include <iomanip>
#include <string.h>
#include <fstream>
#include <sstream>

#define MAX 100

using namespace std;

struct PhanSo{
 int tu;
 int mau;
};
struct Node{
 PhanSo info;
 Node* link;
};
struct List{
 Node* firstnode;
 Node* lastnode;
};

Node* crenode(PhanSo init_data);
void creList(List& l);
void addtail(List& l, Node* node);
void nhapmang(char* filename, PhanSo a[], int &n);
void nhapList (PhanSo a[], int n, List& l);
void printlist (List l);
void printNode(Node* node);
void listMore1 (List l, List &lmore1);
void writefile(string filename,List l,List l2,List l3, List l4);
int removehead(List& l, PhanSo& x);
int remove_after(List& l, Node* node_previous, PhanSo& x);
void remove_more1(List &l);
void duplicateList(List l1, List &l2);
void Sort_phanso(List lst);
void change(PhanSo &a, PhanSo &b);


int main(){

    PhanSo a[MAX];
    int n;
    nhapmang("phanso.txt",a,n);
    List lst;
    nhapList(a,n,lst);
    printlist(lst);
    List lstmore1;
    listMore1(lst,lstmore1);
    printlist(lstmore1);
    List lstsmall1;
    duplicateList(lst, lstsmall1);
    remove_more1(lstsmall1);
    printlist(lstsmall1);
    List lstsort;
    duplicateList(lstsmall1,lstsort);
    Sort_phanso(lstsort);
    printlist(lstsort);
    writefile("46_19469421.txt",lst,lstmore1,lstsmall1,lstsort);
    return 0;
}

Node* crenode(PhanSo init_data){
    Node* node = new Node;
    node->info = init_data;
    node->link = NULL;
    return node;
}

void creList(List& l){
    l.firstnode= NULL;
    l.lastnode= NULL;
}

void addtail(List& l, Node* node){
    if (l.firstnode==NULL)
    {
        l.firstnode= node;
        l.lastnode= node;
    }
    else
    {
        l.lastnode->link= node;
        l.lastnode= node;
    }
}

void nhapmang(char* filename, PhanSo a[], int &n){
    FILE *fptr= fopen(filename, "r");
    int i = 0;
    if (fptr== NULL)
    {
        printf("Error! opening file");
        exit(1);
    }
    char line[200];
    while (fgets(line, sizeof(line), fptr))
    {
        char*token;
        int column = 0;
        token = strtok(line, " ");
        while(token!= NULL)
        {

            if (column == 0){
                a[i].tu= atoi(token) ;
            }
            if (column == 1){
                a[i].mau= atoi(token) ;
            }
            token = strtok(NULL, " ");
            column+=1;
        }
        i+=1;
    }
    n = i;
    fclose(fptr);
}

void nhapList (PhanSo a[], int n, List& l){
    creList(l);

    Node* node;
    for (int i=0;i<n;i++)
    {
        node = crenode(a[i]);
        addtail(l,node);
    }
}

void printlist (List l){
    if (l.firstnode != NULL)
    {
        Node* node= l.firstnode;
        while(node != NULL)
        {
            printNode(node);
            node=node->link;
        }
        cout<<"\n";
    }
}

void printNode(Node* node){
    cout<<node->info.tu <<'/';
    cout<<node->info.mau <<endl;
}

void listMore1 (List l, List &lmore1){
    if (l.firstnode != NULL)
    {
        creList(lmore1);
        float value;
        Node* node= l.firstnode;
        Node* nodemore1;
        while(node != NULL)
        {
            value = (float)node->info.tu/node->info.mau;
            if(value > 1) {
                nodemore1 = crenode(node->info);
                addtail(lmore1,nodemore1);
            }
            node=node->link;
        }
    }
}

void writefile(string filename,List l,List l2,List l3,List l4){
    ofstream fptr (filename);
    if (!fptr){
        cout<<"Error! writing file";
        exit(1);
    }
    
    Node* node = l.firstnode;
    Node* node2 = l2.firstnode;
    Node* node3 = l3.firstnode;
    Node* node4 = l4.firstnode;
    if (node!=NULL)
    {
        while(node!=NULL){
            fptr<<node->info.tu<<"/";
            fptr<<node->info.mau<<" ";
            node = node->link;
        }
        fptr<<"\n";
    }
    if (node2!=NULL)
    {
        while(node2!=NULL){
            fptr<<node2->info.tu<<"/";
            fptr<<node2->info.mau<<" ";
            node2 = node2->link;
        }
        fptr<<"\n";
    }
    if (node3!=NULL)
    {
        while(node3!=NULL){
            fptr<<node3->info.tu<<"/";
            fptr<<node3->info.mau<<" ";
            node3 = node3->link;
        }
        fptr<<"\n";
    }
    if (node4!=NULL)
    {
        while(node4!=NULL){
            fptr<<node4->info.tu<<"/";
            fptr<<node4->info.mau<<" ";
            node4 = node4->link;
        }
    }
    else{
        cout<<"Danh sach rong";
    }
    fptr.close();
}

int removehead(List& l, PhanSo& x){
    if (l.firstnode!=NULL)
    {
        Node* node = l.firstnode;
        x = node->info;
        l.firstnode = node->link;
        delete node;
        if (l.firstnode==NULL)
        {
            l.lastnode=NULL;
        }
        return 1;
    }
    return 0;
}

int remove_after(List& l, Node* node_previous, PhanSo& x){
    if(node_previous != NULL){
        Node* node_after = node_previous->link;
        if (node_after != NULL){
            if (l.lastnode==node_after)
                l.lastnode = node_previous;
            node_previous->link = node_after->link;
            x = node_after->info;
            delete node_after;
            return 1;
        }
        return 0;
    }
    return 0;
}

void remove_more1(List &l){
    Node* node = l.firstnode;

    if (node!=NULL){
        float value = (float)node->info.tu/node->info.mau;
        if (value>1){
            PhanSo data_phanso;
            removehead(l,data_phanso);
        }
        while(node!=NULL){
            if (node->link!=NULL){
                value = (float) node->link->info.tu/node->link->info.mau;
                if(value>1){
                    PhanSo data_phanso;
                    remove_after(l,node,data_phanso);
                }
            }
            node = node->link;
        }
    }
    else{
        cout<<"Danh sach rong\n";
    }
}

void duplicateList(List l1, List &l2){
    creList(l2);

    Node* node1 = l1.firstnode;
    Node* node2;
    if (node1 != NULL)
    {
        while (node1!=NULL)
        {
            node2 = crenode(node1->info);
            addtail(l2,node2);
            node1 = node1->link;
        }
    }
}

void Sort_phanso(List lst){
    if (lst.firstnode!=NULL)
    {
        Node* node1 = lst.firstnode;
        float value1, value2;
        while(node1!=NULL)
        {
            Node* node2 = node1->link;
            while(node2!=NULL)
            {
                value1 = (float) node1->info.tu/node1->info.mau;
                value2 = (float) node2->info.tu/node2->info.mau;
                if (value1 > value2)
                {
                    change(node1->info, node2->info);
                }
                node2 = node2->link;
            }
            node1 = node1->link;
        }
    }
    else
    {
        cout<<"List rong khong the sort";
    }
}

void change(PhanSo &a, PhanSo &b){
    PhanSo temp = a;
    a = b;
    b = temp;
}