

def plug_adapters(n_adapters, curr, adapters, diff_1, diff_3):
	if n_adapters == 0:
		return diff_1, diff_3

	possible = [x for x in adapters if x - curr <= 3]

	if possible == []:
		return None

	for adapter in possible:
		rest_adapters = [x for x in adapters if x != adapter]
		upd_diff_1 = diff_1 + (adapter - curr == 1)
		upd_diff_3 = diff_3 + (adapter - curr == 3)

		res = plug_adapters(n_adapters-1, adapter, rest_adapters, \
			                                upd_diff_1, upd_diff_3)
		if res is not None:
			return res



input_file = open("input.txt", "r")
lines = input_file.readlines()
input_file.close()

adapters = sorted([int(line) for line in lines])

diff_1, diff_2 = plug_adapters(len(adapters), 0, adapters, 0, 0)
print(diff_1 * (diff_2+1))

