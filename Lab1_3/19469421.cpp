#include <iostream>
#include <stdio.h>
#include <vector>
#include <algorithm>

#define MAX 100

using namespace std;

struct phanso
{
    int tu;
    int mau;
    int soluong=0;
};

void nhapmang(char* filename, phanso a[], int &n);
void xuatmang(phanso a[], int n);
void timphanso(phanso a[],phanso x, int n);
void timphanso_1_4(phanso a[],vector<phanso> y, int n);
int frequency (vector<phanso> a,phanso x);
void value_counts (vector<phanso> x);
int writefile (char* filename, phanso a[], int n);

int main()
{
    phanso a[MAX];
    int n;
    nhapmang("phanso.dat",a,n);
    xuatmang(a,n);
    phanso x;
    cout<<"Nhap phan so can tim:\n";
    cout<<"Nhap tu:";
    cin>>x.tu;
    cout<<"Nhap mau:";
    cin>>x.mau;
    timphanso(a,x,n);
    vector<phanso> y;
    timphanso_1_4(a,y,n);
    return 0;
}

void nhapmang(char* filename, phanso a[], int &n)
{
    FILE* fp = fopen(filename,"r+");

    fscanf(fp, "%d", &n);
    for (int i=0;i<n;i++)
    {
        fscanf(fp, "%d %d",&a[i].tu,&a[i].mau);
    }
    fclose(fp);
}

void xuatmang(phanso a[], int n)
{
    for (int i=0;i<n;i++)
    {
        cout<<"a["<<i<<"]= "<<a[i].tu<<"/"<<a[i].mau<<" = "<<(float)a[i].tu/a[i].mau<<"\n";
    }
}

void timphanso(phanso a[],phanso x, int n)
{
    int count_x=0;

    for (int i=0;i<n;i++)
    {
        if (x.tu==a[i].tu && x.mau==a[i].mau)
        {
            cout<<"phan so "<<x.tu<<"/"<<x.mau<<" nam index: "<<i<<"\n";
            count_x+=1;
        }
    }

    if (count_x==0)
    {
        cout<<"Khong tim thay\n";
    }
}

void timphanso_1_4(phanso a[],vector<phanso> x, int n)
{
    bool flag=true;
    int count_x = 0;

    for (int i=0;i<n;i++)
    {
        float one_four = (float)a[i].tu/a[i].mau;
        if (one_four == 0.25)
        {
            flag=true;
            x.push_back(a[i]);
        }
    }
    if (flag==false)
    {
        cout<<"Khong tim thay";
    }
    else
    {
        for (int i=0; i<x.size();i++)
        {
            for (int j=i+1; j<x.size(); j++)
            {
                if (x[i].tu==x[j].tu && x[i].mau==x[j].mau)
                {
                    phanso temp = x[j];
                    x[j] = x[i+1];
                    x[i+1] = temp;
                }
            }
            x[i].soluong= frequency(x, x[i]);
        }
        value_counts (x);
    }
}

int frequency (vector<phanso> a,phanso x)
{
    int count_x=0;

    for (int i=0;i<a.size();i++)
    {
        if (x.tu==a[i].tu && x.mau==a[i].mau)
        {
            count_x+=1;
        }
    }
    return count_x;
}

void value_counts (vector<phanso> x)
{
    vector<phanso> counts;
    phanso temp = x[0];
    for (int i=0;i<x.size();i++)
    {
        if (x[i].tu==temp.tu && x[i].mau==temp.mau)
        {
            temp = x[i];
        }
        else
        {
            cout<<""<<temp.tu<<"/"<<temp.mau<<" "<<temp.soluong<<"\n";
            counts.push_back(temp);
            temp = x[i];
        }
        if (i == x.size())
        {
            cout<<""<<temp.tu<<"/"<<temp.mau<<" "<<temp.soluong<<"\n";
            counts.push_back(temp);
        }
    }
    int n = counts.size();
    phanso a[n];
    copy(counts.begin(),counts.end(),a);
    if (writefile("19469421.txt",a,n) == 0)
    {
        cout<<"Khong mo duoc file";
    }
    else
    {
        cout<<"Ghi file thanh cong";
    }
}
int writefile (char* filename, phanso a[], int n)
{
    FILE* fp = fopen(filename,"r+");

    if (!fp)
        return 0;

    fprintf(fp,"19469421-Pham Minh Tuan\n");
    fprintf(fp,"\n");
    for (int i=0;i<n;i++)
    {
        fprintf(fp, "%d/%d %d\n",a[i].tu,a[i].mau,a[i].soluong);
        fprintf(fp,"\n");
    }
    fclose(fp);
    return 1;
}





