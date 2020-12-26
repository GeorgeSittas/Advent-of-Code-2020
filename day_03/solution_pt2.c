#include <stdio.h>

int main(void) {
	FILE *fp = fopen("input.txt", "r");

	char map[323][31];

	for (int i = 0; i < 323; fgetc(fp), i++)
		for (int j = 0; j < 31; j++)
			map[i][j] = fgetc(fp);

	long trees1 = 0, trees2 = 0, trees3 = 0, trees4 = 0, trees5 = 0;
	int row = 1, fastrow = 2;
	int col1 = 1, col2 = 3, col3 = 5, col4 = 7, col5 = 1;

	while (row < 323) {
		if (map[row][col1] == '#') trees1++;
		if (map[row][col2] == '#') trees2++;
		if (map[row][col3] == '#') trees3++;
		if (map[row][col4] == '#') trees4++;
		if (fastrow < 323 && map[fastrow][col1] == '#') trees5++;

		col1 = (col1 + 1) % 31;
		col2 = (col2 + 3) % 31;
		col3 = (col3 + 5) % 31;
		col4 = (col4 + 7) % 31;
		col5 = col1;
		fastrow += 2;
		row++;
	}

	printf("All trees multiplied: %ld\n",
		trees1 * trees2 * trees3 * trees4 * trees5);

	fclose(fp);
	return 0;
}
