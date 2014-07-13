#include <stdio.h>
#include "system.h"

int main(void){
	printf("%f\n", toDegree(theta(1, 1, -1, 3)));
	printf("%f\n", toDegree(theta(-1, 1, 1, 3)));
	return 0;
}
