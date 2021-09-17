#include <iostream>
#include <stdio.h>
#include <cstring>
#include <iomanip>
#include <string.h>

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

void nhapmang(char* filename, sinhvien a[], int &n);
void xuatmang(sinhvien a[], int n);
void timsinhvien(sinhvien a[], int n, int x);
void tyle_nam_nu(sinhvien a[], int n);
void xepdtb(sinhvien a[], int n);
void change(sinhvien &a, sinhvien &b);
void xepten(sinhvien a[], int n);
int writefile (char* filename, sinhvien a[], int n);

int main()
{
    sinhvien a[MAX];
    int n;
    nhapmang("sv.csv",a,n);
    xuatmang(a,n);
    int x;
    cout<<"MSSV can tim : ";
    cin>>x;
    timsinhvien(a,n,x);
    tyle_nam_nu(a,n);
    cout<<"Xep theo DTB\n";
    xepdtb(a,n);
    xuatmang(a,n);
    cout<<"Xep ten A-Z\n";
    xepten(a,n);
    xuatmang(a,n);
    xepdtb(a,n);
    if (writefile("19469421.txt",a,n) == 0)
    {
        cout<<"Khong mo duoc file";
    }
    else
    {
        cout<<"Ghi file thanh cong";
    }
    return 0;
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
        printf("%-20d",i);
        while(token!= NULL)
        {
            printf("%d ",column);
            printf("%-20s",token);

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
        printf("\n");
    }
    n = i;
    fclose(fptr);
}

void xuatmang(sinhvien a[], int n)
{
    for (int i=0;i<n;i++)
    {
        cout<<"a["<<i<<"]= "<<a[i].mssv<<" ";
        cout<<""<<setw(20)<<a[i].hodem<<" ";
        cout<<""<<setw(20)<<a[i].ten<<" ";
        cout<<""<<setw(20)<<a[i].gioitinh<<" ";
        cout<<""<<setw(20)<<a[i].dtb<<"\n";
    }
}

void timsinhvien(sinhvien a[], int n, int x)
{
    bool flag=false;
    for (int i=0;i<n;i++)
    {
        if (x == a[i].mssv)
        {
            cout<<"Thong tin can tim:\n";
            cout<<"Ho va Ten: "<<a[i].hodem<<" "<<a[i].ten<<"\n";
            cout<<"Gioi tinh: "<<a[i].gioitinh<<"\n";
            cout<<"DTB: "<<a[i].dtb<<"\n";
            flag=true;
        }
    }
    if (flag==false)
    {
        cout<<"Khong tim thay MSSV\n";
    }
}

void tyle_nam_nu(sinhvien a[], int n)
{
    int count_nam = 0;
    int count_nu = 0;
    for (int i=0;i<n;i++)
    {
        string gioitinh=a[i].gioitinh;
        if (gioitinh.compare("Nam") == 0)
        {
            count_nam+=1;
        }
        if (gioitinh.compare("Nu") == 0)
        {
            count_nu+=1;
        }
    }
    cout<<"Ty le nam:"<<(float)count_nam/n<<"\n";
    cout<<"Ty le nu:"<<(float)count_nu/n<<"\n";
}

void xepdtb(sinhvien a[], int n)
{
    for (int i=0;i<n;i++)
    {
        for (int j=i+1;j<n;j++)
        {
            if (a[i].dtb<a[j].dtb)
            {
                change(a[i],a[j]);
            }
        }
    }
}

void change(sinhvien &a, sinhvien &b)
{
    sinhvien temp = a;
    a = b;
    b = temp;
}

void xepten(sinhvien a[], int n)
{
    for (int i=0;i<n;i++)
    {
        for (int j=i+1;j<n;j++)
        {
            if (tolower(a[i].ten[0]) > tolower(a[j].ten[0]))
            {
                change(a[i],a[j]);
            }
        }
    }
}

int writefile (char* filename, sinhvien a[], int n)
{
    FILE* fp = fopen(filename,"r+");

    if (!fp)
        return 0;

    for (int i=0;i<5;i++)
    {
        string fullname= a[i].hodem+" "+a[i].ten;
        fprintf(fp, "%d,%s,%d\n",i+1,fullname.c_str(),a[i].mssv);
        fprintf(fp,"\n");
    }
    fclose(fp);
    return 1;
}
