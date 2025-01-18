# B-wbsft
Blockchain Simulation in C++


## Assumptions
- Blocks with no transactions are still stored (maintains the property that we create blocks at regular interval of 10s)
- The first block is created at T=10
- Throw an error if user attempts to create an account that already exists
- It's said that 'Ctrl+C' should end the simulation. In most terminals 'Ctrl+C' is already assigned to abort the current task and regain user control, so no command/hot-key assignment needs to be done here

## Dependency Graph


```mermaid
graph LR
    A["main.cpp"] --> B["Node.h"]
    A["main.cpp"] --> C["Node.cpp"]
    B["Node.h"] --> D["Transaction.h"]
    B["Node.h"] --> E["Block.h"]
    C["Node.cpp"] --> B["Node.h"]
    
    %% Class Relationships
    F["Node Class"] --> D["Transaction.h"]
    F["Node Class"] --> E["Block.h"]
    
    %% Custom Styles
    classDef fileNode fill:#f9f,stroke:#333,stroke-width:2px;
    class A,B,C,D,E,F fileNode;
```
