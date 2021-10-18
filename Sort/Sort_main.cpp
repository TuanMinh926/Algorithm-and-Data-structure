#include <iostream>
#include <stdio.h>
#include <time.h>

#define MAX 1000


using namespace std;

void printArray (int a[], int n);
void bubbleSort (int a[], int n);
void quickSort (int a[], int start, int end);
void selectionSort (int a[], int n);
int find_imin(int a[],int istart, int iend);
void insertionSort(int a[], int n);
void change (int &a, int &b);

int main(){
    int a[7] = {5,7,1,2,8,4,8};
    // ,5,7,1,2,8,4,5,7,1,2,8,4,5,7,1,2,8,4,5,7,1,2,8,4,5,7,1,2,8,4,
    // 5,7,1,2,8,4,5,7,1,2,8,4,5,7,1,2,8,4,5,7,1,2,8,4,5,7,1,2,8,4,5,7,1,2,8,4,5,7,1,2,8,4,
    // 5,7,1,2,8,4,5,7,1,2,8,4,5,7,1,2,8,4,5,7,1,2,8,4,5,7,1,2,8,4,5,7,1,2,8,4,5,7,1,2,8,4,5,7,1,2,8,4,
    // 5,7,1,2,8,4,5,7,1,2,8,4,5,7,1,2,8,4,5,7,1,2,8,4,5,7,1,2,8,4,5,7,1,2,8,4,5,7,1,2,8};
    int n = sizeof(a)/sizeof(int);
    // clock_t start, end;
    // start = clock();
    // bubbleSort(a,n);
    // end = clock();
    // cout<<"Time process: "<<end-start<<endl;

    // int start = 0;
    // int end = n-1;
    // quickSort(a,start,end);

    // selectionSort(a,n);

    insertionSort(a,n);
    printArray(a,n);
    return 0;
}

void printArray (int a[], int n){
    for (int i=0;i<n;i++){
        cout<<a[i]<<" ";
    }
    cout<<""<<endl;
}

void bubbleSort (int a[], int n){
    for (int i=0;i<n;i++){
        for (int j=n;j>i;j--){
            if (a[j-1]>a[j])
                change(a[j-1],a[j]);
        }
    }
}

void quickSort (int a[], int start, int end){
    int i,j,x;
    if (start>end) return;
    x = (start+end)/2;
    i = start; j = end;
    cout<<i<<" "<<x<<" "<<j<<endl;
    while (i<j)
    {
        while(a[i]<a[x]) i++;
        while(a[j]>a[x]) j--;
        if (i<=j){
            cout<<a[i]<<" "<<a[j]<<endl;
            change(a[i],a[j]);
            i++;
            j--;
            cout<<"Loop"<<i<<" "<<x<<" "<<j<<endl;
        }
    }
    if(start<j) quickSort(a,start,j);
    if(i<end) quickSort(a,i,end);
}

void selectionSort (int a[], int n){
    int imin;
    for (int i=0;i<n;i++){
        imin = find_imin(a,i,n-1);
        change(a[imin],a[i]);
    }
}
int find_imin(int a[],int istart, int iend){
    int imin = istart;
    for(int i=istart;i<=iend;i++){
        if (a[imin]>a[i]) imin = i;
    }
    return imin;
}

void insertionSort(int a[], int n){
    int temp;
    for(int i=1;i<n;i++){
        temp=a[i];
        cout<<temp<<endl;
        int j= i-1;
        while(j>=0){
            if(a[j]>a[j+1]) change(a[j],a[j+1]);
            j--;
        }
        change(temp,a[j]);
    }
}

void change (int &a, int &b){
    int temp = a;
    a = b;
    b = temp;
}