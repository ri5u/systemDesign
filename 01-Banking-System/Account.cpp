#include "Account.h"

Account::Account(long long amount, std::string& name) : balance(amount) , name(name) {}

void Account::deposit(long long amount) {
    std::lock_guard<std::mutex> lock(mtx);
    this->balance += amount;
}

bool Account::withdraw(long long amount) {
    std::lock_guard<std::mutex> lock(mtx);
    if(amount > this->balance) {
        return false;
    }
    
    this->balance -= amount;
    return true;
}

long long Account::getBalance() const {
    std::lock_guard<std::mutex> lock(mtx);
    return this->balance;
}


