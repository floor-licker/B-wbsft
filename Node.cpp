/*
#TO-DO

X 1. Implement Node constructor

X 2. Implement Node destructor
    - Actually stop the node when the destructor gets called to prevent memory leaks and dangling references

X 3. Implement startNode()

X 4. Implement stopNode()

X 5. Implement createBlock()
	- Acquire lock on the pending transactions (txMutex)
	- Create a new Block object, copying or moving 
         `pendingTxs` into the block's transaction list.
	- Clear pendingTxs
	- For each transaction in the block:
		- If CREATE_ACCOUNT, update the accounts map accordingly
		- If TRANSFER, adjust sender and recipient balances
		- Append the new Block to the `blockchain` vector
 
X 6. Implement blockProducer()
	- background function running in its own thread, periodically
	  creating new blocks
 
X 7. Implement transfer()
     - Create a Transaction object (type=TRANSFER)
     - Lock txMutex and push it into `pendingTxs`
 
X 8 Implement createAccount()
	- Create a Transaction object (type=CREATE_ACCOUNT)
	- Lock txMutex and push it into `pendingTxs`

X 9. Implement getBalance()
	- Lock txMutex (to ensure consistency with
          the accounts map)
	- Return the current balance for the requested account
          (or 0 / error if not found)
 
 // compiles to blockchainSimulator executable
 // g++ -std=c++14 -pthread -I include -Wall -Wextra -pedantic -O2 -o blockchainSimulator src/Node.cpp

*/
#include "Node.h"

#include <iostream>
#include <chrono>
#include <ctime>           // time_t and std::ctime
#include <sys/stat.h>     // mkfifo


// Constructor
Node::Node() : running(false) {}

// Destructor
Node::~Node() {
    stopNode(); // Ensure the miner thread is stopped
}

// Start the miner thread
void Node::startNode() {
    if (running.load()) {
        std::cout << "Node is already running.\n";
        return;
    }
    running = true;
    blockProductionThread = std::thread(&Node::blockProducer, this);
}

// Stop the miner thread
void Node::stopNode() {
    if (running.load()) {
        running = false;
        if (blockProductionThread.joinable()) {
            blockProductionThread.join();
        }
        std::cout << "Node stopped.\n";
    }
}

// Miner thread function
void Node::blockProducer() {
    while (running.load()) {
        // Sleep for 10 seconds
        std::this_thread::sleep_for(std::chrono::seconds(10));

        // Create a new block from pending transactions
        createBlock();
    }
}

// Create a new block
void Node::createBlock() {
    std::lock_guard<std::mutex> lock(txMutex);

    
    
    // Optionally print that a block was empty
    // Commented out to avoid cluttering the console
    /*
    if (pendingTxs.empty()) {
        std::cout << "No pending transactions. Creating an empty block.\n";
       
    }
     */

    Block newBlock;
    // Get current time as timestamp
    newBlock.timestamp = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());

    // Move pending transactions to the block
    newBlock.txs = std::move(pendingTxs);

    // Clear pending transactions
    pendingTxs.clear();

    // Apply transactions to accounts
    for (const auto& tx : newBlock.txs) {
        switch (tx.type) {
            case TransactionType::CREATE_ACCOUNT:
                if (accounts.find(tx.accountId) == accounts.end()) {
                    accounts[tx.accountId] = tx.startingBalance;
                    std::cout << "Account '" << tx.accountId << "' created with balance " << tx.startingBalance << ".\n";
                } else {
                    std::cout << "Error: Account '" << tx.accountId << "' already exists.\n";
                }
                break;
            case TransactionType::TRANSFER:
                if (accounts.find(tx.fromAccount) != accounts.end() &&
                    accounts.find(tx.toAccount) != accounts.end()) {
                    if (accounts[tx.fromAccount] >= tx.amount) {
                        accounts[tx.fromAccount] -= tx.amount;
                        accounts[tx.toAccount] += tx.amount;
                        std::cout << "Transferred " << tx.amount << " from '" << tx.fromAccount
                                  << "' to '" << tx.toAccount << "'.\n";
                    } else {
                        std::cout << "Error: Insufficient funds in account '" << tx.fromAccount << "'.\n";
                    }
                } else {
                    std::cout << "Error: One or both accounts do not exist for transfer.\n";
                }
                break;
            default:
                std::cout << "Error: Unknown transaction type.\n";
                break;
        }
    }

    // Add the new block to the blockchain
    blockchain.push_back(newBlock);

    /*
    std::cout << "Block created at " << std::ctime(reinterpret_cast<time_t*>(&newBlock.timestamp))
              << " with " << newBlock.txs.size() << " transaction(s).\n";
     */
}

// Submit a create account transaction
void Node::createAccount(const std::string& accountId, long long balance) {
    Transaction tx;
    tx.type = TransactionType::CREATE_ACCOUNT;
    tx.accountId = accountId;
    tx.startingBalance = balance;

    std::lock_guard<std::mutex> lock(txMutex);
    pendingTxs.push_back(tx);
}

// Submit a transfer transaction
void Node::transfer(const std::string& from, const std::string& to, long long amount) {
    Transaction tx;
    tx.type = TransactionType::TRANSFER;
    tx.fromAccount = from;
    tx.toAccount = to;
    tx.amount = amount;

    std::lock_guard<std::mutex> lock(txMutex);
    pendingTxs.push_back(tx);
}

// Get the balance of an account
long long Node::getBalance(const std::string& accountId) {
    std::lock_guard<std::mutex> lock(txMutex);
    auto it = accounts.find(accountId);
    if (it != accounts.end()) {
        return it->second;
    } else {
        std::cout << "Error: Account '" << accountId << "' does not exist.\n";
        return 0;
    }
}
