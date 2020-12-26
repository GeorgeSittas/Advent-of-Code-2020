from math import inf

def terminates(stop, curr, instructions, changed, acc):
	if stop == curr:
		return acc

	op, val, already_executed = instructions[curr]

	if already_executed:
		return -inf

	instructions[curr] = (op, val, True)
	v = int(val)

	if op == 'acc':
		res = terminates(stop, curr+1, instructions, changed, acc + v)
	elif not changed:
		next_ind1 = curr + (v + (1-v) * (op == 'jmp'))
		next_ind2 = curr + (1 - (1-v) * (op == 'jmp'))

		# We either change the current instruction or not
		res = max(terminates(stop, next_ind1, instructions, True,  acc), \
		          terminates(stop, next_ind2, instructions, False, acc))
	else:
		res = terminates(stop, curr + (1 + (v-1) * (op == 'jmp')), \
			               instructions, changed, acc)

	instructions[curr] = (op, val, False)
	return res

import re

input_file = open("input.txt", "r")
lines = input_file.readlines()
input_file.close()

delimiters = " ", "\n"
re_pattern = '|'.join(map(re.escape, delimiters))

instructions = {}

for idx, line in enumerate(lines):
	tokens = list(filter(('').__ne__, re.split(re_pattern, line)))
	instructions[idx] = tuple(tokens + [False])

n_instructions = len(lines)

print(terminates(n_instructions, 0, instructions, False, 0))
