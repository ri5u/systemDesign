#pragma once
#include <mutex>
#include <shared_mutex>
#include <cstdint>

class Account{
    private:
        long long balance;
        uint64_t id;

        // replacing the normal mutex locks with a read/write locks allowing for multiple threads to do read operations. 
        mutable std::shared_mutex rw_mutex;
        
        uint64_t getId();
        void setBalance(long long amount);
        long long getBalanceInternal();

        friend class Bank;

    public:
        Account(long long amount);

        void deposit(long long amount);

        bool withdraw(long long amount);

        long long getBalance() const;

        std::shared_mutex& getMutex();
};
