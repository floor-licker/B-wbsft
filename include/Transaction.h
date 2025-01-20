
#pragma once

#include <string>

// using a scoped enum
enum class TransactionType { CREATE_ACCOUNT, TRANSFER };

struct Transaction {
    TransactionType type;
    
    // For CREATE_ACCOUNT
    std::string accountId;
    long long startingBalance;

    // For TRANSFER
    std::string fromAccount;
    std::string toAccount;
    long long amount;
};
