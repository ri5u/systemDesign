# Multi-Threaded Banking System

## Overview

A high-performance, concurrent banking system implementation in C++ that demonstrates advanced multi-threading techniques and system design principles. The system safely manages multiple bank accounts and concurrent fund transfers across thousands of threads without data corruption or deadlocks.

## Key Features

- Thread-safe account operations with read/write lock optimization
- Deadlock-free concurrent fund transfers between accounts
- Custom thread pool for efficient task scheduling
- Concurrent stress testing with 1.5M+ simultaneous transactions
- Atomic ID generation for accounts
- Data consistency validation and invariant checking

## Architecture

### Core Components

#### 1. Account Class

Represents an individual bank account with thread-safe balance management.

- Uses std::shared_mutex for optimized read/write locking
- Multiple threads can read balance simultaneously
- Write operations (deposit/withdraw) have exclusive access
- Atomic account ID assignment prevents race conditions

Key Methods:
- deposit(long long amount): Add funds to account
- withdraw(long long amount): Remove funds from account
- getBalance() const: Read current balance (allows multiple concurrent readers)

#### 2. Bank Class

Central registry managing all accounts and coordinating fund transfers.

- Static account registry using unordered_map
- Deadlock-free transfer implementation using std::scoped_lock
- Acquires locks on both source and destination accounts atomically
- Prevents self-transfers and invalid account references

Key Methods:
- createAccount(long long balance): Create new account and register it
- getAccount(uint64_t id): Retrieve account by ID
- transfer(uint64_t fromId, uint64_t toId, long long amount): Safe fund transfer

#### 3. ThreadPool Class

Efficient worker thread pool for concurrent task execution.

- Dynamically scales to hardware concurrency level
- Uses std::counting_semaphore for task signaling
- Eliminates busy-waiting and improves CPU efficiency
- Graceful shutdown with proper thread joining
- RAII pattern ensures resource cleanup

Key Methods:
- start(): Initialize worker threads
- pushTask(std::function<void()> task): Queue task for execution
- stop(): Gracefully shutdown all threads

## Technical Design

### Concurrency Strategy

The system employs multiple synchronization mechanisms:

1. Read/Write Locks (shared_mutex)
   - Allows multiple concurrent readers of account balance
   - Exclusive access for writers (deposit/withdraw)
   - Improves throughput for read-heavy workloads

2. Deadlock Prevention
   - std::scoped_lock acquires multiple locks atomically
   - Prevents circular wait conditions
   - Ensures consistent lock ordering

3. Atomic Operations
   - std::atomic<uint64_t> for thread-safe ID generation
   - Eliminates race conditions in counter increment

4. Semaphore-Based Signaling
   - std::counting_semaphore coordinates task availability
   - Worker threads block when queue is empty
   - Reduces CPU overhead compared to polling

### Data Consistency

The system guarantees:
- Money conservation: Total balance across all accounts never changes
- Account isolation: Operations on one account do not corrupt others
- Transfer atomicity: Money either transfers completely or not at all
- No double-spending: Withdrawal only succeeds if sufficient funds exist

## Building

### Requirements
- C++17 or later
- Standard C++ library with threading support
- A modern C++ compiler (g++, clang, MSVC)

### Compilation

Using g++:
```
g++ -std=c++17 -pthread -O2 Account.cpp Bank.cpp ThreadPool.cpp main.cpp -o bank_system
```

Using clang:
```
clang++ -std=c++17 -pthread -O2 Account.cpp Bank.cpp ThreadPool.cpp main.cpp -o bank_system
```

## Running

Execute the compiled binary:
```
./bank_system
```

This runs a comprehensive stress test that:
1. Creates 10,000 accounts with 1,000 units each (10M total)
2. Executes 1,500,000 concurrent fund transfers
3. Measures execution time
4. Validates total money conservation

## Performance Testing

The main program serves as a stress test with the following configuration:

Test Parameters:
- Account count: 10,000
- Initial balance per account: 1,000 units
- Total money in system: 10,000,000 units
- Concurrent transfers: 1,500,000
- Transfer amount: 1 unit per transaction
- Thread pool size: hardware_concurrency

Expected Output:
```
Initial Sum: 10000000
Final Sum: 10000000
Time taken: X.XXX seconds
```

The invariant that initial sum equals final sum validates that the system maintains money conservation under concurrent access.

## Code Quality

The implementation demonstrates:
- RAII (Resource Acquisition Is Initialization) pattern throughout
- Const correctness in method signatures
- Smart pointer usage for automatic memory management
- Proper synchronization primitives selection
- Clear separation of concerns across classes
- Comprehensive inline documentation

## Design Decisions

1. Shared Mutex over Regular Mutex
   - Balance reads are frequent; write operations are less common
   - Allows multiple threads to read simultaneously
   - Improves system throughput

2. Scoped Lock for Transfers
   - Atomic acquisition of multiple locks prevents deadlocks
   - Automatic cleanup via RAII principle
   - No manual lock/unlock reduces error surface

3. Semaphore-Based Task Signaling
   - More efficient than busy-waiting or condition variables for this use case
   - Prevents spurious wakeups
   - Better CPU utilization

4. Static Account Registry
   - All accounts visible to all bank operations
   - Simplifies account lookup and transfer coordination
   - Thread-safe via shared_mutex protection

## Limitations and Future Improvements

Current limitations:
- All data is in-memory (no persistence)
- Single process execution (not distributed)
- No transaction rollback mechanism
- No overdraft protection
- Limited error reporting

Potential enhancements:
- Add persistent storage layer (database integration)
- Implement distributed transactions for multi-process scenarios
- Add comprehensive logging and audit trails
- Include transaction history per account
- Add rate limiting and fraud detection
- Implement interest calculation
- Add REST API for client access

## Testing

The system includes a built-in stress test that validates:
- Concurrent account creation
- Parallel fund transfers
- Data consistency under load
- Performance characteristics

To verify correctness, the test ensures:
- Sum of all accounts before operations equals sum after operations
- No data corruption occurs with concurrent access
- All transfers complete successfully

## Usage Example

```cpp
// Create bank accounts
uint64_t account1 = Bank::createAccount(1000);
uint64_t account2 = Bank::createAccount(500);

// Retrieve account
auto account = Bank::getAccount(account1);
std::cout << "Balance: " << account->getBalance() << std::endl;

// Transfer funds
bool success = Bank::transfer(account1, account2, 100);
if (success) {
    std::cout << "Transfer successful" << std::endl;
}

// Use thread pool for concurrent operations
ThreadPool pool;
pool.start();
pool.pushTask([]() { 
    Bank::transfer(account1, account2, 50); 
});
pool.stop();
```

## References

- C++ Standard Library Documentation: Threading Support
- Herb Sutter - Effective Concurrency Articles
- Anthony Williams - C++ Concurrency in Action

---

Author: ri5u
Date: 2026-04-08