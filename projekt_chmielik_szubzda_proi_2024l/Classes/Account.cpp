#include "Account.h"

Account::Account(double starting_money) : balance(starting_money) {}

void Account::deposit(double amount) {
    balance += amount;
}

void Account::withdraw(double amount) {
    balance -= amount;
}

double Account::getBalance() const {
    return balance;
}