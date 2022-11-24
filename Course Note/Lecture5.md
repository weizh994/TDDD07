- [Distributed Systems \& Real-time Communication](#distributed-systems--real-time-communication)
  - [Overview](#overview)
  - [Reading material](#reading-material)
  - [Timing of events](#timing-of-events)
    - [Different views](#different-views)
    - [Event detection](#event-detection)
    - [Security in industrial control](#security-in-industrial-control)
  - [Safety-critical systems](#safety-critical-systems)
    - [Causality(因果)](#causality因果)
    - [Questions](#questions)
  - [Clock synchronisation](#clock-synchronisation)
    - [Lamport/Melliar-Smith Algorithm](#lamportmelliar-smith-algorithm)
    - [Faulty clocks](#faulty-clocks)
    - [Bound on the faulty clocks](#bound-on-the-faulty-clocks)
  - [Event ordering](#event-ordering)
  - [Logical time](#logical-time)
    - [Happened before$\\prec$](#happened-beforeprec)
    - [Lamport’s Logical clocks](#lamports-logical-clocks)
    - [Implementing logical clocks](#implementing-logical-clocks)
  - [Vector clocks (VC)](#vector-clocks-vc)
    - [Implementation of VC](#implementation-of-vc)
    - [Precedence in VC](#precedence-in-vc)
    - [Concurrency and VC](#concurrency-and-vc)
  - [Pros and cons](#pros-and-cons)
    - [Distributed snapshot](#distributed-snapshot)
  - [Recap](#recap)
    - [Fundamental reason](#fundamental-reason)
  - [Real-time message scheduling](#real-time-message-scheduling)
    - [Message constraints](#message-constraints)
    - [New resource](#new-resource)
    - [Two approaches](#two-approaches)
  - [Time-triggered protocol (TTP)](#time-triggered-protocol-ttp)
    - [Temporal firewall](#temporal-firewall)
    - [Message scheduling](#message-scheduling)
    - [Communication protocol](#communication-protocol)
    - [TTP error detection](#ttp-error-detection)
# Distributed Systems & Real-time Communication
## Overview
From one CPU to networked CPUs:
* First, from one CPU to multiple CPUs
  * Allocating VMs on multiple CPUs: Cloud
* Next, fully distributed systems
  * fundamental issues with timing and order of
events
* Next, hard real-time communication
  * Guaranteed message delivery within a
deadline, bandwidth as a resource
* Finally: QoS guarantees instead of
timing guarantees, focus on soft RT
## Reading material
* Internal clock synchronisation 
  * Slides are a summary of the article
(up to section 2.2) in
https://dl.acm.org/doi/pdf/10.1145/2455.2457
* Logical clocks
  * Chapter 6 (specially sections 6.1 and
6.2) of the Attiya et al. book
## Timing of events
> Consider a nuclear reactor equipped
with many sensors that monitor
different entities (e.g. Values of
pressures, flows in various pipes). If a
pipe ruptures, a number of entities will
show values outside their normal
operating ranges. When an entity enters
its alarm region an alarm event is
signalled to the operator
### Different views
* The (global) system view:
  * First, the pressure in the ruptured pipe
changes abruptly
  * Then the flow changes causing many other
entities to react
  * These in turn generate own alarms
* The operator view:
  * Operator sees a set of (correlated) alarms,
called an “alarm shower”
  * Operator wants to identify the primary event

### Event detection
* The computer system must assist the
operator to detect the primary event
that triggers the alarm shower
* Knowledge of exact temporal order of
the events is helpful in identifying the
primary event
### Security in industrial control
* [Smart factories will become a reality](https://www.youtube.com/watch?v=CIAijpyN3_4)


## Safety-critical systems
* Inaccurate local clocks can be a problem
if the result of computations at different
nodes depend on time
  * If the brake signal is issued separately in
different wheels, will the car stop and when?
### Causality(因果)
* If event e occurs after event e’ then e
cannot be the cause of e’
* If event e occurs before event e’ then e
can be the cause of e’ (but need not be)
* Temporal order is necessary but not
sufficient for causal order
### Questions
* Can we temporally order all events in a
distributed system?
  * Only if we can timestamp them with a
value from a global (universal) clock
* Can we draw any conclusions if we do
not have a global clock?
  * What about a set of local clocks?
  * What if no clocks at all?
## Clock synchronisation
Two types of algorithms:
* External synchronisation
  * Tries to keep the values of a set of
clocks agree with an accurate clock,
within a skew of δ
* Internal synchronisation
  * Tries to keep a set of clock values
close to each other with a maximum
skew of δ
> skew: max earliness or laterness of a tick of a clock relative a ref. clock
### Lamport/Melliar-Smith Algorithm
* Internal synchronisation of n clocks
* Each clock reads the value of all other
clocks at regular intervals(固定间隔)
  * – If the value of some clock differs from value
of own clock by more than δ, that clock
value is replaced by own clock value
  * The average of all clocks is computed at
each node
  * Own clock value is updated to the average
value
### Faulty clocks
* If a clock skew exceeds δ then its value
is eliminated – does not “harm” other
clocks
* What if the skew is exactly δ? 
  * check it as an exercise!
* What is the worst case?
### Bound on the faulty clocks
* To guarantee that the algorithm will
keep all **non-faulty** clocks within δ we
need an assumption on the number of
faulty clocks
* For **f** faulty clocks the algorithm works if
the number of clocks **n >3f**
## Event ordering
* In the absence of clock synchronisation
we may use order that is intrinsic in an
application
## Logical time
* Based on event counts at each node
* May reflect causality(可反映出因果关系)
* Sending a message always precedes(之前)
receiving it
* Messages sent in a sequence by one
node are (potentially) causally related to
each other
  *  I do not pay for an item if I do not first
check the item’s availability
### Happened before$\prec$
* Assume each process has a
monotonically increasing local clock
* Rule 1: if the time for event x is before
the time for event y then x$\prec$y
* Rule 2: if x denotes sending a message
and y denotes receiving the same
message then x$\prec$y
* Rule 3: $\prec$ is transitive(可传递的)
### Lamport’s Logical clocks
* Logical clock: An event counter that
respects the “happened before” ordering
* Partial order: Hence, any pair of events
that are not in the “happened before”
relation are treated as concurrent
### Implementing logical clocks
LC “time-stamps” each event
* Rule 1: Each time a local event takes
place, increment LC by 1
* Rule 2: Each time a message m is sent
the LC value at the sender is appended
to the message (m_LC)
* Rule 3: Each time a message m is
received set LC to max(LC, m_LC)+1
* x$\prec$y → LC(x) < LC(y)
* Note that: LC(x) < LC(y) does not imply x$\prec$y
## Vector clocks (VC)
* Every node maintains a vector of
counted events (one entry for each
other node)
* VC for event e, VC(e) = [1,…,n], shows
the perceived count of events at nodes
1,…,n
* VC(e)[k] denotes the entry for node k
### Implementation of VC
* Rule 1: For each local event increment own
entry
* Rule 2: When sending message m, append to
m the VC(send(m)) as a timestamp T
* Rule 3: When event x is “receiving a message”
at node i,
  *  increment own entry: VC(x)[i]:= VC(x)[i]+1
  *  For every entry j in the VC: Set the entry to
max (T[j], VC(x)[j])
### Precedence in VC
* Relation < on vector clocks defined by:
VC(x) < VC(y) **iff**
  - For all i: VC(x)[i] ≤ VC(y)[i]
  - For some i: VC(x)[i] < VC(y)[i]
* It follows that event x $\prec$ event y if
VC(x) < VC(y)
### Concurrency and VC
Hence:
* VC(x) < VC(y) **iff** x$\prec$y
* If neither VC(x) < VC(y) nor
VC(y) < VC(x) then x and y are
concurrent(并发)
## Pros and cons
* Vector clocks are a simple means of
capturing “happened before” exactly
>VC(x) < VC(y) **iff** x$\prec$y  
Recall: LC(x) < LC(y)$\nrightarrow$ x$\prec$y
* For large systems we have resource
issues (bandwidth wasted), and
maintainability issues
### Distributed snapshot
* Vector clocks help to synchronise at
event level
* But reasoning about response times and
fault management needs quantitative
bounds 
## Recap
* In the scheduling lectures we looked at
single processor hard real-time
scheduling
* RT communication is about scheduling
the communication medium
### Fundamental reason
Two interaction models in distributed
systems
* Synchronous model
  -  Assumes that the rate of computation at
different nodes can be related, and there is
a bound on maximum message exchange
latency
     - Can use timers and
timeouts
* Asynchronous model
  * Has no assumptions on rate of processing in
different nodes, or bounds on message
latency
    * Only coordination possible
at event level
## Real-time message scheduling
* Needed for providing the bound on
maximum message delay
* Essential for reasoning about system
properties under the synchronous model
of distributed systems
  *  e.g. proof that a service will be
provided despite a single node crash
will need bounds on message delay
### Message constraints
* Message delivery time bound dictated
by application
  * So called end-to-end deadlines
* Example: shortly after each driver
braking, brake light must know it in
order to turn on!
### New resource
|                       | Single Node                    | Distributed                   |
| :-------------------- | :----------------------------- | :---------------------------- |
| Resource              | CPU                            | Bandwidth                     |
| Scheduled<br>element  | Task/process                   | Message                       |
| Demand on<br>resource | WCET &<br>interarrival         | Message size &<br>frequency   |
| Performance<br>metric | Deadlines met &<br>Utilisation | Message delay &<br>Throughput |
### Two approaches
* We will look at two well-known methods
for bus scheduling
  * Time triggered(触发) (TTP)
  *  Event triggered (CAN)
* Used extensively in aerospace and
automotive applications respectively
## Time-triggered protocol (TTP)
* Reading material: Section I-III in
Kopetz & Bauer 2003
* Time division multiple access (TDMA)
### Temporal firewall
* CC provides temporally accurate state
information (via clock synchronisation)
* When the data is temporally not valid, it
can no longer be exchanged
### Message scheduling
* TDMA round implemented through the
MEDL (message description list)
  * The communication system (collection of
CC:s and the bus) reads a message from the
CNI of sending node at the apriori known
fetch instant and places in the CNI of all
other nodes at the apriori known delivery
instant, replacing the previous value
* No constraints on (local) node CPU
scheduling
### Communication protocol
* Message Description List (MEDL):
allocates a pre-defined slot within which
each node can send its (pre-defined)
message
### TTP error detection
> BG: Buss Guardian (stops babbling idiots)  
>CRC: for corruption in transit
* The major success of the TTP is due to
the possibility of detecting additional
faults including arbitrary (Byzantine)
faults