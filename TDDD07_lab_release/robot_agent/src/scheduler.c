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
#include "file.h"

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
	scheduler_t *ces = (scheduler_t *)malloc(sizeof(scheduler_t));

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
	// printf("ces->minor = %d\nces->tv_cycle = %f\n", ces->minor, timelib_timer_get(ces->tv_cycle));
	sleep_time = (ces->minor * 1000) - (int)(timelib_timer_get(ces->tv_cycle) * 1000);

	// Add minor cycle period to timer
	timelib_timer_add_ms(&ces->tv_cycle, ces->minor);

	// Check for overrun and execute sleep only if there is no
	if (sleep_time > 0)
	{
		// Go to sleep (multipy with 1000 to get miliseconds)
		printf("Did not overun the timer.\n");
		usleep(sleep_time);
	}
	else if (sleep_time < 0)
	{
		printf("Overran the timer!!\n");
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
	switch (task_id)
	{
	// Mission
	case s_TASK_MISSION_ID:
		task_mission();
		break;
	// Navigate
	case s_TASK_NAVIGATE_ID:
		task_navigate();
		break;
	// Control
	case s_TASK_CONTROL_ID:
		task_control();
		break;
	// Refine
	case s_TASK_REFINE_ID:
		task_refine();
		break;
	// Report
	case s_TASK_REPORT_ID:
		task_report();
		break;
	// Communicate
	case s_TASK_COMMUNICATE_ID:
		task_communicate();
		break;
	// Collision detection
	case s_TASK_AVOID_ID:
		task_avoid();
		break;
	// Other
	default:
		// Do nothing
		break;
	}
}
FILE *fp = NULL;
#define ITERATIONS 40
#define TASK_NUM 8
// Runs the given task ID and updates task_times for that id
#define RUN_AND_UPDATE(id)                                   \
	{                                                        \
		task_times[id] += run_task(ces, id, &max_times[id]); \
		task_num[id]++;                                      \
		fp = fopen("data.txt", "w+");                        \
		fprintf(fp, "%d takes %lf\n", id, task_times[id]);   \
		fclose(fp);                                          \
	}

const char *TASK_NAMES[] = {
	"nop",
	"mission",
	"navigate",
	"control",
	"refine",
	"report",
	"communicate",
	"avoid",
};

/**
 * Runs given task and returns elapsed time, updates the given max time if it changed
 * @param scheduler_t* ces Pointer to scheduler structure
 * @param int task_id The task ID to run
 * @param double* curr_max_time Pointer to the current max time for the given task
 * @return double elapsed time in milliseconds
 */
double run_task(scheduler_t *ces, int task_id, double *curr_max_time)
{
	double start_time = timelib_unix_timestamp();
	scheduler_exec_task(ces, task_id);
	double end_time = timelib_unix_timestamp();
	double elapsed_time = end_time - start_time;

	*curr_max_time = (elapsed_time > *curr_max_time) ? elapsed_time : *curr_max_time;
	return elapsed_time;
}

/**
 * Run scheduler
 * @param ces Pointer to scheduler structure
 * @return Void
 */
