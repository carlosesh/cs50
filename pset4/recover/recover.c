#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef uint8_t  BYTE;

int recover(FILE *file, long int numberOfBytes);
long int getNumberOfBytesOfFile(FILE *file);
int isJpeg(BYTE *bytes);

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./recover image\n");

        return 1;
    }

    // Open input file
    FILE *file = fopen(argv[1], "r");
    if (file == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", argv[1]);
        return 1;
    }

    else
    {
        recover(file, getNumberOfBytesOfFile(file));
    }
}

long int getNumberOfBytesOfFile(FILE *file)
{
    fseek(file, 0L, SEEK_END);

    // calculating the size of the file
    long int res = ftell(file);

    return res;
}

int recover(FILE *file, long int numberOfBytes)
{
    int countOfJpegs = 0, flag = 0, previous = 0, current = 0;
    char filename [6];
    FILE *img = NULL;

    //reset the pointer to the beginning of the file
    fseek(file, 0, SEEK_SET);

    //iterate through the file in 512 blocks
    for (int i = 0; i < numberOfBytes / 512; i++)
    {
        //create an array of bytes with a size of 512
        BYTE *bytes = malloc(sizeof(BYTE) * 512);

        //assign to a buffer 512 bytes of the file pointed to
        fread(bytes, sizeof(BYTE), 512, file);

        //check if it's a jpeg and the flag is 1
        // this means that you have an open file and you need to close it
        if (isJpeg(bytes) == 1 && flag == 1)
        {
            flag = 0;
            countOfJpegs++;
            fclose(img);
        }

        //check if the i'th block is a jpeg and the flag is 0,
        //this will mean that the flag has now changed and it's
        //a new jpeg
        if (isJpeg(bytes) == 1 && flag == 0)
        {
            flag = 1;
            sprintf(filename, "%03i.jpg", countOfJpegs);
            img = fopen(filename, "w");
        }

        //if flag is 1 it meants to keep writing to the file
        if (flag == 1)
        {
            fwrite(bytes, sizeof(BYTE), 512, img);
        }

        free(bytes);
    }

    // closing the file
    fclose(file);

    return 0;
}

int isJpeg(BYTE *bytes)
{
    if (bytes[0] == 0xff &&  bytes[1] == 0xd8 && bytes[2] == 0xff && (bytes[3] & 0xff) == 0xe0)
    {
        return 1;
    }

    return 0;
}
