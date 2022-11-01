## Examination
* Written exam in January
* Laboratory exercises

## Course contents overview
* Three lectures on CPU scheduling
* Three lectures on distributed (networked)_(分布式)_ systems and associated
resource/timing aspects
* Three lectures on dependability _(可靠性)_
concepts and predictability _(可预测性)_ in
applications
* Final lecture: tying it all together
  
# This lecture
- Overview on Real-time systems and
why dependability matters
- We start with cyclic scheduling
  
## Real-time system
>**Systems that have explicit timing
requirements**

### Hard real-time systems
>The time that the
result of the computation is delivered is as
important as the result itself

### Deadlines
* Hard 
  > Not meeting any deadline is a
failure of the system
* Soft
  >It is desirable that deadlines are
met, but OK if they are missed every
now and then
* Firm
  >It is OK that they are missed now
and again, but after the deadline the
result is of no use

## Scheduling
>If **all** processes meet their deadlines
then the process set is **schedulable**.

* Performed **off-line** or **on-line**
* With information available **statically** or **dynamically**
* **Preemptive** or **non-preemptive**

### **Worst case execution time (WCET)**

### Cyclic scheduling
* A schedule is created based on
statically known and fixed parameters
(period, WCET)
* Off-line decision on which task runs &
when it runs  
  - When executing: Run the processes in predetermined order using a table look-up
* To run processes in the “right”
frequency find 
    * Minor cycle
    * Major cycle