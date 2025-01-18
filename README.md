# B-wbsft
Blockchain Simulation in C++


## Assumptions
- Blocks with no transactions are still stored (maintains the property that we create blocks at regular interval of 10s)
- The first block is created at T=10
- Throw an error if user attempts to create an account that already exists
- It's said that 'Ctrl+C' should end the simulation. In most terminals 'Ctrl+C' is already assigned to abort the current task and regain user control, so no command/hot-key assignment needs to be done here

## Dependency Graph


![Dependency Graph](dependency_graph.svg)

## Features
- If user enters an invalid command, i.e., doesn't begin with `b`, the program prints `<Unknown command. Must start with 'b'>` and gives an example of a valid command for starting the node
- If user enters a valid command but uses the command incorrectly, i.e., not properly parameterized, the program explains the format of proper parameterization of that command, for example if 
you attempted to use `b create-account` incorrectly, you would see: `Usage: b create-account <account-id> <starting-balance>`




## Checklist
