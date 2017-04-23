/**
 * resize.c
 **
 * CS50 Computer Science 50
 * Problem Set 4
 **
 * Resizes a BMP file by a n factor.
 **/

#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main(int argc, char* argv[])
{
		// ensure that commandf entry is valid
		if (argc != 4)
		{
				printf("Usage: ./resize n infile outfile\n");
				return 1;
		}

		// verify the resize factor is valid
		int fconvertion = atoi(argv[1]);
		if(fconvertion < 0 || fconvertion > 100)
		{
				printf("The resize factor should be a positive integer <= 100.\n");
				return 2;
		}

		// define filenames and fconvertion 
		char* infile = argv[2];
		char* outfile = argv[3];

		// open files (input and output) 
		FILE* inptr = fopen(infile, "r");
		if (inptr == NULL)
		{
				printf("Could not open %s.\n", infile);
				return 3;
		}
		FILE* outptr = fopen(outfile, "w");
		if (outptr == NULL)
		{
				fclose(inptr);
				fprintf(stderr, "Could not create %s.\n", outfile);
				return 4;
		}

		// read BITMAPFILEHEADER and BITMAPINFOHEADER in the infile
		BITMAPFILEHEADER bf;
		fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);

		BITMAPINFOHEADER bi;
		fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);

		// verify that infile is a 24-bit uncompressed BMP 4.0
		if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 || 
						bi.biBitCount != 24 || bi.biCompression != 0)
		{
				fclose(outptr);
				fclose(inptr);
				fprintf(stderr, "Unsupported file format.\n");
				return 4;
		}

		// build bitmap headers for the outfile
		BITMAPFILEHEADER final_bf;
		BITMAPINFOHEADER final_bi;	
		final_bf = bf;
		final_bi = bi;
		final_bi.biWidth = bi.biWidth * fconvertion;
		final_bi.biHeight = bi.biHeight * fconvertion;

		// define padding for scanlines
		int in_padding =  (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
		int out_padding =  (4 - (final_bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

		// Calculate file and image size
		// biSizeImage calculation.
		final_bf.bfSize = 54 + final_bi.biWidth * abs(final_bi.biHeight) * 3 + abs(final_bi.biHeight) *  out_padding;
		final_bi.biSizeImage = ((((final_bi.biWidth * final_bi.biBitCount) + 31) & ~31) / 8) * abs(final_bi.biHeight);

		// write BITMAPFILEHEADER of the outfile
		fwrite(&final_bf, sizeof(BITMAPFILEHEADER), 1, outptr);

		// write BITMAPINFOHEADER of the outfile
		fwrite(&final_bi, sizeof(BITMAPINFOHEADER), 1, outptr);

		for (int i = 0, biHeight = abs(bi.biHeight); i < biHeight; i++)
		{
				// Write each line n factor-times
				for(int n = 0; n < fconvertion; n++)
				{
						// iterate over pixels in scanline
						for (int j = 0; j < bi.biWidth; j++)
						{
								// temporary storage
								RGBTRIPLE triple;

								// read RGB triple from infile
								fread(&triple, sizeof(RGBTRIPLE), 1, inptr);

								// write RGB triple to outfile
								for(int m = 0; m < fconvertion; m++) 
								{
										fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
								}
						}

						// skip over padding in infile
						fseek(inptr, in_padding, SEEK_CUR);

						// then add it to outfile
						for (int k = 0; k <out_padding; k++)
								fputc(0x00, outptr);

						fseek(inptr, -(bi.biWidth * 3 + in_padding ), SEEK_CUR);

				}
				fseek(inptr, bi.biWidth*3+in_padding, SEEK_CUR);
		}

		// close infile and outfile
		fclose(inptr);
        fclose(outptr);

		return 0;
}