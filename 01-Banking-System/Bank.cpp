#include "Bank.h"
#include <memory>
#include <cmath>

uint64_t Bank::createAccount(long long balance){
    std::shared_ptr<Account> newAccount = std::make_shared<Account>(balance); 
    uint64_t id = newAccount->getId();
    
    std::unique_lock lock(registryMutex);
    accounts[id] = newAccount;
    
    return id;
}

std::shared_ptr<Account> Bank::getAccount(uint64_t id){
    std::shared_lock lock(registryMutex);
    auto it = accounts.find(id);
    
    if(it == accounts.end()) return nullptr;

    return it->second;
}

bool Bank::transfer(uint64_t fromId, uint64_t toId, double amount) {
    auto from = getAccount(fromId);
    auto to  = getAccount(toId);
   
    if(!from || !to) return false;
    if(from == to) return false;
      
    long long amountPaise = static_cast<long long>(std::round(amount * 100));

    //This scoped lock ensures that both the locks are acquired safely without causing any deadlocks. 
    //And also ensures RAII
    std::scoped_lock lock(from->rw_mutex, to->rw_mutex);

    long long fromAccountBalance = from->getBalanceInternal();
    long long toAccountBalance = to->getBalanceInternal();
    bool success = false;
    if(fromAccountBalance >= amountPaise) {
        success = true;
        from->setBalance(fromAccountBalance - amountPaise);        
        to->setBalance(toAccountBalance + amountPaise);        
    }

    return success;
}
