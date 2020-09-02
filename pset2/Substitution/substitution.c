//
// Created by Kun on 2020/9/2.
//

#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Wrong command line argument!\n");
        return 1;
    }

    char *key = argv[1];
    int len = strlen(key);
    if (len != 26)
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }

    for (int i = 0; i < len; i += 1)
    {
        if (isalpha(key[i]) == 0)
        {
            printf("Your key can only contain alphabetic characters.\n");
            return 1;
        }
    }

    char check[26] = "";
    for (int i = 0; i < len; i += 1)
    {
        int c = tolower(key[i]) - 97;
        if (check[c] != 0)
        {
            printf("Your key must contain each character exactly once.\n");
            return 1;
        }
        check[c] = 1;
    }

    char input[100];
    printf("plaintext: ");
    scanf("%[^\n]s", input);

    int position;
    int input_len = strlen(input);
    for (int i = 0; i < input_len; i += 1)
    {
        if (isalpha(input[i]) == 0)
        {
            continue;
        }
        else if (input[i] > 96)
        {
            position = input[i] - 97;
            input[i] = tolower(key[position]);
        }
        else
        {
            position = input[i] - 65;
            input[i] = toupper(key[position]);
        }
    }
    printf("ciphertext: %s\n", input);
}
