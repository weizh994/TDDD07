1. What is the role of the go-ahead message?
   The go-ahead message is a safety mechanism that ensure the robot gets the message from the server so than it can take actions.
2. What are the different message types?
    1. Victim reports
    2. Location messages
    3. Pheromone maps
    4. Stream data
3. In which file(s) will solutions for lab 2 go?
   * `tasks/task communicate.c`
4. How can you make sure that the robot only sends messages within its allocated time slot?
   * Make sure the period of COMMUNICATION TASK is 1000ms
5. What metric(s) do you plan to use in lab 2?
   1. How many stops are there when robot runs, the fewer the better.
   2. Assuming each message can be received by server since the period of COMMUNICATION TASK is 1000ms, How many messages with three critical type have been send successfully
   3. the waiting time in the minor cycle with the COMMUNICATION TASK
   4. the times of overrun happens during the agent running.
6. How do you plan to evaluate your solution?
   1. Counting the number of stops during the running of agent
   2. Counting the number of critical data which has been received by the server.
   3. How long the waiting time in the minor cycle with the COMMUNICATION TASK
   4. Counting the times of overrun happens during the agent running.
7. When is your solution satisfactory?
   1. No critical data is missed.
   2. The agent only sends message in its time slots.
   3. The schedual does not degrage from lab1
   4. The agent can run with other robots concourrently. 
   5. The fitted priorities are given to different message types.
8. How do you ensure that the performance you had in lab 1 does not degrade due to lab 2?
   1. Ensure the period of COMMUNICATION TASK is 1000ms in lab1's scdualing.
   2. Ensure each running time of COMMUNICATION TASK will not cause the overrun of the minor cycle.