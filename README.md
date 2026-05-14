*This project has been created as part of the 42 curriculum by yabuawad.*

# Philosophers

## Description

Concurrency is one of the fundamental challenges in computer science. When multiple processes or threads attempt to access shared resources simultaneously, improper synchronization can lead to unpredictable behavior, race conditions, deadlocks, and starvation.

This Philosophers project explores these problems through the classic Dining Philosophers Problem ,a well-known synchronization challenge that demonstrates the complexity of resource sharing in concurrent systems.

In this simulation, philosophers sit around a table while continuously eating, sleeping, and thinking. To eat, each philosopher must acquire two shared forks, creating a scenario where resource management becomes critical. The project focuses on building a reliable multithreaded system capable of coordinating these actions safely and efficiently.

Implemented in C using POSIX threads (`pthread`) and mutexes, this project provides practical experience with:
- multithreading
- synchronization primitives
- shared memory protection
- deadlock prevention
- starvation handling
- precise timing and monitoring systems

The objective is not only to make the simulation work, but to design it in a way that remains stable, fair, and thread-safe under concurrent execution.  
My approach to solve the deadlock was `Ordered Resource Allocation` that is directly related to the classic deadlock prevention principle:
1. break circular wait
2. enforce strict resource ordering

## Instructions

### Compilation

Compile the project using:

```bash
make
```
then take the following arguments:
number_of_philosophers time_to_die time_to_eat time_to_sleep
[number_of_times_each_philosopher_must_eat]

example:
```bash
./philo 5 800 200 200
```
or you can limit the number of meals:
``` bash
./philo 4 600 100 200 3
```

## Resources
**The Dining Philosophers Problem explained** https://en.wikipedia.org/wiki/Dining_philosophers_problem  
**whats a thread ?** https://www.reddit.com/r/explainlikeimfive/comments/1jwix0w/eli5_what_are_threads_in_operating_system/
**Mutexes & Data Races** https://medium.com/@ruinadd/philosophers-42-guide-the-dining-philosophers-problem-893a24bc0fe2


### AI Usage

AI tools were used for:
- understanding mutex behavior
- reviewing deadlock prevention strategies
- clarifying starvation vs deadlock concepts  
`All implementation and final debugging were completed manually.`
