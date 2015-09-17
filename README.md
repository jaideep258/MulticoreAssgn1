# MulticoreAssgn1
N thread Mutual Exclusion using Peterson 2 thread algorithm

generalization of Peterson’s algorithm 2-thread mutual exclusion to n-threads using a binary tree. Implemented a tournament based algorithm in which the node which reaches root wins and enter CS.

Measured the performance of the implementation experimentally with respect to system throughput
using the following system parameters:

1. System load: this depends on the mean inter-request delay. Made inter-request delay values exponentially distributed and varied the mean time between two critical section requests from [0, 100] time units in suitable increments.

2. Degree of contention: This depends on the number of threads in the system. Varied the number of threads from one to two times the number of cores in the machine in suitable increments.


tree.cpp contains the main code.
script.py contains an automated script to test above.
