#include <iostream>
#include <sstream>
#include <cstdlib>    // system()
#include <string>
#include <unistd.h>   // getcwd()
#include <climits>    // PATH_MAX
#include "Node.h"

/*
 Transaction enum as well as corresponding member variables are declared in 'include/Transaction.h'
 Block struct with member variables for timestamp and transactions is declared in 'include/Block.h'
 */

int main() {

    std::cout << "Type 'b start-node' to start the simulation.\n";
    std::cout << "Type 'Ctrl+C' at any time to end the simulation.\n";

    std::string line;

    while (true) {
        std::cout << "> ";

        // Read user input
        if (!std::getline(std::cin, line)) break; // user pressed Ctrl+C or closed

        // I'm using streams to read input since streams automatically parse tokens
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
            

            std::cout << "Starting node in a new Terminal window...\n";

            // Get the current working directory
            char cwd[PATH_MAX];
            
            if (getcwd(cwd, sizeof(cwd)) == NULL) {
                std::perror("getcwd() error");
                continue;
            }
            std::string currentDir(cwd);

                        
            std::string executable = "./blockchainSimulator";

            // Construct the AppleScript command
            // This command tells Terminal.app to open a new window, change to the current directory,
            // and execute the blockchainSimulator executable.
            std::string appleScriptCommand = "osascript -e 'tell application \"Terminal\" to do script \"cd "
                                                         + currentDir + "; " + executable + "\"'";

            // Execute the AppleScript command
            int result = system(appleScriptCommand.c_str());

            if (result == -1) {
                std::cerr << "Failed to open Terminal.app and start the node.\n";
            }
            else {
                            std::cout << "Node started in a new Terminal window.\n";
            }

            
            
        }
        else if ( token == "create-account" or token == "transfer" or token == "balance" ) {
            std::cout << "Please initiate the simulation before attempting commands." << "\n";
        }
        else {
            std::cout << "Unknown command: " << token << "\n";
            std::cout << "Try starting the simulation with `b start-node`" <<  "\n";
        }
    }

    return 0;
}
