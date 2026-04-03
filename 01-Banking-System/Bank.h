#include "Account.h"
#include <memory>
#include <shared_mutex>
#include <unordered_map>

class Bank{
    inline static std::unordered_map<uint64_t, std::shared_ptr<Account>> accounts;
    inline static std::shared_mutex registryMutex;
    public:
        static bool transfer(uint64_t fromId, uint64_t toId, long long amount);
        static uint64_t createAccount(long long Balance);
        static std::shared_ptr<Account> getAccount(uint64_t id);
};
