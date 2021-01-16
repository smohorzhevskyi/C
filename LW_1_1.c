// Відредагувати речення; видаливши з нього зайві пробіли, залишаючи лише
// один пробіл між словами.

#include <stdio.h>
#include <string.h>

#define SIZE 64

int main()
{
    char input[SIZE];
    char buffer[SIZE] = "";
    int i=1, len;

    puts("Enter your phrase to edit:");
    fgets(input, SIZE, stdin);
    len = strlen(input);

    if (input[0] != ' ')
        strncat(buffer, &input[i], 1);

    while (i<len) {
        if (!((input[i] == ' ') && (input[i-1] == ' ') || i==0))
            strncat(buffer, &input[i], 1);
        i++;
    }

    puts(buffer);

    return (0);
}
