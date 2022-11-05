// Recovers JPEGS from memory card file
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>


typedef uint8_t  BYTE;
#define BLOCKSIZE 512
 
int main(int argc, char *argv[])
{
    // Only 2 arguments allowed
    if (argc != 2)
    {
        printf("Usage Error: ./recover image\n");
        return 1;
    }
    
    // Open file and check for NULL
    FILE* memoryCard = fopen(argv[1], "r");
    if (memoryCard == NULL)
    {
         printf("ERROR: Couldn't open file, please try again\n");
         return 1;
    }
    
    BYTE buffer[BLOCKSIZE]; // 512 byte block of memory
    int numOfJpg = 0; // Tracks # of JPEG files created
    FILE* img = NULL;
    char filename[8]; // ###.jpg\0, holds the filename of JPEG file     
     
    while (fread(buffer, sizeof(BYTE), BLOCKSIZE, memoryCard)) // Repeat as long as we are able to read a 512 byte block, if fread() returns any less than 512, we have read through entire memory card
    {
       
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0) // Checks to see if current 512 block of memory is the start of a JPEG
        {
            if (img != NULL) // If not first image
            {
                fclose(img); // Close previous JPEG file
            }
            // Open new JPEG file with correct numbering
            sprintf(filename, "%03i.jpg", numOfJpg);
            img = fopen(filename, "w");
            numOfJpg++;
        }
        
        // Keep filling up JPEG file with blocks as long as the block belongs to a JPEG file
        if (img != NULL)
        {
            fwrite(buffer, sizeof(BYTE), BLOCKSIZE, img);
        }
    }
    
    // Close files after done working with them
    fclose(img);
    fclose(memoryCard);
}
