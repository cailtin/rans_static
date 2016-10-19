#ifdef MAIN
#include <stdio.h>

/*
 * Shuffle based on input bits.
 * So bit N true  => keep Nth byte.
 *    bit N false => skip Nth byte.
 */

int main(void) {
    int i, j;

    FILE *fp = fopen(__FILE__, "r");
    char line[8192];
    while(fgets(line, 8192, fp)) {
	printf("%s", line);
    }
    close(fp);
    printf("\n");

    // Decode table; distributes N adjacent values across lanes
    printf("#define _ 9\n");
    printf("static uint32_t permute[256][8] = { // reverse binary bit order\n");
    for (i = 0; i < 256; i++) {
	int b = 0;
	int v[8] = {0};
	for (j = 0; j < 8; j++) {
	    if (i & (1<<j)) {
		v[j] = ++b;
	    }
	}
	printf("  { ");
	for (j = 0; j < 8; j++) {
	    if (v[j])
		printf("%d,", v[j]-1);
	    else
		printf("_,");
	}
	printf("},\n");
    }
    printf("};\n\n");

    // Encode table; collapses N values spread across lanes
    printf("static uint32_t permutec[256][8] = { // reverse binary bit order\n"); 
    for (i = 0; i < 256; i++) {
	int b = 0;
	int v[9] = {0};
	for (j = 0; j < 8; j++) {
	    if (i & (1<<j)) {
		v[b++] = j+1;
	    }
	}
	printf("  { ");
	for (j = b-8; j < b; j++) {
	    if (j >= 0 && v[j])
		printf("%d,", v[j]-1);
	    else
		printf("_,");
	}
	printf("},\n");
    }
    printf("};\n");

   return 0;
}
#endif

