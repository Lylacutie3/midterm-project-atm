#include <algorithm>
#include <cstddef>
#include <ctime>
#include <iostream>
#include <string>
#include <fstream>
#include <conio.h>
#define key 11212
#define MIN_LENGTH 4
#define MAX_LENGTH 6

using namespace std;

struct Info{ //Info dont think about registration info
    string accountNo;
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

    bool isempty(const char* input) {
        return input[0] == '\0';  // If the first character is null, the input is empty
    }

    void backspace(char* input) {
        int length = 0;
        while (input[length] != '\0') {
            ++length;  // Find the length of the character array
        }

        if (length > 0) {
            input[length - 1] = '\0';  // Set the last character to null to "pop" it
        }
    }

    int get_length(const char* input) {
        int length = 0;
        while (input[length] != '\0') {
            ++length;  // Count the number of characters until the null terminator
        }
        return length;
    }

    void get_numeric_input(char *input) { //Censoredship, legth and data validation
    while (true) {
        char ch = _getch(); // Get character without printing it to the console

        if (ch == '\r') {  // Enter key is pressed (carriage return)
            int length = get_length(input);
            if (length >= MIN_LENGTH && length <= MAX_LENGTH) {
                break;  // Accept input only if the length is between MIN_LENGTH and MAX_LENGTH
            } else {
                cout << "\nInput length must be between " << MIN_LENGTH << " and " << MAX_LENGTH << ". Please try again." << endl;
                input[0] = '\0'; // Reset the input
            }
        } else if (ch == '\b') {  // Backspace key is pressed
            if (!isempty(input)) {
                backspace(input);  // Remove last character from input
                cout << "\b \b"; // Erase the last asterisk from console
            }
        } else if (ch >= '0' && ch <= '9') {  // Only accept numeric characters
            int length = get_length(input);

            if (length < MAX_LENGTH) {  // Ensure we don't exceed the buffer size
                input[length] = ch;  // Store the character
                input[length + 1] = '\0';  // Null-terminate the character array
                cout << '*'; // Print an asterisk for each typed character
                }
            }
        }
    }


    int widdepValidation(){ //return value of real number
        int number=0;
        while(true){
            char ch = _getch();

            if(ch == '\r'){ //Enter breaks the loop
                if (number == 0){
                    continue;
                }else{
                    break;
                }
            }
            else if(ch == '\b'){ // using backspace
                if (number > 0) {
                number /= 10;
                cout << "\b \b"; // Move back, overwrite with space, and move back again
            }
            }
            else if(ch >='0' && ch <= '9'){
                if(ch == '0'){
                    if(number == 0)
                        continue;
                }
                number = number * 10 + (ch - '0');
                cout << ch; // Display the digit
            }else{
                continue;
            }
        }
        return number;
    }

    string initializedAccNo(){
    srand(time(0));//randomized number base on time
    string acc;
    Info* p = head;

    for(int i = 0; i < 5; i++){
        char a = rand() % 9 + '0';//make it char
        acc += a; //add to the string
    }

        while(p!= NULL && p->accountNo != acc){
            p = p->next; //look for whether exist or not
        }
        if(p!= NULL && p->accountNo == acc){
            initializedAccNo(); // do it again if its exist
        }
        return acc; //return if its unique
    }

    char intro() { //(menu function nasa labas siya ng class nilagay ko siya sa loob para sa data validation)
        char pick;
        system("cls");
            cout << "1. Enroll Account" << endl;
            cout << "2. Use Account" << endl;
            cout << "3. Exit" << endl;
            cout << "Press your choice: ";
            pick = _getch();
            return pick;
    }

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

    void home(Info s, int x){ //check if the password correct
    char inputPin[MAX_LENGTH + 1] = "";
        if(search(s) == 1){
            transac(s);
        }else if(search(s) == 2){//if incorrect it will go back
            cout << "\nAccount Pin is incorrect" << endl;
            if(x < 3){
                cout << "Input pin: ";
                inputPin[0] =  '\0';
                get_numeric_input(inputPin);
                s.pin = inputPin;
                home(s, x + 1);
            }else
                cout << "enought tries, wait for card...";
             
        }else{
            cout << "Account Number is not found!" << endl;
        }
    }

    char choice(){ //menu choice
        char pick;
        cout << "1. Deposit" << endl;
        cout << "2. Withdraw" << endl;
        cout << "3. Check Balance" << endl;
        cout << "4. Bank Transfer" << endl;
        cout << "5. Change Pin" << endl;
        pick = _getch();
        return pick;
    }

    void transac(Info s){ //(void menu siya dati pero pinalitan ko ng name "Transac")
        Info t;
        int money;
        system("cls");
        switch(choice()){
            case '1':system("cls"); cout << "Input how much deposit: "; money = widdepValidation();
                    deposit(s, money); cout << "Deposit Successful!" <<
                    endl; balanceInquiry(s); anotherTransaction(s); break;
            case '2':system("cls"); cout << "Input how much withdraw: "; money = widdepValidation();
                    withdraw(s, money);cout << "Withdrawal Successful!\n"
                    << "Wait for the card!!!" << endl; break;
            case '3':system("cls"); balanceInquiry(s); anotherTransaction(s); break;
            case '4':system("cls"); cout << "Input transfer Account: "; cin >> t.accountNo;
                    transfer(t,s);break;
            case '5':system("cls"); cout << "CHANGE PIN:\n"; changePin(s); break;
            case '6': return;
            default:transac(s);
            }
    }

