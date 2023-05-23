#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ROW 1000
#define COL 21

void radix_sort(char S[][COL], int ptr[], unsigned int rows) {
	printf("INSIDE RADIX SORT");
    int i, j, k = 0;
	int bucket[256] = {0};
    char S2[ROW][COL];
    for (k = COL - 1; k >= 0; k--) {
        for (j = 0; j < 256; j++)
            bucket[j] = 0;
        for (i = 0; i < rows; i++)
            bucket[S[ptr[i]][k]]++;
        for (j = 1; j < 256; j++)
            bucket[j] += bucket[j-1];
        for (i = rows-1; i >= 0; i--)
            strcpy(S2[--bucket[S[ptr[i]][k]]], S[ptr[i]]);
        for (i = 0; i < rows; i++)
            strcpy(S[i], S2[i]);
    }
}

int main(){
	//GET FILE NAME
    char infile[20];
    char outfile[20];
	printf("Input file (default = f.txt): ");
	//scanf("%s", infile);
	fgets(infile, sizeof(infile), stdin);
	if (infile[0] == '\n')
		strcpy(infile, "f.txt");
	infile[strcspn(infile, "\n")] = 0;
	
	printf("Output file (default = g.txt): ");
	//scanf("%s", outfile);
	fgets(outfile, sizeof(outfile), stdin);
	if (outfile[0] == '\n')
		strcpy(outfile, "g.txt");
	outfile[strcspn(outfile, "\n")] = 0;
	
	puts(infile);
	puts(outfile);	
	
	//READ FROM FILE INTO 2D ARRAY
    FILE *f, *g;
    f = fopen(infile, "r");
    g = fopen(outfile, "w");
    
    int i, j, n = 0;
    char S[ROW][COL];
    int ptr[ROW];
    while (fgets(S[n], COL, f) != NULL) {
        S[n][strlen(S[n])-1] = ' ';
        ptr[n] = n;
        n++;
    }

    //SORT STRINGS
    radix_sort(S, ptr, n);
    
    for (i = 0; i < n; i++) {
        fprintf(g, "%s\n", S[ptr[i]]);
    }
    fclose(f);
    fclose(g);
    return 0;
}