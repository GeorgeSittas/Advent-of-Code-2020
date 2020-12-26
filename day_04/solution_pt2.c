#include <ctype.h>
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

	fgetc(fp); // Consume ':'
}

void skip_passport(FILE *fp) {
	bool found_nl = false;
	for (int token = fgetc(fp); true; token = fgetc(fp)) {
		if (token == '\n') {
			if (found_nl) return;
			found_nl = true;
		}
		else found_nl = false;
	}
}

bool read_byr(FILE *fp) {
	int token, byr = 0;

	for (int i = 0; i < 4; i++) {
		if (!isdigit(token = fgetc(fp))) return false;
		byr = byr * 10 + (token - '0');
	}

	return 1920 <= byr && byr <= 2002;
}

bool read_iyr(FILE *fp) {
	int token, iyr = 0;

	for (int i = 0; i < 4; i++) {
		if (!isdigit(token = fgetc(fp))) return false;
		iyr = iyr * 10 + (token - '0');
	}

	return 2010 <= iyr && iyr <= 2020;
}

bool read_eyr(FILE *fp) {
	int token, eyr = 0;

	for (int i = 0; i < 4; i++) {
		if (!isdigit(token = fgetc(fp))) return false;
		eyr = eyr * 10 + (token - '0');
	}

	return 2020 <= eyr && eyr <= 2030;
}

bool read_hgt(FILE *fp) {
	int token, hgt = 0;

	while (isdigit(token = fgetc(fp)))
		hgt = hgt * 10 + (token - '0');

	int let1 = token, let2 = fgetc(fp);

	if (let1 == 'c' && let2 == 'm')
		return 150 <= hgt && hgt <= 193;
	if (let1 == 'i' && let2 == 'n')
		return 59 <= hgt && hgt <= 76;

	return false;
}

bool read_hcl(FILE *fp) {
	if (fgetc(fp) != '#') return false;
	for (int i = 0; i < 6; i++)
		if (!isxdigit(fgetc(fp)))
			return false;

	return true;
}

bool read_ecl(FILE *fp) {
	int let1 = fgetc(fp), let2 = fgetc(fp), let3 = fgetc(fp);

	return (let1 == 'a' && let2 == 'm' && let3 == 'b')
      || (let1 == 'b' && let2 == 'l' && let3 == 'u')
      || (let1 == 'b' && let2 == 'r' && let3 == 'n')
      || (let1 == 'g' && let2 == 'r' && let3 == 'y')
      || (let1 == 'g' && let2 == 'r' && let3 == 'n')
      || (let1 == 'h' && let2 == 'z' && let3 == 'l')
      || (let1 == 'o' && let2 == 't' && let3 == 'h');
}

bool read_pid(FILE *fp) {
	for (int i = 0; i < 9; i++)
		if (!isdigit(fgetc(fp)))
			return false;

	return true;
}

bool is_whitespace(int token) {
	return token == ' ' || token == '\n';
}


bool next_passport(FILE *fp, char *fields[]) {
	int token;
	char field[4];
	bool byr, iyr, eyr, hgt, hcl, ecl, pid, cid;

	field[3] = '\0';
	byr = iyr = eyr = hgt = hcl = ecl = pid = cid = false;

	for (bool stop = false; !stop; ) {
		read_field(fp, field);

		switch (field_idx(fields, field)) {
			case 1:
				byr = true;
				if (!read_byr(fp) || !is_whitespace(fgetc(fp))) {
					skip_passport(fp);
					return false;
				}
				break;

			case 2:
				iyr = true;
				if (!read_iyr(fp) || !is_whitespace(fgetc(fp))) {
					skip_passport(fp);
					return false;
				}
				break;

			case 3:
				eyr = true;
				if (!read_eyr(fp) || !is_whitespace(fgetc(fp))) {
					skip_passport(fp);
					return false;
				}
				break;

			case 4:
				hgt = true;
				if (!read_hgt(fp) || !is_whitespace(fgetc(fp))) {
					skip_passport(fp);
					return false;
				}
				break;

			case 5:
				hcl = true;
				if (!read_hcl(fp) || !is_whitespace(fgetc(fp))) {
					skip_passport(fp);
					return false;
				}
				break;

			case 6:
				ecl = true;
				if (!read_ecl(fp) || !is_whitespace(fgetc(fp))) {
					skip_passport(fp);
					return false;
				}
				break;

			case 7:
				if (!read_pid(fp) || !is_whitespace(fgetc(fp))) {
					skip_passport(fp);
					return false;
				}
				pid = true;
				break;

			case 8:
				cid = true;
				while (!is_whitespace(fgetc(fp)));
				break;

			default: return false;
		}

		int token = fgetc(fp);
		if (token == '\n') { stop = true; continue; }
		if (token == EOF) { stop = eof_found = true; continue; }

		ungetc(token, fp);
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
