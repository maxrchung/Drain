#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define ROWS	748 // height
#define COLS	1328 // width
#define PI		3.14159265
#define sqr(x)	((x)*(x))
#define bucket_size 100

void clear(unsigned char image[][COLS]);
void header(int row, int col, unsigned char head[32]);

int main(int argc, char** argv)
{
	int				i, j, k;
	int				dedx, dedy, sgm;
	int             max, index_offset;
	int				sgm_threshold, hough_threshold;
	// const int		num_buckets = 129360 / bucket_size;
	FILE*			fp;
	unsigned char	image[ROWS][COLS], simage[ROWS][COLS], bimage[ROWS][COLS], himage[ROWS][COLS], head[32];
	// A is voting array, size determined by finding maximum rho
	// no need for combining buckets for the given image
	unsigned int    s[ROWS][COLS], A[180][10000] = { 0 };
	char			filename[50], ch;

	strcpy(filename, "test2.raw");
	header(ROWS, COLS, head);
	max = 0;
	memset(himage, 0, sizeof(char) * ROWS * COLS);	// init himage bg to 0
	index_offset = 598;		// determined by finding minimum rho
	sgm_threshold = 2; // 200
	hough_threshold = 180;	// will result in the 3 lines of the given triangle

	if (!(fp = fopen(filename, "rb")))
	{
		fprintf(stderr, "error: couldn't open %s\n", argv[1]);
		exit(1);
	}

	for (i = 0; i < ROWS; i++)
		if (!(COLS == fread(image[i], sizeof(char), COLS, fp)))
		{
			fprintf(stderr, "error: couldn't read %s\n", argv[1]);
			exit(1);
		}
	fclose(fp);

	for (i = ROWS - 2; i > 0; i--)
		for (j = COLS - 2; j > 0; j--)
		{
			dedx =
				-image[i - 1][j - 1] + image[i - 1][j + 1] +
				-2 * image[i][j - 1] + 2 * image[i][j + 1] +
				-image[i + 1][j - 1] + image[i + 1][j + 1];

			dedy =
				-image[i - 1][j - 1] - 2 * image[i - 1][j] - image[i - 1][j + 1] +
				image[i + 1][j - 1] + 2 * image[i + 1][j] + image[i + 1][j + 1];

			sgm = sqr(dedx) + sqr(dedy);
			s[i][j] = sgm;
			max = (sgm > max) ? sgm : max;
		}
	int min = 0;
	int rho;
	int topVotes[180] = { 0 };
	for (i = 0; i < ROWS; i++) {
		for (j = 0; j < COLS; j++) {
			if (i == 0 || j == 0 || i == ROWS - 1 || j == COLS - 1) {
				s[i][j] = 0;	// SGM has no outer edge
				continue;
			}
			simage[i][j] = s[i][j] *= 255.0 / max;
			if (simage[i][j] > sgm_threshold) {
				bimage[i][j] = 255;		// binary image
				for (k = 0; k < 180; k++) {
					rho = -1 * (j * sin(k*PI / 180) - (ROWS - i - 1) * cos(k*PI / 180));	// Hough Transform equation
					max = (rho > max) ? rho : max;	// was used for finding max rho for voting array size
					min = (rho < min) ? rho : min;	// was used for index offset for negative rho
					//A[k][(rho + -min)/bucket_size]++;		// increase vote count in this accumulator bucket
					// printf("min %d\n", min);
					if (A[k][(rho + -min) / bucket_size] > topVotes[k]) {
						topVotes[k] = A[k][(rho + -min) / bucket_size];
						printf("%d votes at theta %d rho %d\n", topVotes[k], k, (rho + -min) / bucket_size);
					}
				}
			}
			else {
				bimage[i][j] = 0;
			}
		}
	}
	/*
	int m;
	for (k = 1; k < 180 - 1; k++) {		// theta
		for (m = 1; m < 129360 - 1; m++) {	// rho, no need for merging
			int cur = A[k][m];	// current vote count
			if (A[k - 1][m - 1] < cur && A[k][m - 1] < cur && A[k + 1][m - 1] < cur && A[k - 1][m] < cur && A[k + 1][m] < cur && A[k - 1][m + 1] < cur && A[k][m + 1] < cur && A[k + 1][m + 1] < cur) {
				// cur is a local maximum (all surrounding vote counts are less than current)
				if (cur > hough_threshold) {
					printf("%d votes at theta = %d rho = %d\n", cur, k, m - index_offset);
					for (i = 0; i < ROWS; i++) {
						for (j = 0; j < COLS; j++) {
							// reconstruct the line at this rho and theta by iterating through all x and y that satisfy Hough transform equation
							if (m - index_offset == (int)(-1 * (j * sin(k*PI / 180) - (ROWS - i - 1) * cos(k*PI / 180)))) {
								himage[i][j] = 255;
							}
						}
					}
				}
			}
		}
	}
	*/
	if (!(fp = fopen("test2.ras", "wb")))
	{
		fprintf(stderr, "error: could not open %s\n", filename);
		exit(1);
	}
	fwrite(head, 4, 8, fp);
	for (i = 0; i < ROWS; i++) fwrite(bimage[i], 1, COLS, fp);
	fclose(fp);
	/*
	if (!(fp = fopen("image-h.ras", "wb")))
	{
		fprintf(stderr, "error: could not open %s\n", filename);
		exit(1);
	}
	fwrite(head, 4, 8, fp);
	for (i = 0; i < ROWS; i++) fwrite(himage[i], 1, COLS, fp);
	fclose(fp);

	printf("Press any key to exit: ");
	gets(&ch);
	return 0;
	*/
}

void clear(unsigned char image[][COLS])
{
	int	i, j;
	for (i = 0; i < ROWS; i++)
		for (j = 0; j < COLS; j++) image[i][j] = 0;
}

void header(int row, int col, unsigned char head[32])
{
	int *p = (int *)head;
	char *ch;
	int num = row * col;

	/* Choose little-endian or big-endian header depending on the machine. Don't modify this */
	/* Little-endian for PC */

	*p = 0x956aa659;
	*(p + 3) = 0x08000000;
	*(p + 5) = 0x01000000;
	*(p + 6) = 0x0;
	*(p + 7) = 0xf8000000;

	ch = (char*)&col;
	head[7] = *ch;
	ch++;
	head[6] = *ch;
	ch++;
	head[5] = *ch;
	ch++;
	head[4] = *ch;

	ch = (char*)&row;
	head[11] = *ch;
	ch++;
	head[10] = *ch;
	ch++;
	head[9] = *ch;
	ch++;
	head[8] = *ch;

	ch = (char*)&num;
	head[19] = *ch;
	ch++;
	head[18] = *ch;
	ch++;
	head[17] = *ch;
	ch++;
	head[16] = *ch;


	/* Big-endian for unix */
	/*
	*p = 0x59a66a95;
	*(p + 1) = col;
	*(p + 2) = row;
	*(p + 3) = 0x8;
	*(p + 4) = num;
	*(p + 5) = 0x1;
	*(p + 6) = 0x0;
	*(p + 7) = 0xf8;
	*/
}

