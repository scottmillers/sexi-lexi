#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include "dcooke.h"

TokenType nextToken;
int P(FILE *fp) {
    printf("Enter <P>\n");
    S(fp); // Since P ::= S, just call S
    return 0;
}
//***********************************************************************************************************************************************************************
int S(FILE *fp) {
    printf("Enter <S>\n");

    // Handle assignment V:=E
    if (nextToken == IDENT) {
        lex(fp); // Consume the identifier
        if (nextToken == ASSIGN_OP) { // Assuming ASSIGN_OP represents :=
            lex(fp); // Consume the assignment operator
            expr(fp); // Parse E
        }
    }
    // Handle read(V)
    else if (nextToken == KEY_READ) { // Assuming READ_FUNC represents the 'read' keyword
        lex(fp); // Consume 'read'
        if (nextToken == LEFT_PAREN) {
            lex(fp); // Consume '('
            if (nextToken == IDENT) {
                lex(fp); // Consume identifier
                if (nextToken == RIGHT_PAREN) {
                    lex(fp); // Consume ')'
                } else {
                    error("Expected right parenthesis");
                    return 13;
                }
            } else {
                error("Expected identifier");
                return 13;
            }
        }
    }
    // Handle write(E)
    else if (nextToken == KEY_WRITE) { // Assuming WRITE_FUNC represents the 'write' keyword
        lex(fp); // Consume 'write'
        if (nextToken == LEFT_PAREN) {
            lex(fp); // Consume '('
            expr(fp); // Parse E
            if (nextToken == RIGHT_PAREN) {
                lex(fp); // Consume ')'
            } else {
                error("Expected right parenthesis");
                return 13;
            }
        }
    }
    // Handle if C: then S fi and if C: then S else S fi
    else if (nextToken == KEY_IF) {
        lex(fp); // Consume 'if'
        C(fp); // Parse condition C
        if (nextToken == KEY_THEN) {
            lex(fp); // Consume 'then'
            S(fp); // Parse the first S
            if (nextToken == KEY_ELSE) {
                lex(fp); // Consume 'else'
                S(fp); // Parse the second S
            }
            if (nextToken == KEY_FI) {
                lex(fp); // Ensure we end with 'fi'
            } else {
                error("Expected 'fi'");
                return 13;
            }
        } else {
            error("Expected 'then'");
            return 13;
        }
    }
        if (nextToken == SEMICOLON) {
        lex(fp); // Consume the identifier
        S(fp);
    }

    printf("Exit <S>\n");
    return 0;
}

//***********************************************************************************************************************************************************************
int C(FILE *fp) {
    printf("Enter <C>\n");

    // Parse the first expression
    expr(fp);

    // Now check for the comparison operator
    if (nextToken == LESSER_OP) { // Assuming LESS_THAN_OP represents '<'
        lex(fp); // Consume the '<' operator
        expr(fp); // Parse the second expression
    } else if (nextToken == GREATER_OP) { // Assuming GREATER_THAN_OP represents '>'
        lex(fp); // Consume the '>' operator
        expr(fp); // Parse the second expression
    } else if (nextToken == EQUAL_OP) { // Assuming EQUAL_OP represents '='
        lex(fp); // Consume the '=' operator
        expr(fp); // Parse the second expression
    } else if (nextToken == NEQUAL_OP) { // Assuming NOT_EQUAL_OP represents '<>'
        lex(fp); // Consume the '<>' operator
        expr(fp); // Parse the second expression
    } else if (nextToken == LEQUAL_OP) { // Assuming LESS_THAN_EQUAL_OP represents '<='
        lex(fp); // Consume the '<=' operator
        expr(fp); // Parse the second expression
    } else if (nextToken == GEQUAL_OP) { // Assuming GREATER_THAN_EQUAL_OP represents '>='
        lex(fp); // Consume the '>=' operator
        expr(fp); // Parse the second expression
    } else if (nextToken == LEFT_PAREN) { // For cases where condition is wrapped in parentheses
        lex(fp); // Consume the '('
        C(fp); // Parse nested condition
        if (nextToken == RIGHT_PAREN) {
            lex(fp); // Consume the ')'
        } else {
            error("Expected right parenthesis");
            return 13;
        }
    } else {
        error("Expected comparison operator or nested condition");
        return 13;
    }

    printf("Exit <C>\n");
    return 0;
}
//***********************************************************************************************************************************************************************
int O(FILE *fp) {
    printf("Enter <O>\n");

    // Handle increment operation ++V
    if (nextToken == INC_OP) { // Assuming INCREMENT_OP represents '++'
        lex(fp); // Consume '++'
        V(fp); // Parse variable V
    }
    // Handle decrement operation --V
    else if (nextToken == DEC_OP) { // Assuming DECREMENT_OP represents '--'
        lex(fp); // Consume '--'
        V(fp); // Parse variable V
    }
    else {
        error("Expected increment or decrement operation");
        return 13;
    }

    printf("Exit <O>\n");
    return 0;
}
//***********************************************************************************************************************************************************************
int V(FILE *fp) {
    printf("Enter <V>\n");

    // Check if the current token is an identifier, which we treat as a valid variable (V).
    if (nextToken == IDENT) {
        lex(fp);  // Consume the identifier, effectively parsing the variable.
    } else {
        // If the current token is not an identifier, report an error.
        error("Expected a variable identifier");
        return 13;
    }

    printf("Exit <V>\n");
    return 0;
}
//***********************************************************************************************************************************************************************
int N(FILE *fp) {
    printf("Enter <N>\n");

    if (nextToken == INT_LIT) { // Assuming NUM or INT_LIT represents a numeral token.
        lex(fp);  // Consume the numeral token.
    } else {
        error("Expected a numeral");
        return 13;
    }

    printf("Exit <N>\n");
    return 0;
}
//***********************************************************************************************************************************************************************

