#include <iostream>
#include <stdio.h>
#include <string.h>
#include <iomanip>

#define MAX 100

using namespace std;

struct Item{
    string id;
    string name;
    int quantity;
};

struct Node{
    Item data;
    Node *link;
};

struct Queue{
    Node *first, *last;
};

Queue InitQueue();
Node* crenode(Item init_data);
bool IsEmpty(Queue q);
void EnQueue(Queue &q, Node *node);
int DeQueue(Queue &q, Item& data);
void nhapmang(char* filename, Item a[], int &n);
void nhapQueue (Item a[], int n, Queue& q);
void printqueue (Queue q);
void printNode(Node* node);
int lengthQueue(Queue q);
void outItems (Queue &q, int n);
int Select_menu();
void Menu();
int Process_menu(Queue &q);

int main(){

    Item a[MAX];
    int n;
    string filename;
    cout<<"Nhap ten file doc: ";
    getline(cin>>ws,filename);
    char* c_file;
    strcpy(c_file,filename.c_str());
    nhapmang(c_file,a,n);
    Queue q_items;
    nhapQueue(a,n,q_items);
    while(Process_menu(q_items)!=1)
    {
        Process_menu(q_items);
    }
    return 0;
}

Queue InitQueue(){
    Queue q;
    q.first = NULL;
    q.last = NULL;
    return q;
}

Node* crenode(Item init_data)
{
    Node* node = new Node;
    node->data = init_data;
    node->link = NULL;
    return node;
}

bool IsEmpty(Queue q){
    return (q.first == NULL);
}

void EnQueue(Queue &q, Node *node)
{
    if (IsEmpty(q))
    {
        q.first = node;
        q.last = node;
    }
    else
    {
        q.last->link = node;
        q.last = node;
    }
}

int DeQueue(Queue &q, Item& data)
{
    
    if(IsEmpty(q)){
        return 0;
    }
    Node* node = q.first;
    data = node->data;
    q.first = node->link;
    delete node;
    if (q.first==NULL)
    {
        q.last=NULL;
    }
    return 1;

}

void nhapmang(char* filename, Item a[], int &n)
{
    FILE *fptr= fopen(filename, "r");
    int i = 0;
    if (fptr== NULL)
    {
        printf("Error! opening file");
        exit(1);
    }
    char line[200];
    fgets(line, sizeof(line), fptr);
    while (fgets(line, sizeof(line), fptr))
    {
        char*token;
        int column = 0;
        token = strtok(line, ",");
        while(token!= NULL)
        {

            if (column == 0){
                a[i].id= token ;
            }
            if (column == 1){
                a[i].name= token ;
            }
            if (column == 2){
                a[i].quantity= atoi(token) ;
            }
            token = strtok(NULL, ",");
            column+=1;
        }
        i+=1;
    }
    n = i;
    fclose(fptr);
}

void nhapQueue (Item a[], int n, Queue& q)
{
    q = InitQueue();

    Node* node;
    for (int i=0;i<n;i++)
    {
        node = crenode(a[i]);
        EnQueue(q,node);
    }
}

void printqueue (Queue q)
{
    if (q.first != NULL)
    {
        Node* node= q.first;
        while(node != NULL)
        {
            printNode(node);
            node=node->link;
        }
        cout<<"\n";
    }
}

void printNode(Node* node){
    cout<<node->data.id <<',';
    cout<<node->data.name <<',';
    cout<<node->data.quantity <<endl;
}

int lengthQueue(Queue q){
    int count = 0;
    Node* node= q.first;
    while(node!=NULL){
        count++;
        node=node->link;
    }
    return count;
}

void outItems (Queue &q, int n){
    if(lengthQueue(q)>n){
        for(int i=0;i<n;i++){
            Item data;
            int check_DeQueue = DeQueue(q,data);
        }
    }else
    {
        cout<<"So luong hang hoa xuat qua nhieu"<<endl;
    }
}

int Select_menu()
{
	int number = 0;
	cout << "\n\nChon menu: ";
	cin >> number;
	return number;
}

void Menu(){
	cout << "=================MENU================\n";
	cout << "1. Them - 1 hang hoa\n";
	cout << "2. Xuat - 1 hang hoa\n";
    cout << "3. Xuat - Nhieu hang hoa\n";
    cout << "4. Xem - Hang hoa chuan bi xuat kho\n";
    cout << "5. Xem - Tat ca hang hoa trong kho\n";
    cout << "Cac so khac Thoat Tim kiem\n";
	cout << "=====================================\n";
}

int Process_menu(Queue &q){
    Menu();
    int select = Select_menu();
    switch (select)
    {
    case 1:
        {
            Item new_item;
            cout<<"ma: ";
            cin>>new_item.id;
            cout<<"ten: ";
            getline(cin>>ws,new_item.name);
            cout<<"so luong: ";
            cin>>new_item.quantity;
            Node* new_node = crenode(new_item);
            EnQueue(q,new_node);
            return 0;
        }
    case 2:
        {
            Item data;
            int checkDeQueue = DeQueue(q,data);
            return 0;
        }
    case 3:
        {
            int n_item;
            cout<<"So luong hang hoa xuat"<<endl;
            cin>>n_item;
            outItems(q, n_item);
            return 0;
        }
    case 4:
        {
            Node* item_prepare_out = q.last;
            printNode(item_prepare_out);
            cout<<endl;
            return 0;
        }
    case 5:
        {
            printqueue(q);
            return 0;
        }
    default:
        {
            cout << "Thoat\n";
            exit(1);
            return 1;
        }
    }
}