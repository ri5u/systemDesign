#include "Account.h"
#include <iostream>
#include <thread>

int main(){
    std::string name = "John Doe";
    long long amount = 0;
    Account myAccount(amount, name);

    // std::cout << "Inital Balance: " << myAccount.getBalance() << std::endl;

    // myAccount.deposit(500);

    // std::cout << "New Balance: " << myAccount.getBalance() << std::endl;

    // if(myAccount.withdraw(1900)) {
    //     std::cout << "Success. Remaining Balance: " << myAccount.getBalance() << std::endl;
    // } else {
    //     std::cout << "Insufficient Funds. Balance in account: " << myAccount.getBalance() << std::endl;
    // }

    std::thread t1([&]() {
        for(int i = 0; i < 100000; i++) {
            myAccount.deposit(1);
        }
    });

    std::thread t2([&]() {
        for(int i = 0; i < 100000; i++) {
            myAccount.deposit(1);
        }
    });

    t1.join();
    t2.join();

    std::cout << myAccount.getBalance() << std::endl;
    return 0;
}
