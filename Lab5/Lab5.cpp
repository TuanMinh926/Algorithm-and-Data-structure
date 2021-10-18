#include <iostream>
#include <stdio.h>
#include <cstring>
#include <iomanip>
#include <string.h>
#include <fstream>

#define MAX 100

using namespace std;

struct sinhvien
{
    int mssv;
    string hodem;
    string ten;
    string gioitinh;
    double dtb;
};

struct Node
{
    sinhvien data;
    Node* link;
};

struct List
{
    Node* head;
    Node* tail;
};

Node* crenode(sinhvien init_data);
void creList(List& l);
void addtail(List& l, Node* node);
int Select_menu();
void Menu_search();
void Process_menu_search(List l);
Node* search_mssv(List l, int x);
Node* search_ten(Node* node_start, string x);
void searches_ten(List l, string x);
void Menu_add();
void Process_menu_add(List l);
void add_sv(List& l);
void add_lst(List& l, List& l_add);
int removehead(List& l, sinhvien& x);
int remove_after(List& l, Node* node_previous, sinhvien& x);
void remove_sv(List& l,int mssv);
void Menu_update();
void Process_menu_update(List l,Node* sv);
void update_sv(List l, int mssv);
void Menu_sort();
void Process_menu_sort(List l);
void Sort_mssv(List lst);
void Sort_ten(List lst);
void Sort_dtb(List lst);
void change(sinhvien &a, sinhvien &b);
void nhapmang(char* filename, sinhvien a[], int &n);
void nhapList (sinhvien a[], int n, List& l);
void writefile(string filename,List l);
void printlist (List l);
void printNode(Node* node);
void Menu_main();
int Process_menu_main(List l);

int main(){

    // File doc,them, ghi vd: sv_add.csv
	// "=================MENU================"
	// "1. Hien thi danh sach"
	// "2. Tim Kiem"
    // "3. Them"
	// "4. Cap nhat 1 sinh vien"
	// "5. Xoa 1 sinh vien"
    // "6. Sap xep"
    // "7. Ghi file"
	// "Cac so khac Thoat Chuong Trinh"
	// "====================================="
    sinhvien a[MAX];
    int n;
    string filename;
    cout<<"Nhap ten file doc: ";
    getline(cin>>ws,filename);
    char* c_file;
    strcpy(c_file,filename.c_str());
    nhapmang(c_file,a,n);
    List lst;
    nhapList(a,n,lst);
    while(Process_menu_main(lst)!=1)
    {
        Process_menu_main(lst);
    }
    return 0;
}

Node* crenode(sinhvien init_data)
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

int Select_menu()
{
	int number = 0;
	cout << "\n\nChon menu: ";
	cin >> number;
	return number;
}

void Menu_search(){
	cout << "=================MENU================\n";
	cout << "1. Tim kiem - mssv\n";
	cout << "2. Tim kiem - Ten\n";
    cout << "Cac so khac Thoat Tim kiem\n";
	cout << "=====================================\n";
}

void Process_menu_search(List l){
    Menu_search();
    int select = Select_menu();
    switch (select)
    {
    case 1:
        {
            int x_mssv;
            cout<<"Nhap mssv:";
            cin>>x_mssv;
            Node* node_mssv = search_mssv(l,x_mssv);
            printNode(node_mssv);
            break;
        }
    case 2:
        {
            string x_ten;
            cout<<"Nhap ten:";
            cin>>x_ten;
            searches_ten(l,x_ten);
            break;
        }
    default:
        {
            cout << "Thoat\n";
            break;
        }
    }
}

Node* search_mssv(List l, int x)
{
    Node* node = l.head;
    while(node!=NULL && node->data.mssv != x)
    {
        node= node->link;
    }
    if (node!=NULL)
    {
        return node;
    }
    return NULL;
}

Node* search_ten(Node* node_start, string x)
{
    Node* node = node_start;
    while(node!=NULL && node->data.ten != x)
    {
        node= node->link;
    }
    if (node!=NULL)
    {
        return node;
    }
    return NULL;
}

