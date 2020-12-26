#include <stdio.h>

int main(void) {
	FILE *fp = fopen("input.txt", "r");

	char map[323][31];

	for (int i = 0; i < 323; fgetc(fp), i++)
		for (int j = 0; j < 31; j++)
			map[i][j] = fgetc(fp);

	int trees = 0;

	for (int row = 1, col = 3; row < 323; row++, col = (col + 3) % 31)
		if (map[row][col] == '#')
			trees++;

	printf("Number of trees to be encountered: %d\n", trees);

	fclose(fp);
	return 0;
}
