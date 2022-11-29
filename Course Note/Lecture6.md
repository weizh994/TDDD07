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
  - [QoS guarantees instead of timing guarantees, moving on to soft RT](#qos-guarantees-instead-of-timing-guarantees-moving-on-to-soft-rt)
    - [From messages to flows](#from-messages-to-flows)
    - [Overview](#overview)
    - [Adaptation](#adaptation)
    - [How do we characterise QoS?](#how-do-we-characterise-qos)
    - [QoS guarantees](#qos-guarantees)
    - [Application categories](#application-categories)
  - [QoS mechanisms](#qos-mechanisms)
    - [WFQ rough description](#wfq-rough-description)
    - [Class-based link sharing](#class-based-link-sharing)
    - [Buffer management](#buffer-management)
  - [Network-wide: Intserv, Diffserv](#network-wide-intserv-diffserv)
    - [Across network nodes](#across-network-nodes)
    - [IntServ](#intserv)
    - [QoS specifications](#qos-specifications)
    - [Not deployed successfully!](#not-deployed-successfully)
    - [DiffServ (1998)](#diffserv-1998)
    - [Service classes](#service-classes)
    - [Scalability of DiffServ](#scalability-of-diffserv)
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
## QoS guarantees instead of timing guarantees, moving on to soft RT
### From messages to flows
* When there is overload:
* Need to allocate available resources
  * To some applications/flows (which ones?)
* Applications may need to adapt as load
mix and resource dynamics changes
  *  Same flow can get different treatments at
different nodes
### Overview
* Some basic notions: QoS parameters,
requirement vs. provision
* We focus on allocation (not adaptation)
* Quality of service in networked (wired)
applications
  * QoS mechanisms at nodes
  * Network-wide: Intserv, Diffserv
* Application nodes (edge nodes)
  * CPU
  * Memory (buffer space)
  * Power
* Links
   * Bandwidth
* Forwarding nodes: buffer space
* Providing QoS: ability to provide
resource assurance and service
differentiation in a network
* Service differentiation
  * When there are overloads some
connections/packets/applications are
preferred to others
* Fairness
  * All should get something
### Adaptation
* Orthogonal(正交) to both
  * Adaptive ones may adapt to make room for
non-adaptive ones
### How do we characterise QoS?
* Application level requirements
  * Image quality (resolution/sharpness),
viewing size, voice quality
* Enforcement (provision) level indicators
  * Bandwidth guarantee (measured as
throughput)
  * delay
  * jitter
  * loss ratio
  * reliability (lack of erroneous messages and
duplications)
### QoS guarantees
* Need description of required/provided
service
  * service commitment: e.g. % of dropped
packets, average end-to-end delay
* In presence of a traffic model
  * Traffic profile: definition of the flow entitled
to the service e.g. by arrival rates,
burstiness, packet size,…
### Application categories
* Elastic or inelastic
  * Mail vs. video conference
* Interactive or non-interactive
  * Voice communication vs. emergency warning at accidents
* Tolerant or non-tolerant
  * MPEG video-on-demand vs. automated
control
* Adaptive or non-adaptive
  * Audio/video streaming vs. electronic trading
* Real-time or non-real-time
  * IP-telephony vs. A/V on demand (streaming)
## QoS mechanisms
* Admission control
  * To manage the limited resource in presence
of oversubscriptions
  * Examples:
    * Policing (does the application ask for the same
level of resources that was assumed as a traffic
profile?)
    * Shaping (influencing the rate of packets fed into
the network to adapt to current resource picture)
* Scheduling
  * Which packet should be forwarded at
the network layer (to serve which QoS
parameters)?
  * No QoS: FIFO
  * Fixed priority scheduling (similar to CAN
when selecting from a queue)
    * With no guarantees on per packet delay,
some can starve
* Weighted Fair Queuing (WFQ)
* Class based queuing
* Buffer management
### WFQ rough description
* Instead of allocating to all packets from
one flow at a time, imagine an
approximation to an ideally fair
scheduler: one packet from each flow in
a given time interval
* Allocate the outgoing bandwidth
according to a weight for each flow
* For flows that are described as a leaky
bucket, the max delay per packet is
computable
### Class-based link sharing
* Hierarchical allocation of the bandwidth
according to traffic classes
* Each class allocated a max share under
a given interval, and the excess shared
according to some sharing policy
### Buffer management
* Scheduling is enough as long as buffers
are infinite
  * In reality buffers (queues) get full during
overloads
  * Shall we drop all the packets arriving after
the overload starts?
* Buffer management is about
determining which stored packets to
drop in preference to incoming ones
  * Can adopt differentiated drop policies
## Network-wide: Intserv, Diffserv
### Across network nodes
* IP datagrams delivered with best effort
* **IntServ** was defined to deliver IP
packets with differentiated treatment
across multiple routers (1994)
* Introduced 3 service classes:
  * BE: Best effort
  * CL: Controlled Load (acceptable service
when no overload)
  * GS: Guaranteed Service (strict bounds on eto-e delay)
### IntServ
* Each router keeps a “soft state” for each
flow (a session) currently passing
through it
  * GS: the leaky-bucket-based requirements
from a flow induce a max local delay in each
router
* The soft state is created with a
reservation scheme RSVP, and refreshed
while the session is in progress
### QoS specifications
* T-spec (traffic specification)
  * A token bucket specification
    * token rate - r
    * bucket size - b
    * peak rate - p
    * maximum packet size - M
    * minimum policed unit - m
* R-spec (reservation specification)
  * Service Rate – R
    * The bandwidth requirement
  * Slack Term – S
    * The delay requirement
### Not deployed successfully!
* IntServ met resistance for several
reasons, including:
  * Not all routers RSVP enabled
  * Set up time can be proportionately long
compared to session time
  * Interactive sessions need to set up a path at
both ends
  * Dynamic and major changes in traffic
pattern
### DiffServ (1998)
* Based on resource provisioning (for a
given SLA) as opposed to reservation
* Applied to traffic aggregates as opposed
to single flows
* Forwarding treatment as opposed to
end-to-end guarantees
* Edge routers labelling packets/flows in
forwarding to next domain, and
accepting only in-profile packets when
accepting from other domains
### Service classes
* Marked with two bits:
  * (P) Premium class: intended for
preferential treatment to which
policing is applied with a small bucket
size
  * (A) Assured class: pass through
policing with a bucket size equal to
the given burst
  * Packets with A-bit compete with best
effort packets when buffers get full
### Scalability of DiffServ
* Admission control is now at edge nodes
not every path on a route
* No set-up time and per-flow state in
each router
* At the cost of no end-to-end guarantees