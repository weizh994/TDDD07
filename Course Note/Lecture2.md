## Recap from [last lecture](Lecture1.md)
* Real-time systems have well-defined
timing requirements
* We look at the extreme case
  * – Computational systems that need to
meet every deadline for every
instance of each process
* Most commonly used: Cyclic scheduling
with Major/Minor cycle 

### Construction of cyclic schedule  

Off-line attempt to construct the schedule
might be iterative

* Each process $P_i$ is run periodically every $T_i$ (i.e. should be **completed once** every $T_i$)
* Processes are placed in _minor cycle_ and _major cycle_ until repetition appears
* Check: Are all process instances runnable with the given periods and estimated WCETs?
* If not, reconsider the minor/major cycle and/orsome process parameters 

### When is the schedule correct?
* All processes should be run at least as often as every (original) $T_i$
* All processes fit in the _minor cycles_ they are placed in  

and  
* Repetition appears!(**反复出现**)

### Harmonic processes
* Sum of WCETs fits in ... (major cycle?)

### Next try
* In either case we need to
  *  change the task set parameters
  *  recall that all processes should be run _at least_ as often as every (original) $T_i$
*  Place the processes in _new_ minor cycle
and major cycle until repetition appears
* If there is no option, $T_i$ can be increased
in cases where the application allows it
### Jitter(抖动) control
> Many applications need to minimise jitter in reading data from sensors or producing output to actuators
#### Alternative 1:
Choose minor cycle as greatest common divisor, and move processes
backwards in time when they clash
> absence of regularity(没有规律可循)
#### Alternative 2:
Run process B more often than necessary,
e.g. once every 75 time units.
$U=\sum {{C_i}\over{T_i}}$  
$U={{C_A}\over{75}}+{{C_B}\over{100}}\rightarrow$ $U'={{C_A}\over{75}}+{{C_B}\over{75}}$
#### Alternative 3:
A mix of the last two  
$U={{C_A}\over{75}}+{{C_B}\over{100}}\rightarrow$ $U'={{C_A}\over{50}}+{{C_B}\over{100}}$
#### If they don't fit
Break some process that does not fit
into two or more processes and run the
different parts in different minor cycles
## self-Check
During run-time:
* What is the de facto “deadline” for each
process?  
End of Minor Cycle.
* How does one know that processes
meet their deadlines?  
If they have never overrun.
* What happens if they don’t?
  

### What if dependent?
* Dependence can be due to sharing resources
or computation precedence requirements
* In a cyclic schedule:
  * Computation precedence automatically taken care of
as each instance of a process reads the inputs at the
beginning of a minor cycle (produced by another
process at the end of some prior minor cycle)
  * Mutual access to resources does not take place as
each process is running alone with no interruptions
## Symmary
### Disadvantage
* Cycles can be hard to determine and
can become looong ...
* Long WCET can create problems
* Sporadic processes are run periodically
    * Can lead to high processor utilisation
* Very inflexible!(We cannot do anything since it is off-line.)
### Advantage
* Simple at run-time
*  No overheads for context switching
*   Processes can exchange data without
the need for explicit (dynamic)
synchronisation
# Priority-based scheduling
 A preemptive method where the priority
of the process determines whether it
continues to run or it is disrupted
>”Most important process first!”
## RMS(Rate Monotonic Scheduling)
* On-line
* Preemptive(抢占式)
* Priority-based with fixed (static priorities
### Priorities
* Each process has a period $T_i$ that is the
shortest interval between its release
times
* Processes are assigned priorities
dependent on length of $T_i$
    * The shorter $T_i$ the higher the priority  
### Schedulability Tests
* Sufficient
  * if test is passed, then tasks are definitely
schedulable
  * if test is not passed, we don’t know 
* Necessary
  * if test is not passed, tasks are definitely not
schedulable
  * if test is passed, we don’t know
* Exact test
  * sufficient & necessary at the same time
**Theorem**: (sufficient condition)  
For $n$ processes, RMS will guarantee their
schedulability if the total utilisation(利用率)   
    $U=C_1/T_1+...+C_n/T_n$  
does not exceed the guarantee level  
    $G=n(2^{1/n} -1)$  
### When the test fails
1. Try testing the critical instant: Assume that
all processes are released simultaneously
at time 0, and then arrive according to
their periods
2. Check whether each process meets its
deadline for all releases before the first
deadline of the process with lowest priority
### Exact schedulability test
* Mathematical equations for computing
worst case response time $R_i$ for each
process 
* Response time: the time between the
release and the completion time
Process set schedulable if **$R_i ≤ T_i$** for all
processes
    
* Tasks suffer interference from higher
priority tasks  
$R_i=C_i+I_i$  
$R_i = C_i +\sum_{j\in hp(i)}[{{R_i} \over {T_j}}]C_j$  
hp= higher priority  
${W_i}^{n+1}=C_i +\sum_{j\in hp(i)}[{{W_i^n} \over {T_j}}]C_j$

## Theorems
* **Optimality**: RMS is optimal among
methods with fixed priority
(in what sense?)
* **Lowest upper bound**: For arbitrarily
large $n$, it suffices that processor
utilisation is $< 0.69$

Utilisation based test:  
$G=n(2^{1/n}-1)$