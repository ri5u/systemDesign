#include "Account.h"
#include <atomic>

//we use this as an id for the new accounts. During constructor call the id is incremented and assigned to the account id. 
//atomic to make sure that the id increment operation is atomic and prevents race condition. 
static std::atomic<uint64_t> global_id_counter = 0;

Account::Account(long long amount){
    this->balance = amount;
    this->id = global_id_counter.fetch_add(1);
}

void Account::setBalance(long long amount) {
    this->balance = amount;
}

long long Account::getBalanceInternal() {
    return this->balance;
}

void Account::deposit(long long amount) {
    std::unique_lock lock(rw_mutex);
    setBalance(this->balance + amount);
}

bool Account::withdraw(long long amount) {
    std::unique_lock lock(rw_mutex);
    if(amount > this->balance) {
        return false;
    }
    
    setBalance(this->balance - amount);
    return true;
}

long long Account::getBalance() const {
    std::shared_lock lock(rw_mutex);
    return this->balance;
}

std::shared_mutex& Account::getMutex() {
    return this->rw_mutex;
}

