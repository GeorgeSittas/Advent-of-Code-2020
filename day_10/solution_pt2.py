def plug_adapters(n_adapters, curr, adapters, cache):
	if n_adapters == 0:
		return 1

	possible = [x for x in adapters if x - curr <= 3]

	if possible == []:
		return 0

	count = 0
	for adapter in possible:
		rest_adapters = [x for x in adapters if x != adapter]

		if adapter not in cache:
			cache[adapter] = plug_adapters(n_adapters-1, adapter, rest_adapters, cache)

		count += cache[adapter]

	return count

input_file = open("input.txt", "r")
lines = input_file.readlines()
input_file.close()

adapters = sorted([int(line) for line in lines])

cache = {}
count = plug_adapters(len(adapters), 0, adapters, cache)
print(count)

