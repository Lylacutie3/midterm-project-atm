#include <iostream>
#include <string>

using namespace std;

struct Info{
    int accountNo;
    string name;
    int balance;
    int pin;
    Info *next;
};

class Transaction{
private:
    Info* head;
public:
    bool search(Info s){
        Info* p = head;
        while (p != NULL && p->accountNo != s.accountNo) {
            p = p->next;
        }    
        if (p != NULL) {
            return 0;
        if else(p->pin){
            return 1;
        }
    }
    void home(){
        Info s;
        cout << "Welcome to the Bank System!" << endl;
        cout << "Input Account Number: ";cin >> s.accountNo;
        cout << "Input pin: ";cin >> s.pin;
        if(search(s)){

        }else{
            cout << "Account Number is not found!" << endl;
        }       
    }

    void balanceInquiry(Info s){
        Info* p = head;
        int pick;
        
        while (p->accountNo != s.accountNo) {
            p = p->next;
        }
        cout << "Account Balance: " << p->balance << endl;
        cout << "Do you want another transaction?\n1.) YES 2.) NO"; 
        cin >> pick;
        switch (pick) {
            case 1: break;
            case 2: home(); break;
            default: balanceInquiry(s);
        }
    }



};