void searches_ten(List l, string x)
{
    Node* node = search_ten(l.head,x);
    if(node != NULL){
        printNode(node);
        while(node != NULL){
            if (node->link!=NULL){
                node = search_ten(node->link,x);
                if(node != NULL){
                    printNode(node);
                }
            }
        }
    }
    else{
        cout<<"Khong tim thay";
    }
}

void Menu_add(){
	cout << "=================MENU================\n";
	cout << "1. Them 1 sinh vien\n";
	cout << "2. Them 1 danh sach sinh vien\n";
    cout << "Cac so khac Thoat Them\n";
	cout << "=====================================\n";
}

void Process_menu_add(List l){
    Menu_add();
    int select = Select_menu();
    switch (select)
    {
    case 1:
        {
            cout<<"Them sinh vien\n";
            add_sv(l);
            break;
        }
    case 2:
        {
            sinhvien a_add[MAX];
            int n_add;
            string fileadd;
            cout<<"Nhap ten file them: ";
            getline(cin>>ws,fileadd);
            char c_fileadd[30];
            strcpy(c_fileadd,fileadd.c_str());
            nhapmang(c_fileadd,a_add,n_add);
            List lst_add;
            nhapList(a_add,n_add,lst_add);
            add_lst(l,lst_add);
            break;
        }
    default:
        {
            cout << "Thoat\n";
            break;
        }
    }
}

void add_sv(List& l){
    Node* node_sv;
    sinhvien sv;

    cout<<"MSSV: ";
    cin>>sv.mssv;
    Node* check_sv = search_mssv(l,sv.mssv);
    if(check_sv == NULL){
        cout<<"Ho dem: ";
        getline(cin>>ws,sv.hodem);
        cout<<"Ten: ";
        cin>>sv.ten;
        cout<<"Gioi Tinh: ";
        cin>>sv.gioitinh;
        cout<<"DTB: ";
        cin>>sv.dtb;
        node_sv = crenode(sv);
        addtail(l,node_sv);
        Sort_mssv(l);
    }
    else{
        cout<<"Trung MSSV:\n";
        printNode(check_sv);
    }
}

void add_lst(List& l, List& l_add){
    int count_success=0;
    int count_error=0;
    if (l_add.head!=NULL){
        Node* node_sv = l_add.head;
        while(node_sv!=NULL){
            int mssv_add = node_sv->data.mssv;
            Node* check_sv = search_mssv(l,mssv_add);
            Node* node_add;
            sinhvien data_sv;
            removehead(l_add,data_sv);
            if(check_sv==NULL){
                node_add = crenode(data_sv);
                addtail(l,node_add);
                count_success++;
            }
            else{
                cout<<"SV trung:\n";
                cout<<"Danh sach chinh: ";
                printNode(check_sv);
                cout<<"Danh sach them: ";
                printNode(node_sv);
                count_error++;
            }
            node_sv = node_sv->link;
        }
        Sort_mssv(l);
    }
    else{
        cout<<"Danh sach them rong";
    }
    cout<<"So Luong SV them Thanh Cong:"<<count_success<<"/ That Bai:"<<count_error<<"\n";
}

