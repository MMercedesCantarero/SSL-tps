#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

int prec(char c) {
    if (c == '^')
        return 3;
    else if (c == '/' || c == '*')
        return 2;
    else if (c == '+' || c == '-')
        return 1;
    else
        return -1;
}

char associativity(char c) {
    if (c == '^')
        return 'R';
    return 'L';
}

char*  infixToPostfix(char s[]) {
    char* result = (char*)malloc(1000 * sizeof(char));
    
    int resultIndex = 0;
    int len = strlen(s);
    char stack[1000];
    int stackIndex = -1;

    for (int i = 0; i < len; i++) {
        char c = s[i];

        if (isdigit(c)) {
            result[resultIndex++] = c;
        }
        else if (c == '(') {
            stack[++stackIndex] = c;
        }
        else if (c == ')') {
            while (stackIndex >= 0 && stack[stackIndex] != '(') {
                result[resultIndex++] = stack[stackIndex--];
            }
            stackIndex--;
        }
        else {
            while (stackIndex >= 0 && (prec(c) <= prec(stack[stackIndex]) ||
                                       prec(c) == prec(stack[stackIndex]) &&
                                           associativity(c) == 'L')) {
                result[resultIndex++] = stack[stackIndex--];
            }
            stack[++stackIndex] = c;
        }
    }

    while (stackIndex >= 0) {
        result[resultIndex++] = stack[stackIndex--];
    }

    result[resultIndex] = '\0';
    
    return result; 
}