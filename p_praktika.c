#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define STACK_SIZE 100

typedef struct {
    double stack[STACK_SIZE];
    int top;
} Stack;

void initStack(Stack *s) {
    s->top = -1;
}

int isEmpty(Stack *s) {
    return s->top == -1;
}

int isFull(Stack *s) {
    return s->top == STACK_SIZE - 1;
}

void push(Stack *s, double value) {
    if (isFull(s)) {
        printf("error : stack is full\n");
        exit(1);
    }
    s->top++;
    s->stack[s->top] = value;
}

double pop(Stack *s) {
    if (isEmpty(s)) {
        printf("error : stack is full\n");
        exit(1);
    }
    double value = s->stack[s->top];
    s->top--;
    return value;
}

int isNumeric(char *token) {
    char *endptr;
    strtod(token, &endptr);
    return *endptr == '\0';
}

int isOperator(char *token) {
    return strcmp(token, "+") == 0 || strcmp(token, "-") == 0 ||
           strcmp(token, "*") == 0 || strcmp(token, "/") == 0 ||
           strcmp(token, "ln") == 0 || strcmp(token, "log") == 0 ||
           strcmp(token, "pi") == 0 || strcmp(token, "e") == 0;
}

double evaluateExpression(char **tokens, int numTokens) {
    Stack stack;
    initStack(&stack);

    for (int i = 0; i < numTokens; i++) {
        char *token = tokens[i];

        if (isNumeric(token)) {
            push(&stack, atof(token));
        } else if (isOperator(token)) {
            if (strcmp(token, "pi") == 0) {
                push(&stack, M_PI);
            } else if (strcmp(token, "e") == 0) {
                push(&stack, M_E);
            } else {
                if (isEmpty(&stack)) {
                    printf("error : invalid expression\n");
                    exit(1);
                }

                double operand = pop(&stack);
                double result;

                if (strcmp(token, "+") == 0) {
                    if (isEmpty(&stack)) {
                        printf("error : invalid expressionn");
                        exit(1);
                    }
                    double operand2 = pop(&stack);
                    result = operand2 + operand;
                } else if (strcmp(token, "-") == 0) {
                    if (isEmpty(&stack)) {
                        printf("error : invalid expression\n");
                        exit(1);
                    }
                    double operand2 = pop(&stack);
                    result = operand2 - operand;
                } else if (strcmp(token, "*") == 0) {
                    if (isEmpty(&stack)) {
                        printf("error : invalid expression\n");
                        exit(1);
                    }
                    double operand2 = pop(&stack);
                    result = operand2 * operand;
                } else if (strcmp(token, "/") == 0) {
                    if (operand == 0) {
                        printf("error : division by zero\n");
                        exit(1);
                    }
                    if (isEmpty(&stack)) {
                        printf("error : invalid expression\n");
                        exit(1);
                    }
                    double operand2 = pop(&stack);
                    result = operand2 / operand;
                } else if (strcmp(token, "ln") == 0) {
                    if (operand <= 0) {
                        printf("error: invalid argument for ln\n");
                        exit(1);
                    }
                    result = log(operand);
                } else if (strcmp(token, "log") == 0) {
                    if (operand <= 0) {
                        printf("error: invalid argument for log log\n");
                        exit(1);
                    }
                    if (isEmpty(&stack)) {
                        printf("error: invalid expression\n");
                        exit(1);
                    }
                    double operand2 = pop(&stack);
                    result = log(operand) / log(operand2);
                }

                push(&stack, result);
            }
        } else {
            printf("error : invalid token \"%s\"\n", token);
            exit(1);
        }
    }

    if (stack.top != 0) {
        printf("error : invalid expression\n");
        exit(1);
    }

    return pop(&stack);
}

int main() {
    char expression[100];
    printf("enter an expression: ");
    fgets(expression, sizeof(expression), stdin);
    expression[strcspn(expression, "\n")] = '\0';

    int numTokens = 0;
    char *tokens[50];

    char *token = strtok(expression, " ");
    while (token != NULL) {
        tokens[numTokens] = token;
        numTokens++;
        token = strtok(NULL, " ");
    }

    double result = evaluateExpression(tokens, numTokens);
    printf("result: %.2f\n", result);

    return 0;
}
