#ifndef NODE_H
#define NODE_H

typedef struct Node{
    long value;
    long (*operator) (long, long);

    struct Node* left;
    struct Node* right;
}node;

node* createNode(void);
long evaluate(node* head);

long add(long a, long b);
long sub(long a, long b);
long mult(long a, long b);
long divi(long a, long b);
long power(long a, long b);

#endif