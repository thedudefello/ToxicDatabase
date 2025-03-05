/* Compressor for MEMZ and VineMEMZ
 * The code has been optimized for the larger files of VineMEMZ */ 

#include <stdio.h>

#define BUFFER_SIZE 65536

#define LMIN 4
#define LMAX 32767

int main(int argc, char **argv) {
	if (argc != 3) {
		fprintf(stderr, "Usage: compress [input file] [output file]\n");
		return 1;
	}
	
	FILE *infile = fopen(argv[1], "rb");
	if (!infile) {
		fprintf(stderr, "Could not open input file for reading.\n");
		return 2;
	}
	
	unsigned char buf[BUFFER_SIZE] = { 0 };
	int fsize = fread(buf, 1, BUFFER_SIZE, infile);
	
	if (fsize >= BUFFER_SIZE) {
		fprintf(stderr, "The input file is too large for compressing!\n");
		return 3;
	} else if (fsize <= 0) {
		fprintf(stderr, "The input file is empty.\n");
		return 3;
	}
	
	fclose(infile);
	
	FILE *outfile = fopen(argv[2], "wb");
	if (!outfile) {
		fprintf(stderr, "Could not open output file for writing.\n");
		return 2;
	}
	
	unsigned char bytes[BUFFER_SIZE] = { 0 };
	int bi = 0;
	
	int pos = 0;
	while (pos < fsize) {
		unsigned short l = 0, ml = 0;
		int p = 0, mp = 0;
		
		for (; p < pos; p++) {
			if (buf[p] == buf[pos+l] && l < LMAX) {
				l++;
			} else {
				if (l >= ml && (pos - p + l) < 32768) {
					ml = l;
					mp = p;
				}
				
				p -= l;
				l = 0;
			}
		}

		if (l >= ml && (pos - p + l) < 32768) {
			ml = l;
			mp = p;
		}

		if (ml >= LMIN) {
			int bs = 0;
			while (bi > 0) {
				int bx = bi;
				if (bx > 128) bx = 128;

				unsigned char b = (1 << 7) | (bx-1);

				fwrite(&b, 1, 1, outfile);
				fwrite(bytes + bs, 1, bx, outfile);

				bi -= bx;
				bs += bx;
			}
			
			unsigned short mp2 = (pos - mp + ml);
			
			if (ml < 64) {
				char ml2 = ml;
				fwrite(&ml2, 1, 1, outfile);
			} else {
				unsigned short ml2 = 0x4000 | ml;
				ml2 = (ml2 >> 8) | (ml2 << 8);
				fwrite(&ml2, 2, 1, outfile);
			}
			
			fwrite(&mp2, 2, 1, outfile);
			
			pos += ml;
		} else {
			bytes[bi++] = buf[pos++];
		}
		
		printf("Position: %d/%d\n", pos, fsize);
	}

	int bs = 0;
	while (bi > 0) {
		int bx = bi;
		if (bx > 128) bx = 128;

		unsigned char b = (1 << 7) | (bx - 1);

		fwrite(&b, 1, 1, outfile);
		fwrite(bytes + bs, 1, bx, outfile);

		bi -= bx;
		bs += bx;
	}
	
	fclose(outfile);
	
	return 0;
}
