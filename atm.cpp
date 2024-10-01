#include <algorithm>
#include <cstddef>
#include <ctime>
#include <iostream>
#include <string>
#include <fstream>
#define key 11212

using namespace std;

struct Info{ //Info dont think about registration info
    int accountNo;
    int balance;
    string pin;    
    Info *next;
    Info(): accountNo(),balance(),pin(),next(NULL){}
};//used in transaction


class Transaction{
private:
    Info* head; //indicate alink list
    char c;
public:
    Transaction(): head(NULL){} //initialized head as NULL
    void add(Info s){ // add just to sample if its working
        Info* newAcc = new Info(s);
        Info* p = head;
        Info* q = head;
        while(p != NULL){
            q = p;
            p = p->next;
    }
       if(head == NULL){
            head = newAcc;
       }else{
            q->next = newAcc;
    }}
    int search(Info s){ //search for the account number
        Info* p = head;
        while (p != NULL && p->accountNo != s.accountNo) {
            p = p->next;
        }    
        if (p == NULL) {
            return 0;
        }else if(p->pin == s.pin){
            return 1;
        }else{
            return 2;
        }
        }
    void home(Info s){ //check if the password correct
        if(search(s) == 1){
             menu(s);
        }else if(search(s) == 2){//if incorrect it will go back
             cout << "Account Pin is incorrect" << endl;
        }else{ 
            cout << "Account Number is not found!" << endl;
        }       
    }
    int choice(){ //menu choice
        int pick;
        cout << "1. Deposit" << endl;
        cout << "2. Withdraw" << endl;
        cout << "3. Check Balance" << endl;
        cout << "4. Bank Transfer" << endl;
        cout << "5. Change Pin" << endl;
        cin >> pick;
        return pick;
    }
    void menu(Info s){
        int money;//here is the basics
        Info t;
        switch(choice()){
            case 1: cout << "Input how much deposit: "; cin >> money; deposit(s,money); break;
            case 2: cout << "Input how much withdraw: "; cin >> money; withdraw(s,money);break;
            case 3: balanceInquiry(s); break;
            case 4: cout << "Input transfer Account: "; cin >> t.accountNo; 
                    cout << "Input how much transfer: "; cin >> money; transfer(t,s,money);break;
            case 5: cout << "CHANGE PIN:\n"; changePin(s);
            default: cout << "Invalid Input";break;
        }
    }
    void balanceInquiry(Info s){ 
        Info* p = head;
        int pick;
        
        while (p->accountNo != s.accountNo) {
            p = p->next;
        }
        cout << "Account Balance: " << p->balance << endl;
        cout << "Do you want another transaction?\n1.) YES\n2.) NO\n"; 
        cin >> pick; // ask for transaction
        switch (pick) {
            case 1: menu(s);break; //comeback to menu if want another
            case 2: break; //home again
            default: balanceInquiry(s);
        }
    }
    void withdraw(Info s, int withdraw){ // withdraw with Info s to know the blance of wothdrawer
        Info* p = head;

        while (p->accountNo != s.accountNo) {
            p = p->next;
        }
        p->balance -= withdraw; 
        cout << "Withdrawal Successful!" << endl;
        cout << "Wait for the card!!!" << endl;
    }
    void deposit(Info s, int deposit){
        Info* p = head;
        int pick;
        while (p->accountNo != s.accountNo) {
            p = p->next;
        }
        p->balance += deposit;
        cout << "Deposit Successful!" << endl;
        balanceInquiry(s);//shows the balance
        }

    void transfer(Info transferAc, Info s, int transfer){
        Info* p = head;
        while (p != NULL && p->accountNo != transferAc.accountNo) {
            p = p->next;
        }
        if (p == NULL){
            cout << "The Account is not Enrolled" << endl;
        }else{
            p->balance += transfer;
            p = head;
            while (p != NULL && p->accountNo != s.accountNo) {
                p = p->next;
            }
            p->balance -= transfer;
            cout << "Transfer Successful!" << endl;
            balanceInquiry(s); //show the balnce after transfer
        }

    }
    void changePin(Info s){
        Info* p = head;
        string NewPin, NewPin1;
        while (p->accountNo != s.accountNo) {
            p = p->next;
        }
        cout << "Input recent password: ";cin >> s.pin;
        if (p->pin == s.pin){
            cout << "Input new password: ";cin >> NewPin;
            cout << "Input new password again: ";cin >> NewPin1;
            if (NewPin == NewPin1){
                p->pin = NewPin;
                cout << "Password changed successfully" << endl;
            }else{
                cout << "Password does not match" << endl;
                changePin(s);
            }
    }   else{
        cout << "Password is incorrect" << endl;
        changePin(s);
    }}


    void save(){
        fstream myFile;
        myFile.open("account.txt", ios::out);
        if(!myFile){
            cout<<"Unable to Open th File";
            cin.ignore();
            cin.get();
        }else{
            Info* p = head;
            while(p != NULL){
                myFile << p->accountNo <<endl;
                myFile << p->balance <<endl;
                myFile << p->pin <<endl;
                p = p->next;
        }
        myFile.close();
    }}
    void retrieve(){
        fstream myFile;
        myFile.open("account.txt", ios::in);
        if(!myFile){
            cout<<"Unable to Open the File";
            cin.ignore();
            cin.get();
        }else{
            Info s;
            while (myFile >> s.accountNo){
                myFile >> s.balance;
                myFile >> s.pin;

                myFile.ignore();
                add(s);
            }
        }
        myFile.close();
    }
    void encrypt() {
        if (head == NULL) {
            return;
        }
        Info* p = head;  // Initialize p to point to the head of the list
        while (p != NULL) {
            string encryptedPin;
            int size = p->pin.size();
            for (int i = 0; i < size; i++) {
                c = p->pin[i];
                c += key;
                encryptedPin += c;
        }
            p->pin = encryptedPin;
            p = p->next;
    }
}

    void decrypt(){
    if (head==NULL) {
        return;
    }else{
        Info* p = head;
        while (p != NULL) {
            string decryptedPin;
            int size = p->pin.size();
            for (int i = 0; i < size; i++) {
                c = p->pin[i];
                c -= key;
                decryptedPin += c;
    }
        p->pin = decryptedPin;
        p = p->next;
}
    }
	}
};

int menu(){
    int choice;
    cout << "1. Enroll Account" << endl;
    cout << "2. Use Account" << endl;
    cout << "3. Exit" << endl;
    cin >> choice;
    return choice;
}

int main(){
    Transaction t;  
    Info s;
    t.retrieve();
    t.decrypt();
    while (true) {
        switch (menu()) {
            case 1: cout << "Welcome to the Bank System!" << endl;
                    cout << "Input Account Number: ";cin >> s.accountNo;
                    cout << "Input pin: ";cin >> s.pin; s.balance = 5000;t.add(s);break;
            case 2: cout << "Welcome to the Bank System!" << endl;
                    cout << "Input Account Number: ";cin >> s.accountNo;
                    cout << "Input pin: ";cin >> s.pin; t.home(s);break;
            case 3:t.encrypt();t.save(); exit(0);
            default:cout << "Invalid Choice"; break;
        }
    
    }
    
}
