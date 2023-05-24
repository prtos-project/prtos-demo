# Description
This example shows UC/OS-II RTOS run on partitions provided by PRTOS Hypervisor

# Partition definition
There are two partitions.
P1 will run one UC/OS-II RTOS instance.
P2 will run one UC/OS-II RTOS instance.

# Configuration table
Basic configuration. Partitions are defined to be executed at different memory addresses.

A scheduling plan is defined under the following premises:

MAF = 1000 msec 		
P1: S   0 ms  D 500 ms  
P2: S 500 ms  D 500 ms  

# Expected results
PRTOS will load, initialise and run in user mode partitions. 
During the execution, P1 will load one UC/OS-II RTOS instance,
P2 will load another UC/OS-II RTOS instance.

