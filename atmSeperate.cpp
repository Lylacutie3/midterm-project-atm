#include <iostream>
#include <fstream>
#include <conio.h>
#include <ctime>
#include <string>
#include <windows.h>
#include <algorithm>
#include <cstddef>
#include <cctype>  // For toupper()
#define MIN_LENGTH 4
#define MAX_LENGTH 6
#define key 11212
using namespace std;

struct Account {
    string firstname;
    string lastname;
    int DD, MM, YY;
    int age;
    int balance;
    string accountNo;
    string number;
    string pin;
    Account():balance(5000){}
};

struct LinkList{
    Account info;
    LinkList* next;
    LinkList(Account x): info(x), next(NULL){}
};

class UsbFunctions{
private:
    string usbDirectory;
    string filePathUSB;
    Account acc;
public:
    string findUSBDrive() { // This function looks for a removable drive like USB
        for (char drive = 'A'; drive <= 'Z'; ++drive) { // Loop through all letters
            string driveName = string(1, drive) + ":\\";
            UINT driveType = GetDriveType(driveName.c_str()); // Use c_str() for the string

            if (driveType == DRIVE_REMOVABLE) {
                return string(driveName); // Return true if a removable drive is found
            }
        }
        return ""; // Return false if no removable drive is found
    }

    bool AccInitialize() { // This function will look for a specific file
        usbDirectory = findUSBDrive();
        if (usbDirectory.empty()) {
            return false; // Return false if no removable drive is found
        }

        filePathUSB = usbDirectory + "USBAccount.txt"; // Construct the file path
        return true; // Check if the file exists
    }


    bool fileExists() {
        ifstream file(filePathUSB);
        return file.good(); // Check if the file can be opened
    }

    void USBload(Account* acc) { //this function use to get info from file inside usb
        ifstream file(filePathUSB);//[6] it will open and read the file of the adress indicated

        if(!file){ //[7] if there is no file found it will return exit to the function
            return;
        }
        //[8] the if the file found it will read and input the value inside this acc
        file >> acc->accountNo;
        file >> acc->pin;

        file.close();//[9] close the file always to prevent corruption
        cout << "\nAccount data loaded from USB successfully." << endl;
    }

    void USBsave(Account acc) { //this function use to save the info inside the file from usb
    fstream file(filePathUSB, ios::out); //[]write if the file exist when not it will create and write
    if (!file) {
        cerr << "Error writing to file: " << filePathUSB << endl;
        return;//[] it will return if the file cant be open
    }
    //[] accountNo and Pin will be write inside the file
    file << acc.accountNo << endl;
    file << acc.pin << endl;

    file.close();
    cout << "Account data saved to USB successfully." << endl;
    }

    void manuallyEject(){ // this function is for manually eject
        //[]promt to eject usbhom
        cout << "Please manually eject your USB..."<<endl;
        while(AccInitialize()){ // [] this will wait until there is no file found
            Sleep(100); //use AccInitialize cause i where by this time we are inside the removable drive
            cout << ". o O o . o O o .";
            cout <<"\r";
            cout << "o O o . o O o . o";
            Sleep(100);
            cout <<"\r";
            cout << "O o . o O o . o O";
            Sleep(100);
            cout <<"\r";
        }
        system("cls");  //[] clear console after removing the file
        cout << "Thank you for using our bank!" << endl;
        Sleep(100);  //[] s  for sec to stay the prompt for sec and continue in home
    }

};

class Validation{
private:
    char c;
public:
    bool isempty(const char* input) {// this function check whether the array si empty
        return input[0] == '\0'; //[] check the first element and if its null then its empty
    }

    int get_length(const char* input) {//this function use get the lenght of an char array
        int length = 0;
        while (input[length] != '\0') {
            ++length;  // Count the number of characters until the null terminator
        }
        return length;
    }

    void backspace(char* input) { //this function use as backspace in (**) password
        int length = get_length(input);//[] get the lenght
        if (length > 0) {
            input[length - 1] = '\0';  //[] set the last character to null to pop or remove it
        }
    }

