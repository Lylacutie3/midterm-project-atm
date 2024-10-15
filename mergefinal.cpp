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
    Account():accountNo("00000"),balance(5000){}
};

struct LinkList{
    Account info;
    LinkList* next;
    LinkList(Account x): info(x), next(NULL){}
};


class Transaction{
private:
    LinkList *head;
    char c;
public:
    Transaction():head(NULL){} //initialized head as NULL
    LinkList* getHead(){ //get the head to acess by the other class
        return head;
    }

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

int widdepValidation(int maxSize){ // maxSize limits the number of digits
    int number = 0;
    int digitCount = 0;

    while(true){
        char ch = _getch();

        if(ch == '\r'){ // Enter breaks the loop
            if (number == 0){
                continue;
            } else {
                break;
            }
        }
        else if(ch == '\b'){ // Using backspace
            if (digitCount > 0) {
                number /= 10;
                digitCount--; // Decrease digit count
                cout << "\b \b"; // Move back, overwrite with space, and move back again
            }
        }
        else if(ch >= '0' && ch <= '9'){
            if(digitCount < maxSize) { // Ensure input does not exceed maxSize
                if(ch == '0' && number == 0) {
                    continue; // Avoid leading zeros
                }
                number = number * 10 + (ch - '0');
                digitCount++; // Increase digit count
                cout << ch; // Display the digit
            }
        } else {
            continue; // Ignore invalid characters
        }
    }
    return number;
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

   void add(Account s){ // add just to sample if its working
        LinkList* newAcc = new LinkList(s);
        LinkList* q, *p;
       if(head == NULL){
            head = newAcc;
       }else{
            q=p=head;
            while(p != NULL){
            q = p;
            p = p->next;
            }
            q->next = newAcc;
    }
}


    void home(Account s, int x){ //check if the password correct
    char inputPin[MAX_LENGTH + 1] = "";
    if(x<3){
        cout << "\nInput pin: ";
        inputPin[0] =  '\0';
        get_numeric_input(inputPin);
        if(search(s,inputPin)){
            transac(s);
        }else{
            home(s, x + 1);
        }
    }else{
        cout << "\nenough tries, wait for your card...";
        return;
    }

    }


    bool search(Account s, string pin){ //search for the account number
        LinkList* p = head;
        while (p->info.accountNo != s.accountNo) {
            p = p->next;
        }
        if(p->info.pin == pin && s.pin == pin) {
            return true;
        }else{
            return false;
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

    void transac(Account s){ //(void menu siya dati pero pinalitan ko ng name "Transac")
        Account t;
        int money;
        system("cls");
        switch(choice()){
            case '1':system("cls"); cout << "Input how much deposit: "; money = widdepValidation(6);//6 digit input
                    deposit(s, money); cout << "Deposit Successful!" <<
                    endl; balanceInquiry(s); anotherTransaction(s); break;
            case '2':system("cls"); cout << "Input how much withdraw: "; money = widdepValidation(6);//6 digit input
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

    void balanceInquiry(Account s){ //hiniwalay ko yung nag-aask for another transaction
        LinkList* p = head;
        int pick;

        while (p->info.accountNo != s.accountNo) {
            p = p->next;
        }
        cout << "Account Balance: " << p->info.balance << endl;
    }

    void anotherTransaction(Account s){ //ask for another transaction
    int pick;
        cout << "Do you want another transaction?\n1.) YES\n2.) NO\n";
        cin >> pick; // ask for transaction
        switch (pick) {
            case 1: transac(s);break; //comeback to menu if want another
            case 2: break; //home again //exit loop of Transac
        }
    }

    void withdraw(Account s, int withdraw){ // withdraw with Info s to know the blance of wothdrawer
        LinkList* p = head;

        while (p->info.accountNo != s.accountNo) {
            p = p->next;
        }

        if(withdraw > 20000){
            cout << "Withdrawal amount is too high. Please try again" << endl;
            anotherTransaction(s);
        }
        if(withdraw%100 == 0 && withdraw >= 500){
            if(p->info.balance>=withdraw){ //check if balance is enough
                p->info.balance -= withdraw;
            }else{
                cout << "Insufficient Balance!!!" << endl;
                anotherTransaction(s);
            }
        }else{
            cout << "Amount should be a multiple of 100!!!" << endl;
            anotherTransaction(s);
        }
    }

    void deposit(Account s, int deposit){
        LinkList* p = head;

        while (p->info.accountNo != s.accountNo) {
            p = p->next;
        }

        if(deposit%100 == 0){
            p->info.balance += deposit;
        }else{
            cout << "Deposit amount should be a multiple of 100!!!" << endl;
        }
        }

    void transfer(Account transferAc, Account s){
        LinkList* t = head;
        LinkList* p = head;
        while (t != NULL && t->info.accountNo != transferAc.accountNo) {
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
            int amount = widdepValidation(10);
            withdraw(s, amount); //the money will withdraw from thge user account since they will transfer it
            deposit(transferAc, amount); // it will add the money to input accNo
            cout << "Transfer Successful" << endl;
            balanceInquiry(s);
            anotherTransaction(s);
        }
    }

    void changePin(Account s){ //inserted (datavalidation, censoredship)
        LinkList* p = head;
        string NewPin, NewPin1;
        char input1[MAX_LENGTH + 1] = ""; // Character array to store input //Enter Current Password
        char ch1, ch2, ch3;
        while (p->info.accountNo != s.accountNo) {
            p = p->next;
        }
        cout << "Input recent password: ";
        get_numeric_input(input1);
        cout<<"YOU TYPED:  "<<input1<<endl;
        s.pin = input1; //data validation with censoredship
        if (p->info.pin == s.pin){
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
                    p->info.pin = NewPin;
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


void save() {
    ofstream myFile("RegisteredAccountPC.txt", ios::out);
    if (!myFile.is_open()) {
        cerr << "Error opening file for writing: " << endl;
        return;
    }

    LinkList* p = head;
    while (p != NULL) {
        myFile << p->info.firstname << endl;
        myFile << p->info.lastname << endl;
        myFile << p->info.DD << " " << p->info.MM << " " << p->info.YY << endl; // Save birthdate
        myFile << p->info.age << endl;
        myFile << p->info.number << endl;
        myFile << p->info.balance << endl;
        myFile << p->info.accountNo << endl;
        myFile << encrypt(p->info.pin) << endl;

        p = p->next;
    }

    myFile.close();
}
void retrieve() {
    ifstream myFile("RegisteredAccountPC.txt", ios::in);
    if (!myFile) {
        cout << "Unable to Open the File";
        return;
    }
    Account acc;
    while (getline(myFile, acc.firstname)) {
        myFile >> acc.lastname;
        myFile >> acc.DD >> acc.MM >> acc.YY; // Retrieve birthdate
        myFile >> acc.age;
        myFile >> acc.number;
        myFile >> acc.balance;
        myFile >> acc.accountNo;
        myFile >> acc.pin; // Retrieve account number

        myFile.ignore();
        acc.pin = decrypt(acc.pin);
        add(acc);
    }
    myFile.close();
    cout << "Account data loaded from PC successfully." << endl;
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


class Atm {
private:
    Transaction trans;
    string usbDirectory;
    string filePathUSB;
    string filePathPC;
    int accountCount;     // To track the number of registered accounts
    Account acc;
public:
    void agecheck(Account&);
    string getnumber();
    string name();
    void reg();
    void USBsave(Account acc);
    void USBload(Account* acc);
    bool Card();
    string initializedAccNo();
    bool EjectUSB(const string& driveLetter);

    string findUSBDrive() {
        char drive = 'A';
        char driveName[] = "A:\\";

        for (drive = 'A'; drive <= 'Z'; ++drive) {
            driveName[0] = drive;
            UINT driveType = GetDriveType(driveName);
            if (driveType == DRIVE_REMOVABLE) {
                return string (driveName);}
        }
        return "";
    }

    bool AccInitialize(){
        usbDirectory = findUSBDrive();
        if (usbDirectory.empty()){
            return false;
        }
        filePathUSB = usbDirectory + "\\USBAccount.txt";
        return true;
    }

void menu() {
    string F = "F";
    while (true) {
        trans.retrieve();
        LinkList* p = trans.getHead();
        system("cls");

        Account acc;
        cout << "WELCOME TO LANDBANK!";

        // Ensure account initialization before proceeding
        while (!AccInitialize()) {
        }

        // Load account from USB
        USBload(&acc);
        acc.pin = trans.decrypt(acc.pin);

        // Search for account in the linked list
        while (p != NULL && p->info.accountNo != acc.accountNo) {
            p = p->next;
        }

        // If account is not found
        if (p == NULL) {
            cout << "\nAccount is not enrolled\n";
            cout << "Press any key to register.";
            cin.get();
            reg();  // Call registration process
        } else {
            // Account found, proceed to home menu
            trans.home(acc, 0);
            EjectUSB(F);
        }
    }
}

};

bool Atm:: EjectUSB(const string& driveLetter) {
    string volumePath = "\\\\.\\" + driveLetter + ":";
    HANDLE hVolume = CreateFileA(volumePath.c_str(),
                                 GENERIC_READ | GENERIC_WRITE,
                                 FILE_SHARE_READ | FILE_SHARE_WRITE,
                                 NULL,
                                 OPEN_EXISTING,
                                 0,
                                 NULL);

    if (hVolume == INVALID_HANDLE_VALUE) {
        cerr << "Error: Unable to open the drive. Check if the drive letter is correct." << std::endl;
        return false;
    }

    DWORD bytesReturned = 0;
    if (!DeviceIoControl(hVolume, FSCTL_LOCK_VOLUME, NULL, 0, NULL, 0, &bytesReturned, NULL)) {
        cerr << "Error: Unable to lock the volume." << std::endl;
        CloseHandle(hVolume);
        return false;
    }

    if (!DeviceIoControl(hVolume, FSCTL_DISMOUNT_VOLUME, NULL, 0, NULL, 0, &bytesReturned, NULL)) {
        cerr << "Error: Unable to dismount the volume." << std::endl;
        CloseHandle(hVolume);
        return false;
    }

    if (!DeviceIoControl(hVolume, IOCTL_STORAGE_EJECT_MEDIA, NULL, 0, NULL, 0, &bytesReturned, NULL)) {
        cerr << "Error: Unable to eject the media." << std::endl;
        CloseHandle(hVolume);
        return false;
    }

    cout << "USB drive " << driveLetter << ": successfully ejected." << std::endl;
    CloseHandle(hVolume);
    return true;
}

void Atm::agecheck(Account &pAcc) {
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
            pAcc.MM = trans.widdepValidation(2); // Validate a 2-digit month
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
            pAcc.DD = trans.widdepValidation(2); // Validate a 2-digit day
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
            pAcc.YY = trans.widdepValidation(4); // Validate a 4-digit year
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


string Atm::getnumber() {
    char number[11] = {0};
    int index = 0;
    bool valid;
        index = 0;
        valid = true;
        system("cls");
        cout << "Enter your contact number: +63";

        while (true) {
            char ch = _getch();

            if (ch == '\r') {
                if (index == 10) {
                    number[index] = '\0'; // Terminate string
                    break;
                }
                continue; // Invalid length
            } else if (ch == '\b' && index > 0) {
                cout << "\b \b"; // Handle backspace
                index--;
            } else if (ch >= '0' && ch <= '9' && index < 10) {
                    number[index++] = ch;
                    if(number[0] != '9'){
                        index--;
                        continue;
                    }
                    cout << ch;
            }
        }


    return "+63" + string(number);
}

string Atm::name(){
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
        } else if (ch == '\b' && !trans.isempty(temp)) {// Ensure there's something to delete
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

void Atm::reg() {
    char input1[MAX_LENGTH + 1] = "";
    if (accountCount >= 100) {
        cout << "Account limit reached!" << endl;
        return;
    }

    Account pAcc;
    bool valid = false;

    // First Name collection with validation
    system("cls");
    cout << "What should we call you?" << endl;
    cout << "First Name: ";
    pAcc.firstname = name();

    // Last Name collection with validation
    system("cls");
    cout << "Last Name: ";
    pAcc.lastname= name();

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
    trans.get_numeric_input(input1);
    pAcc.pin = input1;
    system("cls");

    // Account number generation
    pAcc.accountNo = initializedAccNo();

    cout << "Account Successfully Created!\n" << endl;
    system("pause");

    trans.add(pAcc);
    pAcc.pin = trans.encrypt(pAcc.pin);
    trans.save();
    USBsave(pAcc);
}

void Atm::USBsave(Account acc) {
    ofstream file(filePathUSB, ios::app);  // Use ios::app to append data
    if (!file) {
        cerr << "Error writing to file: " << filePathUSB << endl;
        return;
    }

    file << acc.accountNo << endl;
    file << acc.pin << endl;

    file.close();
    cout << "Account data saved to USB successfully." << endl;
}

void Atm::USBload(Account* acc) {
    ifstream file(filePathUSB);

    if(!file){
        return;
    }
    // Read the account number and pincode from the USB file
    file >> acc->accountNo;
    file >> acc->pin;


    // Debug prints to verify what is being read from the USB file
    cout << "USB Loaded Account Number: " << acc->accountNo << endl;
    cout << "USB Loaded Pincode: " << acc->pin << endl;
    file.close();
    cout << "\nAccount data loaded from USB successfully." << endl;
}

string Atm:: initializedAccNo(){
    srand(time(0));//randomized number base on time
    string acc;
    LinkList* head;
    LinkList* p = trans.getHead();

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



int main() {
    Atm a; // Initial ize USB and file paths
    a.menu();
    return 0;
}
