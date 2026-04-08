# Multi-Threaded Banking System

## Overview
This document provides a comprehensive overview of the multi-threaded banking system implementation. The banking system allows multiple users to perform transactions concurrently while ensuring data consistency and integrity.

## Features
- **Account Management**: Create, delete, and manage user accounts.
- **Concurrent Transactions**: Handle multiple transactions simultaneously using threads.
- **Data Integrity**: Implement locking mechanisms to ensure data consistency.

## Architecture
The system follows a client-server architecture:
- **Client**: Interaction interface for users to perform banking operations.
- **Server**: Handles requests from clients and performs operations on the database.

### Technologies Used
- Programming Language: Java
- Threading Model: Java Threads
- Database: MySQL
- Synchronization: Using synchronized blocks and locks.

## Classes
1. **Account**: Represents a bank account with attributes such as account number, account holder name, and balance.
2. **Transaction**: Represents a banking transaction with methods for deposit and withdrawal.
3. **Bank**: Manages a collection of accounts and processes transactions.
4. **Client**: Handles user input and interacts with the Bank class.

## How It Works
1. **User Interface**: Users can interact with the program through a console interface.
2. **Thread Management**: Each transaction is handled by a separate thread to achieve concurrency.
3. **Synchronization**: Critical sections of code that modify shared data are synchronized to prevent race conditions.

## Installation
To install and run the banking system:
1. Clone the repository: `git clone https://github.com/ri5u/systemDesign.git`
2. Navigate to the directory: `cd systemDesign/01-Banking-System`
3. Compile the Java files: `javac *.java`
4. Run the main class: `java Main`

## Usage
- Create an account by selecting the appropriate option in the client interface.
- Perform deposits and withdrawals.
- View account balances.

## Future Enhancements
- Implement user authentication.
- Add support for multiple currencies.

## Conclusion
The multi-threaded banking system demonstrates the implementation of concurrent programming concepts in a real-world application. It showcases how to manage multiple transactions while maintaining data integrity through synchronization techniques.

---

## Author
- **Name**: ri5u  
- **Date**: 2026-04-08  
- **Email**: [your-email@example.com]  

> This documentation is intended for developers looking to understand and extend the multi-threaded banking system.