#include <bits/stdc++.h>
using namespace std;

// ---------------- ACCOUNT ----------------
class Account {
public:
    long long accNo;
    string ifsc;
    int balance;
    int pin;
    bool blocked;

    Account(long long a, string i, int b, int p)
        : accNo(a), ifsc(i), balance(b), pin(p), blocked(false) {}
};

// ---------------- AUTH POLICY (OCP) ----------------
class AuthPolicy {
public:
    virtual bool authenticate(Account* acc, int enteredPin) = 0;
    virtual ~AuthPolicy() {}
};

// Default PIN based authentication
class PinAuth : public AuthPolicy {
public:
    bool authenticate(Account* acc, int enteredPin) override {
        return acc->pin == enteredPin;
    }
};

// ---------------- BLOCK POLICY (OCP) ----------------
class BlockPolicy {
public:
    virtual bool shouldBlock(int invalidAttempts) = 0;
    virtual ~BlockPolicy() {}
};

class DefaultBlockPolicy : public BlockPolicy {
    int limit;
public:
    DefaultBlockPolicy(int l = 3) : limit(l) {}
    bool shouldBlock(int invalidAttempts) override {
        return invalidAttempts >= limit;
    }
};

// ---------------- SECURITY TRACKER ----------------
class Security {
public:
    unordered_map<long long, int> attempts;

    void recordFail(long long acc) { attempts[acc]++; }
    void reset(long long acc) { attempts[acc] = 0; }
    int getFails(long long acc) { return attempts[acc]; }
};

// ---------------- TRANSACTION SERVICE ----------------
class TransactionService {
public:
    AuthPolicy* auth;
    BlockPolicy* block;
    Security* sec;

    TransactionService(AuthPolicy* a, BlockPolicy* b, Security* s)
        : auth(a), block(b), sec(s) {}

    long long withdraw(Account* acc, int enteredPin, int amount) {

        if (acc->blocked) {
            cout << "Card Blocked!\n Please contact your bank.\n";
            return -1;
        }

        // Authentication
        if (!auth->authenticate(acc, enteredPin)) {
            sec->recordFail(acc->accNo);
            cout << "Invalid PIN!\n";

            if (block->shouldBlock(sec->getFails(acc->accNo))) {
                acc->blocked = true;
                cout << "Card Blocked due to multiple failures!\n";
            }
            return -1;
        }

        sec->reset(acc->accNo);

        // Balance check
        if (amount > acc->balance) {
            cout << "Insufficient Balance!\n";
            return -1;
        }

        acc->balance -= amount;
        return acc->balance;
    }
};

// ---------------- ATM + USER ----------------
class ATM {
public:
    string name, address;
    ATM(string n, string a) : name(n), address(a) {}
};

class User {
public:
    string username;
    Account* acc;
    User(string u, Account* a) : username(u), acc(a) {}
};

// ---------------- MAIN ----------------
int main() {
    ATM* sbi = new ATM("SBI", "Rohini Sec-21");
    Account* acc = new Account(12023, "SBIN001200", 5000, 1234);
    User* user = new User("Prateek", acc);

    Security sec;
    AuthPolicy* auth = new PinAuth();
    BlockPolicy* block = new DefaultBlockPolicy(3);
    TransactionService tx(auth, block, &sec);

    cout << "User " << user->username << " using ATM: "
         << sbi->name << " " << sbi->address << "\n";

    // Withdraw
    long long remain = tx.withdraw(acc, 1234, 1000);
    remain = tx.withdraw(acc, 1234, 1000);
    remain = tx.withdraw(acc, 1234, 1000);

    if(remain == -1){

        cout << "Account is temporarly blocked!" << endl;
    }
    else cout << "Remaining balance: " << remain << "\n";

    return 0;
}
