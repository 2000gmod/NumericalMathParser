#include "node.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>


extern int verboseMode;

node* createNode(void){
    node* out = malloc(sizeof(node));
    out->left = NULL;
    out->right = NULL;
    out->operator = NULL;
    out->value = 0;
    return out; 
}

long evaluate(node* head){
    if(head == NULL) return 0;
    
    //evaluate operator first, value only if operator is null
    if(head->operator == NULL){
        long value = head->value;
        free(head);
        return value;
    }
    else{
        long (*operator) (long, long) = head->operator;
        node* left = head->left;
        node* right = head->right;
        free(head);
        return operator(evaluate(left), evaluate(right));
    }
}

long add(long a, long b){
    if (verboseMode) printf("$: ADD %ld %ld = %ld\n", a, b, a+b);
    return a + b;
}
long sub(long a, long b){
    if (verboseMode) printf("$: SUB %ld %ld = %ld\n", a, b, a-b);
    return a - b;
}
long mult(long a, long b){
    if (verboseMode) printf("$: MUL %ld %ld = %ld\n", a, b, a*b);
    return a*b;
}
long divi(long a, long b){
    if (b == 0){
        printf("$: Warning: division by 0. This will return 0 as fallback.\n");
        return 0;
    }
    float test = (float) a/b;
    if (fabs(test - a/b) > 0.00001) printf("$: Warning: division will return rounded down integer value.\n");
    if (verboseMode) printf("$: DIV %ld %ld = %ld\n", a, b, a/b);
    return a/b;
}
long power(long a, long b){
    long out = 1;
    
    for(int i = 1; i<= b; i++){
        out *= a;
    }
    if (verboseMode){
        printf("$: POW %ld %ld = %ld\n", a, b, out);
    }

    if(b == 0){
        if (a == 0){
            printf("$: Warning: undefined operation. Expression is of type 0^0, will return 1 as fallback.\n");
        }
        return 1;
    }
    if (b < 0){
        printf("$: Warning: number with negative exponent.\n$: This parser does not support non-integer values, this will return 0 as fallback.\n");
        return 0;
    }

    return out;
}