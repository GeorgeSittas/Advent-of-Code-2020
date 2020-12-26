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
instruction_index = 0
accumulator = 0

while instruction_index != n_instructions:
	op, val, already_executed = instructions[instruction_index]

	if already_executed:
		break

	instructions[instruction_index] = (op, val, True)
	val = int(val)

	if op == 'jmp':
		instruction_index += val
	else:
		instruction_index += 1
		if op == 'acc':
			accumulator += val

print(accumulator)
