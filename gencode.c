#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int i = 1, j = 0, no = 0, tmpch = 90; // tmpch starts at 'Z'
char str[100], left[15], right[15];

struct exp {
    int pos;
    char op;
} k[15];

// Function declarations
void findopr();
void explore();
void fleft(int);
void fright(int);

int main() {
    printf("\t\tINTERMEDIATE CODE GENERATION\n\n");
    printf("Enter the Expression : ");
    scanf("%s", str);

    printf("The intermediate code:\n");

    findopr();
    explore();

    return 0;
}

void findopr() {
    // Find operators in order of precedence (lowest to highest)
    // Store their positions and operator in array k

    for (i = 0; str[i] != '\0'; i++)
        if (str[i] == ':') {
            k[j].pos = i;
            k[j++].op = ':';
        }

    for (i = 0; str[i] != '\0'; i++)
        if (str[i] == '/') {
            k[j].pos = i;
            k[j++].op = '/';
        }

    for (i = 0; str[i] != '\0'; i++)
        if (str[i] == '*') {
            k[j].pos = i;
            k[j++].op = '*';
        }

    for (i = 0; str[i] != '\0'; i++)
        if (str[i] == '+') {
            k[j].pos = i;
            k[j++].op = '+';
        }

    for (i = 0; str[i] != '\0'; i++)
        if (str[i] == '-') {
            k[j].pos = i;
            k[j++].op = '-';
        }
    // Mark end of operators array with a null char
    k[j].op = '\0';
}

void explore() {
    i = 1;
    while (k[i].op != '\0') {
        fleft(k[i].pos);
        fright(k[i].pos);

        str[k[i].pos] = tmpch--;  // Replace operator position in str with a temp var like Z, Y, X...

        printf("\t%c := %s %c %s\n", str[k[i].pos], left, k[i].op, right);

        i++;
    }

    // For last operator or expression part
    fright(-1);
    if (no == 0) {
        fleft(strlen(str));
        printf("\t%s := %s\n", right, left);
        exit(0);
    }

    printf("\t%s := %c\n", right, str[k[--i].pos]);
}

void fleft(int x) {
    int w = 0, flag = 0;
    x--;
    while (x != -1 && str[x] != '+' && str[x] != '*' && str[x] != '=' &&
           str[x] != '\0' && str[x] != '-' && str[x] != '/' && str[x] != ':') {
        if (str[x] != '$' && flag == 0) {
            left[w++] = str[x];
            left[w] = '\0';
            str[x] = '$';
            flag = 1;
        }
        x--;
    }
}

void fright(int x) {
    int w = 0, flag = 0;
    x++;
    while (x != -1 && str[x] != '+' && str[x] != '*' && str[x] != '\0' &&
           str[x] != '=' && str[x] != ':' && str[x] != '-' && str[x] != '/') {
        if (str[x] != '$' && flag == 0) {
            right[w++] = str[x];
            right[w] = '\0';
            str[x] = '$';
            flag = 1;
        }
        x++;
    }
}
