#include "Bank.h"

bool Bank::transfer(Account& from, Account& to, long long amount) {
    if(&from == &to) return false;
      
    //This scoped lock ensures that both the locks are acquired safely without causing any deadlocks. 
    //And also ensures RAII
    std::scoped_lock lock(from.rw_mutex, to.rw_mutex);

    long long fromAccountBalance = from.getBalanceInternal();
    long long toAccountBalance = to.getBalanceInternal();
    bool success = false;
    if(fromAccountBalance >= amount) {
        success = true;
        from.setBalance(fromAccountBalance - amount);        
        to.setBalance(toAccountBalance + amount);        
    }

    return success;
}

