# B-wbsft
Blockchain Simulation in C++


## Assumptions
- Blocks with no transactions are still stored (maintains the property that we create blocks at regular interval of 10s)
- The first block is created at T=10
- Throw an error if user attempts to create an account that already exists
- It's said that 'Ctrl+C' should end the simulation. In most terminals 'Ctrol+C' is already assigned to abort the current task and regain user control, so command/hot-key assignment needs to be done here
