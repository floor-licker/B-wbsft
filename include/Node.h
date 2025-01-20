// ensure inclusion only once
#pragma once

#include <string>
#include <map>
#include <vector>
#include <thread>
#include <mutex>
#include <atomic>


#include "Transaction.h"
#include "Block.h"

class Node {
public:
    // Constructor
    Node();

    // Destructor
    ~Node();

    // Starts the node's miner thread
    void startNode();

    // Stops the node's miner thread
    void stopNode();

    // The main loop handling user commands
    void nodeEngine();

    // Miner thread function that periodically creates new blocks
    void blockProducer();

    // Creates a new block from pending transactions
    void createBlock();

    // Submits a create account transaction
    void createAccount(const std::string& accountId, long long balance);

    // Submits a transfer transaction
    void transfer(const std::string& from, const std::string& to, long long amount);

    // Retrieves the balance of a specific account
    long long getBalance(const std::string& accountId);

private:
    // Thread responsible for producing blocks
    std::thread blockProductionThread;

    // Atomic flag to control the thread for the block production execution
    std::atomic<bool> running;

    // Mutex to protect access to shared resources like pending transactions
    std::mutex txMutex;

    std::vector<Transaction> pendingTxs;

    // Mapping of address to balance
    std::map<std::string, long long> accounts;

    // our "blockchain" represented by a vector of Block objects
    std::vector<Block> blockchain;
};
