- [Overview: Next three lectures](#overview-next-three-lectures)
- [Reading material](#reading-material)
- [Distributed model of computing](#distributed-model-of-computing)
- [Reasons for distribution](#reasons-for-distribution)
- [This lecture](#this-lecture)
- [Overloads with one CPU](#overloads-with-one-cpu)
- [Datacentre Scheduling](#datacentre-scheduling)
- [Overview](#overview)
- [Two mechanisms](#two-mechanisms)
- [Estimating resource usage](#estimating-resource-usage)
  - [Skewness and temprature](#skewness-and-temprature)
- [Load adaptation algorithm](#load-adaptation-algorithm)
- [Green computing adaptation](#green-computing-adaptation)
- [Summary: Sharing the load](#summary-sharing-the-load)
  - [Questions](#questions)
- [Time in Distributed Systems](#time-in-distributed-systems)
  - [Local vs. global clock](#local-vs-global-clock)
- [Event ordering](#event-ordering)
## Overview: Next three lectures
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
* Note specially that from now on we
have articles covering our topics
* These are posted for each lecture,
linked from the course web page!
*  For this lecture, see reading guidelines
– Xiao et al. 2013 
## Distributed model of computing
* Multiple processes
* Disjoint address spaces
* Inter-process communication
* Collective goal
## Reasons for distribution
* Locality
  * Engine control, brake system, gearbox control, airbag,…
  * Clients and servers
* Organisation of functions/cod
  * An extension of modularisation, avoiding single points of failure
* Loadj sharing
  * Web services, search, parallelisation of
heavy computations
> Multicore scheduling:
research topic - not part of
the course!
## This lecture
1. Can we guarantee scheduling of tasks
arriving from distributed nodes over a set
of CPUs in the cloud? 
2. What are the fundamental timerelated issues in distributed systems?
   * Time, clocks, and ordering of events
   * And why faults cannot be ignored...
## Overloads with one CPU
* What happens if the task arrival rate is
not predetermined?
* What if the load is not predictable?
## Datacentre Scheduling
* Tasks are encapsulated in virtual machines (VM)
* Arrive from different nodes and their resource need varies over time 
* Goals of scheduling: Allocate VMs to physical
machines (PMs) such that 
  * No PM is overloaded so that performance of
tasks is not degraded
  * No PM is severely underloaded so that
energy is not wasted
* As load changes, decide which VM to migrate!
## Overview
* Skewness: Notion that describes uneven
utilisation of resources - minimise
skewness over a set of PMs
* To deal with fluctuations it helps to
predict the forthcoming load on each PM 
* Identify the candidates for overload
  * Hotspot solver
*  Identify any PM that runs at lower
utilisation than an energy-efficient one
   * Coldspot solver
## Two mechanisms
* The hotspot solver detects if *any* PM’s
sum of resource usage is above the hot
threshold
  *  It will migrate away some VM from that PM
* The coldspot solver detects if the PMs
are on average running at a utilisation
below the green computing (GC)
threshold
  * It will migrate away the VMs from some cold
PM to prepare it for shut down
## Estimating resource usage
* **Predictor**: Based on observation O(t)
and previous estimate E(t-1) they
suggest the Fast Up Slow Down (FUSD)
estimation model:
> E(t) =
α . E(t-1) + (1 -
α). O(t)

where
α is a parameter (experimentally) chosen
as -0.2 when O(t) is rising and 0.7 when O(t) is
falling
### Skewness and temprature
* The skewness for a server p (here a PM)
as a function of the individual resources
ri used within it (here sum of VM
utilisations for a resource
ri) and the
average resource utilisation
$\bar{r}$
* A hotspot is a server that has high
temperature 
> $$temper4ature(p)=\sum_{r\in R}(r-r_t)^2$$
## Load adaptation algorithm
* Order the PMs, choose a PM with highest
temperature first
* Choose one VM on that PM that would reduce
PM’s temperature (if migrated away)
* If many such VMs, choose the one that
increases skewness the least
* Find a PM that can accept this VM and not
become a hot spot
* If many such PMs, choose the one that reduces
its skewness most after accepting the VM
* If no such PM can be found proceed to the next
VM on the hot PM (and eventually to next PM)
## Green computing adaptation
* The algorithm is invoked when average PM
resource utilisation is below the GC threshold
* A PM is a cold spot if the utilisation of all of its
different resources is below a given cold
threshold
* Start with the PM that has the lowest
utilisation for *memory* below the cold threshold
* Try to migrate all its VMs to another PM that
will not become hot/cold after migration (will
stay below a *warm* threshold) to avoid future
hotspots
## Summary: Sharing the load
* A first attempt to study load adaptation
vs. energy optimisation
* Clearly shows how scheduling is related
to load control
* Note that there are no performance
guarantees (live migration is expected
to somewhat increase response time) 
* Check the scalability arguments!
### Questions
* Can we temporally order all events in a
distributed system?
  * Only if we can timestamp them with a
value from a global (universal) clock
*  Can we draw any conclusions if we do
not have a global clock? 
   * What about a set of local clocks?
   * What if no clocks at all?
## Time in Distributed Systems
* Physical time vs. Logical time
* Example clock synchronisation algorithm
* Logical clocks
* Vector clocks
### Local vs. global clock
* Most physical (local) clocks are not
always accurate
* What is meant by accurate?
  *  Agreement with UTC
  *  Coordinated Universal Time (UTC) is in turn
an adjusted time to account for the discrepancy between time measured based on rotation of earth, and the International
Atomic Time (IAT)
* An atomic global clock accurately
measures IAT
* If we rely on value of local clocks, they need to be synchronised regularly
