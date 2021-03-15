#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "node.h"

#ifndef PARSER_H
#define PARSER_H

int checkSyntax(char* string);
node* parseExpression(char* string);
char* remove_spaces (const char* str);

void displayHelp();

int findMatchingParenthesisIndexLeft(char* string, int index);
int findMatchingParenthesisIndexRight(char* string, int index);


#endif