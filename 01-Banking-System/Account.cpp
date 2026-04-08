#include "Account.h"
#include <atomic>
#include <cmath>

//we use this as an id for the new accounts. During constructor call the id is incremented and assigned to the account id. 
//atomic to make sure that the id increment operation is atomic and prevents race condition. 
static std::atomic<uint64_t> global_id_counter = 0;

Account::Account(long long amount){
    this->balance = amount;
    this->id = global_id_counter.fetch_add(1);
}

uint64_t Account::getId(){
    return this->id;
}

void Account::setBalance(long long amount) {
    this->balance = amount;
}

long long Account::getBalanceInternal() {
    return this->balance;
}

void Account::deposit(double amount) {
    long long amountPaise = static_cast<long long>(std::round(amount * 100));
    std::unique_lock lock(rw_mutex);
    setBalance(this->balance + amountPaise);
}

bool Account::withdraw(double amount) {
    long long amountPaise = static_cast<long long>(std::round(amount * 100));
    std::unique_lock lock(rw_mutex);
    if(amountPaise > this->balance) {
        return false;
    }
    
    setBalance(this->balance - amountPaise);
    return true;
}

long long Account::getBalance() const {
    std::shared_lock lock(rw_mutex);
    return this->balance;
}

std::shared_mutex& Account::getMutex() {
    return this->rw_mutex;
}

