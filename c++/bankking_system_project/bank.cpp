#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;

class BankAccount {
private:
    int accountNumber;
    char name[50];
    double balance;

public:
    void createAccount() {
        cout << "\nEnter Account Number: ";
        cin >> accountNumber;
        cin.ignore();
        cout << "Enter Account Holder Name: ";
        cin.getline(name, 50);
        cout << "Enter Initial Deposit: ";
        cin >> balance;
        cout << "\nAccount created successfully!\n";
    }

    void showAccount() const {
        cout << "\nAccount Number: " << accountNumber;
        cout << "\nAccount Holder Name: " << name;
        cout << "\nBalance: $" << fixed << setprecision(2) << balance << endl;
    }

    void deposit(double amount) {
        balance += amount;
    }

    void withdraw(double amount) {
        if (balance >= amount)
            balance -= amount;
        else
            cout << "\nInsufficient funds!\n";
    }

    int getAccountNumber() const {
        return accountNumber;
    }

    double getBalance() const {
        return balance;
    }
};

void writeAccount() {
    BankAccount acc;
    acc.createAccount();
    ofstream outFile("accounts.dat", ios::binary | ios::app);
    outFile.write(reinterpret_cast<char*>(&acc), sizeof(BankAccount));
    outFile.close();
}

void displayAccount(int accNo) {
    BankAccount acc;
    bool found = false;
    ifstream inFile("accounts.dat", ios::binary);
    while (inFile.read(reinterpret_cast<char*>(&acc), sizeof(BankAccount))) {
        if (acc.getAccountNumber() == accNo) {
            acc.showAccount();
            found = true;
            break;
        }
    }
    inFile.close();
    if (!found)
        cout << "\nAccount not found!\n";
}

void depositWithdraw(int accNo, int option) {
    BankAccount acc;
    fstream file("accounts.dat", ios::binary | ios::in | ios::out);
    bool found = false;

    while (file.read(reinterpret_cast<char*>(&acc), sizeof(BankAccount))) {
        if (acc.getAccountNumber() == accNo) {
            acc.showAccount();
            double amount;
            cout << "\nEnter amount: ";
            cin >> amount;

            if (option == 1)
                acc.deposit(amount);
            else
                acc.withdraw(amount);

            // Update record
            int pos = static_cast<int>(file.tellg()) - sizeof(BankAccount);
            file.seekp(pos, ios::beg);
            file.write(reinterpret_cast<char*>(&acc), sizeof(BankAccount));
            cout << "\nTransaction successful!\n";
            found = true;
            break;
        }
    }
    file.close();
    if (!found)
        cout << "\nAccount not found!\n";
}

void displayAllAccounts() {
    BankAccount acc;
    ifstream inFile("accounts.dat", ios::binary);
    cout << "\n\n=== Account Holder List ===\n";
    while (inFile.read(reinterpret_cast<char*>(&acc), sizeof(BankAccount))) {
        acc.showAccount();
        cout << "-----------------------------\n";
    }
    inFile.close();
}

void deleteAccount(int accNo) {
    BankAccount acc;
    ifstream inFile("accounts.dat", ios::binary);
    ofstream outFile("temp.dat", ios::binary);
    bool found = false;

    while (inFile.read(reinterpret_cast<char*>(&acc), sizeof(BankAccount))) {
        if (acc.getAccountNumber() != accNo) {
            outFile.write(reinterpret_cast<char*>(&acc), sizeof(BankAccount));
        } else {
            found = true;
        }
    }
    inFile.close();
    outFile.close();

    remove("accounts.dat");
    rename("temp.dat", "accounts.dat");

    if (found)
        cout << "\nAccount deleted successfully!\n";
    else
        cout << "\nAccount not found!\n";
}

int main() {
    int choice;
    int accNo;

    do {
        cout << "\n====== BANK MENU ======";
        cout << "\n1. Create New Account";
        cout << "\n2. Deposit";
        cout << "\n3. Withdraw";
        cout << "\n4. Check Balance";
        cout << "\n5. Display All Accounts";
        cout << "\n6. Delete Account";
        cout << "\n7. Exit";
        cout << "\nChoose an option: ";
        cin >> choice;

        switch (choice) {
            case 1:
                writeAccount();
                break;
            case 2:
                cout << "\nEnter Account Number: ";
                cin >> accNo;
                depositWithdraw(accNo, 1);
                break;
            case 3:
                cout << "\nEnter Account Number: ";
                cin >> accNo;
                depositWithdraw(accNo, 2);
                break;
            case 4:
                cout << "\nEnter Account Number: ";
                cin >> accNo;
                displayAccount(accNo);
                break;
            case 5:
                displayAllAccounts();
                break;
            case 6:
                cout << "\nEnter Account Number: ";
                cin >> accNo;
                deleteAccount(accNo);
                break;
            case 7:
                cout << "\nThank you for using the banking system.\n";
                break;
            default:
                cout << "\nInvalid choice!\n";
        }
    } while (choice != 7);

    return 0;
}