#include "Account.h"

Account::Account(long long amount, std::string& name) : balance(amount) , name(name) {}

void Account::setBalance(long long amount) {
    this->balance = amount;
}

long long Account::getBalanceInternal() {
    return this->balance;
}

void Account::deposit(long long amount) {
    std::lock_guard<std::mutex> lock(this->mtx);
    setBalance(this->balance + amount);
}

bool Account::withdraw(long long amount) {
    std::lock_guard<std::mutex> lock(this->mtx);
    if(amount > this->balance) {
        return false;
    }
    
    setBalance(this->balance - amount);
    return true;
}

long long Account::getBalance() const {
    std::lock_guard<std::mutex> lock(this->mtx);
    return this->balance;
}

std::mutex& Account::getMutex() {
    return this->mtx;
}

// bool Account::transfer(Account& account, long long amount) {
//     std::lock_guard<std::mutex> lock(this->mtx);
//     if(amount > this->getBalance()) {
//         return false;
//     }

//     this->withdraw(amount);
//     account.deposit(amount);
//     return true;
// }
