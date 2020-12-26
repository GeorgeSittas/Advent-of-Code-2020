#include <stdio.h>

void search_seat(char *seat_code, int *row, int *col) {
	int low = 0, high = 127;

	for (int i = 0; i < 7; i++)
		if (seat_code[i] == 'F') high = (low + high) / 2;
		else                     low  = (low + high) / 2 + 1;

	*row = (seat_code[6] == 'F') ? low : high;

	low = 0, high = 7;
	for (int i = 0; i < 3; i++) {
		if (seat_code[i+7] == 'L') high = (low + high) / 2;
		else                       low  = (low + high) / 2 + 1;
	}

	*col = (seat_code[9] == 'L') ? low : high;
}

void read_seat_code(FILE *fp, char *seat_code) {
	for (int i = 0; i < 10; i++)
		seat_code[i] = fgetc(fp);

	fgetc(fp); // consume newline
}

int main(void) {
	FILE *fp = fopen("input.txt", "r");

	int row, col;
	char seat_code[11];

	int max_id = -1, seat_id;
	for (int token; 1; ) {
		read_seat_code(fp, seat_code);
		search_seat(seat_code, &row, &col);

		seat_id = row * 8 + col;
		if (seat_id > max_id)
			max_id = seat_id;

		if ((token = fgetc(fp)) == EOF) break;
		ungetc(token, fp);
	}

	printf("Max ID is %d\n", max_id);

	fclose(fp);
	return 0;
}
