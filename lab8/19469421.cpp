#include <iostream>
#include <stdio.h>
#include <string.h>
#include <iomanip>
#include <cstring>

#define MAX 100

using namespace std;

typedef int MyData;

class BST {
private:
    struct Node
    {
        MyData data;
        Node* left;
        Node* right;
    };
    
    Node* root;
    
    Node* crenode(MyData init_data){
        Node* node = new Node;
        node->data = init_data;
        node->left = NULL;
        node->right = NULL;
        return node;
    }

    Node* insert(MyData init_data, Node* node_t){
        if(node_t==NULL)
            node_t = crenode(init_data);
        else if (init_data < node_t->data)
            node_t->left = insert(init_data,node_t->left);
        else if (init_data > node_t->data)
            node_t->right = insert(init_data,node_t->right);
        return node_t;
    }

    Node* search(Node* node_t, MyData data){
        if(node_t==NULL)
            return NULL;
        else if(data < node_t->data)
            return search(node_t->left,data);
        else if(data > node_t->data)
            return search(node_t->right,data);
        return node_t;
    }

    Node* delTree(Node* node_t){
        if(node_t==NULL)
            return NULL;
        delTree(node_t->left);
        delTree(node_t->right);
        delete node_t;
        return NULL;
    }

    Node* removeNode(MyData x, Node* node_t){
        Node* temp;
        if(!node_t)
            return NULL;
        else if (node_t->data > x)
            node_t->left = removeNode(x, node_t->left);
        else if (node_t->data < x)
            node_t->right = removeNode(x, node_t->right);
        else if(node_t->left && node_t->right){
            temp = findMin(node_t->right);
            node_t->data = temp->data;
            node_t->right = removeNode(temp->data,node_t->right);
        }
        else{
            temp = node_t;
            if (!node_t->left)
                node_t = node_t->right;
            else if (!node_t->right)
                node_t = node_t->left;
            delete temp;
        }
        return node_t;
    }

    int height(Node* node_t){
        if(node_t){
            int left_height = height(node_t->left);
            int right_height = height(node_t->right);
            int height_tree = left_height >= right_height ? left_height+1 : right_height+1;
            return height_tree;
        }else{
            return 0;
        }
    }

    int countNode(Node* node_t){
        if(!node_t)
            return 0; 
        int count = 1+countNode(node_t->left)+countNode(node_t->right);
        return count;
    }

    int countLeaf(Node* node_t){
        if (node_t){
            if(node_t->left==NULL && node_t->right==NULL)
                return 1;
            int count = countLeaf(node_t->left)+countLeaf(node_t->right);
            return count;
        }
        return 0;
    }

    MyData sumData(Node* node_t){
        if(!node_t)
            return 0; 
        int sum_node = node_t->data+sumData(node_t->left)+sumData(node_t->right);
        return sum_node;
    }

    Node* findMax(Node* node_t){
        if(!node_t)
            return NULL;
        else if(node_t->right==NULL)
            return node_t;
        else
            return findMax(node_t->right);
    }

    Node* findMin(Node* node_t){
        if(!node_t)
            return NULL;
        else if(node_t->left==NULL)
            return node_t;
        else 
            return findMin(node_t->left);
    }

    int countRange(Node* node_t, int low, int high){
        if(!node_t)
            return 0;
        if(node_t->data==high && node_t->data==low){
            cout<<node_t->data<<" ";
            return 1;
        }
        if(node_t->data>=low && node_t->data<=high){
            cout<<node_t->data<<" ";
            return 1+countRange(node_t->left,low,high)+countRange(node_t->right,low,high);
        }
        else if(node_t->data<low)
            return countRange(node_t->right,low,high);
        else if(node_t->data>high)
            return countRange(node_t->left,low,high);
    }

    void printLevel(Node* node_t, int level){
        if(node_t)
        {
            if (level == 0)
                cout<<node_t->data<<" ";
            else{
                printLevel(node_t->left,level-1);
                printLevel(node_t->right,level-1);
            }
        }
    }

    void printLeaf(Node* node_t){
        if (node_t){
            if(node_t->left==NULL && node_t->right==NULL)
                cout<<node_t->data<<" ";
            printLeaf(node_t->left);
            printLeaf(node_t->right);
        }
    }

