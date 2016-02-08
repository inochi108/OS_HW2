#define _CRT_SECURE_NO_WARNINGS
#define MAX_NUMBER_OF_PCB 30
#define MAX_NUMBER_OF_RUNTIME 24
#define PRINT_EVERY_xTIMES 4

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include "CPU.h"

/*
Group 5: Nok Him Nam, Jowy Tran, Mark Johnson, David Humphreys
Date (DD/MM/YY) : 28/ 01/ 2015
Assignment : Problem 2 - Scheduling
This Driver program tests the CPU class. It creates between 0 and 5 PCBs and adds them
to the CPU in those respective groups. The CPU works using a round robin scheduling,
so each process ends with a timer interrupt.
*/

void main(void) {

	srand(time(NULL));
	char processNameSetUp[10] = "Process";
	int i = 0;
	FIFO_queue_p PCBContainer = createLinkedList();
	PCB_p tempPCB;
	int PCBCounter = 0;
	int loopCounter = 0;
	int numberOfPCB = 0;

	FILE* outFile = fopen("scheduleTrace.txt", "w+");
	fprintf(outFile, "Group 5: Nok Him Nam, Jowy Tran, Mark Johnson, David Humphreys\nDate (DD/MM/YY) : 28/ 01/ 2015\nAssignment : Problem 2 - Scheduling\n");

	//Create CPU
	CPU_instance_p testingCPU = createCPU();

	//Master CPU Loop
	while (loopCounter <= MAX_NUMBER_OF_RUNTIME) {

		if (loopCounter % PRINT_EVERY_xTIMES == 0) {
			fprintf(outFile, "\n__________NEXT TIME QUANTUM  : %d___________\n", loopCounter);
		}

		numberOfPCB = rand() % 6;

		//While the number of PCBs created is less than 30, create more PCBs
		if (PCBCounter < MAX_NUMBER_OF_PCB && PCBCounter + numberOfPCB <= MAX_NUMBER_OF_PCB) {

			if (loopCounter % PRINT_EVERY_xTIMES == 0) {
				//fprintf(outFile, "\n__________NEXT TIME QUANTUM  : %d___________\n", loopCounter);
				fprintf(outFile, "//----------------------------------\n");
				fprintf(outFile, "We are creating %d PCBs \n\n", numberOfPCB);
			}

			for (i = 0; i < numberOfPCB; i++) {

				sprintf(processNameSetUp, "Process%d", PCBCounter);

				enqueue(PCBContainer, tempPCB = createPCB(processNameSetUp, PCBCounter, rand() % 15,
					0, 1000 * PCBCounter, ready));
				if (loopCounter % PRINT_EVERY_xTIMES == 0) {
					toStringFileVersion(tempPCB, outFile);
				}

				strcpy(processNameSetUp, "Process");
				PCBCounter++;
			}
		} else if(PCBCounter == MAX_NUMBER_OF_PCB && loopCounter % 4 == 0) {
			fprintf(outFile, "We are done creating PCBs\n");
		}

		if (loopCounter % PRINT_EVERY_xTIMES == 0) {
			fprintf(outFile, "//----------------------------------\n");
		}

		//If we have started a running processes, increment the PC value to simulate running
		if (testingCPU->runningProcess != NULL) {
			testingCPU->runningProcess->pc += rand() % 1000 + 3000;

			//strcpy(testingCPU->systemStack->name, testingCPU->runningProcess->name);
			testingCPU->systemStack->pc = testingCPU->runningProcess->pc;
		}
		//else, create a temp "fake" processs PCB till a "real" one is created
		else {
			testingCPU->runningProcess = createPCB("Default", 0, 0, 0, 0, running);
			testingCPU->systemStack = createPCB("Default", 0, 0, 0, 0, running);
		}

		//Simulate Timer Interrupt
		timerISR(testingCPU, PCBContainer);

		if (loopCounter % PRINT_EVERY_xTIMES == 0) {
			//PRINT RESULTS AFTER TIMER ISR
			fprintf(outFile, "\nRunning process: \n");
			//printf("//--------------------------------------\n");
			toStringFileVersion(testingCPU->runningProcess, outFile);
			fprintf(outFile, "//---------------------------------------\n\n");
			fprintf(outFile, "State of the Ready Queue: \n\n");
			printListFileVersion(testingCPU->readQueue_p, outFile);
			fprintf(outFile, "\n\n");
		}

		//pseudo halt for debug screen
		//getchar();

		//one run has passed
		loopCounter++;
		
	}

	//free used memory
	freeLinkedList(PCBContainer);
	freeCPU(testingCPU);
}