    void get_numeric_input(char *input) { //Censoredship of a input password
    while (true) {
        char ch = _getch(); // [] get character without printing it to the console

        if (ch == '\r') {  //[] if the user enter
            int length = get_length(input);//[] get the lenght
            if (length >= MIN_LENGTH && length <= MAX_LENGTH) { //[] check the lenght if is valid
                break; //[] when valid it will exit from the loop and accept the password
            } else {
               continue;//[]it will not continue unless its become valid
            }
        } else if (ch == '\b') {  // if user backspace
            if (!isempty(input)) {
                backspace(input);  //[] remove the last char input
                cout << "\b \b"; // [] erase the ** display from the console
            }
        } else if (ch >= '0' && ch <= '9') {  //only accept a numerical character as input
            int length = get_length(input);

            if (length < MAX_LENGTH) {  //
                input[length] = ch;  //[]store the character
                input[length + 1] = '\0';  //[] making space for next input
                cout << '*'; //[] print a ** in the console
                }
            }
        }
    }
    //add parameter to be usable
    int validationMoney(int maxSize){ //this function validate the input(number input only valid)
    int number = 0;
    int digitCount = 0;

    while(true){
        char ch = _getch();

        if(ch == '\r'){ //enter
            if (number == 0){ // [] when the value is 0
                continue; // it will just continue
            } else {
                break;//break if nots
            }
        }
        else if(ch == '\b'){ // backspace
            if (digitCount > 0) {
                number /= 10; //[] use to remove last number
                digitCount--; //[]reduce the digit count
                cout << "\b \b"; // []remove the last digit from the console
            }
        }
        else if(ch >= '0' && ch <= '9'){ //[] check the type if digit
            if(digitCount < maxSize) { // [] check if the input digit exceed
                if(ch == '0' && number == 0) {
                    continue; // [] make sure first input is not 0
                }
                number = number * 10 + (ch - '0'); // make the char to int
                digitCount++; // []increase digit count
                cout << ch; // [] display the digit in the console
            }
        } else {
            continue; //[] ignore invalid characters
        }
    }
        return number;//[]return acceptable input
    }

    int validationOthers(int maxSize){ //this function validate the input(number input only valid)
    int number = 0;
    int digitCount = 0;

    while(true){
        char ch = _getch();

        if(ch == '\r'){ //enter
            if (number == 0){ // [] when the value is 0
                continue; // it will just continue
            } else {
                break;//break if nots
            }
        }
        else if(ch == '\b'){ // backspace
            if (digitCount > 0) {
                number /= 10; //[] use to remove last number
                digitCount--; //[]reduce the digit count
                cout << "\b \b"; // []remove the last digit from the console
            }
        }
        else if(ch >= '0' && ch <= '9'){ //[] check the type if digit
            if(digitCount < maxSize) { // [] check if the input digit exceed
                number = number * 10 + (ch - '0'); // make the char to int
                digitCount++; // []increase digit count
                cout << ch; // [] display the digit in the console
            }
        } else {
            continue; //[] ignore invalid characters
        }
    }
        return number;//[]return acceptable input
    }

    string encrypt(string pin) { //encrypt pass before saving
            string encryptedPin;
            int size = pin.size();
            for (int i = 0; i < size; i++) {
                c = pin[i];
                c += key;
                encryptedPin += c;
            }
    return encryptedPin;
    }

string decrypt(string pin){ //decreypt all pin after retrieve
    string decryptedPin;
    int size = pin.size();
    for (int i = 0; i < size; i++) {
        c = pin[i];
        c -= key;
        decryptedPin += c;
    }
    return decryptedPin;
}

};

class Transaction : public UsbFunctions{
private:
    Validation v;
    LinkList *head;
public:
    Transaction():head(NULL){} //this function initialized head as NULL

    LinkList* getHead(){ //this is a getter function to acess head by other class
        return head;
    }
    void deleteLinklist() {
        while (head != NULL) {
            LinkList* temp = head; // Store the current head
            head = head->next; // Move head to the next node
            delete temp; // Delete the old head
        }
        head = NULL; // Set head to nullptr after deletion
    }

