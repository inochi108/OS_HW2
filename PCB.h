#ifndef PCB_H
#define PCB_H

/*
Group 5: Nok Him Nam, Jowy Tran, Mark Johnson, David Humphreys
Date : 28/ 01/ 2015
Assignment : Problem 2 - Scheduling
*/

enum state_type {
	created,
	ready,
	running,
	blocked,
	interrupted,
	terminated
};

typedef enum state_type State;

struct PCB {
	char name[20];
	int pid;
	int priority;
	int interrupt_simulator;
	unsigned int pc;
	State currentState;
};

typedef struct PCB* PCB_p;

PCB_p createPCB(char* name, int newPid, int newPriority, int theInterruptSimulator,
	int thePcValue, State theState);

char* getName(PCB_p pcb);
int getPid(PCB_p pcb);
int getPriority(PCB_p pcb);
int getInterruptSimulator(PCB_p pcb);
int getPCValue(PCB_p pcb);
char* getState(PCB_p pcb);

void freePCB(PCB_p pcb);
void toString(PCB_p pcb);
void toStringFileVersion(PCB_p pcb, FILE* theOuputFile);

void setName(PCB_p pcb, char* newName);
void setPid(PCB_p pcb, int newPid);
void setPriority(PCB_p pcb, int newPriority);
void setInterruptSimulator(PCB_p pcb, int theInterruptSimulator);
void setPCValue(PCB_p pcb, int thePCValue);
void setTheState(PCB_p pcb, State theState);

#endif
