#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char input[50];
int ip = 0;  // current input index

void E();
void Eprime();
void T();
void Tprime();
void F();

void advance() { ip++; }

char lookahead() {
    return input[ip];
}

void error(const char *msg) {
    printf("Syntax error: %s at '%c'\n", msg, input[ip]);
    exit(1);
}

void E() {
    printf("E -> T E'\n");
    T();
    Eprime();
}

void Eprime() {
    if (lookahead() == '+') {
        printf("E' -> + T E'\n");
        advance();  // consume '+'
        T();
        Eprime();
    } else {
        printf("E' -> ε\n");
    }
}

void T() {
    printf("T -> F T'\n");
    F();
    Tprime();
}

void Tprime() {
    if (lookahead() == '*') {
        printf("T' -> * F T'\n");
        advance();  // consume '*'
        F();
        Tprime();
    } else {
        printf("T' -> ε\n");
    }
}

void F() {
    if (lookahead() == 'i') {
        printf("F -> i\n");
        advance();
    } else if (lookahead() == '(') {
        printf("F -> (E)\n");
        advance();  // consume '('
        E();
        if (lookahead() == ')') {
            advance();
        } else {
            error("expected ')'");
        }
    } else {
        error("invalid symbol");
    }
}

int main() {
    printf("Grammar:\n");
    printf("E  -> T E'\nE' -> + T E' | ε\nT  -> F T'\nT' -> * F T' | ε\nF  -> (E) | i\n\n");

    printf("Enter input (like i+i*i): ");
    scanf("%s", input);

    printf("\nParsing trace:\n\n");
    E();

    if (lookahead() == '\0') {
        printf("\n✅ Parsing successful!\n");
    } else {
        printf("\n❌ Syntax error at '%c'\n", lookahead());
    }

    return 0;
}

