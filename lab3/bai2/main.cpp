#include <iostream>

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
void addtail(List& l, Node* node);
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
        int x = node->data;
        Node* check_data = search_x(l,x);
        if (check_data==NULL)
        {
            l.tail->link= node;
            l.tail= node;
        }
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
