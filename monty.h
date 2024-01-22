#ifndef MONTY_H
#define MONTY_H

#include <stdio.h>
#include <stdlib.h>

#define STACK_MAX 1024

typedef struct MontyStack {
    int data[STACK_MAX];
    int size;
} MontyStack;

void push(MontyStack *stack, int value);
void pall(MontyStack *stack);
void handle_error(int line_number, const char *message);

#endif
