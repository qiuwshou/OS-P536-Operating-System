xsh $ process_ring -v work
Number of Process: 4
Version :work
Number of Rounds: 5
Ring element:0, Round:0, Value:20
Ring element:1, Round:0, Value:19
Ring element:2, Round:0, Value:18
Ring element:3, Round:0, Value:17
Ring element:0, Round:1, Value:16
Ring element:1, Round:1, Value:15
Ring element:2, Round:1, Value:14
Ring element:3, Round:1, Value:13
Ring element:0, Round:2, Value:12
Ring element:1, Round:2, Value:11
Ring element:2, Round:2, Value:10
Ring element:3, Round:2, Value:9
Ring element:0, Round:3, Value:8
Ring element:1, Round:3, Value:7
Ring element:2, Round:3, Value:6
Ring element:3, Round:3, Value:5
Ring element:0, Round:4, Value:4
Ring element:1, Round:4, Value:3
Ring element:2, Round:4, Value:2
Ring element:3, Round:4, Value:1
---------------------------------
xsh $ process_ring -v chaos
Number of Process: 4
Version :chaos
Number of Rounds: 5
xsh $ Ring element:3, Round:1, Value:20
Ring element:0, Round:0, Value:19
Ring element:1, Round:0, Value:18
Ring element:2, Round:4, Value:17
Ring element:3, Round:0, Value:16
Ring element:2, Round:0, Value:17
Ring element:0, Round:2, Value:15
Ring element:0, Round:1, Value:15
Ring element:2, Round:1, Value:17
Ring element:2, Round:2, Value:17
Ring element:0, Round:4, Value:15
Ring element:1, Round:1, Value:14
Ring element:3, Round:2, Value:16
Ring element:1, Round:2, Value:14
Ring element:3, Round:4, Value:16
Ring element:2, Round:3, Value:13
Ring element:0, Round:3, Value:15
Ring element:3, Round:3, Value:12
Ring element:1, Round:4, Value:14
----------------------------------
xsh $ process_ring -v hang
Number of Process: 4
Version :hang
Number of Rounds: 5
Ring element:0, Round:0, Value:20
Ring element:1, Round:0, Value:19
Ring element:2, Round:0, Value:18
----------------------------------
xsh $ process_ring -v loop
Number of Process: 4
Version :loop
Number of Rounds: 5
Ring element:0, Round:0, Value:20
Ring element:1, Round:0, Value:20
Ring element:2, Round:0, Value:20
Ring element:3, Round:0, Value:20
Ring element:0, Round:1, Value:20
Ring element:1, Round:1, Value:20
Ring element:2, Round:1, Value:20
Ring element:3, Round:1, Value:20
Ring element:0, Round:2, Value:20
Ring element:1, Round:2, Value:20
Ring element:2, Round:2, Value:20
Ring element:3, Round:2, Value:20
Ring element:0, Round:3, Value:20
Ring element:1, Round:3, Value:20
Ring element:2, Round:3, Value:20
Ring element:3, Round:3, Value:20
Ring element:0, Round:4, Value:20
Ring element:1, Round:4, Value:20
Ring element:2, Round:4, Value:20
Ring element:3, Round:4, Value:20
Ring element:0, Round:0, Value:20
Ring element:1, Round:0, Value:20
Ring element:2, Round:0, Value:20
Ring element:3, Round:0, Value:20
Ring element:0, Round:1, Value:20
Ring element:1, Round:1, Value:20
Ring element:2, Round:1, Value:20
Ring element:3, Round:1, Value:20
Ring element:0, Round:2, Value:20
...repeat
---------------------------------
1.Why does your program hang? What is the name of this behavior in an operating system?
Semaphore is not released by one processes then the other processes will be blocked. This is called mutual exclusion.
2.Why does your program go into an infinite loop? What is the name of this behavior in an operating system?
The value to the inbox of process is never updated so it doesn't satisfy the condition that the value will be counted down to 1. This is called infinite loop in an operating system.
3.Why does your program print numbers out of order? What is the name of this behavior in an operating system?
Because when the processes are created the priority of the processes are different. So when the processes are in the ready state, the operating system will pick the ones that have the higher priority to execute. This is called priority scheduling.
4.What property of Xinu allows the working version of your program to print values in the correct order?
The mutual exclusion allows the working version. When a process is accessing the inbox value all the other processes have to wait until the process releases the semaphore.