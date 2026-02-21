#include "Bank.h"
#include <utility>

bool Bank::transer(Account& from, Account& to, long long amount) {
    if(&from == &to) return false;
    
    Account* first = &from;
    Account* second = &to;

    if(first > second) {
        std::swap(first, second);
    }

    first->getMutex().lock();
    second->getMutex().lock();

    long long fromAccountBalance = from.getBalanceInternal();
    long long toAccountBalance = to.getBalanceInternal();
    bool success = false;
    if(fromAccountBalance >= amount) {
        success = true;
        from.setBalance(fromAccountBalance - amount);        
        to.setBalance(toAccountBalance + amount);        
    }

    first->getMutex().unlock();
    second->getMutex().unlock();

    return success;
}

