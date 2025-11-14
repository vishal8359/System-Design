#include <bits/stdc++.h>
using namespace std;

// ---------------- ATM ----------------
class ATM {
public:
    string name;
    string address;

    ATM(string name, string address) {
        this->name = name;
        this->address = address;
    }
};

// ---------------- AccountInfo ----------------
class AccountInfo {
public:
    long long account_no;
    string Ifsc_code;
    int balance;
    int pin;
    bool isBlock;

    unordered_map<long long, long long> accountToBalance;
    unordered_map<long long, int> accountToPin;

    AccountInfo(long long account_no, string Ifsc_code, int balance, int pin) {

        this->account_no = account_no;
        this->Ifsc_code = Ifsc_code;
        this->balance = balance;
        this->pin = pin;

        accountToBalance[account_no] = balance;
        accountToPin[account_no] = pin;

        isBlock = false;
    }
};

// ---------------- ManageAccount ----------------
class ManageAccount : public AccountInfo {
public:

    ManageAccount(long long account_no, string Ifsc_code, int balance, int pin)
        : AccountInfo(account_no, Ifsc_code, balance, pin) {}

    void checkBalance(long long account_no) {
        cout << "Your remaining balance is : "
             << accountToBalance[account_no] << endl;
    }

    void updateBalance(long long account_no, int newBalance) {
        accountToBalance[account_no] = newBalance;
    }

    void hold() {
        isBlock = true;
    }

    long long Withdraw(int amount, int enteredPin) {

        static int invalid = 0;

        if (isBlock) {
            cout << "Your card is blocked!" << endl;
            return 0;
        }

        if (accountToPin[account_no] != enteredPin) {
            invalid++;
            cout << "Invalid PIN" << endl;

            if (invalid >= 3) {
                hold();
                cout << "Card blocked due to suspicious activity!" << endl;
            }
            return 0;
        }

        invalid = 0; // reset on correct pin

        if (amount > balance) {
            cout << "Insufficient balance!" << endl;
            return 0;
        }

        balance -= amount;
        updateBalance(account_no, balance);

        return balance;
    }
};

// ---------------- User ----------------
class User {
public:
    string username;
    AccountInfo *account;
    ATM *atmUsed;

    User(string name, AccountInfo *acc, ATM *atm) {
        this->username = name;
        this->account = acc;
        this->atmUsed = atm;
    }
};

// ---------------- MAIN ----------------
int main() {

    ATM *Sbi = new ATM("SBI", "Rohini Sec - 21");

    ManageAccount *acc = new ManageAccount(12023, "SBIN001200", 5000, 1234);

    User *User1 = new User("Prateek", acc, Sbi);

    cout << "User " << User1->username
         << " is using ATM: " << User1->atmUsed->name << User1->atmUsed->address << endl;

    long long remaining = acc->Withdraw(1000, 1234);
    cout << "Remaining balance: " << remaining << endl;

    return 0;
}
