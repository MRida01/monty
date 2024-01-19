#include <stdio.h>
#include <stdlib.h>

#define STACK_SIZE 1000

typedef struct {
    int stack[STACK_SIZE];
    int top;
} Stack;

Stack stack;

void push(int value, int line_number) {
    if (stack.top == STACK_SIZE - 1) {
        fprintf(stderr, "L%d: Error: Stack overflow\n", line_number);
        exit(EXIT_FAILURE);
    }
    stack.stack[++stack.top] = value;
}

void pall() {
    int i;
    for (i = stack.top; i >= 0; i--) {
        printf("%d\n", stack.stack[i]);
    }
}

int main(int argc, char *argv[]) {
    FILE *file;
    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    int line_number = 0;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <file>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    file = fopen(argv[1], "r");
    if (file == NULL) {
        fprintf(stderr, "Error: Can't open file %s\n", argv[1]);
        exit(EXIT_FAILURE);
    }

    stack.top = -1;

    while ((read = getline(&line, &len, file)) != -1) {
        line_number++;

        if (line[0] == '\n' || line[0] == '#') {
            continue;
        }

        char opcode[5];
        int value;

        if (sscanf(line, "%4s %d", opcode, &value) == 2) {
            if (strcmp(opcode, "push") == 0) {
                push(value, line_number);
            } else if (strcmp(opcode, "pall") == 0) {
                pall();
            } else {
                fprintf(stderr, "L%d: Error: Unknown opcode %s\n", line_number, opcode);
                exit(EXIT_FAILURE);
            }
        } else {
            fprintf(stderr, "L%d: Error: Invalid instruction\n", line_number);
            exit(EXIT_FAILURE);
        }
    }

    free(line);
    fclose(file);

    return 0;
}
