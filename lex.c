#include <stdio.h>
#include <ctype.h>

// Token types
typedef enum {
    TOKEN_INTEGER,
    TOKEN_OPERATOR,
    TOKEN_PARENTHESIS,
    TOKEN_UNKNOWN,
    TOKEN_EOF // End of input
} TokenType;

// Token structure
typedef struct {
    TokenType type;
    char value;
} Token;

// Global variables
char *input;
char currentChar;

// Function prototypes
void advance();
char lex();
Token nextToken();

int main() {
    char inputString[] = "10 + (23 - 45) * 67";
    input = inputString;
    currentChar = lex();

    Token token;
    do {
        token = nextToken();
        switch(token.type) {
            case TOKEN_INTEGER:
                printf("INTEGER: %c\n", token.value);
                break;
            case TOKEN_OPERATOR:
                printf("OPERATOR: %c\n", token.value);
                break;
            case TOKEN_PARENTHESIS:
                printf("PARENTHESIS: %c\n", token.value);
                break;
            case TOKEN_EOF:
                printf("END OF INPUT\n");
                break;
            default:
                printf("UNKNOWN: %c\n", token.value);
                break;
        }
    } while(token.type != TOKEN_EOF);

    return 0;
}

// Function to advance to the next character in the input
void advance() {
    input++;
    currentChar = lex();
}

// Function to get the next lexical character
char lex() {
    if (*input != '\0') {
        return *input;
    } else {
        return EOF; // End of file/input character
    }
}

// Function to get the next token
Token nextToken() {
    Token token;
    token.type = TOKEN_UNKNOWN;
    token.value = currentChar;

    if (currentChar == EOF) {
        token.type = TOKEN_EOF;
    } else if (isdigit(currentChar)) {
        token.type = TOKEN_INTEGER;
        advance();
    } else if (currentChar == '+' || currentChar == '-' || currentChar == '*' || currentChar == '/') {
        token.type = TOKEN_OPERATOR;
        advance();
    } else if (currentChar == '(' || currentChar == ')') {
        token.type = TOKEN_PARENTHESIS;
        advance();
    } else {
        advance();
    }

    return token;
}
