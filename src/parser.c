#include "parser.h"

int checkSyntax(char* string){

    //Check syntax, right now only checks if the characters are valid.
    /*
    TODO:
        - Check parenthesis as valid
        - Check all operators as valid
    */
    char math[] = "+-*/^()1234567890";
    char alphabet[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    char* checkA = strpbrk(string, alphabet);
    char* checkB = strpbrk(string, math);

    if(checkA != NULL || checkB == NULL){
        printf("$: INVALID COMMAND\n");
        printf("$: Only the math operation symbols:\n '+', '-', '*', '/', '^', '(', ')', numbers and commands are accepted as input.\n");
        return 0;
    }
    else return 1;
}

node* parseExpression(char *string){
    string = remove_spaces(string);
    node* current = malloc(sizeof(node));
    int len = strlen(string);
    int parenthesisLevel = 0;

    //First base case, check if the string contains only an integer number

    char *check;
    int number = strtol(string, &check, 10);
    if(check[0] == '\0'){
        current->value = number;
        current->operator = NULL;
        return current;
    }
    //Second "base" case, check if entire string is within parenthesis
    //not really a base case if it calls itself again, but it behaves like one

    if(string[0] == '(' && string[len - 1] == ')' && findMatchingParenthesisIndexRight(string, 0) == len - 1){
        string[len - 1] = '\0';
        parseExpression(&string[1]);
        current = parseExpression(&string[1]);
        return current;
    }

    //Right to left, because tree is later evaluated left to right, so the tree constructor does it in reverse
    //First pass is + and - signs, again because tree is evaluated in inverse order to its construction

    for(int i = len -1; i >= 0; i--){
        char c = string[i];
        if (c == '(') parenthesisLevel--;
        if (c == ')') parenthesisLevel++;

        if (c == '+' && parenthesisLevel == 0){
            string[i] = 0;
            current->operator = add;

            current->left = parseExpression(string);
            current->right = parseExpression(&string[i + 1]);

            return current;
        }
        else if (c == '-' && parenthesisLevel == 0){
            string[i] = 0;
            current->operator = sub;

            current->left = parseExpression(string);
            current->right = parseExpression(&string[i + 1]);

            return current;
        }
    }

    //Second pass for * and / signs

    for(int i = len -1; i >= 0; i--){
        char c = string[i];
        if (c == '(') parenthesisLevel--;
        if (c == ')') parenthesisLevel++;

        if (c == '*' && parenthesisLevel == 0){
            string[i] = 0;
            current->operator = mult;

            current->left = parseExpression(string);
            current->right = parseExpression(&string[i + 1]);

            return current;
        }
        else if (c == '/' && parenthesisLevel == 0){
            string[i] = 0;
            current->operator = divi;

            current->left = parseExpression(string);
            current->right = parseExpression(&string[i + 1]);

            return current;
        }
    }

    //Third pass for ^ operator

    for(int i = len -1; i >= 0; i--){
        char c = string[i];
        if (c == '(') parenthesisLevel--;
        if (c == ')') parenthesisLevel++;

        if (c == '^' && parenthesisLevel == 0){
            string[i] = 0;
            current->operator = power;

            current->left = parseExpression(string);
            current->right = parseExpression(&string[i + 1]);

            return current;
        }
    }
    return NULL;
}

char* remove_spaces(const char* str){
    
    //This function causes a small memory leak, fix soon

    int oLen = strlen(str);
    int nLen = 0;
    for(int i = 0; i <= oLen; i++){
        if(str[i] != ' ' && str[i] != '\n') nLen++;
    }
    char *out = malloc(nLen);
    int counter = 0;
    for(int i = 0; i <= oLen; i++){
        if(str[i] != ' ' && str[i] != '\n'){
            out[counter] = str[i];
            counter++;
        }
    }
    return out;
}

void displayHelp(){
    printf("$: Command list.\n");
    printf("$: 'quit' or 'exit': exits the program.\n");
    printf("$: 'verb' or 'verbose': toggles verbose mode on/off.\n");
    printf("$: 'help': displays this page.\n");
    return;
}

int findMatchingParenthesisIndexRight(char* string, int index){
    int len = strlen(string);
    int parentesisLevel = 1;
    for (int i = index + 1; i < len; i++){
        char c = string[i];
        if(c == '(') parentesisLevel++;
        else if (c == ')'){
            parentesisLevel--;
        }
        if (parentesisLevel == 0){
            return i;
        }
    }
    return 0;
}

//Not used, but useful to have anyways

int findMatchingParenthesisIndexLeft(char* string, int index){
    int parentesisLevel = 1;
    for (int i = index - 1; i >= 0; i--){
        char c = string[i];
        if(c == '(') parentesisLevel--;
        else if (c == ')'){
            parentesisLevel++;
        }
        if (parentesisLevel == 0){
            return i;
        }
    }
    return 0;
}
