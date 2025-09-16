%{
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int yylex();
int yyerror(const char *s);

#define YYSTYPE double
%}

%token NUMBER
%left '+' '-'
%left '*' '/'
%right UMINUS

%%

lines:
    lines expr '\n'      { printf("%g\n", $2); }
  | lines '\n'
  | /* empty */
;

expr:
    expr '+' expr         { $$ = $1 + $3; }
  | expr '-' expr         { $$ = $1 - $3; }
  | expr '*' expr         { $$ = $1 * $3; }
  | expr '/' expr         { $$ = $1 / $3; }
  | '-' expr %prec UMINUS { $$ = -$2; }
  | '(' expr ')'          { $$ = $2; }
  | NUMBER                { $$ = $1; }
;

%%

int yylex() {
    int c;

    // Skip whitespace
    while ((c = getchar()) == ' ' || c == '\t');

    if (c == EOF) return 0;

    // Number (digit or starting with .)
    if (isdigit(c) || c == '.') {
        ungetc(c, stdin);
        if (scanf("%lf", &yylval) != 1) {
            fprintf(stderr, "Invalid number\n");
            exit(1);
        }
        return NUMBER;
    }

    // Single-character operators and delimiters
    return c;
}

int yyerror(const char *s) {
    fprintf(stderr, "Error: %s\n", s);
    return 1;
}

int main() {
    return yyparse();
}

int yywrap() {
    return 1;
}

