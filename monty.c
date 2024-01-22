#include "monty.h"

void push(MontyStack *stack, int value) {
    if (stack->size < STACK_MAX) {
        stack->data[stack->size++] = value;
    } else {
        handle_error(__LINE__, "stack overflow");
    }
}

void pall(MontyStack *stack) {
    int i;
    for (i = stack->size - 1; i >= 0; i--) {
        printf("%d\n", stack->data[i]);
    }
}


void handle_error(int line_number, const char *message) {
    fprintf(stderr, "L%d: %s\n", line_number, message);
    exit(EXIT_FAILURE);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <file>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    FILE *file = fopen(argv[1], "r");
    if (!file) {
        fprintf(stderr, "Error: Can't open file %s\n", argv[1]);
        exit(EXIT_FAILURE);
    }

    MontyStack stack = { .size = 0 };

    char line[100];
    int line_number = 0;

    while (fgets(line, sizeof(line), file) != NULL) {
        line_number++;

        if (sscanf(line, "push %d", &value) == 1) {
            push(&stack, value);
        } else if (strcmp(line, "pall\n") == 0) {
            pall(&stack);
        } else {
            handle_error(line_number, "unknown opcode");
        }
    }

    fclose(file);
    return 0;
}
