// Modifies the volume of an audio file

#include <stdint.h> // Contains uint8_t and int16_t
#include <stdio.h>
#include <stdlib.h>

// Number of bytes in .wav header
const int HEADER_SIZE = 44;

int main(int argc, char *argv[])
{
    // Check command-line arguments
    if (argc != 4)
    {
        printf("Usage: ./volume input.wav output.wav factor\n");
        return 1;
    }

    // Open input file for reading
    FILE *input = fopen(argv[1], "r");
    if (input == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    // Open input file for writing
    FILE *output = fopen(argv[2], "w");
    if (output == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    // Get scaling factor from command-line argument
    float factor = atof(argv[3]);

    // Copy header from input file to output file
    uint8_t header[HEADER_SIZE];
    fread(header, HEADER_SIZE, 1, input);
    fwrite(header, HEADER_SIZE, 1, output);

    // Read samples from input file and write updated data to output file
    int16_t buffer;
    
    // Read and adjust samples until the end of the file
    while (fread(&buffer, sizeof(int16_t), 1, input))
    {
        buffer *= factor;    // Scale sample value by factor
        fwrite(&buffer, sizeof(int16_t), 1, output);    // Write updated sample to output file
    }

    // Close input and output files
    fclose(input);
    fclose(output);
}
