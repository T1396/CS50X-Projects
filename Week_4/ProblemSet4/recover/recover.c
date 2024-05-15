#include <stdio.h>
#include <stdint.h>

typedef uint8_t BYTE;

#define BLOCK_SIZE 512

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./recover image\n");
        return 1;
    }

    FILE *file = fopen(argv[1], "r");
    if (file == NULL)
    {
        printf("Could not open %s.\n", argv[1]);
        return 1;
    }

    BYTE buffer[BLOCK_SIZE];
    FILE *jpeg = NULL;
    char filename[8];
    int counter = 0;

    while (fread(buffer, 1, BLOCK_SIZE, file) == BLOCK_SIZE)
    {
        // JPEG signature pattern
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            // Close the current file
            if (jpeg != NULL)
            {
                fclose(jpeg);
            }

            // Open a new file
            sprintf(filename, "%03i.jpg", counter++);
            jpeg = fopen(filename, "w");
            if (jpeg == NULL)
            {
                printf("Could not create %s.\n", filename);
                return 1;
            }
        }

        // Write to the current file
        if (jpeg != NULL)
        {
            fwrite(buffer, 1, BLOCK_SIZE, jpeg);
        }
    }

    // Close the last file
    if (jpeg != NULL)
    {
        fclose(jpeg);
    }

    fclose(file);

    return 0;
}
