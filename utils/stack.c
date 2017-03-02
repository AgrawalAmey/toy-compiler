#include <stdio.h>
#include <stdlib.h>
#include "../custom_types/token.h"
#include "../custom_types/structs.h"
#include "../headers/utils.h"

stack createStack(){
   stack s;
   s.front = (stackNode**) malloc(sizeof(stackNode*));
   s.rear = (stackNode**) malloc(sizeof(stackNode*));
   *s.front = NULL;
   *s.rear = NULL;
   return s;
}

void push(token data, stack s){
	stackNode* temp = (stackNode*)malloc(sizeof(stackNode));
	temp->data = data;
	temp->next = NULL;
	if(*s.front == NULL && *s.rear == NULL){
		*s.front = *s.rear = temp;
		return;
	}
	(**s.rear).next = temp;
	*s.rear = temp;
}

token pop(stack s){
	stackNode* temp = *s.rear;
	if(*s.rear == NULL) {
		printf("Stack is Empty\n");
		return -1;
	}
	if(*s.front == *s.rear) {
        t = (**s.rear).data;
		*s.front = *s.rear = NULL;
	}else {
		t = (**s.rear).data;
		*s.rear = (**s.rear).next;
	}
	free(temp);
	return t;
}

token top(stack s){
	token t;
	if(*s.rear == NULL) {
		printf("Stack is Empty\n");
		return -1;
	}
	if(*s.front == *s.rear) {
		*s.front = *s.rear = NULL;
	}else {
		t = (**s.rear).data;
		*s.rear = (**s.rear).next;
	}
	return t;
}


int isStackEmpty(stack s){
	if(*s.front == NULL && *s.rear == NULL) {
		printf("Stack is Empty\n");
		return 1;
	} else {
		return 0;
	}
}

void printStack(stack s) {
	stackNode* temp = *s.front;
	if(*s.front == NULL) {
		printf("Stack is Empty\n");
		return;
	}
	while(temp != NULL) {
		printf("%d ", temp->data);
		temp = temp->next;
	}
	printf("\n");
}