    void print1Branch(Node* node_t){
        if(node_t){
            if(node_t->left==NULL && node_t->right==NULL)
                return;
            else if(node_t->left==NULL || node_t->right==NULL)
                cout<<node_t->data<<" ";
            print1Branch(node_t->left);
            print1Branch(node_t->right);
        }
    }

    int sum1Branch(Node* node_t){
        if(node_t){
            if(node_t->left==NULL && node_t->right==NULL)
                return 0;
            else if(node_t->left==NULL || node_t->right==NULL)
                return node_t->data;
            return sum1Branch(node_t->left)+sum1Branch(node_t->right);
        }
    }

    void print2Branch(Node* node_t){
        if(node_t){
            if(!(node_t->left==NULL || node_t->right==NULL))
                cout<<node_t->data<<" ";
            print2Branch(node_t->left);
            print2Branch(node_t->right);
        }
    }

    int sum2Branch(Node* node_t){
        if(node_t){
            if(!(node_t->left==NULL || node_t->right==NULL))
                return node_t->data + sum2Branch(node_t->left)+sum2Branch(node_t->right);
        }
    }

    void printLNR(Node* node_t){
        if(node_t!=NULL){
            printLNR(node_t->left);
            cout<<node_t->data<<" ";
            printLNR(node_t->right);
        }
    }

    void printNLR(Node* node_t){
        if(node_t!=NULL){
            cout<<node_t->data<<" ";
            printNLR(node_t->left);
            printNLR(node_t->right);
        }
    }

    void printLRN(Node* node_t){
        if(node_t!=NULL){
            printNLR(node_t->left);
            printNLR(node_t->right);
            cout<<node_t->data<<" ";
        }
    }

    void printRNL(Node* node_t){
        if(node_t){
            printRNL(node_t->right);
            cout<<node_t->data<<" ";
            printRNL(node_t->left);
        }
    }

public:
    BST(){
        root=NULL;
    }
    
    void insert_unique_t(MyData init_data){
        Node* node_check = search(root,init_data);
        if (node_check==NULL){
            root = insert(init_data,root);
        }
        else{
            cout<<"Nhap lai gia tri bi "<<node_check->data<<" :";
            cin>>init_data;
            insert_unique_t(init_data);
        }
    }

    void displayLNR(){
        printLNR(root);
        cout<<endl;
    }

    void displayNLR(){
        printNLR(root);
        cout<<endl;
    }

    void displayLRN(){
        printLRN(root);
        cout<<endl;
    }

    void displayRNL(){
        printRNL(root);
        cout<<endl;
    }

    void displayLevel(int level){
        if(!root)
            cout<<"Empty Tree!"<<endl;
        else
            if(level>=0 && level<height_t()){
                printLevel(root,level);
                cout<<endl;
            }else
                cout<<"Level invalid!!";
    }

    void displayAlllevel(){
        for(int i=0;i<height_t();i++){
            cout<<"Level "<<i<<": ";
            displayLevel(i);
        }
    }

    void displayLeaf(){
        if(!root)
            cout<<"Empty Tree!";
        else
            printLeaf(root);
        cout<<endl;
    }

    void display1Branch(){
        if(!root)
            cout<<"Empty Tree!";
        else 
            print1Branch(root);
        cout<<endl;
    }

    int sumData1Branch(){
        int sum = sum1Branch(root);
        return sum;
    }

    void display2Branch(){
        if(!root)
            cout<<"Empty Tree!";
        else
            print2Branch(root);
        cout<<endl;
    }

    int sumData2Branch(){
        int sum = sum2Branch(root);
        return sum;
    }

    void displayNodeRange5_18(){
        cout<<"Node Value Range (5-18): ";
        int count = countRange(root,6,17);
        cout<<endl;
        cout<<"Count Value Range (5-18): ";
        cout<<count<<endl;
    }

    int num_leaf_t(){
        int num_leaf = countLeaf(root);
        return num_leaf;
    }

    void inserts_unique_t(){
        MyData value;
        int n_element;
        cout<<"Nhap n du lieu: ";
        cin>>n_element;
        for (int i=0;i<n_element;i++){
            cout<<"insert node tree "<<i<<": ";
            cin>>value;
            insert_unique_t(value);
        }
    }