#define _ 9
static uint32_t permute[256][8] = { // reverse binary bit order
  { _,_,_,_,_,_,_,_,},
  { 0,_,_,_,_,_,_,_,},
  { _,0,_,_,_,_,_,_,},
  { 0,1,_,_,_,_,_,_,},
  { _,_,0,_,_,_,_,_,},
  { 0,_,1,_,_,_,_,_,},
  { _,0,1,_,_,_,_,_,},
  { 0,1,2,_,_,_,_,_,},
  { _,_,_,0,_,_,_,_,},
  { 0,_,_,1,_,_,_,_,},
  { _,0,_,1,_,_,_,_,},
  { 0,1,_,2,_,_,_,_,},
  { _,_,0,1,_,_,_,_,},
  { 0,_,1,2,_,_,_,_,},
  { _,0,1,2,_,_,_,_,},
  { 0,1,2,3,_,_,_,_,},
  { _,_,_,_,0,_,_,_,},
  { 0,_,_,_,1,_,_,_,},
  { _,0,_,_,1,_,_,_,},
  { 0,1,_,_,2,_,_,_,},
  { _,_,0,_,1,_,_,_,},
  { 0,_,1,_,2,_,_,_,},
  { _,0,1,_,2,_,_,_,},
  { 0,1,2,_,3,_,_,_,},
  { _,_,_,0,1,_,_,_,},
  { 0,_,_,1,2,_,_,_,},
  { _,0,_,1,2,_,_,_,},
  { 0,1,_,2,3,_,_,_,},
  { _,_,0,1,2,_,_,_,},
  { 0,_,1,2,3,_,_,_,},
  { _,0,1,2,3,_,_,_,},
  { 0,1,2,3,4,_,_,_,},
  { _,_,_,_,_,0,_,_,},
  { 0,_,_,_,_,1,_,_,},
  { _,0,_,_,_,1,_,_,},
  { 0,1,_,_,_,2,_,_,},
  { _,_,0,_,_,1,_,_,},
  { 0,_,1,_,_,2,_,_,},
  { _,0,1,_,_,2,_,_,},
  { 0,1,2,_,_,3,_,_,},
  { _,_,_,0,_,1,_,_,},
  { 0,_,_,1,_,2,_,_,},
  { _,0,_,1,_,2,_,_,},
  { 0,1,_,2,_,3,_,_,},
  { _,_,0,1,_,2,_,_,},
  { 0,_,1,2,_,3,_,_,},
  { _,0,1,2,_,3,_,_,},
  { 0,1,2,3,_,4,_,_,},
  { _,_,_,_,0,1,_,_,},
  { 0,_,_,_,1,2,_,_,},
  { _,0,_,_,1,2,_,_,},
  { 0,1,_,_,2,3,_,_,},
  { _,_,0,_,1,2,_,_,},
  { 0,_,1,_,2,3,_,_,},
  { _,0,1,_,2,3,_,_,},
  { 0,1,2,_,3,4,_,_,},
  { _,_,_,0,1,2,_,_,},
  { 0,_,_,1,2,3,_,_,},
  { _,0,_,1,2,3,_,_,},
  { 0,1,_,2,3,4,_,_,},
  { _,_,0,1,2,3,_,_,},
  { 0,_,1,2,3,4,_,_,},
  { _,0,1,2,3,4,_,_,},
  { 0,1,2,3,4,5,_,_,},
  { _,_,_,_,_,_,0,_,},
  { 0,_,_,_,_,_,1,_,},
  { _,0,_,_,_,_,1,_,},
  { 0,1,_,_,_,_,2,_,},
  { _,_,0,_,_,_,1,_,},
  { 0,_,1,_,_,_,2,_,},
  { _,0,1,_,_,_,2,_,},
  { 0,1,2,_,_,_,3,_,},
  { _,_,_,0,_,_,1,_,},
  { 0,_,_,1,_,_,2,_,},
  { _,0,_,1,_,_,2,_,},
  { 0,1,_,2,_,_,3,_,},
  { _,_,0,1,_,_,2,_,},
  { 0,_,1,2,_,_,3,_,},
  { _,0,1,2,_,_,3,_,},
  { 0,1,2,3,_,_,4,_,},
  { _,_,_,_,0,_,1,_,},
  { 0,_,_,_,1,_,2,_,},
  { _,0,_,_,1,_,2,_,},
  { 0,1,_,_,2,_,3,_,},
  { _,_,0,_,1,_,2,_,},
  { 0,_,1,_,2,_,3,_,},
  { _,0,1,_,2,_,3,_,},
  { 0,1,2,_,3,_,4,_,},
  { _,_,_,0,1,_,2,_,},
  { 0,_,_,1,2,_,3,_,},
  { _,0,_,1,2,_,3,_,},
  { 0,1,_,2,3,_,4,_,},
  { _,_,0,1,2,_,3,_,},
  { 0,_,1,2,3,_,4,_,},
  { _,0,1,2,3,_,4,_,},
  { 0,1,2,3,4,_,5,_,},
  { _,_,_,_,_,0,1,_,},
  { 0,_,_,_,_,1,2,_,},
  { _,0,_,_,_,1,2,_,},
  { 0,1,_,_,_,2,3,_,},
  { _,_,0,_,_,1,2,_,},
  { 0,_,1,_,_,2,3,_,},
  { _,0,1,_,_,2,3,_,},
  { 0,1,2,_,_,3,4,_,},
  { _,_,_,0,_,1,2,_,},
  { 0,_,_,1,_,2,3,_,},
  { _,0,_,1,_,2,3,_,},
  { 0,1,_,2,_,3,4,_,},
  { _,_,0,1,_,2,3,_,},
  { 0,_,1,2,_,3,4,_,},
  { _,0,1,2,_,3,4,_,},
  { 0,1,2,3,_,4,5,_,},
  { _,_,_,_,0,1,2,_,},
  { 0,_,_,_,1,2,3,_,},
  { _,0,_,_,1,2,3,_,},
  { 0,1,_,_,2,3,4,_,},
  { _,_,0,_,1,2,3,_,},
  { 0,_,1,_,2,3,4,_,},
  { _,0,1,_,2,3,4,_,},
  { 0,1,2,_,3,4,5,_,},
  { _,_,_,0,1,2,3,_,},
  { 0,_,_,1,2,3,4,_,},
  { _,0,_,1,2,3,4,_,},
  { 0,1,_,2,3,4,5,_,},
  { _,_,0,1,2,3,4,_,},
  { 0,_,1,2,3,4,5,_,},
  { _,0,1,2,3,4,5,_,},
  { 0,1,2,3,4,5,6,_,},
  { _,_,_,_,_,_,_,0,},
  { 0,_,_,_,_,_,_,1,},
  { _,0,_,_,_,_,_,1,},
  { 0,1,_,_,_,_,_,2,},
  { _,_,0,_,_,_,_,1,},
  { 0,_,1,_,_,_,_,2,},
  { _,0,1,_,_,_,_,2,},
  { 0,1,2,_,_,_,_,3,},
  { _,_,_,0,_,_,_,1,},
  { 0,_,_,1,_,_,_,2,},
  { _,0,_,1,_,_,_,2,},
  { 0,1,_,2,_,_,_,3,},
  { _,_,0,1,_,_,_,2,},
  { 0,_,1,2,_,_,_,3,},
  { _,0,1,2,_,_,_,3,},
  { 0,1,2,3,_,_,_,4,},
  { _,_,_,_,0,_,_,1,},
  { 0,_,_,_,1,_,_,2,},
  { _,0,_,_,1,_,_,2,},
  { 0,1,_,_,2,_,_,3,},
  { _,_,0,_,1,_,_,2,},
  { 0,_,1,_,2,_,_,3,},
  { _,0,1,_,2,_,_,3,},
  { 0,1,2,_,3,_,_,4,},
  { _,_,_,0,1,_,_,2,},
  { 0,_,_,1,2,_,_,3,},
  { _,0,_,1,2,_,_,3,},
  { 0,1,_,2,3,_,_,4,},
  { _,_,0,1,2,_,_,3,},
  { 0,_,1,2,3,_,_,4,},
  { _,0,1,2,3,_,_,4,},
  { 0,1,2,3,4,_,_,5,},
  { _,_,_,_,_,0,_,1,},
  { 0,_,_,_,_,1,_,2,},
  { _,0,_,_,_,1,_,2,},
  { 0,1,_,_,_,2,_,3,},
  { _,_,0,_,_,1,_,2,},
  { 0,_,1,_,_,2,_,3,},
  { _,0,1,_,_,2,_,3,},
  { 0,1,2,_,_,3,_,4,},
  { _,_,_,0,_,1,_,2,},
  { 0,_,_,1,_,2,_,3,},
  { _,0,_,1,_,2,_,3,},
  { 0,1,_,2,_,3,_,4,},
  { _,_,0,1,_,2,_,3,},
  { 0,_,1,2,_,3,_,4,},
  { _,0,1,2,_,3,_,4,},
  { 0,1,2,3,_,4,_,5,},
  { _,_,_,_,0,1,_,2,},
  { 0,_,_,_,1,2,_,3,},
  { _,0,_,_,1,2,_,3,},
  { 0,1,_,_,2,3,_,4,},
  { _,_,0,_,1,2,_,3,},
  { 0,_,1,_,2,3,_,4,},
  { _,0,1,_,2,3,_,4,},
  { 0,1,2,_,3,4,_,5,},
  { _,_,_,0,1,2,_,3,},
  { 0,_,_,1,2,3,_,4,},
  { _,0,_,1,2,3,_,4,},
  { 0,1,_,2,3,4,_,5,},
  { _,_,0,1,2,3,_,4,},
  { 0,_,1,2,3,4,_,5,},
  { _,0,1,2,3,4,_,5,},
  { 0,1,2,3,4,5,_,6,},
  { _,_,_,_,_,_,0,1,},
  { 0,_,_,_,_,_,1,2,},
  { _,0,_,_,_,_,1,2,},
  { 0,1,_,_,_,_,2,3,},
  { _,_,0,_,_,_,1,2,},
  { 0,_,1,_,_,_,2,3,},
  { _,0,1,_,_,_,2,3,},
  { 0,1,2,_,_,_,3,4,},
  { _,_,_,0,_,_,1,2,},
  { 0,_,_,1,_,_,2,3,},
  { _,0,_,1,_,_,2,3,},
  { 0,1,_,2,_,_,3,4,},
  { _,_,0,1,_,_,2,3,},
  { 0,_,1,2,_,_,3,4,},
  { _,0,1,2,_,_,3,4,},
  { 0,1,2,3,_,_,4,5,},
  { _,_,_,_,0,_,1,2,},
  { 0,_,_,_,1,_,2,3,},
  { _,0,_,_,1,_,2,3,},
  { 0,1,_,_,2,_,3,4,},
  { _,_,0,_,1,_,2,3,},
  { 0,_,1,_,2,_,3,4,},
  { _,0,1,_,2,_,3,4,},
  { 0,1,2,_,3,_,4,5,},
  { _,_,_,0,1,_,2,3,},
  { 0,_,_,1,2,_,3,4,},
  { _,0,_,1,2,_,3,4,},
  { 0,1,_,2,3,_,4,5,},
  { _,_,0,1,2,_,3,4,},
  { 0,_,1,2,3,_,4,5,},
  { _,0,1,2,3,_,4,5,},
  { 0,1,2,3,4,_,5,6,},
  { _,_,_,_,_,0,1,2,},
  { 0,_,_,_,_,1,2,3,},
  { _,0,_,_,_,1,2,3,},
  { 0,1,_,_,_,2,3,4,},
  { _,_,0,_,_,1,2,3,},
  { 0,_,1,_,_,2,3,4,},
  { _,0,1,_,_,2,3,4,},
  { 0,1,2,_,_,3,4,5,},
  { _,_,_,0,_,1,2,3,},
  { 0,_,_,1,_,2,3,4,},
  { _,0,_,1,_,2,3,4,},
  { 0,1,_,2,_,3,4,5,},
  { _,_,0,1,_,2,3,4,},
  { 0,_,1,2,_,3,4,5,},
  { _,0,1,2,_,3,4,5,},
  { 0,1,2,3,_,4,5,6,},
  { _,_,_,_,0,1,2,3,},
  { 0,_,_,_,1,2,3,4,},
  { _,0,_,_,1,2,3,4,},
  { 0,1,_,_,2,3,4,5,},
  { _,_,0,_,1,2,3,4,},
  { 0,_,1,_,2,3,4,5,},
  { _,0,1,_,2,3,4,5,},
  { 0,1,2,_,3,4,5,6,},
  { _,_,_,0,1,2,3,4,},
  { 0,_,_,1,2,3,4,5,},
  { _,0,_,1,2,3,4,5,},
  { 0,1,_,2,3,4,5,6,},
  { _,_,0,1,2,3,4,5,},
  { 0,_,1,2,3,4,5,6,},
  { _,0,1,2,3,4,5,6,},
  { 0,1,2,3,4,5,6,7,},
};

