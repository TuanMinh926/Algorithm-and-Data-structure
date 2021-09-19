#include <iostream>
#include <stdio.h>

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
void addtail(List& l, Node* node);
int removehead(List& l);
void takehead(List& l);
void taketail(List& l);
Node* search_x(List& l, int x);
void printlist (List l);
void nhapList (int a[], int n, List& l);

int main()
{
    int a[MAX] = {5,4,3,2,1};
    int n = 5;
    List lst;
    nhapList(a,n,lst);
    cout<<"List ban dau:\n";
    printlist(lst);
    if (removehead(lst)==0)
    {
        cout<<"List rong khong the xoa!\n";
    }
    else
    {
        cout<<"Xoa dau thanh cong!\n";
    }
    cout<<"List sau khi xoa dau:\n";
    printlist(lst);
    takehead(lst);
    taketail(lst);
    Node* x_find = search_x(lst,3);
    if (x_find!=NULL)
    {
        cout<<"Gia tri can tim\n";
        cout<<"Vi tri: "<<x_find<<"\n";
        cout<<"Data: "<<x_find->data<<"\n";
    }
    else
    {
        cout<<"Khong tim thay";
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

void addhead(List& l, Node* node)
{
    if (l.head==NULL)
    {
        l.head= node;
        l.tail= node;
    }
    else
    {
        node->link = l.head;
        l.head = node;
    }
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

int removehead(List& l)
{
    if (l.head!=NULL)
    {
        Node* node = l.head;
        l.head = node->link;
        delete node;
        if (l.head==NULL)
        {
            l.tail=NULL;
        }
        return 1;
    }
    return 0;
}

void takehead(List& l)
{
    if (l.head != NULL)
    {
        int x = l.head->data;
        cout<<"Data head list: "<<x<<"\n";
    }
}

void taketail(List& l)
{
    if (l.head != NULL)
    {
        int x = l.tail->data;
        cout<<"Data tail list: "<<x<<"\n";
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

void printlist (List l)
{
    if (l.head != NULL)
    {
        Node* node= l.head;
        while(node != NULL)
        {
            cout<<node->data<<' ';
            node=node->link;
        }
        cout<<"\n";
    }
}

void nhapList (int a[], int n, List& l)
{
    creList(l);

    Node* node;
    for (int i=0;i<n;i++)
    {
        node = crenode(a[i]);
        //addhead(lst,node);
        addtail(l,node);
    }
}
