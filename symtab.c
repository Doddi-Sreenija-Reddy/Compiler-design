#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int main() {
    int x = 0, n, i = 0, j = 0;
    void *mypointer, *T4Tutorials_address[5];
    char ch, T4Tutorials_Array2[15], T4Tutorials_Array3[15], c;

    printf("Input the expression ending with $ sign:\n");

    // Read input until $ is encountered
    while ((c = getchar()) != '$' && i < 14) {
        T4Tutorials_Array2[i] = c;
        i++;
    }
    T4Tutorials_Array2[i] = '\0'; // Null-terminate the string
    n = i - 1;

    // Display input expression
    printf("Given Expression: ");
    for (i = 0; i <= n; i++) {
        printf("%c", T4Tutorials_Array2[i]);
    }

    printf("\n\nSymbol Table display\n");
    printf("Symbol\t\tAddress\t\tType\n");

    while (j <= n) {
        c = T4Tutorials_Array2[j];
        if (isalpha(c)) {
            // Allocate memory for identifier
            mypointer = malloc(sizeof(char));
            if (mypointer == NULL) {
                printf("Memory allocation failed\n");
                return 1;
            }
            T4Tutorials_address[x] = mypointer;
            T4Tutorials_Array3[x] = c;
            printf("%c\t\t%p\tidentifier\n", c, mypointer);
            x++;
        } else if (c == '+' || c == '-' || c == '*' || c == '=') {
            // Allocate memory for operator
            mypointer = malloc(sizeof(char));
            if (mypointer == NULL) {
                printf("Memory allocation failed\n");
                return 1;
            }
            T4Tutorials_address[x] = mypointer;
            T4Tutorials_Array3[x] = c;
            printf("%c\t\t%p\toperator\n", c, mypointer);
            x++;
        }
        j++;
    }

    // Free allocated memory
    for (i = 0; i < x; i++) {
        free(T4Tutorials_address[i]);
    }

    return 0;
}

