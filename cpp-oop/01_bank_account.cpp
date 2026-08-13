#include <string>
#include <iostream>

class BankAccount{
private:
    std::string accountHolder;
    double balance = 0;

public:
    void setAccountHolder(const std::string& name) {
        accountHolder = name;
    }

    std::string getAccountHolder() const {
        return accountHolder;
    }

    double getBalance() const {
        return balance;
    }

    bool deposit(double amount) {
        if(amount <= 0) {
            return false;
        }

        balance += amount;
        return true;
    }

    bool withdraw(double amount) {
        if(amount > balance || amount <= 0){
            return false;
        }

        balance -= amount;
        return true;
    }
};

int main(void){
    BankAccount account1;
    account1.setAccountHolder("john");
    if(account1.deposit(500)){
        std::cout << "Successful Deposit" << std::endl;
    } else {
        std::cout << "Deposit amount should be greater than 0" << std::endl;
    }

    if(account1.withdraw(600)) {
        std::cout << "Money debited Successfully" << std::endl;
    } else {
        std::cout << "Insufficient balance" << std::endl;
    }

    std::cout << account1.getAccountHolder() << " " << account1.getBalance() << std::endl;
}
