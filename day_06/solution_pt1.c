#include <stdio.h>

int questions[26];
int eof_found = 0;

int count_yes(FILE *fp) {
	int count = 0, found_nl = 0;

	for (int token; 1; ) {
		token = fgetc(fp);

		if (token == '\n') {
			if (found_nl) break;
			found_nl = 1;
		}
		else if (token == EOF) {
			eof_found = 1;
			return count;
		}
		else {
			found_nl = 0;
			if (!questions[token - 'a']) count++;
			questions[token - 'a'] = 1;
		}
	}

	return count;
}

int main(void) {
	FILE *fp = fopen("input.txt", "r");

	int sum = 0;
	while (!eof_found) {
		for (int i = 0; i < 26; i++) questions[i] = 0;
		sum += count_yes(fp);
	}

	printf("%d\n", sum);

	fclose(fp);
	return 0;
}
