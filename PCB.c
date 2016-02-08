#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "PCB.h"

/*
Group 5: Nok Him Nam, Jowy Tran, Mark Johnson, David Humphreys
Date : 28/ 01/ 2015
Assignment : Problem 2 - Scheduling
*/

// returns the pointer to the list; NULL if list not created
PCB_p createPCB(char* name, int newPid, int newPriority, int theInterruptSimulator,
	int thePcValue, State theState) {
	if (newPriority > 15 || newPriority < 0) {
		printf("Error: Priority must be 0 - 15. PCD not Created.");
	}
	//struct control_block_type testing;
	PCB_p pcb = malloc(sizeof(struct PCB));
	// if allocation was succesfull
	if (pcb != NULL) {

		strcpy(pcb->name, name);
		pcb->pid = newPid;
		pcb->priority = newPriority;
		pcb->interrupt_simulator = theInterruptSimulator;
		pcb->pc = thePcValue;
		pcb->currentState = theState;

	}
	return pcb;
}

char* getName(PCB_p pcb) {
	return pcb->name;
}

int getPid(PCB_p pcb) {
	return pcb->pid;
}

int getPriority(PCB_p pcb) {
	return pcb->priority;
}

int getInterruptSimulator(PCB_p pcb) {
	return pcb->interrupt_simulator;
}

int getPCValue(PCB_p pcb) {
	return pcb->pc;
}

char* getState(PCB_p pcb) {
	
	switch (pcb->currentState) {
		case created: return "created"; break;
		case ready: return "ready"; break;
		case running: return "running"; break;
		case blocked: return "blocked"; break;
		case interrupted: return "interrupted"; break;
		case terminated: return "terminated"; break;
		default: return "ERROR";
	}
}

void setName(PCB_p pcb, char* newName) {
	strcpy(pcb->name, newName);
}

void setPid(PCB_p pcb, int newPid) {
	pcb->pid = newPid;
}

void setPriority(PCB_p pcb, int newPriority) {
	pcb->priority = newPriority;
}

void setInterruptSimulator(PCB_p pcb, int theInterruptSimulator) {
	pcb->interrupt_simulator = theInterruptSimulator;
}

void setPCValue(PCB_p pcb, int thePCValue) {
	pcb->pc = thePCValue;
}

void setTheState(PCB_p pcb, State theState) {
	pcb->currentState = theState;
}

void freePCB(PCB_p pcb) {
	free(pcb);
	pcb = NULL;
}

void toString(PCB_p pcb) {
	printf("Name: %s, PID: %d, Priority: %d\nInterrupt simulator : %d, PC : %d, State : %s\n\n",
		pcb->name, pcb->pid, pcb->priority,
		pcb->interrupt_simulator, pcb->pc, getState(pcb));
}

void toStringFileVersion(PCB_p pcb, FILE* theOuputFile) {
	fprintf(theOuputFile, "Name: %s, PID: %d, Priority: %d\nInterrupt simulator : %d, PC : %d, State : %s\n\n",
		pcb->name, pcb->pid, pcb->priority,
		pcb->interrupt_simulator, pcb->pc, getState(pcb));
}