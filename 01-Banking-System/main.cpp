#include "Bank.h"
#include "Account.h"
#include <iostream>
#include <thread>

int main(){
    Account myAccount1(100);
    Account myAccount2(100);

    std::thread t1([&]() {
        for(long i = 1; i <= 100; i++) {
            Bank::transfer(myAccount1, myAccount2, 1);
        }
    });

    std::thread t2([&]() {
        for(int i = 1; i <= 10; i++) {
            Bank::transfer(myAccount2, myAccount1, 1);
        }
    });

    t1.join();
    t2.join();


    std::cout << myAccount1.getBalance() << std::endl;
    std::cout << myAccount2.getBalance() << std::endl;
    return 0;
}
