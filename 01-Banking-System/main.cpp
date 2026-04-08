#include "Bank.h"
#include "Account.h"
#include "ThreadPool.h"
#include <iostream>
#include <chrono>

int main(){
    ThreadPool pool(std::thread::hardware_concurrency()); 
    pool.start();

    std::vector<uint64_t> account_ids;
    uint64_t initial_sum = 0; 
    
    // Create 10,000 accounts with 1,000.00 Rupees (100,000 Paise) each
    for(uint64_t i = 0; i < 10000; i++){
        uint64_t id = Bank::createAccount(100000); 
        account_ids.push_back(id);
        initial_sum += 100000;
    }

    auto start = std::chrono::high_resolution_clock::now();
    
    // Blast 1,000,000 random transfers of 10.37 Rupees
    for(int i = 0; i < 1000000; i++){
        uint64_t fromId = account_ids[rand() % account_ids.size()];
        uint64_t toId = account_ids[rand() % account_ids.size()];
        pool.pushTask([fromId, toId](){
            Bank::transfer(fromId, toId, 10.37);
        });
    }
    
    // Safely stop the pool (waits for all tasks to finish)
    pool.stop();
    
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> diff = end - start;

    uint64_t final_sum = 0;
    for(auto id : account_ids) {
        auto account = Bank::getAccount(id); 
        final_sum += account->getBalance();
    }
    
    std::cout << "Initial Sum (Paise): " << initial_sum << std::endl;
    std::cout << "Final Sum (Paise): " << final_sum << std::endl;
    std::cout << "Audit Result: " << (initial_sum == final_sum ? "PASSED" : "FAILED") << std::endl;
    std::cout << "Time taken: " << diff.count() << " seconds" << std::endl;
    
    return 0;
}
