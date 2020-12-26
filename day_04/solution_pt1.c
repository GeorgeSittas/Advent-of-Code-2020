#include <stdio.h>
#include <string.h>
#include <stdbool.h>


bool eof_found = false;

int field_idx(char *fields[], char *field) {
	for (int i = 0; i < 8; i++)
		if (strcmp(field, fields[i]) == 0)
			return i+1;

	return -1;
}

void read_field(FILE *fp, char *field) {
	for (int i = 0; i < 3; i++)
		field[i] = fgetc(fp);
}

bool next_passport(FILE *fp, char *fields[]) {
	char field[4];
	bool byr, iyr, eyr, hgt, hcl, ecl, pid, cid;

	field[3] = '\0';
	byr = iyr = eyr = hgt = hcl = ecl = pid = cid = false;
	for (bool stop = false; !stop; ) {
		read_field(fp, field);

		switch (field_idx(fields, field)) {
			case 1: byr = true; break; case 2: iyr = true; break;
			case 3: eyr = true; break; case 4: hgt = true; break;
			case 5: hcl = true; break; case 6: ecl = true; break;
			case 7: pid = true; break; case 8: cid = true; break;
			default: return false;
		}

		for (int tok = fgetc(fp); true; tok = fgetc(fp)) {
			if (tok == ' ') break;
			if (tok == '\n') {
				tok = fgetc(fp); // peak into next character in stream

				if (tok == '\n') { stop = true;                   break; }
				if (tok == EOF)  { stop = true; eof_found = true; break; }

				ungetc(tok, fp);
				break;
			}
		}
	}

	return byr && iyr && eyr && hgt && hcl && ecl && pid;
}

int main(void) {
	FILE *fp = fopen("input.txt", "r");
	char *fields[8] = { "byr", "iyr", "eyr", "hgt", "hcl", "ecl", "pid", "cid" };

	int n_valid = 0;
	while (true) {
		n_valid += next_passport(fp, fields);
		if (eof_found) break;
	}

	printf("Number of valid passports : %d\n", n_valid);

	fclose(fp);
	return 0;
}