    bool findAccount(Account acc){
        LinkList *p = head;
        while(p!=NULL && p->info.accountNo != acc.accountNo){
            p = p-> next;
        }

        if(p!= NULL){
            return true;
        }else{
            return false;
        }
    }
    void add(Account s) { // Function to add a new account
        LinkList* newAcc = new LinkList(s); // Create a new node to be added
        LinkList* q = nullptr; // Previous node pointer
        LinkList* p = head; // Current node pointer

        if (head == NULL) { // If the list is empty
            head = newAcc; // Set head to the new node
            return;
        }

        // Traverse the list to find the correct position
        while (p != NULL && p->info.lastname < s.lastname) {
            q = p;
            p = p->next;
        }

        if (p == head) {
            newAcc->next = head;
            head = newAcc;
        } else if (p == NULL) {
            q->next = newAcc;
        } else {
            newAcc->next = p;
            q->next = newAcc;
        }
    }


    bool checkPass(Account s, string pin){ //check the input password if accurate
        LinkList* p = head;
        while (p->info.accountNo != s.accountNo) { //[]look for the account number
            p = p->next;
        }
        if(p->info.pin == pin && s.pin == pin) { //[]compare the input password to file and file
            return true; //[]return true if its accurate
        }else{
            return false; //[]false if not all the same
    }}

    void home(Account s, int x){ //input password
    char inputPin[MAX_LENGTH + 1] = "";
    LinkList *p = head;
    if(x<3){ //check the tries
        cout << "\nInput pin: "; //[]prompt to input pass
        inputPin[0] =  '\0';
        v.get_numeric_input(inputPin); //[]to display password as **
        if(checkPass(s,inputPin)){ //[]compare input pass
            while(p->info.accountNo != s.accountNo){
                p = p->next;
            }
            transac(p); //[] if the pasword correct it will let to continue in the transactions
        }else{
            home(s, x + 1); // []else it will let to input again
        }
    }else{
        cout << "\nenough tries.\n";
        return;//[]exit after enough tries and the password still wrong
    }}

    char choice(){//a function for transaction
        char pick;
        cout << "1. Deposit" << endl;
        cout << "2. Withdraw" << endl;
        cout << "3. Check Balance" << endl;
        cout << "4. Bank Transfer" << endl;
        cout << "5. Change Pin" << endl;
        pick = _getch();
        return pick;//[] return the user pick
    }

    void transac(LinkList *p){ //function to run user choice
        system("cls");
        switch(choice()){
            case '1':system("cls");deposit(p); break;//[] go to deposit function
            case '2':system("cls"); withdraw(p); break;
            case '3':system("cls"); balanceInquiry(p); anotherTransaction(p); break;
            case '4':system("cls"); transfer(p);break;
            case '5':system("cls"); changePin(p); break;
            case '6': return;
            default:transac(p);
            }
    }

    void deposit(LinkList *p){
        cout << "\nWarning! No coins only paper bill"<<endl; //[] warning for user
        cout << "\nInput how much deposit: ";
        int deposit = v.validationMoney(6); //[]validate the input

        if(deposit%100 == 0){//[]check for the amount input
            p->info.balance += deposit;
            cout << "\nDeposit Successful!" <<endl;
            Sleep(1000);
            balanceInquiry(p);
            anotherTransaction(p);
        }else{
            cout << "\nInvalid Amount Deposit" << endl;
            Sleep(1000);
            transac(p);
        }
    }

    void withdraw(LinkList *p){ // withdraw with Info s to know the blance of wothdrawer
        cout << "\nWarning! No coins only paper bill"<<endl; //[] warning for user
        cout << "\nInput how much withdraw: ";
        int withdraw = v.validationMoney(6); //[]validate the input

        if (withdraw%100 == 0){ //[]check if its multiple by a hundred
            if(p->info.balance>=withdraw){ //[]check if balance is enough
                p->info.balance -= withdraw;
                cout << "\nWithdraw Successful!" <<endl;
                Sleep(1000);
                balanceInquiry(p); //[]prompt the balance after withdraw
                return;
            }else{
                cout << "\nInsufficient Balance!!!" << endl;
                cout << "\nWithdraw unsaccessful!" <<endl;
                Sleep(1000);
                balanceInquiry(p); //[]prompt the balance available
                Sleep(1000);
                transac(p); //[]call transact again
            }
        }else{
            cout << "\nInvalid Amount Withdraw" << endl;
            Sleep(1000);
            transac(p); //[]call transact again
        }
    }

    void balanceInquiry(LinkList *p){ //this function show the balance
        cout << "\nAccount Balance: " << p->info.balance << endl;
    }

