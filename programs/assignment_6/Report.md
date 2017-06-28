1.Starvation is that a process never gets the resource to execute.
The protocal is starvation-free if the priority of all the processes are the same. Because the outer do-while loop makes sure that the same process can't hold the resource repeatly. After a process is executed it has to hanlde the turn to other other processes. So the processes will be executed based on FIFO.  


2.Deadlock is that a process is waiting for the resource which is held by other processes.
The protocal is not deadlock-free. Suppose there are two processes 1 and 2. Process 1 acquires the lock first and set the variable busy=true and variable turn=thread_id of process 1. Right after that processes 2 comes in and interrupts process 1. Because process 1 doesn't release the lock, so the busy=true won't be changed  and process 2 will stuck in the inner do-while loop to wait forever for the variable busy to be set to false, which causes a deadlock.