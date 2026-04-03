#include "Bank.h"
#include "Account.h"
#include "ThreadPool.h"
#include <iostream>
#include <chrono>

int main(){
    ThreadPool pool;
    pool.start();

    std::vector<uint64_t> account_ids;
    uint64_t initial_sum = 0; 
    for(uint64_t i = 0; i < 10000; i++){
        account_ids.push_back(Bank::createAccount(1000));
        initial_sum += 1000;
    }
    auto start = std::chrono::high_resolution_clock::now();
    for(int i = 0; i < 1500000; i++){
        uint64_t fromId = account_ids[rand() % account_ids.size()];
        uint64_t toId = account_ids[rand() % account_ids.size()];
        pool.pushTask([fromId, toId](){
                Bank::transfer(fromId, toId, 1);
        });
    }
    
    pool.stop();
    auto end = std::chrono::high_resolution_clock::now();
    uint64_t final_sum = 0;
    for(auto id : account_ids) {
        auto account = Bank::getAccount(id); 
        final_sum += account->getBalance();
    }
     
    std::cout << "Initial Sum: " << initial_sum << std::endl;
    std::cout << "Final Sum: " << final_sum << std::endl;
    std::chrono::duration<double> duration = end - start;
    std::cout << "Time taken: " << duration.count() << std::endl;
    return 0;
}
