- [From Hard to Soft RT Communication, overloads \& QoS](#from-hard-to-soft-rt-communication-overloads--qos)
  - [Two approaches](#two-approaches)
  - [The CAN bus](#the-can-bus)
    - [Predecessor to CAN (1976)](#predecessor-to-can-1976)
    - [Collisions](#collisions)
    - [Backoff](#backoff)
    - [Collisions \& non-determinism](#collisions--non-determinism)
    - [CAN protocol](#can-protocol)
    - [Message priority](#message-priority)
    - [Bitwise arbitration](#bitwise-arbitration)
    - [Response time analysis](#response-time-analysis)
    - [Worst Case Response](#worst-case-response)
    - [Interference and blocking](#interference-and-blocking)
    - [Solving recurrent equations](#solving-recurrent-equations)
    - [CAN: The original analysis](#can-the-original-analysis)
    - [The correct analysis](#the-correct-analysis)
    - [Revised computation](#revised-computation)
    - [CAN Error detection](#can-error-detection)
    - [Further developments](#further-developments)
# From Hard to Soft RT Communication, overloads & QoS
## Two approaches
* We will look at two well-known methods
for bus scheduling
  * [Time triggered (TTP)](Lecture5.md)
  * Event triggered (CAN)
## The CAN bus
### Predecessor to CAN (1976)
Ethernet:
* Current versions give high bandwidth
but time-wise nondeterministic
* CSMA/CD
  * Sense before sending on the medium
(Carrier Sense: CS)
  * All nodes broadcast to all (Multiple
Access: MA)
  * If collision(碰撞), back off and resend
(Collision Detection: CD)
### Collisions
* The original Ethernet has high
throughput but temporally
nondeterministic
### Backoff
* The period for waiting after a collision
* Each node waits up to two “slot times”
after a collision (random wait)
* If a new collision, the max. backoff
interval is doubled
* After 10 attempts the node stops
doubling
* After 16 attempts declares an error
### Collisions & non-determinism
* Model the network throughput and
compute probabilistic guarantees that
collisions will not be too often
  * Theoretical study: With 100Mbps, sending
1000 messages of 128 bytes per second,
there is a 99% probability that there will not
be a delay longer than 1 ms due to collisions
over ~1140 years
* If you cannot measure effects of
collisions, make collision resolution
deterministic!
### CAN protocol
* Highest bandwidth 1Mbps, ~40m
* CSMA/CR: broadcast to all nodes
* CR: Collision resolution by bit-wise
arbitration plus fixed priorities
(deterministic)
* Bus value is bitwise **AND** of the sent
messages
### Message priority
* The ID of the frame is located at the
beginning
  * initial bits that are inserted into the
bus are the ID-bits
  * ID also determines the priority of a
frame(lower ID higher priority)
  * priority of the frame increases as the
ID decreases 
### Bitwise arbitration
> Node 1 sends: 010...    ... sends rest of packet
> Node 2 sends: 100...    ... detects collision first
> Node 3 sends: 011...    ... detects collision next
* This is how ID for a message (frame)
works as its priority
* Two roles for message ID:
  * Arbitration via priority
  * Processes on every node that receives
a message, use the ID to work out
whether that message is any use to
them or not(ID is fixed)
### Response time analysis
* Scheduling analysis: Is every message
delivered before its deadline?
### Worst Case Response
Message response time =  
$J_i$: Jitter (from event to placement in queue)+   
$w_i$: Queuing time (response time of first bit)+   
$C_i$: Transmission time for whole message  
$R_i = J_i +w_i + C_i – t_{bit}\\$
$wi =t_{bit} + B_i + I_i$(identity by cpu schedualing)  
$B_i + I_i$ : Blocking and Interference time (as RMS)
### Interference and blocking
* $I_i$: waiting due to higher priority
messages, bounded if messages are
sent periodically
* $B_i$: waiting due to lower priority
messages, only one can start before i
* $J_i$: jitter, has to be assumed bounded
(by assumptions on the node CPU
scheduling policy!)
### Solving recurrent equations
* Blocking is fixed: max $C_j$ of all lower priority messages
* $w_i=B_i+\sum_{k\in hp(i)}\lceil (w_i+J_k+t_{bit})/T_k\rceil C_k$
* $w_i^0=B_i$
* $w_i^{n+1}=B_i+\sum_{k\in hp(i)}\lceil (w_i^n+J_k+t_{bit})/T_k\rceil C_k$
* After fixed point is reached: $B_i + w^{n+1}_i + C_i ≤ D_i ?$
### CAN: The original analysis
* … was Optimistic!
* Constructed a case where (old) analysis
shows schedulability but in fact
deadlines can be missed!
### The correct analysis
* Takes account of the fact that different
instances of the same message may
affect the length of a busy period
and
* All instances should be shown to meet
their deadlines!
> [Reading: Sec. 3.1 & 3.2, Davis et al. 07]
### Revised computation
* $R_m(q)=J_m+w_m(q)-qT_m+C_m$
* $q=_i, w(q)$ computes busy period for $i^{th}$
instance of message m
* To know range of q, i.e. how many
instances of message m are relevant,
we need to find the longest busy period
for message m, denoted $t_m$
### CAN Error detection
* If a transmitted message is corrupted the
Cyclic Redundancy Check (CRC) field will
be wrong
* The first receiver that notes this sends
000000
* Note that corruption at source and
corruption in transit cannot be
distinguished
* This works as long as a node is not
erroneous – Babbling idiot!
### Further developments
* New solutions to combine event-triggered and
time-triggered messages have appeared:
  * Simulating CAN over TTP, or TT-CAN
  * FlexRay
  * RT/TT-Ethernet
* In the past ten years there are many
standardisation efforts ongoing for
industrial IoT to make the link layer
more reliable, e.g. Time-Sensitive
Networking (TSN) for 5G