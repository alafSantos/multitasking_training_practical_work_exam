#include <unistd.h>
#include <stdio.h>
#include <pthread.h>
#include "displayManager.h"
#include "iDisplay.h"
#include "iAcquisitionManager.h"
#include "iMessageAdder.h"
#include "msg.h"
#include "multitaskingAccumulator.h"
#include "debug.h"

//  #####################################################################
//  extern pid_t gettid(void); // just to remove one warning
//  #####################################################################

// DisplayManager thread.
pthread_t displayThread;

/**
 * Display manager entry point.
 * */
static void *display(void *parameters);

void displayManagerInit(void)
{
	// TODO
	//  #####################################################################
	pthread_create(&displayThread, NULL, display, NULL);
	// #####################################################################
}

void displayManagerJoin(void)
{
	// TODO
	//  #####################################################################
	pthread_join(displayThread, NULL);
	// #####################################################################
}

static void *display(void *parameters)
{
	//  #####################################################################
	// Hors de la boucle pour éviter de le recréer à chaque iteration
	MSG_BLOCK tmp;
	status etat;
	//  #####################################################################

	D(printf("[displayManager]Thread created for display with id %d\n", gettid()));
	unsigned int diffCount = 0;
	while (diffCount < DISPLAY_LOOP_LIMIT)
	{
		sleep(DISPLAY_SLEEP_TIME);
		// TODO
		//  #####################################################################
		etat = getStatus();
		tmp = etat.out;
		messageDisplay(&tmp);
		print(getProducedCount(), etat.consumeCount);
		diffCount++;
		//  #####################################################################
	}
	printf("[displayManager] %d termination\n", gettid());
	// TODO
	//  #####################################################################
	pthread_exit(NULL);
	// #####################################################################
}