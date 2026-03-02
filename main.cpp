#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
using namespace std;

// Account structure
struct Account {
    string name;
    string number;
    string pin;
    double balance;
};

// Vector to hold all accounts
vector<Account> accounts;

// Function declarations
void mainMenu();
void atmMenu();
void bankMenu();
void createAccount();
void showBalance(Account &acc);
void depositMoney(Account &acc);
void transferMoney(Account &acc);
void billPayment(Account &acc);
void saveAccounts();
void loadAccounts();
Account* findAccount(const string &accNum);
bool authenticatePIN(Account &acc);

int main() {
    loadAccounts();
    cout << fixed << setprecision(2);
    mainMenu();
    return 0;
}

// Main menu
void mainMenu() {
    int choice;
    do {
        cout << "\n===== Bank & ATM PF System =====\n";
        cout << "1. ATM\n2. Bank\n3. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch(choice) {
            case 1: atmMenu(); break;
            case 2: bankMenu(); break;
            case 3: cout << "Thank you for using the PF Bank System!\n"; break;
            default: cout << "Invalid choice.\n";
        }
    } while(choice != 3);
}

// ATM Menu
void atmMenu() {
    string accNum;
    cout << "Enter Account Number for ATM access: ";
    cin >> accNum;

    Account* acc = findAccount(accNum);
    if(!acc) {
        cout << "Account not found.\n";
        return;
    }

    cout << "Insert Card (Press Enter)...";
    cin.ignore();
    cin.get();

    if(!authenticatePIN(*acc)) {
        cout << "Incorrect PIN. Access denied.\n";
        return;
    }

    int choice;
    do {
        cout << "\n===== ATM Menu =====\n";
        cout << "1. Show Balance\n2. Transfer Money\n3. Exit ATM\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch(choice) {
            case 1: showBalance(*acc); break;
            case 2: transferMoney(*acc); break;
            case 3: cout << "Exiting ATM...\n"; break;
            default: cout << "Invalid option.\n";
        }
    } while(choice != 3);
}

// Bank Menu
void bankMenu() {
    int choice;
    do {
        cout << "\n===== Bank Menu =====\n";
        cout << "1. Create Account\n2. Deposit Money\n3. Pay Bill\n4. Exit Bank\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch(choice) {
            case 1: createAccount(); break;
            case 2: {
                string accNum;
                cout << "Enter Account Number: ";
                cin >> accNum;
                Account* acc = findAccount(accNum);
                if(acc) depositMoney(*acc);
                else cout << "Account not found.\n";
                break;
            }
            case 3: {
                string accNum;
                cout << "Enter Account Number: ";
                cin >> accNum;
                Account* acc = findAccount(accNum);
                if(acc) billPayment(*acc);
                else cout << "Account not found.\n";
                break;
            }
            case 4: cout << "Exiting Bank...\n"; break;
            default: cout << "Invalid option.\n";
        }
    } while(choice != 4);
}

// Create account
void createAccount() {
    Account acc;
    cin.ignore();
    cout << "Enter Account Holder Name: ";
    getline(cin, acc.name);
    cout << "Enter Account Number: ";
    cin >> acc.number;
    cout << "Set 4-digit PIN: ";
    cin >> acc.pin;
    acc.balance = 0.0;

    accounts.push_back(acc);
    saveAccounts();

    cout << "Account created successfully!\n";
}

// Show balance
void showBalance(Account &acc) {
    cout << "Current Balance: " << acc.balance << endl;
}

// Deposit money
void depositMoney(Account &acc) {
    double amount;
    cout << "Enter amount to deposit: ";
    cin >> amount;

    if(amount > 0) {
        acc.balance += amount;
        saveAccounts();
        cout << "Deposit successful. New Balance: " << acc.balance << endl;
    } else {
        cout << "Invalid amount.\n";
    }
}

// Transfer money 
void transferMoney(Account &acc) {
    string recipientNum;
    double amount;
    cout << "Enter recipient account number: ";
    cin >> recipientNum;

    Account* recipient = findAccount(recipientNum);
    if(!recipient) {
        cout << "Recipient account not found.\n";
        return;
    }

    cout << "Enter amount to transfer: ";
    cin >> amount;

    if(amount > 0 && amount <= acc.balance) {
        acc.balance -= amount;
        recipient->balance += amount;
        saveAccounts();
        cout << "Transfer successful. Remaining Balance: " << acc.balance << endl;
    } else {
        cout << "Insufficient balance or invalid amount.\n";
    }
}

// Bill payment
void billPayment(Account &acc) {
    string billID;
    double amount;
    cout << "Enter Bill ID: ";
    cin >> billID;
    cout << "Enter Bill Amount: ";
    cin >> amount;

    if(amount > 0 && amount <= acc.balance) {
        acc.balance -= amount;
        saveAccounts();
        cout << "Bill paid successfully. Remaining Balance: " << acc.balance << endl;
    } else {
        cout << "Insufficient balance or invalid amount.\n";
    }
}

// Save all accounts to file
void saveAccounts() {
    ofstream file("accounts.txt");
    for(const auto &acc : accounts) {
        file << acc.name << "," << acc.number << "," << acc.pin << "," << acc.balance << endl;
    }
    file.close();
}

// Load accounts from file
void loadAccounts() {
    accounts.clear();
    ifstream file("accounts.txt");
    string line;
    while(getline(file, line)) {
        Account acc;
        size_t pos = 0;
        vector<string> tokens;
        while((pos = line.find(',')) != string::npos) {
            tokens.push_back(line.substr(0,pos));
            line.erase(0,pos+1);
        }
        tokens.push_back(line);
        if(tokens.size()==4){
            acc.name = tokens[0];
            acc.number = tokens[1];
            acc.pin = tokens[2];
            acc.balance = stod(tokens[3]);
            accounts.push_back(acc);
        }
    }
    file.close();
}

// Find account by number
Account* findAccount(const string &accNum) {
    for(auto &acc : accounts) {
        if(acc.number == accNum) return &acc;
    }
    return nullptr;
}

// Authenticate PIN
bool authenticatePIN(Account &acc) {
    string enteredPIN;
    cout << "Enter PIN: ";
    cin >> enteredPIN;
    return enteredPIN == acc.pin;
}