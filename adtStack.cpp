#include <cstddef>
#include <iostream>

using namespace std;

struct Node{
    int data;
    Node *next;
    Node(int x):data(x),next(NULL){}
};

class Stacks{
private:
    Node* top;
public:
    Stacks():top(NULL){}

    void push(int x){
        Node* temp = new Node(x);
        if(top == NULL){
            top = temp;
        }else{
            temp->next = top;//add from the top
            top = temp;
        }
    }

    void pop(){
        if(top == NULL){
            cout << "List is Empty";
            return;
        }
        Node* temp = top;
        cout << "remove number: " << temp ->data; 
        top = top->next; //remove from the top
        delete temp;
    }

    void fronV(){
        if(top == NULL){
            cout << "List is Empty";
            return;
        }
        cout << "top: " << top->data; //view the top
    }

    void bottomV(){
        if(top == NULL){
            cout << "List is Empty";
            return;
        }
        Node* p = top;
            while(p->next != NULL){
                p = p->next;
            }
        cout << "bottom: " << p->data;
    }

    void displayAll(){
        if(top == NULL){
            cout << "List is Empty";
            return;
        }
        Node* p = top;
            while(p!=NULL){
                cout<< p->data << endl;
                p =p->next;
            }
    }
};

int menu(){
    int pick;
    cout << "\n1. Push" << endl;
    cout << "2. Pop" << endl;
    cout << "3. Top" << endl;
    cout << "4. Bottom" << endl;
    cout << "5. Display" << endl;
    cout << "6. Exit" << endl;
    cin >> pick;
    return pick;
}

int main(){
    Stacks u;
    int x;
    while(true){
    switch(menu()){
        case 1: cout << "Number to ADD: "; cin >> x; 
                u.push(x); break;
        case 2: u.pop(); break;
        case 3: u.fronV(); break;
        case 4: u.bottomV(); break;
        case 5: u.displayAll(); break;
        case 6: exit(0);
        default: cout << "INVALID INPUT";break;

    }   
    }
}