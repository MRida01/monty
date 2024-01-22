#ifndef MONTY_H
#define MONTY_H

#include <stdio.h>
#include <stdlib.h>


typedef struct stack_s {
    int n;
    struct stack_s *prev;
    struct stack_s *next;
} stack_t;


typedef struct instruction_s {
    char *opcode;
    void (*f)(stack_t **stack, unsigned int line_number);
} instruction_t;


void push(stack_t **stack, int value);
void pall(stack_t **stack, unsigned int line_number);
void handle_error(unsigned int line_number, const char *message);

#endif
