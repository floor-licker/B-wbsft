#pragma once
//ensure inclusion only once

#include <vector>

#include "Transaction.h"

struct Block {
    
    // this will end up being either unix system time or time since startNode() call
    long long timestamp;

    // Transactions included in this block
    std::vector<Transaction> txs; 
};

