# Paging-Simulator

### Grant Novota

grno9650@colorado.edu

A paging simulator project that is used to implement predictive page algorithms to increase performance.

## Contents:

```
paging-simulator/                 
├── Makefile             # GNU Make makefile to build the code.
├── simulator.c          # core simulator source code.
├── simulator.h          # simulator header file including the simulator API.
├── programs.c           # struct representing simulated programs for use by simulator. For reference and use by simulator code only.
├── pager-basic.c        # basic paging implementation that only runs one process at a time. 
├── pager-lru.c          # LRU paging implementation. 
├── pager-predict.c      # predictive paging implementation
├── api-test.c           # pageit implemenation that detects and prints simulator state changes. May be useful if you want to confirm the behavior of the simulator API. Builds to test-api.
├── test-*               # executable test programs. Run ./test-* -help for info on available options. It also responds to varios signals by printing the current page table and process execution state to the screen.
├── test-api             # API test program. See api-test.c
└── see.R                # R script for displaying a visualization of the process run/block activity in a simulation. You must first run ./test-* -csv to generate the necessary trace files. To run visualization, lunch R in windowed graphics mode (in Linux: R -g Tk & at the command prompt) from the directory containing the trace files (or use setwd to set your working directory to the directory containing the trace files). Then run source(‘‘see.r’’) at the R command prompt to launch the visualization. 
```

## Usage

`$ make` builds the executables.

Execute `./test-*` with desired flags. `-help` will display options.