#ifndef PARSER_H
#define PARSER_H

#include "node.h"

int checkSyntax(char* string);
node* parseExpression(char* string);
void removeSpaces(char* str);

void displayHelp();

int findMatchingParenthesisIndexLeft(char* string, int index);
int findMatchingParenthesisIndexRight(char* string, int index);


#endif