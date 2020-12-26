# Retarded O(n^2) solution, but oh well, the input is 10^3 numbers ...
# Probably could be done in O(nlogn) using divide and conquer approach

input_file = open("input.txt", "r")
lines = input_file.readlines()
input_file.close()

invalid_num = 248131121 # As found in solution_pt1.py

nums = [int(line) for line in lines]
n_nums = len(nums)

for i in range(n_nums):
	for j in range(n_nums):
		target_nums = nums[i:j]
		res_sum = sum(target_nums)

		if res_sum > invalid_num:
			break
		if res_sum == invalid_num:
			print(min(target_nums) + max(target_nums))
			quit()
