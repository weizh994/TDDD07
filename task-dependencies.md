* Mission task
  No specific dependencies.
  
  Needs to be ran after the Report task if we want to hit the first if-statement.
  
  Needs to have received a command from the Mission Control if we want to hit the second if-statement.
  
  Since the task runs a for-loop, we might want to think about the maximum feasible size of the `mission_queue`.
* Navigate task
  Produces data that is later processed by the Control task.
  
  Doesn't have any branching, so we only have to consider the size of the `navigation_queue` when timing the task.
* Control task
  Timing is important for the localisation algorithm to work properly. Too slow and the approximation will be very inaccurate. Too fast and the robot can't process the requests. Should not run more often than 300 ms.
* Avoid task
  Movement commands will overwrite each other, so it's important that the Avoid task is run after the Control task to ensure that the robot can run the appropriate movement commands to avoid collision.
* Refine task
  No specific dependencies.
* Report task
  The Report task should run *at least* as often as the Refine task to avoid losing potential victims. 
* Communicate task
  Will only be allowed to run every 1000 ms in lab 2. Should probably be ran last since almost all other tasks provide information to the Control task.
