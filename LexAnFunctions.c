#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "dcooke.h"

TokenType nextToken1;


// Array of token names for printing
const char* tokenNames[] = {
    "ASSIGN_OP", "ADD_OP", "KEY_READ", "LESSER_OP", "SUB_OP", "KEY_WRITE", "GREATER_OP", 
    "MULT_OP", "KEY_IF", "EQUAL_OP", "DIV_OP", "KEY_FI", "NEQUAL_OP", "MOD_OP", "KEY_ELSE", 
    "LEQUAL_OP", "INC_OP", "KEY_THEN", "GEQUAL_OP", "DEC_OP", "IDENT", "LEFT_PAREN", "SEMICOLON", 
    "INT_LIT", "RIGHT_PAREN", "COLON", "END_OF_FILE", "UNKNOWN"
};

// Function to classify lexemes
TokenType getToken(const char *lexeme) {
    // maps lexemes to token types
    if (strcmp(lexeme, ":=") == 0) return ASSIGN_OP;
    else if (strcmp(lexeme, "+") == 0) return ADD_OP;
    else if (strcmp(lexeme, "read") == 0) return KEY_READ;
    else if (strcmp(lexeme, "<") == 0) return LESSER_OP;
    else if (strcmp(lexeme, "-") == 0) return SUB_OP;
    else if (strcmp(lexeme, "write") == 0) return KEY_WRITE;
    else if (strcmp(lexeme, ">") == 0) return GREATER_OP;
    else if (strcmp(lexeme, "*") == 0) return MULT_OP;
    else if (strcmp(lexeme, "if") == 0) return KEY_IF;
    else if (strcmp(lexeme, "=") == 0) return EQUAL_OP;
    else if (strcmp(lexeme, "/") == 0) return DIV_OP;
    else if (strcmp(lexeme, "fi") == 0) return KEY_FI;
    else if (strcmp(lexeme, "<>") == 0) return NEQUAL_OP;
    else if (strcmp(lexeme, "%") == 0) return MOD_OP;
    else if (strcmp(lexeme, "else") == 0) return KEY_ELSE;
    else if (strcmp(lexeme, "<=") == 0) return LEQUAL_OP;
    else if (strcmp(lexeme, "++") == 0) return INC_OP;
    else if (strcmp(lexeme, "then") == 0) return KEY_THEN;
    else if (strcmp(lexeme, ">=") == 0) return GEQUAL_OP;
    else if (strcmp(lexeme, "--") == 0) return DEC_OP;
    else if (isalpha(lexeme[0])) return IDENT;
    else if (isdigit(lexeme[0])) return INT_LIT; 
    else if (strcmp(lexeme, "(") == 0) return LEFT_PAREN;
    else if (strcmp(lexeme, ";") == 0) return SEMICOLON;
    else if (strcmp(lexeme, ")") == 0) return RIGHT_PAREN;
    else if (strcmp(lexeme, ":") == 0) return COLON;
    return UNKNOWN; // For lexemes that don't match
}


// Function to print the identified token and its corresponding output
void printToken(const char *lexeme, TokenType type) {
    printf("%s %s\n", lexeme, tokenNames[type]); 
}

