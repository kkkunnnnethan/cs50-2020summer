#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

// int *p = &n; 的意思是：
// go ahead and create a variable called p and store in it the address of n
// compile --> clang -o recover recover.c
// run --> ./recover card.raw
typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    FILE *file;
    FILE *img;
    int count = 0;
    char filename[8]; // 8 --> string長度(7) + 1(/0 --> 判別string結束) --> 檔名長度 + 1
    BYTE buffer[512]; // memory card 儲存方式為一格512bytes

    if (argc != 2)
    {
        printf("Error --> wrong input\n");
        printf("Correct input --> ./recover 'your input file name'\n");
        return 1;
    }

    file = fopen(argv[1], "r");
    if (file == NULL)
    {
        printf("Cannot load your file\n");
        return 1;
    }

    while (fread(buffer, 512, 1, file) != 0)
    {
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            if (count == 0)
            {
                sprintf(filename, "%03i.jpg", count);
                img = fopen(filename, "w");
                fwrite(buffer, 512, 1, img);
                count += 1;
            } else
            {
                fclose(img);
                sprintf(filename, "%03i.jpg", count);
                img = fopen(filename, "w");
                fwrite(buffer, 512, 1, img);
                count += 1;
            }
        } else if (count > 0)
        {
            fwrite(buffer, 512, 1, img);
        }
    }
    fclose(file);
    return 0;
}