int error(const char *errorMessage) {
    printf("Error: %s\n", errorMessage);
    // Handle error appropriately (e.g., by exiting or skipping to next statement)
        return 0;
}
//***********************************************************************************************************************************************************************
/* expr
 * Parses strings in the language generated by the rule:
 * <expr> -> <term> {(+ | -) <term>}
 */
int expr(FILE *fp) 
{
    printf("Enter <expr>\n");

    /* Parse the first term */
    term(fp);

    /* As long as the next token is + or -, get
    the next token and parse the next term */
    while (nextToken == ADD_OP || nextToken == SUB_OP) {
        lex(fp);
        term(fp);
    }

    printf("Exit <expr>\n");
    return 0;
} /* End of function expr */
//***********************************************************************************************************************************************************************
/* term
 * Parses strings in the language generated by the rule:
 * <term> -> <factor> {(* | /) <factor>)
 */
int term(FILE *fp) 
{
    printf("Enter <term>\n");
    /* Parse the first factor */
    factor(fp);
    /* As long as the next token is * or /, get the
    next token and parse the next factor */
    while (nextToken == MULT_OP || nextToken == DIV_OP || nextToken == MOD_OP) {
            lex(fp);
            factor(fp);
    }
    printf("Exit <term>\n");
    return 0;
} /* End of function term */
//***********************************************************************************************************************************************************************
/* factor
 * Parses strings in the language generated by the rule:
 * <factor> -> id | int_constant | ( <expr )
 * */
int factor(FILE *fp) 
{
    printf("Enter <factor>\n");
    /* Determine which RHS */
    if (nextToken == IDENT || nextToken == INT_LIT) {
        lex(fp); /* Get the next token */
    } else {
        /* If the RHS is (<expr>), call lex to pass over the 
        left parenthesis, call expr, and check for the right 
        parenthesis */
        if (nextToken == LEFT_PAREN) {
            lex(fp); 
            expr(fp);

            if (nextToken == RIGHT_PAREN) {
                lex(fp); 
            } else { 
                error("in factor");
                return 13;
            }
        } /* End of if (nextToken == ... */
        /* It was not an id, an integer literal, or a left parenthesis */
        else 
        { 
            error("in factor"); 
            return 13;
        }
    } /* End of else */
    printf("Exit <factor>\n");;
    return 0;
} /* End of function factor */
//***********************************************************************************************************************************************************************


