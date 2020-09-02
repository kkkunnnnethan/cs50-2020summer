/*
 * C Program To Find the Sum of ASCII values of All Characters in a
 * given String
 */
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main(void)
{
    int sum = 0, i, len;
    char string1[100];

    printf("Enter the string : ");
    scanf("%[^\n]s", string1);
    len = strlen(string1);
    for (i = 0; i < len; i++)
    {
        sum = sum + tolower(string1[i]);
    }
    printf("\nSum of all characters : %d ",sum); //2847
}
