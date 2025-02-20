
#include "Node.h"


#include <iostream>
#include <chrono>
#include <ctime>


/*
 The executable called `blockchainSimulator` is just compiled Simulator.cpp
 */

int main() {
    //Open new terminal
    //Run node simulation logic
    
    Node node;
    std::string line;
    
    node.startNode();
    
    std::cout << "Node started. Blocks will be created every 10s.\n";

    while (true) {
        std::cout << "> ";

        // Read user input
        if (!std::getline(std::cin, line)) break; // user pressed Ctrl+C or closed

        // Treat the string as a stream
        std::stringstream ss(line);

        std::string token;

        ss >> token; // Load token starting at ss[0] to variable `token`

        // Check if the command is valid, i.e., starts with 'b'
        if (token != "b") {
            std::cout << "Unknown command. Must start with 'b'.\n";
            std::cout << "An example of a valid command is 'b start-node'.\n";
            continue;
        }

        // Next token decides the action
        ss >> token;

        if (token == "start-node") {
            node.startNode();
            std::cout << "Node started. Blocks will be created every 10s.\n";
        }
        
        else if (token == "help"){
            std::cout << "Here is a list of valid commands" << "\n";
            std::cout << "To start a blockchain simulation: b start-node" << "\n";
            std::cout << "To create an account: b create-acconut <address> <starting-balance>" << "\n";
            std::cout << "To transfer between accounts: b transfer <from> <to> <amount>" << "\n";
            std::cout << "To query balance of an account: b balance <account>" << "\n";
            std::cout << "To end the simulation and erase all data: Ctrl+c" << "\n";
        }
        
        else if (token == "create-account") {
            std::string accountId;
            long long balance;

            // Validate input
            if (!(ss >> accountId >> balance)) {
                std::cout << "Usage: b create-account <account-id> <starting-balance>\n";
                continue;
            }
            
            std::string extra;
            if (ss >> extra) {
                std::cout << "Error: Too many arguments provided.\n";
                std::cout << "Usage: b create-account <account-id> <starting-balance>\n";
                continue;
                }

            if (balance < 0) {
                std::cout << "Starting balance cannot be negative.\n";
                continue;
            }

            node.createAccount(accountId, balance);
            std::cout << "Transaction submitted: create account "
                      << accountId << " with balance " << balance << "\n";
        }
        else if (token == "transfer") {
            std::string from, to;
            long long amount;

            if (!(ss >> from >> to >> amount)) {
                std::cout << "Usage: b transfer <from> <to> <amount>\n";
                continue;
            }
            
            // Check for any extra parameters
            std::string extra;
            if (ss >> extra) {
                std::cout << "Error: Too many arguments provided.\n";
                std::cout << "Usage: b transfer <from> <to> <amount>\n";
                continue;
                }


            if (amount <= 0) {
                std::cout << "Transfer amount must be positive.\n";
                continue;
            }

            if (node.getBalance(from) < amount) {
                std::cout << "Insufficient funds in account " << from << ".\n";
                continue;
            }

            node.transfer(from, to, amount);
            std::cout << "Transaction submitted: transfer " << amount
                      << " from " << from << " to " << to << "\n";
        }
        else if (token == "balance") {
            std::string accountId;

            if (!(ss >> accountId)) {
                std::cout << "Usage: b balance <account-id>\n";
                continue;
            }

            long long bal = node.getBalance(accountId);
            
            std::cout << "Balance for " << accountId << " is " << bal << "\n";
        }
        else {
            std::cout << "Unknown command: " << token << "\n";
        }
    }

    // Stop the node if still running
    node.stopNode();

    return 0;
    
}
