#include <stdio.h>
#include <stdlib.h>

int main(void) {
	FILE *fp = fopen("input.txt", "r");

	int nums[200];
	for (int i = 0; i < 200; i++)
		fscanf(fp, "%d", &nums[i]);

	// part 1
	for (int i = 0; i < 200; i++)
		for (int j = i+1; j < 200; j++)
			if (nums[i] + nums[j] == 2020)
				printf("%d + %d = 2020, %d * %d = %d\n",
					nums[i], nums[j], nums[i], nums[j], nums[i]*nums[j]);

	// part 2
	for (int i = 0; i < 200; i++)
		for (int j = i+1; j < 200; j++)
			for (int k = j+1; k < 200; k++)
				if (nums[i] + nums[j] + nums[k] == 2020)
					printf("%d + %d + %d = 2020, %d * %d * %d = %d\n",
						nums[i], nums[j], nums[k],
						nums[i], nums[j], nums[k], nums[i]*nums[j]*nums[k]);

	fclose(fp);
	return 0;
}
