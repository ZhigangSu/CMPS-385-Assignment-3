#include <iostream>
#include <iomanip>
#include <string>
#include <cstdlib>
#include <ctime>
using namespace std;

class Account {
protected:
    string name;
    int accountNumber;
    double balance;
public:
    Account(string n = "", double b = 0.0) {
        name = n;
        balance = b;
        accountNumber = 10000 + rand() % 90000;
    }
    virtual void deposit(double amount) {
        balance += amount;
    }
    virtual bool withdraw(double amount) {
        if (amount <= balance) {
            balance -= amount;
            return true;
        }
        return false;
    }
    virtual void displayBalance() const {
        cout << "[Regular Account] Current balance: $"
            << fixed << showpoint << setprecision(2)
            << balance << endl;
    }
    int getAccountNumber() const { return accountNumber; }
    string getName() const { return name; }
    double getBalance() const { return balance; }
    virtual ~Account() {}
};

class SavingsAccount : public Account {
public:
    SavingsAccount(string n = "", double b = 0.0) : Account(n, b) {}
    void displayBalance() const override {
        cout << "[Savings Account] Current balance: $"
            << fixed << showpoint << setprecision(2)
            << balance << endl;
    }
};

int main() {
    unsigned int seed = static_cast<unsigned int>(time(nullptr));
    srand(seed);

    const int MAX_ACCOUNTS = 100;
    Account* accounts[MAX_ACCOUNTS];
    int accountCount = 0;

    int choice;
    do {
        cout << "***************Welcome to Chase***************" << endl;
        cout << "Please choose one of the following operations" << endl;
        cout << "1- Create a new bank account with an initial balance" << endl;
        cout << "2- Deposit Money to an Account" << endl;
        cout << "3- Withdraw Money from an Account" << endl;
        cout << "4- Display Current Balance of an Account" << endl;
        cout << "5- Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 1) {
            string cname;
            double initBalance;
            int accType;
            cout << "Enter your name: ";
            cin.ignore();
            getline(cin, cname);
            cout << "Enter your initial balance: ";
            cin >> initBalance;
            cout << "Choose account type (1 = Regular, 2 = Savings): ";
            cin >> accType;

            if (accType == 2) {
                accounts[accountCount] = new SavingsAccount(cname, initBalance);
                cout << "Congratulations " << cname
                    << "! You have successfully opened a SAVINGS account "
                    << "with an initial balance of $"
                    << fixed << showpoint << setprecision(2) << initBalance
                    << ". Your account number is "
                    << accounts[accountCount]->getAccountNumber() << "." << endl;
            }
            else {
                accounts[accountCount] = new Account(cname, initBalance);
                cout << "Congratulations " << cname
                    << "! You have successfully opened a REGULAR account "
                    << "with an initial balance of $"
                    << fixed << showpoint << setprecision(2) << initBalance
                    << ". Your account number is "
                    << accounts[accountCount]->getAccountNumber() << "." << endl;
            }
            accountCount++;
            cout << "Press any key to return to Main Menu!" << endl;
            cin.ignore(); cin.get();
        }
        else if (choice == 2) {
            int accNo;
            cout << "Enter the account number: ";
            cin >> accNo;
            bool found = false;
            for (int i = 0; i < accountCount; i++) {
                if (accounts[i]->getAccountNumber() == accNo) {
                    double depositAmt;
                    cout << "Enter the amount that you would like to deposit: ";
                    cin >> depositAmt;
                    accounts[i]->deposit(depositAmt);
                    cout << "Congratulations " << accounts[i]->getName()
                        << "! You have successfully deposited $" << depositAmt
                        << " in your account #" << accNo
                        << ". Your current balance is $" << accounts[i]->getBalance() << "." << endl;
                    found = true;
                }
            }
            if (!found) {
                cout << "No account number exists!" << endl;
            }
            cout << "Press any key to return to Main Menu!" << endl;
            cin.ignore(); cin.get();
        }
        else if (choice == 3) {
            int accNo;
            cout << "Enter the account number: ";
            cin >> accNo;
            bool found = false;
            for (int i = 0; i < accountCount; i++) {
                if (accounts[i]->getAccountNumber() == accNo) {
                    double withdrawAmt;
                    cout << "Enter the amount that you would like to withdraw: ";
                    cin >> withdrawAmt;
                    if (accounts[i]->withdraw(withdrawAmt)) {
                        cout << "Congratulations " << accounts[i]->getName()
                            << "! You have successfully withdrawn $" << withdrawAmt
                            << " in your account #" << accNo
                            << ". Your current balance is $" << accounts[i]->getBalance() << "." << endl;
                    }
                    else {
                        cout << "Insufficient balance!" << endl;
                    }
                    found = true;
                }
            }
            if (!found) {
                cout << "No account number exists!" << endl;
            }
            cout << "Press any key to return to Main Menu!" << endl;
            cin.ignore(); cin.get();
        }
        else if (choice == 4) {
            int accNo;
            cout << "Enter the account number: ";
            cin >> accNo;
            bool found = false;
            for (int i = 0; i < accountCount; i++) {
                if (accounts[i]->getAccountNumber() == accNo) {
                    accounts[i]->displayBalance();
                    found = true;
                }
            }
            if (!found) {
                cout << "No account number exists!" << endl;
            }
            cout << "Press any key to return to Main Menu!" << endl;
            cin.ignore(); cin.get();
        }
        else if (choice == 5) {
            cout << "Thank you for using Chase Bank System!" << endl;
        }
        else {
            cout << "Invalid choice! Try again." << endl;
        }
    } while (choice != 5);

    for (int i = 0; i < accountCount; i++) {
        delete accounts[i];
    }
    return 0;
}