    void anotherTransaction(LinkList *p){ //ask for another transaction
        int pick;
        cout << "\nDo you want another transaction?\n1.) YES\n2.) NO\n";
        cin >> pick; //[] ask user for another transaction
        switch (pick) {
            case 1: transac(p);break; //[]go to menu if want another
            case 2: break; //[]home again //exit loop of Transac
        }
    }

    void transfer(LinkList *p){// this function is for transfer fund
        LinkList* t = head;

        //[]prompt warning and space to input accno
        cout << "\nYou only can transfer to enrolled Account" << endl;
        cout << "\nInput Account Number: ";
        string accountNo = to_string(v.validationOthers(6)); //[] make int to string

        while (t != NULL && t->info.accountNo != accountNo) {
            t = t->next;
        } //look for trnasAccount
        if(accountNo == p->info.accountNo){
            cout << "\nYou can not transfer on your Account." << endl;
            Sleep(1000);
            transac(p);
        }else if (t == NULL){
            cout << "\nThe Account is not Enrolled" << endl;
            Sleep(1000);
            transac(p);
        }else{ //[] ask fro transfer amount
            cout << "\nTransfer Amount: ";
            int amount = v.validationMoney(6);
            if (amount < p->info.balance){ //[] check if have enought balance
                t->info.balance += amount;
                p->info.balance -= amount;
                cout << "Transfer Successful" << endl;
                balanceInquiry(p);
                Sleep(1000);
                transac(p);
            }else{
                cout << "\nInsufficient Balance" << endl;
                Sleep(1000);
                transac(p);
            }
        }
    }

     void changePin(LinkList *p){ //inserted (datavalidation, censoredship)
        string NewPin, NewPin1;
        Account acc;
        char input1[MAX_LENGTH + 1] = ""; // Character array to store input //Enter Current Password
        char ch1, ch2, ch3;

        cout << "\nInput recent password: ";
        v.get_numeric_input(input1);
        cout<<"YOU TYPED:  "<<input1<<endl;
        acc.pin = input1; //data validation with censoredship
        if (p->info.pin == acc.pin){
            while(true){
                char input2[MAX_LENGTH + 1] = ""; // Verified
                char input3[MAX_LENGTH + 1] = ""; // Verified
                cout << "Input new password: ";

                v.get_numeric_input(input2); //data validation with censoredship

                cout<<"YOU TYPED:  "<<input2<<endl;
                NewPin =  input2;

                cout << "\nInput new password again: ";
                v.get_numeric_input(input3); //data validation with censoredship

                NewPin1 = input3;

                if (NewPin == NewPin1){
                    p->info.pin = NewPin;
                    acc.accountNo = p->info.accountNo;
                    acc.pin = NewPin;
                    cout << "\nPassword changed successfully\n\n" << endl;
                    acc.pin = v.encrypt(acc.pin);
                    USBsave(acc);
                    Sleep(1000);
                    break;
                }else{
                    cout << "\nPassword does not match" << endl;
                }
            }
        return;
        }else{
            cout << "\nPassword is incorrect" << endl;
            changePin(s);
        }
        anotherTransaction(p);
    }

void save() {// function save the file from pc
    fstream myFile("RegisteredAccountPC.txt", ios::out);
    if (!myFile.is_open()) {
        cerr << "\nError opening file for writing: " << endl;
        return;
    }

    LinkList* p = head;
        while (p != NULL) {
            myFile << p->info.lastname << endl;
            myFile << p->info.firstname << endl;
            myFile << p->info.DD << " " << p->info.MM << " " << p->info.YY << endl; // Save birthdate
            myFile << p->info.age << endl;
            myFile << p->info.number << endl;
            myFile << p->info.balance << endl;
            myFile << p->info.accountNo << endl;
            myFile << v.encrypt(p->info.pin) << endl;

            p = p->next;
        }

        myFile.close();
        cout << "successfully save!";
}


    void retrieve() {// function retreive the file from pc
        fstream myFile("RegisteredAccountPC.txt", ios::in);
        if (!myFile) {
            cout << "Unable to Open the File";
            return;
        }
        Account acc;
            while (getline(myFile, acc.lastname)) {
            myFile >> acc.firstname;
            myFile >> acc.DD >> acc.MM >> acc.YY; // Retrieve birthdate
            myFile >> acc.age;
            myFile >> acc.number;
            myFile >> acc.balance;
            myFile >> acc.accountNo;
            myFile >> acc.pin; // Retrieve account number

            myFile.ignore();
            acc.pin = v.decrypt(acc.pin);
            add(acc);
        }
            myFile.close();
            cout << "Account data loaded from PC successfully." << endl;
    }

};


