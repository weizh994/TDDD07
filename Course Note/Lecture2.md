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

* Each process $P_i$ is run periodically every $T_i$ (i.e. should be completed once every $T_i$)
* Processes are placed in _minor cycle_ and _major cycle_ until repetition appears
* Check: Are all process instances runnable with the given periods and estimated WCETs?
* If not, reconsider the minor/major cycle and/orsome process parameters 

### When is the schedule correct?
* All processes should be run at least as often as every (original) $T_i$
* All processes fit in the _minor cycles_ they are placed in  

and  
* Repetition appears!(**反复出现**)

### Next try
* In either case we need to
  *  change the task set parameters
  *  recall that all processes should be run _at least_ as often as every (original) $T_i$
*  Place the processes in _new_ minor cycle
and major cycle until repetition appears
* If there is no option, $T_i$ can be increased
in cases where the application allows it

## self-Check
During run-time:
* What is the de facto “deadline” for each
process?
* How does one know that processes
meet their deadlines?
* What happens if they don’t?

# RMS(Rate Monotonic Scheduling)
* On-line
* Preemptive(抢占式)
* Priority-based with fixed (static priorities


**Theorem**: (sufficient condition)  
For $n$ processes, RMS will guarantee their
schedulability if the total utilisation(利用率)   
    $U=C_1/T_1+...+C_n/T_n$  
does not exceed the guarantee level  
    $G=n(2^{1/n} -1)$  
    
    
    
$R_i = C_i +\sum_{j\in hp(i)}[{{R_i} \over {T_j}}]$