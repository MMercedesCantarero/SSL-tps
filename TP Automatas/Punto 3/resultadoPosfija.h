#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

int charToInt(char c) {
    return c - '0';
}

struct Stack {
    int top;
    unsigned capacity;
    int* array;
};
 
struct Stack* createStack(unsigned capacity)
{
    struct Stack* stack = (struct Stack*)malloc(sizeof(struct Stack));
    if (!stack)
        return NULL;
    stack->top = -1;
    stack->capacity = capacity;
    stack->array = (int*)malloc(stack->capacity * sizeof(int));
    if (!stack->array)
        return NULL;
    return stack;
}
 
int isEmpty(struct Stack* stack)
{
    return stack->top == -1;
}
 
int peek(struct Stack* stack)
{
    return stack->array[stack->top];
}
 
int pop(struct Stack* stack)
{
    if (!isEmpty(stack))
        return stack->array[stack->top--];
    return -1;
}
 
void push(struct Stack* stack, int op)
{
    stack->array[++stack->top] = op;
}

int evaluatePostfix(char* exp)
{
    struct Stack* stack = createStack(strlen(exp));
    int i;

    if (!stack)
        return -1;

    for (i = 0; exp[i]; ++i) {
        if (isdigit(exp[i]))
            push(stack, charToInt(exp[i]));
        else {
            int val1 = pop(stack);
            int val2 = pop(stack);
            switch (exp[i]) {
            case '+':
                push(stack, val2 + val1);
                break;
            case '-':
                push(stack, val2 - val1);
                break;
            case '*':
                push(stack, val2 * val1);
                break;
            case '/':
                push(stack, val2 / val1);
                break;
            }
        }
    }
    return pop(stack);
}