class Register : public Transaction{
private:
    Validation v;
public:
void agecheck(Account &pAcc) {
    bool valid = false;
    int maxDays;
    time_t t = time(0);
    tm* now = localtime(&t);
    int currentYear = now->tm_year + 1900;
    int currentMonth = now->tm_mon + 1;
    int currentDay = now->tm_mday;

    do {
        system("cls");
        cout << "Enter your Birthdate (MM/DD/YYYY):\n";

        // MONTH validation
        do {
            cout << "MONTH (MM): ";
            pAcc.MM = v.validationOthers(2); // Validate a 2-digit month
            cout << endl;
            if (pAcc.MM > 12 || pAcc.MM <= 0) {
                cout << "Invalid Month. Please enter a valid month (1-12)." << endl;
                system("pause");
                system("cls"); cout << "Enter your Birthdate (MM/DD/YYYY):\n";

            }
        } while (pAcc.MM > 12 || pAcc.MM <= 0); // Repeat until valid

        // DAY validation
        do {
            cout << "DAY (DD): ";
            pAcc.DD = v.validationOthers(2); // Validate a 2-digit day
            cout << endl;
        maxDays = 31;
        if (pAcc.MM == 2) {//FEBRUARY
            maxDays = 29;

        } else if (pAcc.MM == 4 || pAcc.MM == 6 || pAcc.MM == 9 || pAcc.MM == 11) {
            maxDays = 30; // April, June, September, November have 30 days
        }

        // Check if the day is valid after gathering all inputs
        if (pAcc.DD > maxDays) {
            cout << "Invalid Day. Please enter a valid day (1-" << maxDays << ") for the month." << endl;
            system("pause");
            system("cls");
            cout << "Enter your Birthdate (MM/DD/YYYY):\n";
            cout<<"MONTH (MM): " << pAcc.MM << endl;
            valid = false; // Reset valid to false to trigger the loop again
        } else {
            valid = true; // Only set valid to true if all validations pass
        }
            }while(!valid);

        // YEAR validation
        do {
            cout << "YEAR (YYYY): ";
            pAcc.YY = v.validationOthers(4); // Validate a 4-digit year
            cout << endl;
            int reprint=1;//for reprinting
            // Check if the year is a four-digit number
            if (pAcc.YY < 1000 || pAcc.YY > 9999) {
                cout << "Invalid Year. Please enter a valid four-digit year." << endl;
                system("pause");

            } else if (pAcc.YY > currentYear || pAcc.YY <= 0) {
                cout << "Invalid Year. Please enter a valid year (must not be in the future)." << endl;
                system("pause");
            }
            if (reprint == 0){//error/validation
                system("cls");
                cout << "Enter your Birthdate (MM/DD/YYYY):\n";
                cout<<"MONTH (MM): " << pAcc.MM << endl;
                cout<<"DAY (DD): " <<pAcc.DD << endl;
            }
        } while (pAcc.YY < 1000 || pAcc.YY > 9999 || pAcc.YY > currentYear || pAcc.YY <= 0); // Repeat until valid

        if(pAcc.MM==2){
            bool isLeapYear = (pAcc.YY % 4 == 0 && (pAcc.YY % 100 != 0 || pAcc.YY % 400 == 0));
            maxDays = isLeapYear ? 29 : 28;
            if(pAcc.DD>maxDays){
                cout<<"year " << pAcc.YY << " is not a Leap Year" << endl;
                system("pause");
                valid = false;
                }
            }else{
                valid = true;
                    pAcc.age = currentYear - pAcc.YY;
                if (currentMonth < pAcc.MM || (currentMonth == pAcc.MM && currentDay < pAcc.DD)) {
                    pAcc.age--; // If birthdate hasn't occurred yet this year
                }

                        // Age validation
                    if (pAcc.age < 18) {
                        cout << "You must be at least 18 years old.\n";
                        system("pause");
                        valid = false; // Early return if age validation fails
                    } else if (pAcc.age > 100) {
                        cout << "Age too old\n";
                        valid = false;
                        system("pause");
                    }
                    else{
                        valid = true;
                    }
                }
    }while(!valid);
}


string getnumber() {
    system("cls");
    cout << "Enter your contact number: +639";
    return "+639" + to_string(v.validationOthers(10));
}

string name(){
string name;
char temp[100]; // Adjust size as needed
int index = 0;

    while (true) {
        char ch = _getch();

        if (ch == '\r') {
            if (index != 0) {
                temp[index] = '\0'; // Null-terminate the string
                break; // Valid length, exit loop
            }
            continue; // Invalid length
        } else if (ch == '\b' && !v.isempty(temp)) {// Ensure there's something to delete
            if (index != 0){
                index--; // Decrement index
                cout << "\b \b"; // Handle backspace display
            }
            } else if (isalpha(ch)) {
            temp[index] = toupper(ch); // Convert to uppercase and store
            cout << temp[index]; // Display uppercase character
            index++; // Increment index
        } else {
            continue; // Ignore invalid characters
        }
    }
return name = temp;
}

Account reg(){
    char input1[MAX_LENGTH + 1] = "";

    Account pAcc;

    // First Name collection with validation
    system("cls");
    cout << "What should we call you?" << endl;
    cout << "First Name: ";
    pAcc.firstname = name();

    // Last Name collection with validation
    system("cls");
    cout << "Last Name: ";
    pAcc.lastname = name();

    // Age Information
    system("cls");
    cout << "Age Information:" << endl;
    agecheck(pAcc);

    // Contact Number Information
    cout << "Contact Number Information:" << endl;
    pAcc.number = getnumber();
    system("cls");

    // Pin code
    cout << "Secure your account!" << endl;
    cout << "Please Enter a Pin code (6 digits): \n";
    v.get_numeric_input(input1);
    pAcc.pin = input1;
    system("cls");

    // Account number generation
    pAcc.accountNo = initializedAccNo();
    cout << "Account Successfully Created!\n" << endl;
    system("pause");

    return pAcc;
}

string initializedAccNo(){
    srand(time(0));//randomized number base on time
    string acc;
    LinkList* head;
    LinkList* p = getHead();

    for(int i = 0; i < 5; i++){
        char a = rand() % 9 + '0';//make it char
        acc += a; //add to the string
    }
        while(p!= NULL && p->info.accountNo != acc){
            p = p->next; //look for whether exist or not
        }
        if(p!= NULL && p->info.accountNo == acc){
            initializedAccNo(); // do it again if its exist
        }
        return acc; //return if its unique
    }

};