int main(int argc, char *argv[]) {

    // Checks for correct # of arguments
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <path_to_source_file>\n", argv[0]);
        return 1;
    }

    // Opens the file
    FILE *fp = fopen(argv[1], "r");
    if (fp == NULL) {
        fprintf(stderr, "Error: Unable to open file %s\n", argv[1]);
        return 1;
    }
    printf("DCooke Parser :: R11770217\n\n");
    lex(fp);
    P(fp);
    


    fclose(fp); // Closes the file
    return 0;
}
//***********************************************************************************************************************************************************************
   int lex2(FILE *fp){

    char lexeme[256]; // Buffer for lexemes
    int lexemeIndex = 0; // Index for the current lexeme
    int c; // hold char
    c = fgetc(fp);
        // Checks if the character is a delimiter or part of a token
        if (isspace(c) || strchr("+-<>*=/<>%();:", c) != NULL || c=='$'|| c=='^'|| c=='#'|| c=='!'|| c=='@'|| c=='?'|| c=='~'|| c=='`'|| c==','|| c=='.'|| c=='&'|| c=='['|| c==']'|| c=='|') {
            if (lexemeIndex != 0) { // Process the accumulated lexeme
                lexeme[lexemeIndex] = '\0'; // Null-terminate lexeme
                printToken(lexeme, getToken(lexeme)); // Print token
                nextToken = getToken(lexeme);
                lexemeIndex = 0; // Reset lexeme
                return nextToken;
            }
            // Checks if char is recognized token
            if (strchr("+-<>*=/<>%();:", c) != NULL|| c=='$'|| c=='^'|| c=='#'|| c=='!'|| c=='@'|| c=='?'|| c=='~'|| c=='`'|| c==','|| c=='.'|| c=='&'|| c=='['|| c==']'|| c=='|') {
                if (c == '$'||c=='^'|| c=='#'|| c=='!'|| c=='@'|| c=='?'|| c=='~'|| c=='`'|| c==','|| c=='.'|| c=='&'|| c=='['|| c==']'|| c=='|') {
                    lexeme[0] = c;
                    lexeme[1] = '\0';
                    printToken(lexeme, getToken(lexeme));
                    nextToken = getToken(lexeme);
                    return nextToken;
                }
            else{                // Checks for possible two-character tokens
                char nextChar = fgetc(fp); 
                char twoCharToken[3] = {c, nextChar, '\0'};
                if (getToken(twoCharToken) != UNKNOWN) {
                    printToken(twoCharToken, getToken(twoCharToken)); // Prints if recognized two-character token
                    nextToken = getToken(lexeme);
                    return nextToken;
                } else { // prints single-character token
                    ungetc(nextChar, fp); // Puts back the next character as it is not part of a two-character token
                    lexeme[0] = c;
                    lexeme[1] = '\0';
                    printToken(lexeme, getToken(lexeme));
                    nextToken = getToken(lexeme);
                    return nextToken;
                }}

            }
        } else {
            lexeme[lexemeIndex++] = c; // Adds the char to current lexeme
        }
        return nextToken;
    }
//***********************************************************************************************************************************************************************
int lex(FILE *fp){
    char lexeme[256]; // Buffer for lexemes
    int lexemeIndex = 0; // Index for the current lexeme
    int c; // hold char
        while ((c = fgetc(fp)) != EOF) {
        // Checks if the character is a delimiter or part of a token
        if (isspace(c) || strchr("+-<>*=/<>%();:", c) != NULL || c=='$'|| c=='^'|| c=='#'|| c=='!'|| c=='@'|| c=='?'|| c=='~'|| c=='`'|| c==','|| c=='.'|| c=='&'|| c=='['|| c==']'|| c=='|') {
            if (lexemeIndex != 0) { // Process the accumulated lexeme
                lexeme[lexemeIndex] = '\0'; // Null-terminate lexeme
                    nextToken = getToken(lexeme);
                    return nextToken;
                printToken(lexeme, getToken(lexeme)); // Print token
                lexemeIndex = 0; // Reset lexeme
            }
            // Checks if char is recognized token
            if (strchr("+-<>*=/<>%();:", c) != NULL|| c=='$'|| c=='^'|| c=='#'|| c=='!'|| c=='@'|| c=='?'|| c=='~'|| c=='`'|| c==','|| c=='.'|| c=='&'|| c=='['|| c==']'|| c=='|') {
                if (c == '$'||c=='^'|| c=='#'|| c=='!'|| c=='@'|| c=='?'|| c=='~'|| c=='`'|| c==','|| c=='.'|| c=='&'|| c=='['|| c==']'|| c=='|') {
                    lexeme[0] = c;
                    lexeme[1] = '\0';
                    nextToken = getToken(lexeme);
                    return nextToken;
                    printToken(lexeme, getToken(lexeme));
                }
            else{                // Checks for possible two-character tokens
                char nextChar = fgetc(fp); 
                char twoCharToken[3] = {c, nextChar, '\0'};
                if (getToken(twoCharToken) != UNKNOWN) {
                    nextToken = getToken(twoCharToken);
                    return nextToken;
                    printToken(twoCharToken, getToken(twoCharToken)); // Prints if recognized two-character token
                    nextToken = getToken(lexeme);
                } else { // prints single-character token
                    ungetc(nextChar, fp); // Puts back the next character as it is not part of a two-character token
                    lexeme[0] = c;
                    lexeme[1] = '\0';
                    nextToken = getToken(lexeme);
                    return nextToken;
                    printToken(lexeme, getToken(lexeme));

                }}

            }
        } else {
            lexeme[lexemeIndex++] = c; // Adds the char to current lexeme
        }
    }

    // Processes the final lexeme if there is one
    if (lexemeIndex != 0) {
        lexeme[lexemeIndex] = '\0'; // Null-terminates the lexeme
        nextToken = getToken(lexeme);
        return nextToken;
        printToken(lexeme, getToken(lexeme)); // Prints the final token
    }
    return nextToken;
    }