    void filetoBST(char* filename){
        FILE *fptr= fopen(filename, "r");
        if (fptr== NULL)
        {
            printf("Error! opening file");
            exit(1);
        }
        char line[200];
        char* token;
        while (fgets(line, sizeof(line), fptr))
        {
            if(line[0] != '\n')
            {
                token = strtok(line, ",");
                while(token!= NULL)
                {
                    root = insert(atoi(token),root);
                    token = strtok(NULL, ",");
                }
            }
        }
        fclose(fptr);
    }

    int height_t(){
        int height_tree = height(root);
        return height_tree;
    }

    int num_node_t(){
        if(!root)
            return 0;
        int num_node = countNode(root);
        return num_node;
    }

    MyData sumDataTree(){
        MyData sum_data = sumData(root);
        return sum_data;
    }

    MyData value_max_t(){
        Node* node_max = findMax(root);
        return node_max->data;
    }

    MyData value_min_t(){
        Node* node_min = findMin(root);
        return node_min->data;
    }

    void displayAfterRemove(MyData x){
        root = removeNode(x, root);
        cout<<"After Remove "<<x<<": ";
        printLNR(root);
        cout<<endl;
    }

    ~BST(){
        root = delTree(root);
    }
};


int main(){
    //1. Đọc file 'data.txt' và thêm các con số có trong file vào cây.
    BST t;
    string filename="data.txt";
    char* c_file = strcpy(new char[filename.length()+1],filename.c_str());
    t.filetoBST(c_file);

    //2. Xuất các giá trị trong cây ra theo 3 thứ tự preorder(NLR), inorder(LNR), postorder(LRN).
    cout<<"LNR: ";
    t.displayLNR();
    cout<<"LRN: ";
    t.displayLRN();
    cout<<"NLR: ";
    t.displayNLR();

    //3. Tính chiều cao của cây.
    cout<<"Height tree: ";
    cout<<t.height_t()<<endl;

    //4. Xuất ra các node ở mức thứ k của cây. Ứng với mỗi k khác nhau, xuất trên một dòng. (Lưu ý: 0 <= k < chiều cao cây).
    cout<<"Node At Level 3: ";
    t.displayLevel(3);

    //5. Xuất cây theo các mức từ thấp đến cao.
    cout<<"Node All Levels: ";
    t.displayAlllevel();

    //6. Đếm số nút trên cây.
    cout<<"Number node in tree: ";
    cout<<t.num_node_t()<<endl;

    //7. Đếm số nút lá trên cây và hiển thị các nút lá.
    cout<<"Number leaf in tree: ";
    cout<<t.num_leaf_t()<<endl;

    cout<<"Node Leaf: ";
    t.displayLeaf();

    //8. Tìm giá trị nhỏ nhất và lớn nhất.
    cout<<"Value max in tree: ";
    cout<<t.value_max_t()<<endl;

    cout<<"Value min in tree: ";
    cout<<t.value_min_t()<<endl;

    //9. Tính tổng các nút.
    cout<<"Sum value in tree: ";
    cout<<t.sumDataTree()<<endl;

    //10. Xuất ra các node có đúng một cây con.
    cout<<"Node 1 Branch: ";
    t.display1Branch();

    //11. Xuất ra các node có đúng hai cây con.
    cout<<"Node 2 Branch: ";
    t.display2Branch();

    //12. Đếm số lượng node có giá trị lớn hơn 5 và nhỏ hơn 18 trong cây, sau đó xuất giá trị của các node đó ra.
    t.displayNodeRange5_18();

    //13. Xuất ra giá trị của các node trong cây theo thứ tự giảm dần.
    cout<<"Sort Descending: ";
    t.displayRNL();

    //14. Liệt kê các node có 1 con và tính tổng các node đó.
    cout<<"Node 1 Branch: ";
    t.display1Branch();

    cout<<"Sum value 1 Branch in tree: ";
    cout<<t.sumData1Branch()<<endl;

    //15. Liệt kê các node có 2 con và tính tổng các node đó.
    cout<<"Node 2 Branch: ";
    t.display2Branch();

    cout<<"Sum value 2 Branch in tree: ";
    cout<<t.sumData2Branch()<<endl;

    //16. Lần lược xóa các node có giá trị là 15, 2, 5, 19. Mỗi lần xóa xong hãy xuất cây theo thứ tự inorder (LNR).
    t.displayAfterRemove(15);
    t.displayAfterRemove(2);
    t.displayAfterRemove(5);
    t.displayAfterRemove(19);

    return 0;
}