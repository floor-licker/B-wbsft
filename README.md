# B-wbsft
Blockchain Simulation in C++


## Assumptions
- Blocks with no transactions are still stored (maintains the property that we create blocks at regular interval of 10s)
- The first block is created at T=10
- Throw an error if user attempts to create an account that already exists
- It's said that 'Ctrl+C' should end the simulation. In most terminals 'Ctrl+C' is already assigned to abort the current task and regain user control, so no command/hot-key assignment needs to be done here
- If the user calls  `b start-node` consecutively, i.e, attempts to start node when it is already running, they recieve a message notifying them that the node is already running

## Dependency Graph


![Dependency Graph](dependency_graph.svg)

## Features
- If user enters an invalid command, i.e., doesn't begin with `b`, the program prints `<Unknown command. Must start with 'b'>` and gives an example of a valid command for starting the node
- If user enters a valid command but uses the command incorrectly, i.e., not properly parameterized, the program explains the format of proper parameterization of that command, for example if 
you attempted to use `b create-account` incorrectly, you would see: `Usage: b create-account <account-id> <starting-balance>`




## Checklist

- [ ] **Block Creation**
  - [ ] Create new blocks every 10 seconds (T=10, T=20, T=30, etc.)

- [ ] **Commands**
  - [ ] **Account Creation**
    - [ ] Implement `b create-account <id-of-account> <starting-balance>`
    - [ ] Create a new account with the specified ID and starting balance
  - [ ] **Fund Transfer**
    - [ ] Implement `b transfer <from-account> <to-account> <amount>`
    - [ ] Send funds from one account to another
    - [ ] Handle confirmation times based on transaction time:
      - [ ] Transactions sent at T=7 take 3 seconds to confirm
      - [ ] Transactions sent at T=12 take 8 seconds to confirm
  - [ ] **Balance Check**
    - [ ] Implement `b balance <account>`
    - [ ] Immediately display the account balance

- [ ] **Node Management**
  - [ ] Implement `b start-node` to spin up the local blockchain server
  - [ ] Allow stopping the node with Ctrl-C, ensuring all data resets upon restart

- [ ] **Error Handling**
  - [ ] Display helpful error messages for incorrect command usage

- [ ] **Additional Constraints**
  - [ ] Implmentation should be of the form that there is no permanent data storage; reset state upon node restart.
