def is_valid(nums, value):
	for i in range(25):
		num1 = nums[i]
		num2 = value - num1

		if num2 != num1:
			for j in range(25):
				if nums[j] == num2:
					return True

	return False


input_file = open("input.txt", "r")
lines = input_file.readlines()
input_file.close()


nums = []

# Set up the preamble
for idx in range(25):
	nums.append(int(lines[idx]))

# Find the invalid number
for line in lines[25:]:
	val = int(line)

	if not is_valid(nums, val):
		print(val)
		break

	nums = nums[1:]
	nums.append(val)
