#ifndef CPU_H
#define CPU_H
#include "LinkedListADT.h"

/*
Group 5: Nok Him Nam, Jowy Tran, Mark Johnson, David Humphreys
Date : 28/ 01/ 2015
Assignment : Problem 2 - Scheduling
*/

struct CPU_instance {
	FIFO_queue_p readQueue_p;
	FIFO_queue_p IOQueue_p;
	PCB_p systemStack;
	PCB_p runningProcess;
};

typedef struct CPU_instance* CPU_instance_p;

CPU_instance_p createCPU(void);
void timerISR(CPU_instance_p theCPUInstance, FIFO_queue_p thePCBContainer);
void schedular(CPU_instance_p theCPUInstance, FIFO_queue_p thePCBContainer);
void dispatcher(CPU_instance_p theCPUInstance);
void freeCPU(CPU_instance_p theCPU_instance);

#endif
