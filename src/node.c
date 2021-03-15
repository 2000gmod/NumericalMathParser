#include "node.h"
extern int verboseMode;

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
    if (verboseMode) printf("$: DIV %ld %ld = %ld\n", a, b, a/b);
    return a/b;
}
long power(long a, long b){
    long out = 1;
    for(int i = 1; i<= b; i++){
        out *= a;
    }

    if (verboseMode) printf("$: POW %ld %ld --> %ld\n", a, b, out);
    return out;
}