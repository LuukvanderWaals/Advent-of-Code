file = open("Day3.txt", "r").read().split()

bits = [0] * len(file[0])
for s in file:
    for i, bit in enumerate(s):
        bits[i] += int(bit)

gamma = int("".join(map(lambda x: "1" if x > len(file) / 2 else "0", bits)), 2)
epsilon = 2 ** len(bits) - 1 - gamma

print(gamma * epsilon)

strings = file
i = 0
while len(strings) > 1:
    strings = [string for string in strings if (sum(int(bits[i]) for bits in strings) >= len(strings) / 2) == (string[i] == "1")]
    i += 1

oxygen = strings[0]

strings = file
i = 0
while len(strings) > 1:
    strings = [string for string in strings if (sum(int(bits[i]) for bits in strings) < len(strings) / 2) == (string[i] == "1")]
    i += 1

co2 = strings[0]

print(int(oxygen, 2) * int(co2, 2))
