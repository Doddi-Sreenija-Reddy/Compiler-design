%{
#include <stdio.h>
#include <stdlib.h>

int COMMENT = 0;
%}

%option noyywrap

identifier [a-zA-Z_][a-zA-Z0-9_]*
number [0-9]+
string \".*\"

%%

"/*"                     { COMMENT = 1; printf("\n%s begins a COMMENT", yytext); }
"*/"                     { COMMENT = 0; printf("\n%s ends a COMMENT", yytext); }

#.*                      { if (!COMMENT) printf("\n%s is a PREPROCESSOR DIRECTIVE", yytext); }

"int" |
"float" |
"char" |
"double" |
"while" |
"for" |
"struct" |
"typedef" |
"do" |
"if" |
"break" |
"continue" |
"void" |
"switch" |
"return" |
"else" |
"goto"                   { if (!COMMENT) printf("\n%s is a KEYWORD", yytext); }

{identifier}\(          { if (!COMMENT) printf("\nFUNCTION CALL or DECLARATION: %s", yytext); }

\{                       { if (!COMMENT) printf("\nBLOCK BEGINS"); }
\}                       { if (!COMMENT) printf("\nBLOCK ENDS"); }

{identifier}(\[[0-9]*\])? { if (!COMMENT) printf("\n%s is an IDENTIFIER", yytext); }

{string}                { if (!COMMENT) printf("\n%s is a STRING", yytext); }

{number}                { if (!COMMENT) printf("\n%s is a NUMBER", yytext); }

=                       { if (!COMMENT) printf("\n%s is an ASSIGNMENT OPERATOR", yytext); }

"<=" |
">=" |
"<"  |
"==" |
">"                      { if (!COMMENT) printf("\n%s is a RELATIONAL OPERATOR", yytext); }

[ \t\n]+                ;   // Ignore whitespace

.                       { if (!COMMENT) printf("\nUnrecognized: %s", yytext); }

%%

int main() {
    FILE *file = fopen("var.c", "r");
    if (!file) {
        fprintf(stderr, "Could not open file.\n");
        exit(1);
    }
    yyin = file;
    yylex();
    printf("\n");
    fclose(file);
    return 0;
}

