#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

#define MAX_STACK_SIZE 100

typedef int element;
typedef struct Stacktype {
    element* data;
    int capacity;
    int top;
} StackType;

void init(StackType* sptr, int ofs) {
    sptr->data = (element*)malloc(sizeof(element) * ofs);
    sptr->top = -1;
    sptr->capacity = ofs;
}

bool is_full(StackType* sptr) {
    return (sptr->top == sptr->capacity - 1);
}

bool is_empty(StackType* sptr) {
    return (sptr->top == -1);
}

void push(StackType* sptr, element item) {
    if (is_full(sptr)) {
        fprintf(stderr, "Stack is full\n");
        return;
    }
    sptr->top++;
    sptr->data[sptr->top] = item;
}

element pop(StackType* sptr) {
    if (is_empty(sptr)) {
        fprintf(stderr, "Stack is empty\n");
        return -1;
    }
    return sptr->data[sptr->top--];
}

int eval(char* expression) {
    StackType s;
    init(&s, 20);
    int op1, op2;
    for (int i = 0; expression[i] != '\0'; i++) {
        char ch = expression[i];
        if (isdigit(ch)) {
            push(&s, ch - '0');
        }
        else if (ch == '+' || ch == '-' || ch == '*' || ch == '/') {
            op1 = pop(&s);
            op2 = pop(&s);
            switch (ch) {
            case '+': push(&s, op2 + op1); break;
            case '-': push(&s, op2 - op1); break;
            case '*': push(&s, op2 * op1); break;
            case '/': push(&s, op2 / op1); break;
            }
        }
    }
    return pop(&s);
}

int main() {
    char expression[MAX_STACK_SIZE];
    int result;

    printf("Postfix Expression: ");
    fgets(expression, sizeof(expression), stdin);
    if (expression[strlen(expression) - 1] == '\n')
        expression[strlen(expression) - 1] = '\0';

    result = eval(expression);
    printf("Result: %d\n", result);

    return 0;
}
