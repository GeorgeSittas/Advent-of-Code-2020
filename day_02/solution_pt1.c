#include <ctype.h>
#include <stdio.h>

int read_num(FILE *fp) {
	int num = 0;
	for (int token = fgetc(fp); isdigit(token); token = fgetc(fp))
		num = num * 10 + (token - '0');
	return num;
}


int main(void) {
	FILE *fp = fopen("input.txt", "r");

	int n_valid = 0;
	int min, max, target, count;

	while (1) {
		if ((min = fgetc(fp)) == EOF) break;
		ungetc(min, fp);

		min = read_num(fp);
		max = read_num(fp);
		target = fgetc(fp);
		count = 0;

		fgetc(fp); fgetc(fp);

		for (int token = 0; (token = fgetc(fp)) != '\n'; )
			if (token == target)
				count++;

		n_valid += (min <= count && count <= max);
	}

	printf("Found %d valid passwords\n", n_valid);

	fclose(fp);
	return 0;
}
