#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define BLOCK_SIZE 512

int main(int argc, char *argv[])
{
    // Accept a single command-line argument
    if (argc != 2)
    {
        printf("Usage: ./recover FILE\n");
        return 1;
    }

    // Open the memory card
    FILE *card = fopen(argv[1], "r");
    if (card == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    // Create a buffer to store a block
    uint8_t buffer[BLOCK_SIZE];

    FILE *img = NULL;
    int file_count = 0;
    char filename[8]; // Filenames are "000.jpg" + the NULL character

    // While there's still data left to read from the memory card
    while (fread(buffer, 1, 512, card) == BLOCK_SIZE)
    {
        // Check the start of JPEG
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff &&
            (buffer[3] & 0xf0) == 0xe0)
        // The last argument checks if the first 4 bits are 1110 (JPEG markers are 1110xxxx)

        {
            // Close open JPEG file
            if (img != NULL)
            {
                fclose(img);
            }

            // Create new filename
            sprintf(filename, "%03i.jpg", file_count);
            file_count++;

            // Open new JPEG file
            img = fopen(filename, "w");
            if (img == NULL)
            {
                printf("Could not create file.\n");
                fclose(card);
                return 1;
            }
        }

        // Write if there's a JPEG open
        if (img != NULL)
        {
            fwrite(buffer, 1, BLOCK_SIZE, img);
        }
    }

    if (img != NULL)
    {
        fclose(img);
    }
    fclose(card);
    return 0;
}
