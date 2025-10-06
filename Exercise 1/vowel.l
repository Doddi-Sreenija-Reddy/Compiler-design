%{
#include <stdio.h>

int vowels = 0;
int cons = 0;
%}

%%
[aeiouAEIOU]     { vowels++; }
[a-zA-Z]         { cons++; }
.|\n             { /* ignore other characters */ }
%%

int yywrap() {
    return 1;
}

int main() {
    printf("Enter the string... (Press Ctrl+D to end input on Unix/Linux or Ctrl+Z on Windows)\n");
    yylex();
    printf("No of vowels = %d\n", vowels);
    printf("No of consonants = %d\n", cons - vowels); // subtract vowels to get consonants
    return 0;
}

