# Bank & ATM PF Project (C++)

## Description
This is a **console-based Bank & ATM system** developed as a PF/semester project using C++.  
The system allows users to **create accounts, authenticate with PIN, deposit money, transfer funds, and pay bills**.  
All account data is saved to a file (`accounts.txt`) for persistence, so data is not lost when the program exits.


## Features
- Create a new bank account with name, account number, and 4-digit PIN
- ATM PIN authentication before accessing account
- Show current balance
- Deposit money into account
- Transfer money to another account (multi-account system)
- Bill payment with balance deduction
- Auto-save data after every transaction
- Console-based, PF-friendly interface


## File Structure
Bank-ATM-PF-Project/
├── main.cpp # PF project C++ source code
├── accounts.txt # File storing all accounts (created automatically)
└── README.md # This file


## How to Run

1. Clone the repository:
git clone https://github.com/MuhammadYousaf-Dev/Bank-ATM-PF-Project.git

2. Navigate to the folder containing main.cpp:
cd Bank-ATM-PF-Project

3. Compile the C++ code:
g++ main.cpp -o BankATM

5. Run the program:
./BankATM


### ATM Menu
![ATM Menu](media/screenshot1.png)

### Bank Menu
![Bank Menu](media/screenshot2.png)

### Transaction Example
![Transaction](media/screenshot3.png)
