#ifndef ACCOUNT_H
#define ACCOUNT_H

class Account {
private:
    double balance;
public:
    Account(double startin_money); // Constructor
    void deposit(double amount); // Adds money to the account
    void withdraw(double amount); // Removes money from the account
    double getBalance() const; // Returns the current balance
};

#endif // ACCOUNT_H