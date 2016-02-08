#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "CPU.h"

/*
Group 5: Nok Him Nam, Jowy Tran, Mark Johnson, David Humphreys
Date : 28/ 01/ 2015
Assignment : Problem 2 - Scheduling
CPU creates a CPU instance that contains 2 lists and 2 PCBs: a Ready Queue to hold ready processes,
a IO Queue to hold processes waiting for IO data, a PCB to hold the running process, and a
PCB that we use to hold information in our metaphorical system stack.
*/

/*Creates a CPU and returns a pointer to that instance.*/
CPU_instance_p createCPU(void) {

	CPU_instance_p CPU_process_p = malloc(sizeof(struct CPU_instance));
	CPU_process_p->readQueue_p = createLinkedList();
	CPU_process_p->IOQueue_p = createLinkedList();
	CPU_process_p->systemStack = NULL;
	CPU_process_p->runningProcess = NULL;
	return CPU_process_p;
}

/*Timer ISR simulates a timer interrupt and calls the scheduler.*/
void timerISR(CPU_instance_p theCPUInstance, FIFO_queue_p thePCBContainer) {

	theCPUInstance->runningProcess->currentState = interrupted;
	schedular(theCPUInstance, thePCBContainer);
}

/*The schedular changing the states of the running process, adds the newly created PCBs
to the Ready Queue, and calls the dispatcher.*/
void schedular(CPU_instance_p theCPUInstance, FIFO_queue_p thePCBContainer) {

	int i = 0;
	int theSizeOfTheList = size_is(thePCBContainer);

	//Add new PCBs
	for (i = 0; i < theSizeOfTheList; i++) {
		enqueue(theCPUInstance->readQueue_p, dequeue(thePCBContainer)->data);
	}

	//If we are simulating a Timer Interupt (always for this assignment)
	//change the current state of the running process to ready.
	if (theCPUInstance->runningProcess->interrupt_simulator == 0) {
		theCPUInstance->runningProcess->currentState = ready;
	}

	dispatcher(theCPUInstance);
}

/*Dispatcher switches the running process with the next process that needs to run.*/
void dispatcher(CPU_instance_p theCPUInstance) {

	int compareResult = -1;

	//checks to see if running process is the temp "fake" processs
	compareResult = strcmp(theCPUInstance->runningProcess->name, "Default");
	
	//If the running process has not been populated yet
	if (compareResult == 0) {
		//If the Ready Queue is still empty
		if (size_is(theCPUInstance->readQueue_p) == 0) {
			theCPUInstance->runningProcess->currentState = running;
		}
		//If the Ready Queue is not empty, add a real PCB to running
		else {
			PCB_p temp = theCPUInstance->runningProcess;
			theCPUInstance->runningProcess = dequeue(theCPUInstance->readQueue_p)->data;
			theCPUInstance->runningProcess->currentState = running;
			freePCB(temp);
		}
	}

	//If the running process is populated with a real process
	else {
		//If the ready queue is empty
		if (size_is(theCPUInstance->readQueue_p) == 0) {
			theCPUInstance->runningProcess->currentState = running;
		}

		//If the ready Queue is not empty, move the running PCB back to ready queue
		else {
			enqueue(theCPUInstance->readQueue_p, theCPUInstance->runningProcess);
			theCPUInstance->runningProcess = dequeue(theCPUInstance->readQueue_p)->data;
			theCPUInstance->runningProcess->currentState = running;
			//printf("Dequeue from the ready q\n");
			//printf("//--------------------------------------\n");
			//toString(theCPUInstance->runningProcess);
			//printf("//---------------------------------------\n\n");
			//printList(theCPUInstance->readQueue_p);

		}
	}
}

/*Free allocated memory*/
void freeCPU(CPU_instance_p theCPU_instance) {

	freeLinkedList(theCPU_instance->IOQueue_p);
	freeLinkedList(theCPU_instance->readQueue_p);

	if (theCPU_instance->systemStack != NULL) {
		freePCB(theCPU_instance->systemStack);
	}

	if (theCPU_instance->runningProcess != NULL) {
		freePCB(theCPU_instance->runningProcess);
	}

	free(theCPU_instance);
}