    void balanceInquiry(Info s){ //hiniwalay ko yung nag-aask for another transaction
        Info* p = head;
        int pick;

        while (p->accountNo != s.accountNo) {
            p = p->next;
        }
        cout << "Account Balance: " << p->balance << endl;
    }

    void anotherTransaction(Info s){ //ask for another transaction
    int pick;
        cout << "Do you want another transaction?\n1.) YES\n2.) NO\n";
        cin >> pick; // ask for transaction
        switch (pick) {
            case 1: transac(s);break; //comeback to menu if want another
            case 2: break; //home again //exit loop of Transac
        }
    }

    void withdraw(Info s, int withdraw){ // withdraw with Info s to know the blance of wothdrawer
        Info* p = head;

        while (p->accountNo != s.accountNo) {
            p = p->next;
        }

        if(withdraw%100 == 0){
            if(withdraw > 20000){
                cout << "Withdrawal amount is too high. Please try again" << endl;
                anotherTransaction(s);
            }
            if(p->balance>=withdraw){ //check if balance is enough
                p->balance -= withdraw;
            }else{
                cout << "Insufficient Balance!!!" << endl;
                anotherTransaction(s);
            }
        }else{
            cout << "Amount should be a multiple of 100!!!" << endl;
            anotherTransaction(s);
        }
    }

    void deposit(Info s, int deposit){
        Info* p = head;

        while (p->accountNo != s.accountNo) {
            p = p->next;
        }

        if(deposit%100 == 0){
            p->balance += deposit;
        }else{
            cout << "Deposit amount should be a multiple of 100!!!" << endl;
        }
        }

    void transfer(Info transferAc, Info s){
        Info* t = head;
        Info* p = head;
        while (t != NULL && t->accountNo != transferAc.accountNo) {
            t = t->next;
        }
        if(transferAc.accountNo == s.accountNo){
            cout << "You can not transfer on your Account." << endl;
            anotherTransaction(s);
        }else if (t == NULL){
            cout << "\nThe Account is not Enrolled" << endl;
            anotherTransaction(s);
        }else{
            cout << "Transfer amout: ";
            int amount = widdepValidation();
            withdraw(s, amount); //the money will withdraw from thge user account since they will transfer it
            deposit(transferAc, amount); // it will add the money to input accNo
            cout << "Transfer Successful" << endl;
            balanceInquiry(s);
            anotherTransaction(s);
        }
    }

    void changePin(Info s){ //inserted (datavalidation, censoredship)
        Info* p = head;
        string NewPin, NewPin1;
        char input1[MAX_LENGTH + 1] = ""; // Character array to store input //Enter Current Password
        char ch1, ch2, ch3;
        while (p->accountNo != s.accountNo) {
            p = p->next;
        }
        cout << "Input recent password: ";
        get_numeric_input(input1);
        cout<<"YOU TYPED:  "<<input1<<endl;
        s.pin = input1; //data validation with censoredship
        if (p->pin == s.pin){
            while(true){
                char input2[MAX_LENGTH + 1] = ""; // Verified
                char input3[MAX_LENGTH + 1] = ""; // Verified
                cout << "Input new password: ";

                get_numeric_input(input2); //data validation with censoredship

                cout<<"YOU TYPED:  "<<input2<<endl;
                NewPin =  input2;

                cout << "Input new password again: ";
                get_numeric_input(input3); //data validation with censoredship

                NewPin1 = input3;

                if (NewPin == NewPin1){
                    p->pin = NewPin;
                    cout << "\nPassword changed successfully\n\n" << endl;
                    break;
                }else{
                    cout << "\nPassword does not match" << endl;
                }
            }

        }else{
            cout << "\nPassword is incorrect" << endl;
            changePin(s);
        }
        anotherTransaction(s);
    }


    void save(){
        encrypt();
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
        decrypt();
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
    void encrypt() { //encrypt pass before saving
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

    void decrypt(){ //decreypt all pin after retrieve
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

int main(){
    Transaction t;
    Info s;
    t.retrieve();
    t.decrypt();
    char inputPin[MAX_LENGTH + 1] = ""; // Character array to store input
    while (true) {
        switch (t.intro()) {
            case '1': system("cls");
                    cout << "Welcome to the Bank System! (REGISTRATION)" << endl;
                    cout << "Input Account Number: ";s.accountNo = t.initializedAccNo();
                    cout << s.accountNo; cout << "\nInput pin: ";
                    inputPin[0] =  '\0';
                    t.get_numeric_input(inputPin);
                    s.pin = inputPin;
                    s.balance = 5000;   t.add(s);
                    cout<<"\nREGISTERATION COMPLETE!" << endl;
                    system("pause");
                    break;
            case '2': system("cls");
                    cout << "Welcome to the Bank System!" << endl;
                    cout << "Input Account Number: ";cin >> s.accountNo;
                    cout << "Input pin: ";
                    inputPin[0] =  '\0';
                    t.get_numeric_input(inputPin);
                    s.pin = inputPin;
                     t.home(s, 1);
                     system("pause");
                     break;
            case '3':t.save();exit(0);
            default:cout << "Invalid Choice"; break;
        }
    }
}
