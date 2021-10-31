#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <cstring>
#include <iomanip>
#include <string.h>
#include <locale>
#include <math.h>
#include <typeinfo>

using namespace std;

struct Node{
    float data;
    Node *link;
};

struct Stack{
    Node* top;
};

/** Stack Function*/
Stack InitStack();
Node* InitNode(float init_data);
bool IsEmpty(Stack s);
float Pop(Stack &s);
void Push(Stack &s, float value);

// Tính giá trị biểu thức từ một chuỗi
float CalculatePosfix_plus(string postfix_string);
// Tính giá trị nhiều biểu thức từ file
void CalculatePosfixes(string file_input, string file_output);

/************************************************************/
int main(){
    CalculatePosfixes(string("posfix.txt"), string("msv.txt"));

    return 0;
}
/************************************************************/
Stack InitStack(){
    Stack s;
    s.top = NULL;
    return s;
}

Node* InitNode(float init_data)
{
    Node* node = new Node;
    node->data = init_data;
    node->link = NULL;
    return node;
}

bool IsEmpty(Stack s){
    return (s.top == NULL);
}

float Pop(Stack &s){
    if (IsEmpty(s) == false){
        float data = s.top->data;
        Node* node_pop = s.top;
        s.top =s.top->link;
        delete(node_pop);
        return data;
    }
    else{
        cout << "Stack is Empty" << endl;
    }
}

void Push(Stack &s, float value){
    Node* node = InitNode(value);
    if (IsEmpty(s) == true){
        s.top= node;
    }
    else{
        node->link = s.top;
        s.top = node;
    }
}

float CalculatePosfix_plus(string line){

    Stack s;
    s = InitStack();
    stringstream postfix_string(line);
    string token;
    while(postfix_string>>token){

        if (isdigit(token[0])){
            Push(s,stof(token));
        }
        else{
            float a = Pop(s);
            float b = Pop(s);
            float result;

            if(token == string("+")){
                result = b + a;
            }else if (token == string("-")){
                result = b - a;
            }else if (token == string("*")){
                result = b * a;
            }else if (token == string("/")){
                result = b / a;
            }else if (token == string("^")){
                result = pow(b,a);
            }else{
                cout<<"Error!!";
            }
            Push(s,result);
        }
    }

    return Pop(s);
}

void CalculatePosfixes(string file_input, string file_output){
    fstream fi(file_input);
    fstream fo;
    fo.open(file_output, ios::out);

    if (!fi || !fo){
        cout<<"Error! opening file"<<endl;
    }
    
    float result;
    for(string line;getline(fi,line);){
        string posfix_string = line;

        result = CalculatePosfix_plus(posfix_string);
        cout<<result<<endl;
        fo << result<<endl;

    }

    fi.close();
    fo.close();
}