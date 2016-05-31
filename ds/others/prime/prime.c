#include <stdio.h>
#include <math.h>

void prime(int n) {
	int i, j;

	for (i = 2; i < n; i++) {
		for (j = 2; j < sqrt(i); j++) {
			if (i % j == 0)	
				break;
		}

		if (j > sqrt(i))
			printf("%d ", i);
	}	
	printf("\n");
}

int main() {
	prime(100);
	return 0;
}
