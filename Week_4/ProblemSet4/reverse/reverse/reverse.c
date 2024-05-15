#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "wav.h"

int check_format(WAVHEADER header);
int get_block_size(WAVHEADER header);

int main(int argc, char *argv[])
{
    // Ensure proper usage
    // TODO #1
    if (argc != 3)
    {
        printf("Usage: ./reverse input.wav output.wav\n");
    }
    // Open input file for reading
    // TODO #2
    FILE *file = fopen(argv[1], "r");
    if (file == NULL)
    {
        printf("Could not open %s.\n", argv[1]);
        return 1;
    }

    // Read header
    // TODO #3
    WAVHEADER header;
    fread(&header, sizeof(WAVHEADER), 1, file);
    printf("%ld\n", ftell(file));



    // Use check_format to ensure WAV format
    // TODO #4
    int x = check_format(header);
    if (x != 1) {
        printf("Error");
    }
    printf("Juhu\n");
    // Open output file for writing
    // TODO #5
    FILE *output = fopen(argv[2], "w");
    if (output == NULL)
    {
        fclose(output);
        printf("Could not create %s.\n", argv[2]);
        return 2;
    }

    // Write header to file
    // TODO #6
    fwrite(&header, sizeof(WAVHEADER), 1, output);

    // Use get_block_size to calculate size of block
    // TODO #7
    int y = get_block_size(header);
    printf("%i\n", y);

    // Write reversed audio to file
    // TODO #8

    // Angenommen, block_size ist die Größe jedes Audio-Blocks
    int block_size = get_block_size(header);
    int header_size = sizeof(WAVHEADER); // Größe des Headers

    fseek(file, 0, SEEK_END); // Gehe zum Ende der Datei
    long file_pos = ftell(file); // Hole die aktuelle Position in der Datei

    for (file_pos = file_pos - block_size; file_pos >= header_size; file_pos -= block_size)
    {
        //setze Dateizeiger auf aktuelle Position
        fseek(file, file_pos, SEEK_SET);

        // Lese den aktuellen Block in einen Puffer
        char *buffer = malloc(block_size);
        fread(buffer, block_size, 1, file);


        // Schreibe den Puffer in die Ausgabedatei
        fwrite(buffer, block_size, 1, output);
        free(buffer);
    }
    fclose(file);
    fclose(output);
}

int check_format(WAVHEADER header)
{
    // TODO #4
    char wave[5] = "WAVE";

    if(strncmp((char *)header.format, wave, 4) == 0){
        printf("gleich\n");
        return 1;
    }
    printf("nicht gleich\n");

    return 0;
}

int get_block_size(WAVHEADER header)
{
    // TODO #7
    return header.numChannels*(header.bitsPerSample/8);
}