class Bank : public Register {
private:
    Validation v;
    Account acc;

public:
    void menu() {
        while (true) {
            deleteLinklist();
            retrieve();
            cout << "WELCOME TO LANDBANK!" << endl;

            while (!AccInitialize()) {
            }

            if (fileExists()) {
                USBload(&acc);  // Load account from USB
                acc.pin = v.decrypt(acc.pin);
                cout << "PIN: " << acc.pin << endl; // Clearer output

                // If account found, proceed to home
                if (findAccount(acc)) {
                    home(acc, 0);
                    save();
                    manuallyEject();
                } else {
                    cout << "\nAccount not enroll.\n";
                    Sleep(1000);
                    int pick;
                    cout << "\nDo you want to Enroll?.\n1.) YES\n2.) NO\n";
                    cin >> pick;
                    switch(pick){
                        case 1: acc = reg();add(acc);save();acc.pin = v.encrypt(acc.pin);
                                USBsave(acc);manuallyEject();break;
                        case 2: cout << "Hope you Enroll with us in the Future" << endl; Sleep(1000);
                                manuallyEject();break;
                        default: cout << "Invalid Option"; system("pause");break;
                    }
                }
            } else {
                cout << "\nAccount is not registered.\n";
                Sleep(1000);

                // Call registration process
                acc = reg();
                add(acc); // Add new account to the list
                save();

                // Encrypt PIN before saving
                acc.pin = v.encrypt(acc.pin);
                USBsave(acc);
                manuallyEject();
                Sleep(1000);
            }
        }
    }
};



int main(){
    Bank b;
    b.menu();
    return 0;
}