static uint32_t permutec[256][8] = { // reverse binary bit order
  { _,_,_,_,_,_,_,_,},
  { _,_,_,_,_,_,_,0,},
  { _,_,_,_,_,_,_,1,},
  { _,_,_,_,_,_,0,1,},
  { _,_,_,_,_,_,_,2,},
  { _,_,_,_,_,_,0,2,},
  { _,_,_,_,_,_,1,2,},
  { _,_,_,_,_,0,1,2,},
  { _,_,_,_,_,_,_,3,},
  { _,_,_,_,_,_,0,3,},
  { _,_,_,_,_,_,1,3,},
  { _,_,_,_,_,0,1,3,},
  { _,_,_,_,_,_,2,3,},
  { _,_,_,_,_,0,2,3,},
  { _,_,_,_,_,1,2,3,},
  { _,_,_,_,0,1,2,3,},
  { _,_,_,_,_,_,_,4,},
  { _,_,_,_,_,_,0,4,},
  { _,_,_,_,_,_,1,4,},
  { _,_,_,_,_,0,1,4,},
  { _,_,_,_,_,_,2,4,},
  { _,_,_,_,_,0,2,4,},
  { _,_,_,_,_,1,2,4,},
  { _,_,_,_,0,1,2,4,},
  { _,_,_,_,_,_,3,4,},
  { _,_,_,_,_,0,3,4,},
  { _,_,_,_,_,1,3,4,},
  { _,_,_,_,0,1,3,4,},
  { _,_,_,_,_,2,3,4,},
  { _,_,_,_,0,2,3,4,},
  { _,_,_,_,1,2,3,4,},
  { _,_,_,0,1,2,3,4,},
  { _,_,_,_,_,_,_,5,},
  { _,_,_,_,_,_,0,5,},
  { _,_,_,_,_,_,1,5,},
  { _,_,_,_,_,0,1,5,},
  { _,_,_,_,_,_,2,5,},
  { _,_,_,_,_,0,2,5,},
  { _,_,_,_,_,1,2,5,},
  { _,_,_,_,0,1,2,5,},
  { _,_,_,_,_,_,3,5,},
  { _,_,_,_,_,0,3,5,},
  { _,_,_,_,_,1,3,5,},
  { _,_,_,_,0,1,3,5,},
  { _,_,_,_,_,2,3,5,},
  { _,_,_,_,0,2,3,5,},
  { _,_,_,_,1,2,3,5,},
  { _,_,_,0,1,2,3,5,},
  { _,_,_,_,_,_,4,5,},
  { _,_,_,_,_,0,4,5,},
  { _,_,_,_,_,1,4,5,},
  { _,_,_,_,0,1,4,5,},
  { _,_,_,_,_,2,4,5,},
  { _,_,_,_,0,2,4,5,},
  { _,_,_,_,1,2,4,5,},
  { _,_,_,0,1,2,4,5,},
  { _,_,_,_,_,3,4,5,},
  { _,_,_,_,0,3,4,5,},
  { _,_,_,_,1,3,4,5,},
  { _,_,_,0,1,3,4,5,},
  { _,_,_,_,2,3,4,5,},
  { _,_,_,0,2,3,4,5,},
  { _,_,_,1,2,3,4,5,},
  { _,_,0,1,2,3,4,5,},
  { _,_,_,_,_,_,_,6,},
  { _,_,_,_,_,_,0,6,},
  { _,_,_,_,_,_,1,6,},
  { _,_,_,_,_,0,1,6,},
  { _,_,_,_,_,_,2,6,},
  { _,_,_,_,_,0,2,6,},
  { _,_,_,_,_,1,2,6,},
  { _,_,_,_,0,1,2,6,},
  { _,_,_,_,_,_,3,6,},
  { _,_,_,_,_,0,3,6,},
  { _,_,_,_,_,1,3,6,},
  { _,_,_,_,0,1,3,6,},
  { _,_,_,_,_,2,3,6,},
  { _,_,_,_,0,2,3,6,},
  { _,_,_,_,1,2,3,6,},
  { _,_,_,0,1,2,3,6,},
  { _,_,_,_,_,_,4,6,},
  { _,_,_,_,_,0,4,6,},
  { _,_,_,_,_,1,4,6,},
  { _,_,_,_,0,1,4,6,},
  { _,_,_,_,_,2,4,6,},
  { _,_,_,_,0,2,4,6,},
  { _,_,_,_,1,2,4,6,},
  { _,_,_,0,1,2,4,6,},
  { _,_,_,_,_,3,4,6,},
  { _,_,_,_,0,3,4,6,},
  { _,_,_,_,1,3,4,6,},
  { _,_,_,0,1,3,4,6,},
  { _,_,_,_,2,3,4,6,},
  { _,_,_,0,2,3,4,6,},
  { _,_,_,1,2,3,4,6,},
  { _,_,0,1,2,3,4,6,},
  { _,_,_,_,_,_,5,6,},
  { _,_,_,_,_,0,5,6,},
  { _,_,_,_,_,1,5,6,},
  { _,_,_,_,0,1,5,6,},
  { _,_,_,_,_,2,5,6,},
  { _,_,_,_,0,2,5,6,},
  { _,_,_,_,1,2,5,6,},
  { _,_,_,0,1,2,5,6,},
  { _,_,_,_,_,3,5,6,},
  { _,_,_,_,0,3,5,6,},
  { _,_,_,_,1,3,5,6,},
  { _,_,_,0,1,3,5,6,},
  { _,_,_,_,2,3,5,6,},
  { _,_,_,0,2,3,5,6,},
  { _,_,_,1,2,3,5,6,},
  { _,_,0,1,2,3,5,6,},
  { _,_,_,_,_,4,5,6,},
  { _,_,_,_,0,4,5,6,},
  { _,_,_,_,1,4,5,6,},
  { _,_,_,0,1,4,5,6,},
  { _,_,_,_,2,4,5,6,},
  { _,_,_,0,2,4,5,6,},
  { _,_,_,1,2,4,5,6,},
  { _,_,0,1,2,4,5,6,},
  { _,_,_,_,3,4,5,6,},
  { _,_,_,0,3,4,5,6,},
  { _,_,_,1,3,4,5,6,},
  { _,_,0,1,3,4,5,6,},
  { _,_,_,2,3,4,5,6,},
  { _,_,0,2,3,4,5,6,},
  { _,_,1,2,3,4,5,6,},
  { _,0,1,2,3,4,5,6,},
  { _,_,_,_,_,_,_,7,},
  { _,_,_,_,_,_,0,7,},
  { _,_,_,_,_,_,1,7,},
  { _,_,_,_,_,0,1,7,},
  { _,_,_,_,_,_,2,7,},
  { _,_,_,_,_,0,2,7,},
  { _,_,_,_,_,1,2,7,},
  { _,_,_,_,0,1,2,7,},
  { _,_,_,_,_,_,3,7,},
  { _,_,_,_,_,0,3,7,},
  { _,_,_,_,_,1,3,7,},
  { _,_,_,_,0,1,3,7,},
  { _,_,_,_,_,2,3,7,},
  { _,_,_,_,0,2,3,7,},
  { _,_,_,_,1,2,3,7,},
  { _,_,_,0,1,2,3,7,},
  { _,_,_,_,_,_,4,7,},
  { _,_,_,_,_,0,4,7,},
  { _,_,_,_,_,1,4,7,},
  { _,_,_,_,0,1,4,7,},
  { _,_,_,_,_,2,4,7,},
  { _,_,_,_,0,2,4,7,},
  { _,_,_,_,1,2,4,7,},
  { _,_,_,0,1,2,4,7,},
  { _,_,_,_,_,3,4,7,},
  { _,_,_,_,0,3,4,7,},
  { _,_,_,_,1,3,4,7,},
  { _,_,_,0,1,3,4,7,},
  { _,_,_,_,2,3,4,7,},
  { _,_,_,0,2,3,4,7,},
  { _,_,_,1,2,3,4,7,},
  { _,_,0,1,2,3,4,7,},
  { _,_,_,_,_,_,5,7,},
  { _,_,_,_,_,0,5,7,},
  { _,_,_,_,_,1,5,7,},
  { _,_,_,_,0,1,5,7,},
  { _,_,_,_,_,2,5,7,},
  { _,_,_,_,0,2,5,7,},
  { _,_,_,_,1,2,5,7,},
  { _,_,_,0,1,2,5,7,},
  { _,_,_,_,_,3,5,7,},
  { _,_,_,_,0,3,5,7,},
  { _,_,_,_,1,3,5,7,},
  { _,_,_,0,1,3,5,7,},
  { _,_,_,_,2,3,5,7,},
  { _,_,_,0,2,3,5,7,},
  { _,_,_,1,2,3,5,7,},
  { _,_,0,1,2,3,5,7,},
  { _,_,_,_,_,4,5,7,},
  { _,_,_,_,0,4,5,7,},
  { _,_,_,_,1,4,5,7,},
  { _,_,_,0,1,4,5,7,},
  { _,_,_,_,2,4,5,7,},
  { _,_,_,0,2,4,5,7,},
  { _,_,_,1,2,4,5,7,},
  { _,_,0,1,2,4,5,7,},
  { _,_,_,_,3,4,5,7,},
  { _,_,_,0,3,4,5,7,},
  { _,_,_,1,3,4,5,7,},
  { _,_,0,1,3,4,5,7,},
  { _,_,_,2,3,4,5,7,},
  { _,_,0,2,3,4,5,7,},
  { _,_,1,2,3,4,5,7,},
  { _,0,1,2,3,4,5,7,},
  { _,_,_,_,_,_,6,7,},
  { _,_,_,_,_,0,6,7,},
  { _,_,_,_,_,1,6,7,},
  { _,_,_,_,0,1,6,7,},
  { _,_,_,_,_,2,6,7,},
  { _,_,_,_,0,2,6,7,},
  { _,_,_,_,1,2,6,7,},
  { _,_,_,0,1,2,6,7,},
  { _,_,_,_,_,3,6,7,},
  { _,_,_,_,0,3,6,7,},
  { _,_,_,_,1,3,6,7,},
  { _,_,_,0,1,3,6,7,},
  { _,_,_,_,2,3,6,7,},
  { _,_,_,0,2,3,6,7,},
  { _,_,_,1,2,3,6,7,},
  { _,_,0,1,2,3,6,7,},
  { _,_,_,_,_,4,6,7,},
  { _,_,_,_,0,4,6,7,},
  { _,_,_,_,1,4,6,7,},
  { _,_,_,0,1,4,6,7,},
  { _,_,_,_,2,4,6,7,},
  { _,_,_,0,2,4,6,7,},
  { _,_,_,1,2,4,6,7,},
  { _,_,0,1,2,4,6,7,},
  { _,_,_,_,3,4,6,7,},
  { _,_,_,0,3,4,6,7,},
  { _,_,_,1,3,4,6,7,},
  { _,_,0,1,3,4,6,7,},
  { _,_,_,2,3,4,6,7,},
  { _,_,0,2,3,4,6,7,},
  { _,_,1,2,3,4,6,7,},
  { _,0,1,2,3,4,6,7,},
  { _,_,_,_,_,5,6,7,},
  { _,_,_,_,0,5,6,7,},
  { _,_,_,_,1,5,6,7,},
  { _,_,_,0,1,5,6,7,},
  { _,_,_,_,2,5,6,7,},
  { _,_,_,0,2,5,6,7,},
  { _,_,_,1,2,5,6,7,},
  { _,_,0,1,2,5,6,7,},
  { _,_,_,_,3,5,6,7,},
  { _,_,_,0,3,5,6,7,},
  { _,_,_,1,3,5,6,7,},
  { _,_,0,1,3,5,6,7,},
  { _,_,_,2,3,5,6,7,},
  { _,_,0,2,3,5,6,7,},
  { _,_,1,2,3,5,6,7,},
  { _,0,1,2,3,5,6,7,},
  { _,_,_,_,4,5,6,7,},
  { _,_,_,0,4,5,6,7,},
  { _,_,_,1,4,5,6,7,},
  { _,_,0,1,4,5,6,7,},
  { _,_,_,2,4,5,6,7,},
  { _,_,0,2,4,5,6,7,},
  { _,_,1,2,4,5,6,7,},
  { _,0,1,2,4,5,6,7,},
  { _,_,_,3,4,5,6,7,},
  { _,_,0,3,4,5,6,7,},
  { _,_,1,3,4,5,6,7,},
  { _,0,1,3,4,5,6,7,},
  { _,_,2,3,4,5,6,7,},
  { _,0,2,3,4,5,6,7,},
  { _,1,2,3,4,5,6,7,},
  { 0,1,2,3,4,5,6,7,},
};
