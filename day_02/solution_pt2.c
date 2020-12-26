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
	int pos1, pos2, target, found, valid;

	while (1) {
		if ((pos1 = fgetc(fp)) == EOF) break;
		ungetc(pos1, fp);

		pos1 = read_num(fp);
		pos2 = read_num(fp);
		target = fgetc(fp);
		found = 0;
		valid = 1;

		fgetc(fp); fgetc(fp);

		for (int token = 0, pos = 1; (token = fgetc(fp)) != '\n'; pos++) {
			if (token == target && (pos == pos1 || pos == pos2)) {
				if (found) {
					valid = 0;
					while (fgetc(fp) != '\n');
					break;
				}

				found = 1;
			}
		}

		n_valid += valid * found;
	}

	printf("Found %d valid passwords\n", n_valid);

	fclose(fp);
	return 0;
}