int removehead(List& l, sinhvien& x)
{
    if (l.head!=NULL)
    {
        Node* node = l.head;
        x = node->data;
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

int remove_after(List& l, Node* node_previous, sinhvien& x){
    if(node_previous != NULL){
        Node* node_after = node_previous->link;
        if (node_after != NULL){
            if (l.tail==node_after)
                l.tail = node_previous;
            node_previous->link = node_after->link;
            x = node_after->data;
            delete node_after;
            return 1;
        }
        return 0;
    }
    return 0;
}

void remove_sv(List& l,int mssv){
    Node* node = l.head;

    if (node!=NULL){
        if (node->data.mssv==mssv){
            sinhvien data_sv;
            removehead(l,data_sv);
        }
        while(node!=NULL){
            if (node->link!=NULL){
                if(node->link->data.mssv==mssv){
                    sinhvien data_sv;
                    int check_remove = remove_after(l,node,data_sv);
                    if(check_remove == 0){
                        cout<<"Xoa thanh cong\n";
                    }
                    else{
                        cout<<"Xoa khong thanh cong\n";
                    }
                }
            }
            node = node->link;
        }
    }
    else{
        cout<<"Danh sach rong\n";
    }
}

void Menu_update() {
	cout << "=================MENU================\n";
	cout << "1. Cap nhat - mssv\n";
	cout << "2. Cap nhat - Ho dem\n";
    cout << "3. Cap nhat - Ten\n";
	cout << "4. Cap nhat - Gioi tinh\n";
	cout << "5. Cap nhat - Diem Trung Binh\n";
	cout << "Cac so khac Thoat Cap Nhat\n";
	cout << "=====================================\n";
}

void Process_menu_update(List l,Node* sv){
    Menu_update();
    int select = Select_menu();
    switch (select)
    {
    case 1:
        {
            int mssv_update;
            cout << "Nhap MSSV:";
            cin>>mssv_update;
            Node* check_sv = search_mssv(l, mssv_update);
            if (check_sv==NULL){
                sv->data.mssv = mssv_update;
            }
            else{
                cout<<"Nhap Trung\n";
                printNode(check_sv);
            }
            break;
        }
    case 2:
        {
            string hodem;
            cout << "Nhap Ho dem\n";
            getline(cin>>ws,hodem);
            sv->data.hodem = hodem;
            break;
        }
    case 3:
        {
            string ten;
            cout << "Nhap Ten\n";
            cin>>ten;
            sv->data.ten = ten;
            break;
        }
    case 4:
        {
            int gioitinh;
            cout << "Nhap Gioi Tinh\n";
            cout << "0 - Nam\n";
            cout << "1 - Nu\n";
            cin>>gioitinh;
            if (gioitinh == 0)
                sv->data.gioitinh = "Nam";
            else if (gioitinh == 1)
                sv->data.gioitinh = "Nu";
            else
                cout<<"Nhap sai Gioi Tinh";
            break;
        }
    case 5:
        {
            double dtb;
            cout << "Nhap Diem Trung Binh\n";
            cin>>dtb;
            if (dtb>=0 && dtb<=10)
                sv->data.dtb = dtb;
            else
                cout<<"Nhap sai";
            break;
        }
    default:
        {
            cout << "Thoat\n";
            break;
        }
    }
}

void update_sv(List l, int mssv){
    Node* sv = search_mssv(l, mssv);

    if (sv!=NULL){
        Process_menu_update(l,sv);
    }
    else{
        cout<<"MSSV khong ton tai";
    }
}

void Menu_sort() {
	cout << "=================MENU================\n";
	cout << "1. Sap Xep - mssv\n";
	cout << "2. Sap Xep - Ten\n";
    cout << "3. Sap Xep - Diem Trung Binh\n";
    cout << "Cac so khac Thoat Sap Xep\n";
	cout << "=====================================\n";
}

void Process_menu_sort(List l){
    Menu_sort();
    int select = Select_menu();
    switch (select)
    {
    case 1:
        {
            Sort_mssv(l);
            break;
        }
    case 2:
        {
            Sort_ten(l);
            break;
        }
    case 3:
        {
            Sort_dtb(l);
            break;
        }
    default:
        {
            cout << "Thoat\n";
            break;
        }
    }
}

void Sort_mssv(List lst)
{
    if (lst.head!=NULL)
    {
        Node* node1 = lst.head;
        while(node1!=NULL)
        {
            Node* node2 = node1->link;
            while(node2!=NULL)
            {
                if (node1->data.mssv > node2->data.mssv)
                {
                    change(node1->data, node2->data);
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

void Sort_ten(List lst)
{
    if (lst.head!=NULL)
    {
        Node* node1 = lst.head;
        while(node1!=NULL)
        {
            Node* node2 = node1->link;
            while(node2!=NULL)
            {
                if (node1->data.ten > node2->data.ten)
                {
                    change(node1->data, node2->data);
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

void Sort_dtb(List lst)
{
    if (lst.head!=NULL)
    {
        Node* node1 = lst.head;
        while(node1!=NULL)
        {
            Node* node2 = node1->link;
            while(node2!=NULL)
            {
                if (node1->data.dtb > node2->data.dtb)
                {
                    change(node1->data, node2->data);
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

void change(sinhvien &a, sinhvien &b)
{
    sinhvien temp = a;
    a = b;
    b = temp;
}

void nhapmang(char* filename, sinhvien a[], int &n)
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
                a[i].mssv= atoi(token) ;
            }
            if (column == 1){
                a[i].hodem= token ;
            }
            if (column == 2){
                a[i].ten= token ;
            }
            if (column == 3){
                a[i].gioitinh= token ;
            }
            if (column == 4){
                a[i].dtb= stod(token) ;
            }
            token = strtok(NULL, ",");
            column+=1;
        }
        i+=1;
    }
    n = i;
    fclose(fptr);
}

void nhapList (sinhvien a[], int n, List& l)
{
    creList(l);

    Node* node;
    for (int i=0;i<n;i++)
    {
        node = crenode(a[i]);
        addtail(l,node);
    }
}

void writefile(string filename,List l){
    ofstream fptr (filename);
    if (!fptr){
        cout<<"Error! writing file";
        exit(1);
    }
    
    Node* node = l.head;
    if (node!=NULL)
    {
        string line;
        fptr<<"mssv,Ho dem,Ten,Gioi Tinh,DTB"<<endl;
        while(node!=NULL){
            fptr<<node->data.mssv<<",";
            fptr<<node->data.hodem<<",";
            fptr<<node->data.ten<<",";
            fptr<<node->data.gioitinh<<",";
            fptr<<node->data.dtb<<endl;
            node = node->link;
        }
    }
    else{
        cout<<"Danh sach rong";
    }
    fptr.close();
}

void printlist (List l)
{
    if (l.head != NULL)
    {
        Node* node= l.head;
        while(node != NULL)
        {
            printNode(node);
            node=node->link;
        }
        cout<<"\n";
    }
}

void printNode(Node* node){
    cout<<node->data.mssv <<' ';
    cout<<""<<setw(20)<<node->data.hodem <<' ';
    cout<<node->data.ten <<' ';
    cout<<""<<setw(20)<<node->data.gioitinh <<' ';
    cout<<""<<setw(20)<<node->data.dtb <<endl;
}

void Menu_main() {
	cout << "=================MENU================\n";
	cout << "1. Hien thi danh sach\n";
	cout << "2. Tim Kiem\n";
    cout << "3. Them\n";
	cout << "4. Cap nhat 1 sinh vien\n";
	cout << "5. Xoa 1 sinh vien\n";
    cout << "6. Sap xep\n";
    cout << "7. Ghi file\n";
	cout << "Cac so khac Thoat Chuong Trinh\n";
	cout << "=====================================\n";
}

int Process_menu_main(List l){
    Menu_main();
    int select = Select_menu();
    switch (select)
    {
    case 1:
        {
            printlist(l);
            return 0;
        }
    case 2:
        {
            Process_menu_search(l);
            return 0;
        }
    case 3:
        {
            Process_menu_add(l);
            return 0;
        }
    case 4:
        {
            int mssv_update;
            cout<<"MSSV can cap nhat:\n";
            cin>>mssv_update;
            update_sv(l,mssv_update);
            return 0;
        }
    case 5:
        {
            int mssv_del;
            cout<<"MSSV xoa:\n";
            cin>>mssv_del;
            remove_sv(l,mssv_del);
            return 0;
        }
    case 6:
        {
            Process_menu_sort(l);
            return 0;
        }
    case 7:
        {
            string fileout;
            cout<<"Nhap ten file ghi:";
            cin>>fileout;
            writefile(fileout,l);
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
