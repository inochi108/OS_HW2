#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "LinkedListADT.h"

/*
Group 5: Nok Him Nam, Jowy Tran, Mark Johnson, David Humphreys
Date : 28/ 01/ 2015
Assignment : Problem 2 - Scheduling
*/

FIFO_queue_p createLinkedList() {

	FIFO_queue_p FIFOList = malloc(sizeof(struct FIFO_queue));
	FIFOList->frontNode_ptr = NULL;
	FIFOList->endNode_ptr = NULL;
	FIFOList->size = 0;
	return FIFOList;
}

int is_empty(FIFO_queue_p theList) {
	return theList->size == 0;
}

void enqueue(FIFO_queue_p theList, PCB_p theData) {
	if (theList && theData) {
		PCB_p tempPCB = malloc(sizeof(struct PCB));

		strcpy(tempPCB->name, theData->name);
		tempPCB->pid = theData->pid;
		tempPCB->priority = theData->priority;
		tempPCB->interrupt_simulator = theData->interrupt_simulator;
		tempPCB->pc = theData->pc;
		tempPCB->currentState = theData->currentState;

		struct node* tempNode = malloc(sizeof(struct node));
		tempNode->data = tempPCB;
		tempNode->next = NULL;

		if (theList->size == 0) {
			theList->frontNode_ptr = tempNode;
			theList->endNode_ptr = tempNode;
		}
		else {
			// Move the pointer to point at the next node 
			// of what is endNode pointing at
			theList->endNode_ptr->next = tempNode;
			// Update the endNode to point at the end of the list
			theList->endNode_ptr = tempNode;
		}

		theList->size++;
	}
	else {
		printf("In enqueue something passed as NULL.\n");
	}
}
struct node* dequeue(FIFO_queue_p theList) {
	if (theList) {
		struct node * tempNode = theList->frontNode_ptr;

		if (theList->size > 1) {

			if (tempNode->next != NULL) {
				theList->frontNode_ptr = tempNode->next;
				theList->size--;
			}
			//free in main
			return tempNode;
		}
		else if (theList->size == 1) {
			tempNode = theList->endNode_ptr;
			theList->endNode_ptr = NULL;
			theList->frontNode_ptr = NULL;
			theList->size--;
			return tempNode;
		}
		else {
			return NULL;
		}
	}
	else {
		printf("dequeue gets passed null.!!!!");
		return NULL;
	}
}

void printList(FIFO_queue_p theList) {

	if (size_is(theList) != 0) {
		struct node *current = theList->frontNode_ptr;
 		//printf("//-----------------------------\n");
		while (current != NULL) {
			printf("Process %d -> ", current->data->pid);
			current = current->next;
		}

		if (current == NULL) {
			printf("* ");
		}
		printf("\n//-----------------------------");
		printf("\n");
	}
	else {
		printf("\nThe list is EMPTY!!\n");
	}
}

void printListFileVersion(FIFO_queue_p theList, FILE* theOuputFile) {

	if (size_is(theList) != 0) {
		struct node *current = theList->frontNode_ptr;
		//printf("//-----------------------------\n");
		while (current != NULL) {
			fprintf(theOuputFile, "Process %d -> ", current->data->pid);
			current = current->next;
		}

		if (current == NULL) {
			fprintf(theOuputFile, "* ");
		}
		fprintf(theOuputFile, "\n//-----------------------------");
		fprintf(theOuputFile, "\n");
	}
	else {
		fprintf(theOuputFile, "\nThe list is EMPTY!!\n");
	}
}

int size_is(FIFO_queue_p theList) {
	return theList->size;
}

void freeLinkedList(FIFO_queue_p theList) {

	if (size_is(theList) != 0) {
		int i = 0;
		struct node* current_ptr = theList->frontNode_ptr->next;
		struct node* temp_ptr = theList->frontNode_ptr;

		for (i = 0; i < size_is(theList); i++) {
			if (current_ptr == NULL) {
				free(temp_ptr->data);
				temp_ptr->data = NULL;
			}
			else {
				free(temp_ptr->data);
				temp_ptr->data = NULL;
				temp_ptr = current_ptr;
				current_ptr = current_ptr->next;
			}
		}
	}
	free(theList);
	theList = NULL;
}
//
//void make_empty(ListType l) {
//
//	struct node *current = l->frontNode;
//	while (current != NULL) {
//		l->frontNode = l->frontNode->next;
//		free(current);
//		current = l->frontNode;
//	}
//	l->size = 0;
//}
//
//int is_full(ListType l) {
//	struct node *temp = malloc(sizeof(struct node));
//	if (temp != NULL) {
//		free(temp);
//		return 0;
//	}
//	return 1;
//}
//
//void destroy(ListType l) {
//
//	make_empty(l);
//	free(l);
//}
