/**
 * @file	scheduler.c
 * @author  Eriks Zaharans and Massimiiliano Raciti
 * @date    1 Jul 2013
 *
 * @section DESCRIPTION
 *
 * Cyclic executive scheduler library.
 */

/* -- Includes -- */
/* system libraries */
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>
/* project libraries */
#include "scheduler.h"
#include "task.h"
#include "timelib.h"

/* -- Defines -- */

/* -- Functions -- */

/**
 * Initialize cyclic executive scheduler
 * @param minor Minor cycle in miliseconds (ms)
 * @return Pointer to scheduler structure
 */
scheduler_t *scheduler_init(void)
{
	// Allocate memory for Scheduler structure
	scheduler_t *ces = (scheduler_t *) malloc(sizeof(scheduler_t));

	return ces;
}

/**
 * Deinitialize cyclic executive scheduler
 * @param ces Pointer to scheduler structure
 * @return Void
 */
void scheduler_destroy(scheduler_t *ces)
{
	// Free memory
	free(ces);
}

/**
 * Start scheduler
 * @param ces Pointer to scheduler structure
 * @return Void
 */
void scheduler_start(scheduler_t *ces)
{
	// Set timers
	timelib_timer_set(&ces->tv_started);
	timelib_timer_set(&ces->tv_cycle);
}

/**
 * Wait (sleep) till end of minor cycle
 * @param ces Pointer to scheduler structure
 * @return Void
 */
void scheduler_wait_for_timer(scheduler_t *ces)
{
	int sleep_time; // Sleep time in microseconds

	// Calculate time till end of the minor cycle
	sleep_time = (ces->minor * 1000) - (int)(timelib_timer_get(ces->tv_cycle) * 1000);

	// Add minor cycle period to timer
	timelib_timer_add_ms(&ces->tv_cycle, ces->minor);

	// Check for overrun and execute sleep only if there is no
	if(sleep_time > 0)
	{
		// Go to sleep (multipy with 1000 to get miliseconds)
		usleep(sleep_time);
	}
}

/**
 * Execute task
 * @param ces Pointer to scheduler structure
 * @param task_id Task ID
 * @return Void
 */
void scheduler_exec_task(scheduler_t *ces, int task_id)
{
	switch(task_id)
	{
	// Mission
	case s_TASK_MISSION_ID :
		task_mission();
		break;
	// Navigate
	case s_TASK_NAVIGATE_ID :
		task_navigate();
		break;
	// Control
	case s_TASK_CONTROL_ID :
		task_control();
		break;
	// Refine
	case s_TASK_REFINE_ID :
		task_refine();
		break;
	// Report
	case s_TASK_REPORT_ID :
		task_report();
		break;
	// Communicate
	case s_TASK_COMMUNICATE_ID :
		task_communicate();
		break;
	// Collision detection
	case s_TASK_AVOID_ID :
		task_avoid();
		break;
	// Other
	default :
		// Do nothing
		break;
	}
}

double run_task(scheduler_t *ces, int task_id) {
	double start_time = timelib_unix_timestamp();
	scheduler_exec_task(ces, task_id);
	double end_time = timelib_unix_timestamp();
	return end_time - start_time;
}

/**
 * Run scheduler
 * @param ces Pointer to scheduler structure
 * @return Void
 */
void scheduler_run(scheduler_t *ces)
{
	/* --- Local variables (define variables here) --- */

	/* --- Set minor cycle period --- */
	ces->minor = 500;

	double refine_time = 0;
	double report_time = 0;
	double mission_time = 0;
	double navigate_time = 0;
	double control_time = 0;
	double avoid_time = 0;
	double avoid_time_max = 0;

	double total_running_time_start = timelib_unix_timestamp();

	int ITERATIONS = 300;

	for (int i= 0; i < ITERATIONS; i++) {
		double task_time = 0;
		/* refine_time += run_task(ces, s_TASK_REFINE_ID); */
		/* report_time += run_task(ces, s_TASK_REPORT_ID); */
		/* mission_time += run_task(ces, s_TASK_MISSION_ID); */
		/* navigate_time += run_task(ces, s_TASK_NAVIGATE_ID); */
		/* control_time += run_task(ces, s_TASK_CONTROL_ID); */

		task_time = run_task(ces, s_TASK_AVOID_ID);
		avoid_time += task_time;
		avoid_time_max = (task_time > avoid_time_max) ? task_time : avoid_time_max;
	
		printf("iteration: %d\n", i);
	}
	
	double total_running_time_end = timelib_unix_timestamp();
	double total_running_time = total_running_time_end - total_running_time_start;

	refine_time /= ITERATIONS;
	report_time /= ITERATIONS;
	mission_time /= ITERATIONS;
	navigate_time /= ITERATIONS;
	control_time /= ITERATIONS;
	avoid_time /= ITERATIONS;

	printf("refine_time: %f\n", refine_time);
	printf("report_time: %f\n", report_time);
	printf("mission_time: %f\n", mission_time);
	printf("navigation_time: %f\n", navigate_time);
	printf("control_time: %f\n", control_time);
	printf("avoid_time: %f\n", avoid_time);
	printf("avoid_time_max: %f\n", avoid_time_max);
	printf("total_running_time: %f\n", total_running_time);

	// Major cycle
	/* while (1) { */
	/* 	// Minor cycle 1 */
	/* 	scheduler_exec_task(ces, s_TASK_MISSION_ID); */
	/* 	scheduler_wait_for_timer(ces); */
		
	/* 	// Minor cycle 2 */
	/* 	scheduler_wait_for_timer(ces); */
		
	/* 	// Minor cycle 3 */
	/* 	scheduler_wait_for_timer(ces); */
		
	/* 	// Minor cycle 4 */
	/* 	scheduler_wait_for_timer(ces); */
	/* } */
	/* scheduler_exec_task(ces, s_TASK_REFINE_ID); */
	/* scheduler_exec_task(ces, s_TASK_REPORT_ID); */
	/* double start_time = timelib_unix_timestamp(); */
	/* scheduler_exec_task(ces, s_TASK_MISSION_ID); */
	/* double end_time = timelib_unix_timestamp(); */
	/* double task_time = end_time - start_time; */
	/* printf("task_time: %f", task_time); */
	printf("hello world");
	

	/* --- Write your code here --- */

}
