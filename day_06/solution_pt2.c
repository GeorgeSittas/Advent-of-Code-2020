#include <stdio.h>

int questions[26];
int eof_found = 0;

int count_yes(FILE *fp) {
	int group_count = 1, count = 0, found_nl = 0;

	for (int token; 1; ) {
		token = fgetc(fp);

		if (token == '\n') {
			if (found_nl) break;
			found_nl = 1;
		}
		else if (token == EOF) {
			eof_found = 1;
			break;
		}
		else {
			if (found_nl == 1) group_count++;
			found_nl = 0;
			questions[token - 'a']++;
		}
	}

	for (int i = 0; i < 26; i++)
		if (questions[i] == group_count)
			count++;

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
