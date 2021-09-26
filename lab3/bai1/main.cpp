#include <iostream>
#include <stdio.h>

#define MAX 10000

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
void addtail(List& l, Node* node);
void nhapList (int a[], int n, List& l);
void printlist (List l);
Node* search_x(List& l, int x);
void nhapmang(char* filename, int a[], int &n);
void xuatmang(int a[], int n);

int main()
{
    int a[MAX];
    int n;
    nhapmang("mang1k.txt",a,n);
    //xuatmang(a,n);
    List lst;
    nhapList(a,n,lst);
    printlist(lst);
    Node* x_find = search_x(lst,1);
    if (x_find!=NULL)
    {
        cout<<"Co\n";
    }
    else
    {
        cout<<"Khong\n";
    }

    return 0;
}

Node* crenode(int init_data)
{
    Node* node = new Node;
    node->data = init_data;
    node->link = NULL;
    return node;
}

void creList(List& l)
{
    l.head= NULL;
    l.tail= NULL;
}

void addtail(List& l, Node* node)
{
    if (l.head==NULL)
    {
        l.head= node;
        l.tail= node;
    }
    else
    {
        l.tail->link= node;
        l.tail= node;
    }
}

Node* search_x(List& l, int x)
{
    Node* node = l.head;
    while(l.head!=NULL && node->data!=x)
    {
        node= node->link;
    }
    if (node!=NULL)
    {
        return node;
    }
    return NULL;
}

void nhapList (int a[], int n, List& l)
{
    creList(l);

    Node* node;
    for (int i=0;i<n;i++)
    {
        node = crenode(a[i]);
        addtail(l,node);
    }
}

void printlist (List l)
{
    if (l.head != NULL)
    {
        Node* node= l.head;
        while(node != NULL)
        {
            cout<<node->data<<'\n';
            node=node->link;
        }
        cout<<"\n";
    }
}

void nhapmang(char* filename, int a[], int &n)
{
    FILE* fp = fopen(filename,"r+");

    fscanf(fp, "%d", &n);
    for (int i=0;i<n;i++)
    {
        fscanf(fp, "%d",&a[i]);
    }
    fclose(fp);
}

void xuatmang(int a[], int n)
{
    for (int i=0;i<n;i++)
    {
        cout<<"a["<<i<<"]= "<<a[i]<<"\n";
    }
}