void scheduler_run(scheduler_t *ces)
{
	// Set minor cycle period
	ces->minor = 105;

	// Array for storing the elapsed time for each task. Initially stored as a
	// sum of the measured values, with the average taken at the end.
	double task_times[TASK_NUM];
	// Array for storing the maximum measured time for each task.
	double max_times[TASK_NUM];

	int task_num[TASK_NUM];

	double total_running_time_start = timelib_unix_timestamp();

	printf("Starting schedule...\n");
	scheduler_exec_task(ces, s_TASK_AVOID_ID);

	scheduler_start(ces);
	// Run tasks and track time
	while (1)
	{
		// See RUN_AND_UPDATE macro above
		RUN_AND_UPDATE(s_TASK_MISSION_ID);
		RUN_AND_UPDATE(s_TASK_COMMUNICATE_ID);
		RUN_AND_UPDATE(s_TASK_NAVIGATE_ID);
		RUN_AND_UPDATE(s_TASK_CONTROL_ID);
		RUN_AND_UPDATE(s_TASK_AVOID_ID);
		scheduler_wait_for_timer(ces);

		RUN_AND_UPDATE(s_TASK_MISSION_ID);
		RUN_AND_UPDATE(s_TASK_REFINE_ID);
		RUN_AND_UPDATE(s_TASK_REPORT_ID);
		RUN_AND_UPDATE(s_TASK_AVOID_ID);
		scheduler_wait_for_timer(ces);

		RUN_AND_UPDATE(s_TASK_MISSION_ID);
		RUN_AND_UPDATE(s_TASK_AVOID_ID);
		scheduler_wait_for_timer(ces);

		RUN_AND_UPDATE(s_TASK_MISSION_ID);
		RUN_AND_UPDATE(s_TASK_NAVIGATE_ID);
		RUN_AND_UPDATE(s_TASK_CONTROL_ID);
		RUN_AND_UPDATE(s_TASK_AVOID_ID);
		scheduler_wait_for_timer(ces);

		RUN_AND_UPDATE(s_TASK_MISSION_ID);
		RUN_AND_UPDATE(s_TASK_REFINE_ID);
		RUN_AND_UPDATE(s_TASK_REPORT_ID);
		RUN_AND_UPDATE(s_TASK_AVOID_ID);
		scheduler_wait_for_timer(ces);

		RUN_AND_UPDATE(s_TASK_MISSION_ID);
		RUN_AND_UPDATE(s_TASK_AVOID_ID);
		scheduler_wait_for_timer(ces);

		RUN_AND_UPDATE(s_TASK_MISSION_ID);
		RUN_AND_UPDATE(s_TASK_NAVIGATE_ID);
		RUN_AND_UPDATE(s_TASK_CONTROL_ID);
		RUN_AND_UPDATE(s_TASK_AVOID_ID);
		scheduler_wait_for_timer(ces);

		RUN_AND_UPDATE(s_TASK_MISSION_ID);
		RUN_AND_UPDATE(s_TASK_REFINE_ID);
		RUN_AND_UPDATE(s_TASK_REPORT_ID);
		RUN_AND_UPDATE(s_TASK_AVOID_ID);
		scheduler_wait_for_timer(ces);

		RUN_AND_UPDATE(s_TASK_MISSION_ID);
		RUN_AND_UPDATE(s_TASK_AVOID_ID);
		scheduler_wait_for_timer(ces);

		RUN_AND_UPDATE(s_TASK_MISSION_ID);
		RUN_AND_UPDATE(s_TASK_NAVIGATE_ID);
		RUN_AND_UPDATE(s_TASK_CONTROL_ID);
		RUN_AND_UPDATE(s_TASK_AVOID_ID);
		scheduler_wait_for_timer(ces);

		RUN_AND_UPDATE(s_TASK_MISSION_ID);
		RUN_AND_UPDATE(s_TASK_REFINE_ID);
		RUN_AND_UPDATE(s_TASK_REPORT_ID);
		RUN_AND_UPDATE(s_TASK_AVOID_ID);
		scheduler_wait_for_timer(ces);

		RUN_AND_UPDATE(s_TASK_MISSION_ID);
		RUN_AND_UPDATE(s_TASK_AVOID_ID);
		scheduler_wait_for_timer(ces);
	}
	printf("\n");

	// Calculate total running time
	double total_running_time_end = timelib_unix_timestamp();
	double total_running_time = total_running_time_end - total_running_time_start;

	// Calculate the average task time for each task
	for (int i = 0; i < TASK_NUM; i++)
	{
		task_times[i] /= task_num[i];
	}

	// Print a summary
	printf("total elapsed time: %f\n", total_running_time);
	printf("summary:\n");
	printf("+-------------+-------------+-------------+\n");
	printf("| task        | time        | max         |\n");
	printf("+-------------+-------------+-------------+\n");
	for (int i = 0; i < TASK_NUM; i++)
	{
		printf("| %-11s | %-11f | %-11f |\n",
			   TASK_NAMES[i],
			   task_times[i],
			   max_times[i]);
	}
	printf("+-------------+-------------+-------------+\n");
	double min_minor_cycle = 0;
	for (int i = 0; i < TASK_NUM; i++)
	{
		min_minor_cycle += max_times[i];
	}
	printf("minimum minor cycle: %f\n", min_minor_cycle);
}
