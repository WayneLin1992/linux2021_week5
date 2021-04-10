#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define FACTOR 1.5
#define CHUNK_SIZE 4
static inline float ilog_factor_1(float n) /* log1.5(n) = log2(n)/log2(1.5)*/
{
    return ceilf(log2f(n)/log2f(FACTOR));
}

static int ilog_factor_2(size_t n){
    if (n <= 1) return 1;
    if (n <= 2) return 2;
    if (n <= 3) return 3;
    if (n <= 5) return 4;
	if (n <= 7) return 5;
	if (n <= 11) return 6;
	if (n <= 17) return 7;
	if (n <= 25) return 8;
	if (n <= 38) return 9;
	if (n <= 57) return 10;
	if (n <= 86) return 11;
	if (n <= 129) return 12;
	if (n <= 194) return 13;
	if (n <= 291) return 14;
	if (n <= 438) return 15;
	if (n <= 656) return 16;
	if (n <= 985) return 17;
	if (n <= 1167) return 18;
}

int main()
{
    time(NULL);
    for(int i=0; i<10; i++){
        printf("%f \n",ilog_factor_1(rand()%1024));
        //printf("%d \n", ilog_factor_2((rand()%1024));
    }
    //printf("%d \n", ilog_factor_2(1024));
}
