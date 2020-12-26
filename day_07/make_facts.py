import re

input_file = open("input.txt", "r")
rules = input_file.readlines()
input_file.close()

delimiters = ",", ".", " ", "\n"
re_pattern = '|'.join(map(re.escape, delimiters))

contains = {}

for rule in rules:
	tokens = list(filter(('').__ne__, re.split(re_pattern, rule)))
	current_entry = tokens[0] + tokens[1] # e.g. 'darkorange'

	if len(tokens) == 7:
		contains[current_entry] = None
		continue

	n_bag_types = int(len(tokens)/4 - 1)
	bags = []

	for i in range(n_bag_types):
		curr_idx = 4 * (i + 1)
		bags.append((tokens[curr_idx], tokens[curr_idx+1] + tokens[curr_idx+2]))

	contains[current_entry] = tuple(bags)


facts_file = open("facts.pl", "w")

for key, value in contains.items():
	facts_file.write("contains(" + key + ", [")

	if value is None:
		facts_file.write("]).\n")
		continue

	bags = list(value)
	for v in bags[:-1]:
		n_bags = v[0]
		b_type = v[1]

		facts_file.write("(" + n_bags + ", " + b_type + "), ")

	facts_file.write("(" + bags[-1][0] + ", " + bags[-1][1] + ")]).\n")

facts_file.close()
