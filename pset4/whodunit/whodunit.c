/**
 * 
 * CS50 Computer Science
 * Problem Set4
 * 
 * Whodunit
 * 
 * Copy a BMP piece for piece
 * 
 * Usage: ./whodunit infile outfile
 */
 
#include <stdio.h>
#include <stdlib.h>
 
#include "bmp.h"
 
int main(int argc, char* argv[])
{
    // User must entry the correct command
    if (argc != 3)
    {
        printf("Usage: ./copy infile outfile\n");
        return 1;
    }
 
    // define filenames
    char* infile = argv[1];
    char* outfile = argv[2];
 
    // open input file 
    FILE* inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        printf("Could not open %s.\n", infile);
        return 2;
    }
 
    // open output file
    FILE* outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 3;
    }
 
    // read BITMAPFILEHEADER of the infile
    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);
 
    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);
 
    // verify infile is a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 || 
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }
 
    // write BITMAPFILEHEADER of the outfile
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);
 
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);
 
    // define padding for scanlines
    int padding =  (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
 
    // loop over infile's scanlines
    for (int i = 0, biHeight = abs(bi.biHeight); i < biHeight; i++)
    {
        // loop over pixels in scanline
        for (int j = 0; j < bi.biWidth; j++)
        {
            RGBTRIPLE triple;
 
            // read RGB triple from infile
            fread(&triple, sizeof(RGBTRIPLE), 1, inptr);
 
            // change any red pixels to white
            if (triple.rgbtRed == 255 && triple.rgbtGreen == 0 && triple.rgbtBlue == 0)
                triple.rgbtGreen = 255, triple.rgbtBlue = 255;
             
            // write RGB triple to outfile
            fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
        }
 
        // skip over padding, if any
        fseek(inptr, padding, SEEK_CUR);
        for (int k = 0; k < padding; k++)
        {
            fputc(0x00, outptr);
        }
    }
 
    // close files
    fclose(inptr);
 
    fclose(outptr);
 
    return 0;
}