#pragma once
#include <string>
#include <mutex>

class Account{
    private:
        long long balance;
        std::string name;
        mutable std::mutex mtx;

        void setBalance(long long amount);
        long long getBalanceInternal();

        friend class Bank;

    public:
        Account(long long amount, std::string& name);

        void deposit(long long amount);

        bool withdraw(long long amount);

        long long getBalance() const;

        // bool transfer(Account& account, long long amount);
        std::mutex& getMutex();
};
