#include <stdio.h>
#include "node.h"
#include "parser.h"

int verboseMode = 0;

int main(){

    printf("Numerical Math Parser, ");
    printf("made by 2000gmod.\n");
    printf("Type \"exit\" or \"quit\" to exit the program.\n");
    printf("Type \"verb\" to toggle verbose mode.\n\n");
    int inputBuffer = 256;
    char inputString[inputBuffer];
    node* head;
    long result;
    int counter = 0;

    while(1){
        //Read from stdin
        printf("IN[%d] >>: ", counter);
        char* l = fgets(inputString, inputBuffer, stdin);
        
        //exit keywords and ctrl+D catching
        if (strcmp(inputString, "quit\n") == 0 || strcmp(inputString, "exit\n") == 0 || l == NULL){
            return 0;
        }
        //verbose
        if (strcmp(inputString, "verb\n") == 0 || strcmp(inputString, "verbose\n") == 0){
            verboseMode = !verboseMode;
            printf("$: VERBOSE MODE: %d\n", verboseMode);
            counter++;
            continue;
        }
        //help page
        if (strcmp(inputString, "help\n") == 0){
            displayHelp();
            counter++;
            continue;
        }
        //check syntax and parse
        int syntax = checkSyntax(inputString);
        if(syntax){
            head = parseExpression(inputString);
            result = evaluate(head);
            printf("#: %ld\n", result);
        }
        counter++;
    }
    return 0;
}